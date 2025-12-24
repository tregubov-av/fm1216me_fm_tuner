#ifndef HD44780_PCF8574T
#define HD44780_PCF8574T

// Адрес PCF8574T (зависит от адресных контактов A0-A2)
#define PCF8574T_ADDR 0x4E  // 0x27 << 1 (бит R/W всегда 0 для записи)

// Биты PCF8574 (соединения с HD44780)
#define LCD_RS  0x01  // Register Select
#define LCD_RW  0x02  // Read/Write
#define LCD_E   0x04  // Enable
#define LCD_BL  0x08  // Backlight
#define LCD_D4  0x10  // Data bit 4
#define LCD_D5  0x20  // Data bit 5
#define LCD_D6  0x40  // Data bit 6
#define LCD_D7  0x80  // Data bit 7

// Команды LCD
#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02
#define LCD_ENTRYMODESET    0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT     0x10
#define LCD_FUNCTIONSET     0x20
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

// Флаги для режима ввода (Entry Mode)
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// Флаги управления дисплеем (Display Control)
#define LCD_DISPLAYON  0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON   0x02
#define LCD_CURSOROFF  0x00
#define LCD_BLINKON    0x01
#define LCD_BLINKOFF   0x00

// Флаги сдвига/движения (Cursor/Display Shift)
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

// Флаги функции (Function Set)
#define LCD_8BITMODE  0x10
#define LCD_4BITMODE  0x00
#define LCD_2LINE     0x08
#define LCD_1LINE     0x00
#define LCD_5x10DOTS  0x04
#define LCD_5x8DOTS   0x00

// Управление функциями
// 1 - Enable
// 0 - Disable
#define LCD_PULSEENABLE 0
#define LCD_RETHOME     0
#define LCD_DISPLAY     0
#define LCD_CURSOR      0
#define LCD_BLINK       0
#define LCD_BACKLIGHT   0

// Прототипы функций
void lcd_init(void);
void lcd_sendcommand(unsigned char cmd);
void lcd_senddata(unsigned char data);
void lcd_sendstring(const char *str);
void lcd_setcursor(unsigned char row, unsigned char col);
void lcd_clear(void);
#if LCD_RETHOME
void lcd_returnhome(void);
#endif
#if LCD_DISPLAY
void lcd_displayon(void);
void lcd_displayoff(void);
#endif
#if LCD_CURSOR
void lcd_cursoron(void);
void lcd_cursoroff(void);
#endif
#if LCD_BLINK
void lcd_blinkon(void);
void lcd_blinkoff(void);
#endif
#if LCD_BACKLIGHT
void lcd_backlighton(void);
void lcd_backlightoff(void);
#endif
void lcd_sendnibble(unsigned char nibble, unsigned char mode);
#if LCD_PULSEENABLE
void lcd_pulseenable(unsigned char data);
#endif
void lcd_showfrequency(unsigned int freq);

#endif /* HD44780_PCF8574T */
