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

#ifndef KEY_MANAGER_H
#define KEY_MANAGER_H

//Установить бит № bitno в переменной var.
#define BITSET(var,bitno) ((var) |= 1 << (bitno))
//Сбросить бит № bitno в переменной var.
#define BITCLR(var,bitno) ((var) &= ~(1 << (bitno)))
//Проверить бит № bitno в переменной var (TRUE=1)
#define BITTST1(var,bitno) ((var) & (1 << (bitno)))
//Проверить бит № bitno в переменной var (TRUE=0)
#define BITTST0(var,bitno) (!((var) & (1 << (bitno))))
//Инвертировать бит № bitno в переменной var.
#define BITINV(var,bitno) var=(var^(1 << (bitno)))

// Конфигурация пинов кнопок
#define BUTTON1   PORTCbits.RC5

// Битмаска флагов
#define BUTTON1_PRESSED    0x0
#define BUTTON1_LONG_PRESS 0x1

// Флаги состояний кнопок
extern volatile unsigned char button_flags;

// Конфигурация таймингов (в миллисекундах)
#define DEBOUNCE_TIME      20
#define LONG_PRESS_TIME    255

// Прототипы функций
void buttons_process(void);

#endif  /* KEY_MANAGER_H */
