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

#ifndef I2C_MASTER_H
#define	I2C_MASTER_H

#include "setup_pic16f876a.h"

// Установить частоту тактирования на 100 кГц.
#define I2C_SPEED 100000 // 100kHz
// Установить тактовую частоту для I2C
// SSPADD = (Fosc / (4 * I2C_SCL)) - 1
#define SSPADD_GEN ((_XTAL_FREQ/(4*I2C_SPEED)) - 1)

// Инициализировать SCL и SDA
#define SDA  PORTCbits.RC4    // SDA
#define SCL  PORTCbits.RC3    // SCL
#define TSDA TRISCbits.TRISC4 // SDA
#define TSCL TRISCbits.TRISC3 // SCL

// Константы протокола I2C
#define I2C_ACK         0 // Подтверждение (ACK) - линия SDA низкий уровень
#define I2C_NACK        1 // Отрицание (NACK) - линия SDA высокий уровень

// Ожидание завершения текущей операции I2C
#define I2C_MASTER_WAIT()  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F))

void i2c_master_init(void);
void i2c_master_start(void);
void i2c_master_stop(void);
void i2c_master_write(unsigned char data);
unsigned char i2c_master_read(unsigned char ack);

#endif	/* I2C_MASTER_H */
