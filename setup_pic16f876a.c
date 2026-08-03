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
#include "setup_pic16f876a.h"

void setup_pic(void) {
    /*CMCON*/ // отключение компараторов
    CMCON = 0x07; // Режим работы компараторов
    /*CCPxCON*/
    CCP1CON = 0x0;            //Отключение модуля CCP1.
    CCP2CON = 0x0;            //Отключение модуля CCP2.
    /*ADCON0*/
    ADCON1 = 0x06;          //Отключение модуля ADC
    /*TRISX*/
    TRISA = 0b00000000; // направление работы ножек порта А
    TRISB = 0b00000000; // направление работы ножек порта В
    TRISC = 0b10111111; // направление работы ножек порта С
    /*PORTX*/
    PORTA = 0; // очищаем порт А
    PORTB = 0; // очищаем порт Б
    PORTC = 0; // очищаем порт С
    /*OPTION*/
    OPTION_REG = 0b01000010;
    /*INTCON*/
    INTCON = 0b01000000; // PEIE = 1
    /*PIE1*/
    PIE1 = 0b00000001; // TMR1IE = 1
    /*RCSTA*/  // Управление модулем USART
    //RCSTAbits.SPEN = 0;  // USART выкл
    /*T1CON*/
    // Расчет для 1 мс при 20 МГц и предделителе 1:4
    // Частота с предделителем = 5 МГц / 4 = 1.25 МГц
    // Период = 0.8 мкс
    // Для 1 мс нужно: 1000 мкс / 0.8 мкс = 1250 тиков
    T1CON = 0b00100001;
    // Начальное значение для 1 мс
    // TMR1 = 65536 - 1250 = 64286 (0xFB1E)
    TMR1 = 64286;
}
