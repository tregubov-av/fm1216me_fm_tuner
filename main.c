#include <xc.h>
#include "main.h"
#include "setup_pic16f876a.h"
#include "usart.h"
#include "usart_debug_board.h"
#include "fm1216me.h"
#include "encoder_manager.h"
#include "key_manager.h"
#include "i2c_master.h"
#include "hd44780_pcf8574t.h"

// Записать в eeprom частоту на которую настроен тюнер
__eeprom unsigned int current_freq_eeprom;

// Поиск сигнала
void fm_scan_up(void){
    current_freq_eeprom = current_freq_eeprom + FM_FREQ_TUNING_STEP;
    while(current_freq_eeprom <= FM_FREQ_LIMIT_H) {
        // Понизить чувствительность тюнера
        fm1216me_tune_fm(current_freq_eeprom, 0, FM_MUTE);
        __delay_ms(50);
        fm1216me_read_status(&fm1216me_status);
        // Если флаги FL и FMIFL подняты, сигнал найден
        if(fm1216me_status.pll_lock && fm1216me_status.signal_fm) {
            // TODO точная подстройка по AFC
            fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, FM_MUTE);
            return;
        }
        // TODO debug. Перечитать статус и вывести в usart
        fm1216me_read_status(&fm1216me_status);
        debug_print_usart(current_freq_eeprom);
        // Прервать сканирование
        current_freq_eeprom = current_freq_eeprom + FM_FREQ_TUNING_STEP;
        if(BITTST1(button_flags, BUTTON2_PRESSED)){
            BITCLR(button_flags ,BUTTON2_PRESSED);
            fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, FM_MUTE);
            return;
        }
    }
    if(current_freq_eeprom >= FM_FREQ_LIMIT_H){
        current_freq_eeprom = FM_FREQ_LIMIT_L;
    }
}

// Вывести на LCD дисплей
void lcd_show(void) {
    lcd_clear();
    lcd_setcursor(0, 4);
    lcd_sendstring("FM TUNER");
    lcd_setcursor(1, 3);
    lcd_showfrequency(current_freq_eeprom);
    lcd_sendstring(" MHz");
}

void main(void) {
    // Конфигурирование регистров специального назначения.
    setup_pic();
    // Инициализация USART
    init_usart();
    // Инициализация I2C
    i2c_master_init();
    // Инициализация энкодера
    encoder_init();
    // Инициализация дисплея
    lcd_init();
    // Инициализация тюнера
    fm1216me_init();
    // Если частота из EEPROM не попдает в заданый интервал,
    // установить частоту по умолчанию
    if (current_freq_eeprom > FM_FREQ_LIMIT_H || current_freq_eeprom < FM_FREQ_LIMIT_L) { 
        current_freq_eeprom = FM_DEFAULT_FREQ;
    }
    // Настроить тюнер на частоту из EEPROM
    fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, FM_MUTE);
    // Вывести частоту на LCD дисплей
    lcd_show();
    // TODO debug. Перечитать статус и вывести в usart
    fm1216me_read_status(&fm1216me_status);
    debug_print_usart(current_freq_eeprom);
    // Разрешить прерывания
    ei();
    while(1){
        // Проверить энкодер на факт вращения
        while (encoder_event_flag <= 1){
            // Вращение влево
            if (!encoder_event_flag) {
                if (current_freq_eeprom > FM_FREQ_LIMIT_L) {
                    current_freq_eeprom = current_freq_eeprom - FM_FREQ_TUNING_STEP;
                } else {
                    current_freq_eeprom = FM_FREQ_LIMIT_L;
                }
            }
            // Вращение вправо
            if (encoder_event_flag == 1) { 
                if (current_freq_eeprom < FM_FREQ_LIMIT_H) {
                    current_freq_eeprom = current_freq_eeprom + FM_FREQ_TUNING_STEP;
                } else {
                    current_freq_eeprom = FM_FREQ_LIMIT_H;
                }
            }
            // Настроить тюнер на частоту из EEPROM
            fm1216me_tune_fm(current_freq_eeprom, FM_STEREO, FM_MUTE);
            // Вывести частоту на LCD дисплей
            lcd_show();
            // TODO debug. Перечитать статус и вывести в usart
            fm1216me_read_status(&fm1216me_status);
            debug_print_usart(current_freq_eeprom);
      }
        // TODO debug. Перечитать статус и вывести в usart
        if (BITTST1(button_flags, BUTTON1_PRESSED)) {
            BITCLR(button_flags, BUTTON1_PRESSED);
            fm1216me_read_status(&fm1216me_status);
            debug_print_usart(current_freq_eeprom);
        }
        // Запустить сканирование
        if (BITTST1(button_flags, BUTTON2_PRESSED)) {
            BITCLR(button_flags ,BUTTON2_PRESSED);
            fm_scan_up();
            lcd_show();  
            fm1216me_read_status(&fm1216me_status);
            debug_print_usart(current_freq_eeprom);
        }
    }
}

// Обработчик прерывания
void __interrupt() isr(void) {
    // Проверка флага прерывания Timer1
    if (PIR1bits.TMR1IF) {
        // Сброс флага прерывания
        PIR1bits.TMR1IF = 0;
        // Перезагрузка таймера для следующего периода 1 мс
        // Для 1 мс при 20 МГц и предделителе 1:4
        TMR1 = 64286;
        // Обработка энкодера
        encoder_manager();        
        // Обработка кнопок
        buttons_process();
    }
}
