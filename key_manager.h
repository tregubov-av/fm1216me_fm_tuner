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
#define BUTTON1   PORTCbits.RC2
#define BUTTON2   PORTCbits.RC5

// Битмаска флагов
#define BUTTON1_PRESSED    0x0
#define BUTTON1_LONG_PRESS 0x1
#define BUTTON2_PRESSED    0x2
#define BUTTON2_LONG_PRESS 0x3

// Флаги состояний кнопок
extern volatile unsigned char button_flags;

// Конфигурация таймингов (в миллисекундах)
#define DEBOUNCE_TIME      20
#define LONG_PRESS_TIME    255

// Прототипы функций
void buttons_process(void);

#endif  /* KEY_MANAGER_H */
