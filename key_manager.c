#include <xc.h>
#include "key_manager.h"

// Глобальные переменные
// Флаги состояний кнопок
volatile unsigned char button_flags = 0;
// Статические переменные для отслеживания состояний
static unsigned char button1_counter = 0;
static unsigned char button2_counter = 0;

// Обработка кнопок (вызывается по прерыванию таймера каждую 1 мс)
void buttons_process(void) {
    // Обработка кнопки 1 (RC2)
    if (!BUTTON1) {  // Кнопка нажата (активный низкий уровень)
        if (button1_counter < 0xFF) {
            button1_counter++;
        }
        // Проверка на дребезг
        if (button1_counter == DEBOUNCE_TIME) {
            // Кнопка уверенно нажата
            BITSET(button_flags, BUTTON1_PRESSED);
        }
    } else {  // Кнопка отпущена
        button1_counter = 0;
    }

    // Обработка кнопки 2 (RC5)
    if (!BUTTON2) {  // Кнопка нажата (активный низкий уровень)
        if (button2_counter < 0xFF) {
            button2_counter++;
        }
        // Проверка на дребезг
        if (button2_counter == DEBOUNCE_TIME) {
            // Кнопка уверенно нажата
            BITSET(button_flags, BUTTON2_PRESSED);
        }
    } else {  // Кнопка отпущена
        button2_counter = 0;
    }
}
