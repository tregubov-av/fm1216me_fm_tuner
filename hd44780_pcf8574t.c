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
#include "hd44780_pcf8574t.h"
#include "i2c_master.h"
#include "setup_pic16f876a.h"

#if LCD_PULSEENABLE
// Импульс на выводе Enable
void lcd_pulseenable(unsigned char data) {
    data |= LCD_E;
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write((unsigned char)data);
    i2c_master_stop();

    __delay_us(1);

    data &= ~LCD_E;
    i2c_master_start();
    i2c_master_write(PCF8574T_ADDR);
    i2c_master_write((unsigned char)data);
    i2c_master_stop();

    __delay_us(50);
}
#endif

// Отправка команды на LCD
void lcd_sendcommand(unsigned char cmd) {
    unsigned char high_nibble = (unsigned char)(cmd & 0xF0);
    unsigned char low_nibble = (unsigned char)((cmd << 4) & 0xF0);

    // Отправить старший nibble
    LCD_SEND_NIBBLE(high_nibble, 0);

    // Отправить младший nibble
    LCD_SEND_NIBBLE(low_nibble, 0);

    if (cmd == LCD_CLEARDISPLAY || cmd == LCD_RETURNHOME)
        __delay_ms(2);  // Длительные команды
}

// Инициализация LCD
void lcd_init(void) {
    __delay_ms(50);  // Ожидание стабилизации питания
    // Последовательность инициализации 4-битного режима
    LCD_SEND_NIBBLE(0x30, 0);
    __delay_ms(5);
    LCD_SEND_NIBBLE(0x30, 0);
    __delay_us(150);
    LCD_SEND_NIBBLE(0x30, 0);
    __delay_us(150);

    // Переключение в 4-битный режим
    LCD_SEND_NIBBLE(0x20, 0);
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

// Отправка строки
void lcd_sendstring(const char *str) {
    unsigned char data;
    while (*str) {
    // Отправка данных на LCD
        data = *str++;
        unsigned char high_nibble = (unsigned char)(data & 0xF0);
        unsigned char low_nibble = (unsigned char)((data << 4) & 0xF0);

        // Отправить старший nibble
        LCD_SEND_NIBBLE(high_nibble, 1);

        // Отправить младший nibble
        LCD_SEND_NIBBLE(low_nibble, 1);    
    }
}

// Установка позиции курсора
void lcd_setcursor(unsigned char row, unsigned char col) {
    unsigned char address;

    switch (row) {
        case 0:
            address = (unsigned char)(0x00 + col);
            break;
        case 1:
            address = (unsigned char)(0x40 + col);
            break;
        default:
            address = (unsigned char)(0x00 + col);
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
