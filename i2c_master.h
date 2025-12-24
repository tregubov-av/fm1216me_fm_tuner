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

void i2c_master_init(void);
void i2c_master_start(void);
void i2c_master_stop(void);
void i2c_master_write(unsigned char data);
unsigned char i2c_master_read(unsigned char ack);


#endif	/* I2C_MASTER_H */
