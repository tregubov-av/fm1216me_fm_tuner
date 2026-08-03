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
#include "i2c_master.h"

void i2c_master_init(void) {
    TSCL = 1;            // Инициализировать SCL
    TSDA = 1;            // Инициализировать SDA
    SSPADD = SSPADD_GEN; // Установить частоту
    SSPSTAT = 0x80;      // Управление скоростью нарастания отключено для стандартного режима
    SSPCON = 0x28;       // Включите SSP и выбрать режим I2C Master.
}

void i2c_master_start(void) {
    I2C_MASTER_WAIT();
    SSPCON2bits.SEN = 1;     // Инициировать условие запуска
    while (SSPCON2bits.SEN); // Дождаться завершения запуска
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

void i2c_master_stop(void) {
    I2C_MASTER_WAIT();
    SSPCON2bits.PEN = 1;     // Инициировать условие остановки
    while (SSPCON2bits.PEN); // Дождаться завершения остановки
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

void i2c_master_write(unsigned char data) {
    I2C_MASTER_WAIT();
    SSPBUF = data;           // Загрузка данных в буфер
    while (!PIR1bits.SSPIF); // Дождаться завершения передачи
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

unsigned char i2c_master_read(unsigned char ack) {
    I2C_MASTER_WAIT();
    SSPCON2bits.RCEN = 1;    // Включить режим приема
    while (!PIR1bits.SSPIF); // Дождаться окончания приема
    PIR1bits.SSPIF = 0;      // Очистить флаг
    // Отправить ACK/NACK
    if (ack) {
        SSPCON2bits.ACKDT = 1; // NACK
    } else {
        SSPCON2bits.ACKDT = 0; // ACK
    }
    SSPCON2bits.ACKEN = 1;     // Отправить ACK/NACK
    while (SSPCON2bits.ACKEN); // Дождаться завершения

    return SSPBUF;
}
