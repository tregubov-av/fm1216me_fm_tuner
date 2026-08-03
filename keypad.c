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
#include <string.h>     // для memset
#include "keypad.h"
#include "setup_pic16f876a.h"

// Таблица символов
static const unsigned char default_keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Указатель на текущую таблицу символов
static const unsigned char (*keymap)[KEYPAD_COLS] = default_keymap;

// Состояния для обработчика событий
static unsigned char last_key = 0;          // Предыдущая нажатая клавиша
static unsigned char hold_counter = 0;       // Счётчик времени удержания  
static unsigned char repeat_counter = 0;     // Счётчик автоповтора

// Переменные антидребезга
static unsigned char debounce_counter = 0; // Счётчик антидребезга
static unsigned char stable_state = 0;     // Стабильное состояние после дребезга
static unsigned char prev_stable_state = 0; // Предыдущее стабильное состояние


// Инициализация клавиатуры
void keypad_init(void) {
    // Настройка направления: строки - входы, столбцы - выходы
    KEYPAD_TRIS |= KEYPAD_ROW_MASK;      // Строки как входы
    KEYPAD_TRIS &= ~KEYPAD_COL_MASK;     // Столбцы как выходы
    // Включение подтягивающих резисторов на PORTB
    OPTION_REGbits.nRBPU = 0;             // 0 = pull-ups включены
    // Установка высокого уровня на всех столбцах
    KEYPAD_PORT |= KEYPAD_COL_MASK;
    // Сброс состояния
    keypad_reset();
}

// Установка пользовательской таблицы символов
#if KEYPAD_SET_KEYMAP
void keypad_set_keymap(const unsigned char map[KEYPAD_ROWS][KEYPAD_COLS]) {
    if (map != NULL) {
        keymap = map;
    }
}
#endif

// Низкоуровневое сканирование клавиатуры
unsigned char keypad_scan(void) {
    unsigned char col, row;
    for (col = 0; col < KEYPAD_COLS; col++) {
        // Формируем маску для текущего столбца
        // Все столбцы в 1, кроме текущего (в 0)
        unsigned char col_mask = (unsigned char)(~(1 << col));
        // Сохраняем состояние строк и применяем маску столбцов
        KEYPAD_PORT = (unsigned char)((KEYPAD_PORT & KEYPAD_ROW_MASK) | (col_mask & KEYPAD_COL_MASK));
        // Небольшая задержка для установки уровней
        NOP();
        // Читаем состояние строк
        unsigned char rows_val = (unsigned char)(KEYPAD_PORT & KEYPAD_ROW_MASK);
        // Проверяем каждую строку
        for (row = 0; row < KEYPAD_ROWS; row++) {
            if (!(rows_val & (1 << (KEYPAD_ROW_SHIFT + row)))) {
                // Восстанавливаем все столбцы в 1 перед выходом
                KEYPAD_PORT |= KEYPAD_COL_MASK;
                return keymap[row][col];
            }
        }
    }
    // Восстанавливаем все столбцы в 1
    KEYPAD_PORT |= KEYPAD_COL_MASK;
    // Ничего не нажато
    return 0;
}

// Проверка, нажата ли какая-либо клавиша
#if KEYPAD_IS_PRESSED
unsigned char keypad_is_pressed(void) {
    unsigned char pressed;
    // Сохраняем текущее состояние порта
    unsigned char saved_port = KEYPAD_PORT;
    pressed = (keypad_scan() != 0);
    // Восстанавливаем порт
    KEYPAD_PORT = saved_port;
    return pressed;
}
#endif

// Получение символа нажатой клавиши с блокировкой
#if KEYPAD_GET_KEY
unsigned char keypad_get_key(void) {
    unsigned char key;
    // Ждём нажатия
    while ((key = keypad_scan()) == 0) {
        __delay_ms(10);
    }
    // Ждём отпускания
    while (keypad_scan() != 0) {
        __delay_ms(10);
    }
    __delay_ms(KEYPAD_DEBOUNCE_MS);
    return key;
}
#endif

// Получение символа нажатой клавиши с таймаутом
#if KEYPAD_GET_KEY_TIMEOUT
unsigned char keypad_get_key_timeout(unsigned int timeout_ms) {
    unsigned char key;
    unsigned int elapsed = 0;
    // Ждём нажатия с таймаутом
    while ((key = keypad_scan()) == 0) {
        __delay_ms(10);
        elapsed += 10;
        if (elapsed >= timeout_ms) {
            return 0;
        }
    }
    // Ждём отпускания
    while (keypad_scan() != 0) {
        __delay_ms(10);
    }
    __delay_ms(KEYPAD_DEBOUNCE_MS);
    return key;
}
#endif

// Получение сырого кода клавиши
#if KEYPAD_GET_RAW
unsigned char keypad_get_raw(unsigned char *row, unsigned char *col) {
    unsigned char r, c;
    for (c = 0; c < KEYPAD_COLS; c++) {
        unsigned char col_mask = ~(1 << c);
        KEYPAD_PORT = (KEYPAD_PORT & KEYPAD_ROW_MASK) | (col_mask & KEYPAD_COL_MASK);
        __delay_us(10);
        unsigned char rows_val = KEYPAD_PORT & KEYPAD_ROW_MASK;
        for (r = 0; r < KEYPAD_ROWS; r++) {
            if (!(rows_val & (1 << (KEYPAD_ROW_SHIFT + r)))) {
                KEYPAD_PORT |= KEYPAD_COL_MASK;
                if (row) *row = r;
                if (col) *col = c;
                return 1;
            }
        }
    }
    KEYPAD_PORT |= KEYPAD_COL_MASK;
    return 0;
}
#endif

// Обработчик состояния клавиатуры
void keypad_process(keypad_event_t *event) {
    unsigned char raw_state;
    unsigned char key;
    
    if (event == NULL) {
        return;
    }
    
    // Инициализация события
    event->key = 0;
    event->event = KEY_EVENT_NONE;
    event->hold_time = 0;
    
    // Сканируем клавиатуру
    key = keypad_scan();
    raw_state = (unsigned char)((key != 0) ? 1 : 0);
    
    // ===========================================
    // АНТИДРЕБЕЗГ
    // ===========================================
    if (raw_state == stable_state) {
        if (debounce_counter < DEBOUNCE_TICKS) {
            debounce_counter++;
        }
    } else {
        debounce_counter = 0;
        stable_state = raw_state;
        return;
    }
    
    if (debounce_counter < DEBOUNCE_TICKS) {
        return;
    }
    
    // ===========================================
    // ОБРАБОТКА ФРОНТОВ
    // ===========================================
    
    // Нажатие (переход 0 -> 1)
    if (stable_state == 1 && prev_stable_state == 0) {
        event->key = key;
        event->event = KEY_EVENT_PRESS;
        hold_counter = 0;
        repeat_counter = REPEAT_DELAY_TICKS;
        last_key = key;
        prev_stable_state = 1;
        return;
    }
    
    // Отпускание (переход 1 -> 0)
    if (stable_state == 0 && prev_stable_state == 1) {
        event->key = last_key;
        event->event = KEY_EVENT_RELEASE;
        hold_counter = 0;
        repeat_counter = 0;
        prev_stable_state = 0;
        return;
    }
    
    // ===========================================
    // УДЕРЖАНИЕ И ПОВТОРЫ
    // ===========================================
    if (stable_state == 1) {
        hold_counter++;
        
        // Проверяем, не переполнился ли счётчик
        if (hold_counter == 255) {
            hold_counter = REPEAT_DELAY_TICKS;  // Защита от переполнения
        }
        
        if (hold_counter >= REPEAT_DELAY_TICKS) {
            if (repeat_counter == 0) {
                // Автоповтор
                event->key = key;
                event->event = KEY_EVENT_REPEAT;
                event->hold_time = (unsigned int)hold_counter * 10;
                repeat_counter = REPEAT_RATE_TICKS;
            } else {
                // Удержание между повторами
                event->key = key;
                event->event = KEY_EVENT_HOLD;
                event->hold_time = (unsigned int)hold_counter * 10;
                repeat_counter--;
            }
        }
    }
}

// Сброс состояния клавиатуры
void keypad_reset(void) {
    stable_state = 0;
    prev_stable_state = 0;
    last_key = 0;
    debounce_counter = 0;
    hold_counter = 0;
    repeat_counter = 0;
    // Устанавливаем все столбцы в 1
    KEYPAD_PORT |= KEYPAD_COL_MASK;
}
