#include <xc.h>
#include "hd44780_pcf8574t.h"
#include "i2c_master.h"
#include "setup_pic16f876a.h"

// Отправка nibble на LCD
void lcd_sendnibble(unsigned char nibble, unsigned char mode) {
    unsigned char data = nibble & 0xF0;  // Берем старший nibble

    if (mode == 1)  // Если передача данных
        data |= LCD_RS;

    data |= LCD_BL;  // Включить подсветку
    data |= LCD_E;   // Установить Enable

    // Запись по I2C
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write(data);
    i2c_master_stop();

    __delay_us(1);  // Пауза для импульса

    data &= ~LCD_E;  // Сбросить Enable

    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write(data);
    i2c_master_stop();

    __delay_us(50);  // Пауза между командами
}

#if LCD_PULSEENABLE
// Импульс на выводе Enable
void lcd_pulseenable(unsigned char data) {
    data |= LCD_E;
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write(data);
    i2c_master_stop();

    __delay_us(1);

    data &= ~LCD_E;
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write(data);
    i2c_master_stop();

    __delay_us(50);
}
#endif

// Инициализация LCD
void lcd_init(void) {
    __delay_ms(50);  // Ожидание стабилизации питания
    // Последовательность инициализации 4-битного режима
    lcd_sendnibble(0x30, 0);
    __delay_ms(5);
    lcd_sendnibble(0x30, 0);
    __delay_us(150);
    lcd_sendnibble(0x30, 0);
    __delay_us(150);

    // Переключение в 4-битный режим
    lcd_sendnibble(0x20, 0);
    __delay_us(150);

    // Настройка: 2 строки, 5x8 точек
    lcd_sendcommand(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);

    // Выключить дисплей
    lcd_sendcommand(LCD_DISPLAYCONTROL | LCD_DISPLAYOFF);

    // Очистить дисплей
    lcd_sendcommand(LCD_CLEARDISPLAY);
    __delay_ms(2);

    // Режим ввода: автоинкремент, без сдвига
    lcd_sendcommand(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);

    // Включить дисплей, курсор выключен, мигание выключено
    lcd_sendcommand(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
}

// Отправка команды на LCD
void lcd_sendcommand(unsigned char cmd) {
    unsigned char high_nibble = cmd & 0xF0;
    unsigned char low_nibble = (cmd << 4) & 0xF0;

    // Отправить старший nibble
    lcd_sendnibble(high_nibble, 0);

    // Отправить младший nibble
    lcd_sendnibble(low_nibble, 0);

    if (cmd == LCD_CLEARDISPLAY || cmd == LCD_RETURNHOME)
        __delay_ms(2);  // Длительные команды
}

// Отправка данных на LCD
void lcd_senddata(unsigned char data) {
    unsigned char high_nibble = data & 0xF0;
    unsigned char low_nibble = (data << 4) & 0xF0;

    // Отправить старший nibble
    lcd_sendnibble(high_nibble, 1);

    // Отправить младший nibble
    lcd_sendnibble(low_nibble, 1);
}

// Отправка строки
void lcd_sendstring(const char *str) {
    while (*str) {
        lcd_senddata(*str++);
    }
}

// Установка позиции курсора
void lcd_setcursor(unsigned char row, unsigned char col) {
    unsigned char address;

    switch (row) {
        case 0:
            address = 0x00 + col;
            break;
        case 1:
            address = 0x40 + col;
            break;
        default:
            address = 0x00 + col;
    }

    lcd_sendcommand(LCD_SETDDRAMADDR | address);
}

// Очистка дисплея
void lcd_clear(void) {
    lcd_sendcommand(LCD_CLEARDISPLAY);
    __delay_ms(2);
}

#if LCD_RETHOME
// Возврат курсора в начало
void lcd_returnhome(void) {
    lcd_sendcommand(LCD_RETURNHOME);
    __delay_ms(2);
}
#endif

#if LCD_DISPLAY
// Включение дисплея
void lcd_displayon(void) {
    static unsigned char displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
// Выключение дисплея
void lcd_displayoff(void) {
    static unsigned char displayControl = LCD_DISPLAYOFF | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
#endif

#if LCD_CURSOR
// Включение курсора
void lcd_cursoron(void) {
    static unsigned char displayControl = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
// Выключение курсора
void lcd_cursoroff(void) {
    static unsigned char displayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
#endif

#if LCD_BLINK
// Включение мигания курсора
void lcd_blinkon(void) {
    static unsigned char displayControl = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
// Выключение мигания курсора
void lcd_blinkoff(void) {
    static unsigned char displayControl = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
    lcd_sendcommand(LCD_DISPLAYCONTROL | displayControl);
}
#endif

#if LCD_BACKLIGHT
// Включение подсветки
void lcd_backlighton(void) {
    // Реализуется аппаратно через PCF8574
    // Включение подсветки происходит при каждой передаче
}
// Выключение подсветки
void lcd_backlightoff(void) {
    // Отправка 0 для выключения подсветки
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write(0x00);  // Все пины в 0, включая подсветку
    i2c_master_stop();
}
#endif

// Вывод частоты
void lcd_showfrequency(unsigned int freq) {
    char buffer[8];
    
    // Для 5-значных чисел
    if (freq >= 10000) {
        // 12345 -> 123.45
        buffer[0] = (freq / 10000) % 10 + '0';       // 1
        buffer[1] = (freq / 1000) % 10 + '0';        // 2
        buffer[2] = (freq / 100) % 10 + '0';         // 3
        buffer[3] = '.';                            // .
        buffer[4] = (freq / 10) % 10 + '0';         // 4
        buffer[5] = freq % 10 + '0';                // 5
        buffer[6] = '\0';
    }
    // Для 4-значных чисел
    else if (freq >= 1000) {
        // 1234 -> 12.34
        buffer[0] = (freq / 1000) % 10 + '0';        // 1
        buffer[1] = (freq / 100) % 10 + '0';         // 2
        buffer[2] = '.';                            // .
        buffer[3] = (freq / 10) % 10 + '0';         // 3
        buffer[4] = freq % 10 + '0';                // 4
        buffer[5] = '\0';
    }
    // Для 3-значных чисел
    else if (freq >= 100) {
        // 123 -> 1.23
        buffer[0] = (freq / 100) % 10 + '0';         // 1
        buffer[1] = '.';                            // .
        buffer[2] = (freq / 10) % 10 + '0';         // 2
        buffer[3] = freq % 10 + '0';                // 3
        buffer[4] = '\0';
    }
    // Для 2-значных чисел
    else if (freq >= 10) {
        // 12 -> 0.12
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = (freq / 10) % 10 + '0';         // 1
        buffer[3] = freq % 10 + '0';                // 2
        buffer[4] = '\0';
    }
    // Для 1-значных чисел
    else {
        // 1 -> 0.01
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = freq % 10 + '0';                // 1
        buffer[4] = '\0';
    }
    
    lcd_sendstring(buffer);
}
