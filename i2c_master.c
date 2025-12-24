#include <xc.h>
#include "i2c_master.h"

void i2c_master_init(void) {
    TSCL = 1;            // Инициализировать SCL 
    TSDA = 1;            // Инициализировать SDA
    SSPADD = SSPADD_GEN; // Установить частоту
    SSPSTAT = 0x80;      // Управление скоростью нарастания отключено для стандартного режима
    SSPCON = 0x28;       // Включите SSP и выбрать режим I2C Master.
}

void i2c_master_wait(void) {
    // Ожидание завершения текущей операции I2C
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); // Проверка битов BF, UA, SSPEN, CKP, RN_W, ...
}

void i2c_master_start(void) {
    i2c_master_wait();
    SSPCON2bits.SEN = 1;     // Инициировать условие запуска
    while (SSPCON2bits.SEN); // Дождаться завершения запуска
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

void i2c_master_stop(void) {
    i2c_master_wait();
    SSPCON2bits.PEN = 1;     // Инициировать условие остановки
    while (SSPCON2bits.PEN); // Дождаться завершения остановки
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

void i2c_master_write(unsigned char data) {
    i2c_master_wait();
    SSPBUF = data;           // Загрузка данных в буфер
    while (!PIR1bits.SSPIF); // Дождаться завершения передачи
    PIR1bits.SSPIF = 0;      // Сбросить флаг прерывания
}

unsigned char i2c_master_read(unsigned char ack) {
    i2c_master_wait();
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
