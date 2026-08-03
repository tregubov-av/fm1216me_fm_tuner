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

#ifndef KEYPAD_H
#define KEYPAD_H
// ==================== НАСТРОЙКИ ПОДКЛЮЧЕНИЯ ====================
// Можно изменить под свою распиновку

#define KEYPAD_PORT         PORTB       // Порт клавиатуры
#define KEYPAD_TRIS         TRISB       // Регистр направления

// Маска строк (какие биты используются как входы)
#define KEYPAD_ROW_MASK     0xF0        // RB4..RB7 - строки
#define KEYPAD_ROW_SHIFT    4           // Сдвиг для приведения к 0..3

// Маска столбцов (какие биты используются как выходы)
#define KEYPAD_COL_MASK     0x0F        // RB0..RB3 - столбцы

// Количество строк и столбцов
#define KEYPAD_ROWS         4
#define KEYPAD_COLS         4

// ==================== НАСТРОЙКИ АНТИДРЕБЕЗГА ====================
#define KEYPAD_DEBOUNCE_MS  20          // Время антидребезга (мс)

// ==================== КОНСТАНТЫ ВРЕМЕНИ ====================
// Важно: все значения должны помещаться в unsigned char (0-255)
#define DEBOUNCE_TICKS    2     // 20 мс / 10 мс = 2 тика
#define REPEAT_DELAY_TICKS 50   // 500 мс / 10 мс = 50 тиков
#define REPEAT_RATE_TICKS  10   // 100 мс / 10 мс = 10 тиков

// ==================== ТИПЫ ДАННЫХ ====================
// Тип события клавиатуры
typedef enum {
    KEY_EVENT_NONE = 0,      // Нет события
    KEY_EVENT_PRESS,         // Клавиша нажата
    KEY_EVENT_RELEASE,       // Клавиша отпущена
    KEY_EVENT_HOLD,          // Клавиша удерживается
    KEY_EVENT_REPEAT         // Автоповтор
} key_event_t;

// Структура события клавиатуры
typedef struct {
    unsigned char key;       // Символ клавиши (0 если нет)
    key_event_t event;       // Тип события
    unsigned long hold_time; // Время удержания в мс (только для HOLD)
} keypad_event_t;

keypad_event_t event;

// ==================== ПРОТОТИПЫ ФУНКЦИЙ ====================

// Управление функциями
// 1 - Enable
// 0 - Disable
#define KEYPAD_SET_KEYMAP      0
#define KEYPAD_IS_PRESSED      0
#define KEYPAD_GET_KEY         0
#define KEYPAD_GET_KEY_TIMEOUT 0
#define KEYPAD_GET_RAW         0

// Инициализация клавиатуры.
// Настраивает порты и включает подтягивающие резисторы.
void keypad_init(void);

// Установка пользовательской таблицы символов.
// @param map Указатель на массив 4x4 с символами клавиш.
#if KEYPAD_SET_KEYMAP
void keypad_set_keymap(const unsigned char map[KEYPAD_ROWS][KEYPAD_COLS]);
#endif

// Низкоуровневое сканирование клавиатуры.
// @return Символ нажатой клавиши или 0, если ничего не нажато.
unsigned char keypad_scan(void);

// Проверка, нажата ли какая-либо клавиша.
// @return 1 если есть нажатие, 0 если нет.
#if KEYPAD_IS_PRESSED
unsigned char keypad_is_pressed(void);
#endif

// Получение символа нажатой клавиши с блокировкой.
// Функция ждёт, пока пользователь не нажмёт и не отпустит клавишу.
// @return Символ нажатой клавиши.
#if KEYPAD_GET_KEY
unsigned char keypad_get_key(void);
#endif

// Получение символа нажатой клавиши с блокировкой и таймаутом.
// @param timeout_ms Таймаут ожидания в миллисекундах.
// @return Символ нажатой клавиши или 0 при таймауте.
#if KEYPAD_GET_KEY_TIMEOUT
unsigned char keypad_get_key_timeout(unsigned int timeout_ms);
#endif

// Получение сырого кода клавиши (номер строки и столбца).
// @param row Указатель для возврата номера строки (0..3).
// @param col Указатель для возврата номера столбца (0..3).
// @return 1 если клавиша нажата, 0 если нет.
#if KEYPAD_GET_RAW
unsigned char keypad_get_raw(char *row, char *col);
#endif

// Обработчик состояния клавиатуры для вызова в основном цикле.
// Формирует события нажатия, отпускания и удержания.
// @param event Указатель на структуру для возврата события.
void keypad_process(keypad_event_t *event);

// Сброс состояния клавиатуры.
// Полезно после длительных операций, чтобы избежать ложных срабатываний.
void keypad_reset(void);

#endif // KEYPAD_H