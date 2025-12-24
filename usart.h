#ifndef USART_H
#define USART_H

#include "setup_pic16f876a.h"

#define BAUD 9600          // Скорость передачи
#define SPEED 1            // Выбор режима (LOW 0, HIG 1)

#if SPEED == 1                                          // вычисляем значение регистра SPBRG
#define DIVIDER ((int)(_XTAL_FREQ/(16UL * BAUD) -1))    // для высокого уровня
#else
#define DIVIDER ((int)(_XTAL_FREQ/(64UL * BAUD) -1))    // для низкого уровня
#endif

// Конфигурация МК для работы с USART
#define init_usart()                            \
    /*TRISB*/                                   \
    TRISCbits.TRISC7 = 1;   /* Порт приема*/        \
    TRISCbits.TRISC6 = 0;   /* Порт передачи*/      \
    /*TXSTA*/                                   \
    TXSTAbits.TX9  = 1;     /* 9bit прием*/         \
    TXSTAbits.TXEN = 1;     /* Разрешить передачу*/ \
    TXSTAbits.SYNC = 0;     /* Асинхронный*/        \
    TXSTAbits.BRGH = SPEED; /* Вбор режима*/        \
    /*RCSTA*/                                   \
    RCSTAbits.SPEN = 1;     /* Разрешить USART*/    \
    RCSTAbits.RX9  = 1;     /* 9bit передача*/      \
    RCSTAbits.CREN = 1;     /* Разрешить прием*/    \
    SPBRG = DIVIDER;         /*Скорость предачи*/

// Управление функциями
// 1 - Enable
// 0 - Disable
#define PUTCH  1
#define GETCH  0
#define GETCHE 0

/* передача одного байта */
#if PUTCH
void putch(unsigned char byte);
#endif

/* получение одного байта */
#if GETCH
unsigned char getch(void);
#endif

/*возвращает очередной символ, считанный с консоли, и выводит этот символ на экран*/
#if GETCHE
unsigned char getche(void);
#endif

#endif
