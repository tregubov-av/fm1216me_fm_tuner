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

#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

// Порты энкодера: определяют, к каким выводам микроконтроллера подключены
// сигналы A и B энкодера.
#define ENCODER_A_PORT  PORTCbits.RC0
#define ENCODER_B_PORT  PORTCbits.RC1
#define ENCODER_A_TRIS  TRISCbits.TRISC0
#define ENCODER_B_TRIS  TRISCbits.TRISC1

// Количество "шагов" (переходов) на один механический щелчок (detent).
// Может быть 2 или 4 в зависимости от используемого энкодера
#define STEPS_PER_DETENT 2

// Типы и состояния (Направление вращения)
typedef enum {
    ENCODER_LEFT = 0,
    ENCODER_RIGHT,
    ENCODER_STOP
} encoder_direction_t;

// Глобальные переменные
extern volatile signed int encoder_raw_counter;
extern volatile encoder_direction_t encoder_event_flag;

// Функция инициализации энкодера
void encoder_init(void);
// Функция обработки энкодера. Предполагается, что она вызывается
// периодически (например, из основного цикла или таймерного прерывания).
void encoder_manager(void);

// Дополнительные функции
// Управление функциями
// 1 - Enable
// 0 - Disable
#define ENCODER_GET_EVENT   0
#define ENCODER_CLEAR_EVENT 0
#define ENCODER_GET_COUNTER 0

#if ENCODER_GET_EVENT
encoder_direction_t encoder_get_event(void);
#endif

#if ENCODER_CLEAR_EVENT
void encoder_clear_event(void);
#endif

#if ENCODER_GET_COUNTER
signed int encoder_get_counter(void);
#endif

#endif /* ENCODER_MANAGER_H */
