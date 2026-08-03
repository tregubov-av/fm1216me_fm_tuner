// MIT License
//
// Copyright (c) 2025 Andrey Tregubov
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <xc.h>
#include <string.h>
#include "main.h"
#include "setup_pic16f876a.h"
#include "usart.h"
#include "usart_debug_board.h"
#include "fm1216me.h"
#include "encoder_manager.h"
#include "key_manager.h"
#include "i2c_master.h"
#include "hd44780_pcf8574t.h"
#include "keypad.h"

// Состояния автомата сканирования
#define SCAN_STATE_IDLE   0
#define SCAN_STATE_TUNE   1   // настройка тюнера на новую частоту
#define SCAN_STATE_WAIT   2   // ожидание 50 мс после настройки
#define SCAN_STATE_CHECK  3   // чтение статуса и проверка сигнала

// Переменные для неблокирующего сканирования
volatile unsigned long system_ms = 0;          // счётчик миллисекунд (обновляется в прерывании)
static unsigned long scan_timeout = 0;         // время для неблокирующей задержки
unsigned char scan_active = 0;                 // 1 – сканирование активно
static signed char scan_direction = 1;         // 1 – вверх, -1 – вниз
static unsigned int scan_freq = 0;             // текущая частота в процессе сканирования
static unsigned char scan_state = 0;           // состояние конечного автомата

// Записать в eeprom частоту на которую настроен тюнер
__eeprom unsigned int current_freq_eeprom;

// Переменные для ввода частоты с клавиатуры
static unsigned char input_mode = 0;          // 0 – ожидание, 1 – ввод
static char input_buffer[6] = {0};            // буфер для 5 цифр + '\0'
static unsigned char input_len = 0;           // текущая длина строки

// Переменные для работы с LCD
static char lcd_buffer[8] = {0};

// Отладка: перечитать статус и вывести в USART
void read_status_send_usart(void){
    fm1216me_read_status(&fm1216me_status);
    debug_print_usart(current_freq_eeprom);
}

// Вывод частоты на LCD

void lcd_showfrequency(unsigned int freq, char *buffer) {
    // Для 5-значных чисел (12345 -> 123.45)
    if (freq >= 10000) {
        buffer[0] = (freq / 10000) % 10 + '0';
        buffer[1] = (freq / 1000) % 10 + '0';
        buffer[2] = (freq / 100) % 10 + '0';
        buffer[3] = '.';
        buffer[4] = (freq / 10) % 10 + '0';
        buffer[5] = freq % 10 + '0';
        buffer[6] = '\0';
    }
    // Для 4-значных чисел (1234 -> 12.34)
    else if (freq >= 1000) {
        buffer[0] = (freq / 1000) % 10 + '0';
        buffer[1] = (freq / 100) % 10 + '0';
        buffer[2] = '.';
        buffer[3] = (freq / 10) % 10 + '0';
        buffer[4] = freq % 10 + '0';
        buffer[5] = '\0';
    }
    // Для 3-значных чисел (123 -> 1.23)
    else if (freq >= 100) {
        buffer[0] = (freq / 100) % 10 + '0';
        buffer[1] = '.';
        buffer[2] = (freq / 10) % 10 + '0';
        buffer[3] = freq % 10 + '0';
        buffer[4] = '\0';
    }
    // Для 2-значных чисел (12 -> 0.12)
    else if (freq >= 10) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = (freq / 10) % 10 + '0';
        buffer[3] = freq % 10 + '0';
        buffer[4] = '\0';
    }
    // Для 1-значных чисел (1 -> 0.01)
    else {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = freq % 10 + '0';
        buffer[4] = '\0';
    }
}

// Вывести на LCD дисплей
void lcd_show(void) {
    lcd_clear();
    lcd_setcursor(0, 4);
    lcd_sendstring("FM TUNER");
    lcd_setcursor(1, 3);
    lcd_showfrequency(current_freq_eeprom, lcd_buffer);
    lcd_sendstring(lcd_buffer);
    lcd_sendstring(" MHz");
}



// Запуск сканирования частот
// Вызывается в основном цикле, пока scan_active == 1.
// Реализует конечный автомат: настройка -> задержка -> проверка сигнала.
void fm_scan_step(void) {
    if (!scan_active) return;

    switch (scan_state) {
        case SCAN_STATE_TUNE:
            // Настроить тюнер на текущую сканируемую частоту в режиме MONO (без mute)
            fm1216me_tune_fm(scan_freq, 0, 0);
            // Показать текущую частоту на LCD
            lcd_clear();
            lcd_setcursor(0, 4);
            lcd_sendstring("SCANNING");
            lcd_setcursor(1, 3);
            lcd_showfrequency(scan_freq, lcd_buffer);
            lcd_sendstring(lcd_buffer);
            lcd_sendstring(" MHz");

            scan_state = SCAN_STATE_WAIT;
            scan_timeout = system_ms + 50;   // ждать 50 мс
            break;

        case SCAN_STATE_WAIT:
            // Неблокирующая задержка
            if (system_ms >= scan_timeout) {
                scan_state = SCAN_STATE_CHECK;
            }
            break;
        case SCAN_STATE_CHECK:
            // Чтение статуса тюнера
            fm1216me_read_status(&fm1216me_status);
            if (fm1216me_status.pll_lock && fm1216me_status.signal_fm) {
                // Сигнал найден – фиксируем частоту, переключаем в стерео
                // TODO точная подстройка по AFC
                current_freq_eeprom = scan_freq;
                fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                scan_active = 0;
                // Показать текущую частоту на LCD
                lcd_show();
                // Отладка
                read_status_send_usart();
                return;
            } else {
                // Переход к следующей частоте с учётом направления
                scan_freq += scan_direction * FM_FREQ_TUNING_STEP;
                // Проверка границ диапазона – при выходе останавливаемся на граничной частоте
                if (scan_freq > FM_FREQ_LIMIT_H) {
                    scan_active = 0;
                    current_freq_eeprom = FM_FREQ_LIMIT_H;
                    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                    // Показать текущую частоту на LCD
                    lcd_show();
                    // Отладка
                    read_status_send_usart();
                    return;
                } else if (scan_freq < FM_FREQ_LIMIT_L) {
                    scan_active = 0;
                    current_freq_eeprom = FM_FREQ_LIMIT_L;
                    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                    // Показать текущую частоту на LCD
                    lcd_show();
                    // Отладка
                    read_status_send_usart();
                    return;
                }
                scan_state = SCAN_STATE_TUNE;   // перейти к настройке следующей частоты
            }
            break;
    }
}

// Обработка ввода с клавиатуры
void process_keypad_input(void) {
    unsigned char key = event.key;

    if (input_mode == 0) {
        if (key >= '0' && key <= '9') {
            input_mode = 1;
            input_len = 0;
            memset(input_buffer, 0, sizeof(input_buffer));
            input_buffer[input_len++] = key;
            input_buffer[input_len] = '\0';
            // Показать текущую частоту на LCD
            lcd_clear();
            lcd_setcursor(0, 0);
            lcd_sendstring("Enter Freq:");
            lcd_setcursor(1, 0);
            lcd_sendstring("                ");
            lcd_setcursor(1, 3);
            lcd_sendstring(input_buffer);
            lcd_sendstring(" MHz");
        }
    } else {
        if (key >= '0' && key <= '9') {
            if (input_len < 5) {
                input_buffer[input_len++] = key;
                input_buffer[input_len] = '\0';
                // Показать текущую частоту на LCD
                lcd_setcursor(1, 3);
                lcd_sendstring(input_buffer);
                lcd_sendstring(" MHz");

                if (input_len == 5) {
                    unsigned int freq_units = 0;
                    char *p = input_buffer;
                    while (*p) {
                        if (*p >= '0' && *p <= '9') {
                            freq_units = freq_units * 10 + (*p - '0');
                        }
                        p++;
                    }
                    unsigned int new_freq = (freq_units + FM_FREQ_TUNING_STEP / 2)
                                            / FM_FREQ_TUNING_STEP * FM_FREQ_TUNING_STEP;
                    if (new_freq < FM_FREQ_LIMIT_L) new_freq = FM_FREQ_LIMIT_L;
                    if (new_freq > FM_FREQ_LIMIT_H) new_freq = FM_FREQ_LIMIT_H;

                    current_freq_eeprom = new_freq;
                    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                    // Показать текущую частоту на LCD
                    lcd_show();
                    // Отладка
                    read_status_send_usart();

                    input_mode = 0;
                    memset(input_buffer, 0, sizeof(input_buffer));
                    input_len = 0;
                }
            }
        } else if (key == '*') {
            // Отмена ввода
            input_mode = 0;
            memset(input_buffer, 0, sizeof(input_buffer));
            input_len = 0;
            // Показать текущую частоту на LCD
            lcd_show();
        } else if (key == '#') {
            // Завершение ввода по '#' (если введено меньше 5 цифр)
            if (input_len == 0) {
                input_mode = 0;
                // Показать текущую частоту на LCD
                lcd_show();
            } else {
                unsigned int freq_units = 0;
                char *p = input_buffer;
                while (*p) {
                    if (*p >= '0' && *p <= '9') {
                        freq_units = freq_units * 10 + (*p - '0');
                    }
                    p++;
                }
                unsigned int new_freq = (freq_units + FM_FREQ_TUNING_STEP / 2)
                                        / FM_FREQ_TUNING_STEP * FM_FREQ_TUNING_STEP;
                if (new_freq >= FM_FREQ_LIMIT_L && new_freq <= FM_FREQ_LIMIT_H) {
                    current_freq_eeprom = new_freq;
                    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                    // Отладка
                    read_status_send_usart();
                }
                input_mode = 0;
                memset(input_buffer, 0, sizeof(input_buffer));
                input_len = 0;
                // Показать текущую частоту на LCD
                lcd_show();
            }
        }
    }
}

void main(void) {
    // Конфигурирование регистров специального назначения.
    setup_pic();
    // Инициализация USART
    init_usart();
    // Инициализация I2C
    i2c_master_init();
    // Инициализация энкодера
    encoder_init();
    // Инициализация дисплея
    lcd_init();
    // Инициализация тюнера
    fm1216me_init();
    // Инициализация клавиатуры
    keypad_init();

    // Если частота из EEPROM не попадает в заданный интервал,
    // установить частоту по умолчанию
    if (current_freq_eeprom > FM_FREQ_LIMIT_H || current_freq_eeprom < FM_FREQ_LIMIT_L) {
        current_freq_eeprom = FM_DEFAULT_FREQ;
    }
    // Настроить тюнер на частоту из EEPROM
    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
    // Вывести частоту на LCD дисплей
    lcd_show();
    // Отладка
    read_status_send_usart();
    // Разрешить прерывания
    ei();
    // Вход в главный цикл
    while (1) {
        // Проверить события клавиатуры
        keypad_process(&event);
        if (event.event == KEY_EVENT_PRESS) {
            if (scan_active) {
                // Остановка сканирования по любой клавише.
                // Применяем текущую частоту сканирования, выключаем mute.
                scan_active = 0;
                current_freq_eeprom = scan_freq;
                fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
                // Показать текущую частоту на LCD
                lcd_show();
                // Отладка
                read_status_send_usart();
                // Саму клавишу игнорируем (не передаём в обработчик ввода)
            } else {
                // Если сканирование не активно – обрабатываем команды
                if (event.key == 'A') {
                    // Запуск сканирования вверх
                    if (input_mode == 0) {
                        scan_active = 1;
                        scan_direction = 1;
                        scan_freq = current_freq_eeprom + FM_FREQ_TUNING_STEP;
                        if (scan_freq > FM_FREQ_LIMIT_H) {
                            scan_freq = FM_FREQ_LIMIT_L;
                        }
                        scan_state = SCAN_STATE_TUNE;
                    }
                } else if (event.key == 'B') {
                    // Запуск сканирования вниз
                    if (input_mode == 0) {
                        scan_active = 1;
                        scan_direction = -1;
                        scan_freq = current_freq_eeprom - FM_FREQ_TUNING_STEP;
                        if (scan_freq < FM_FREQ_LIMIT_L) {
                            scan_freq = FM_FREQ_LIMIT_H;
                        }
                        scan_state = SCAN_STATE_TUNE;
                    }
                } else {
                    // Обычный ввод частоты (цифры, *, #)
                    process_keypad_input();
                }
            }
        }

        // Если сканирование активно – выполняем шаг автомата
        if (scan_active) {
            fm_scan_step();
        }

        // Проверить энкодер на факт вращения (только если не сканируем)
        if (!scan_active && encoder_event_flag <= 1) {
            // Вращение влево
            if (!encoder_event_flag) {
                if (current_freq_eeprom > FM_FREQ_LIMIT_L) {
                    current_freq_eeprom -= FM_FREQ_TUNING_STEP;
                } else {
                    current_freq_eeprom = FM_FREQ_LIMIT_L;
                }
            }
            // Вращение вправо
            if (encoder_event_flag == 1) {
                if (current_freq_eeprom < FM_FREQ_LIMIT_H) {
                    current_freq_eeprom += FM_FREQ_TUNING_STEP;
                } else {
                    current_freq_eeprom = FM_FREQ_LIMIT_H;
                }
            }
            // Настроить тюнер на частоту из EEPROM
            fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, 0);
            // Вывести частоту на LCD дисплей
            lcd_show();
            // Отладка
            read_status_send_usart();
        }

        // Отладка: перечитать статус и вывести в USART по кнопке BUTTON1
        if (BITTST1(button_flags, BUTTON1_PRESSED)) {
            BITCLR(button_flags, BUTTON1_PRESSED);
            read_status_send_usart();
        }
    }
}

// Обработчик прерываний
void __interrupt() isr(void) {
    // Проверка флага прерывания Timer1
    if (PIR1bits.TMR1IF) {
        // Сброс флага прерывания
        PIR1bits.TMR1IF = 0;
        // Перезагрузка таймера для следующего периода 1 мс
        // Для 1 мс при 20 МГц и предделителе 1:4
        TMR1 = 64286;
        // Обновляем системный счётчик миллисекунд (используется для неблокирующих задержек)
        system_ms++;
        // Обработка энкодера
        encoder_manager();
        // Обработка кнопок
        buttons_process();
    }
}
