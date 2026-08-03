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

#ifndef USART_DEBUG_BOARD_H
#define USART_DEBUG_BOARD_H

// 0 - use putch
// 1 - use prinf
#define PRINTF_OR_PUTCH_USE 0

#if !PRINTF_OR_PUTCH_USE
// Макрос для вывода строки
#define PUTSTR(s) do {                          \
    const char *_p = (s);                       \
    while (*_p) putch(*_p++);                   \
} while(0)

// Макрос для вывода беззнакового числа (0..65535)
#define PUTNUM(n) do {                          \
    unsigned int _num = (n);                    \
    char _buf[6];                               \
    unsigned char _i = 0;                       \
    if (_num == 0) {                            \
        putch('0');                             \
    } else {                                    \
        while (_num > 0) {                      \
            _buf[_i++] = (_num % 10) + '0';     \
            _num /= 10;                         \
        }                                       \
        while (_i > 0) putch(_buf[--_i]);       \
    }                                           \
} while(0)

// Макрос для вывода знакового числа – безопасно вычисляет модуль
#define PUTNUM_SIGNED(n) do {                   \
    signed int _val = (n);                      \
    if (_val < 0) {                             \
        putch('-');                             \
        /* Безопасное вычисление |_val| без переполнения */ \
        unsigned int _abs = (unsigned int)(-(_val + 1)) + 1; \
        /* Вывод _abs как беззнакового */       \
        unsigned int _num = _abs;               \
        char _buf[6];                           \
        unsigned char _i = 0;                   \
        if (_num == 0) {                        \
            putch('0');                         \
        } else {                                \
            while (_num > 0) {                  \
                _buf[_i++] = (_num % 10) + '0'; \
                _num /= 10;                     \
            }                                   \
            while (_i > 0) putch(_buf[--_i]);   \
        }                                       \
    } else {                                    \
        /* Положительное число */               \
        unsigned int _num = (unsigned int)_val; \
        char _buf[6];                           \
        unsigned char _i = 0;                   \
        if (_num == 0) {                        \
            putch('0');                         \
        } else {                                \
            while (_num > 0) {                  \
                _buf[_i++] = (_num % 10) + '0'; \
                _num /= 10;                     \
            }                                   \
            while (_i > 0) putch(_buf[--_i]);   \
        }                                       \
    }                                           \
} while(0)
#endif

void debug_print_usart(unsigned int freq);

#endif  /* USART_DEBUG_BOARD_H */
