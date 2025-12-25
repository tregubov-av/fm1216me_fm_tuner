#include <xc.h>
#include "encoder_manager.h"

// Переменные для отслеживания состояния.
// Общий счетчик, который увеличивается/уменьшается при каждом действительном
// шаге (переходе) энкодера.
volatile signed int encoder_raw_counter = 0;
// Значение raw_counter при последнем зарегистрированном "щелчке" (detent).
volatile signed int encoder_last_detent = 0;
// Предыдущее состояние энкодера (2 бита: A и B).
volatile unsigned char encoder_last_state = 0;
// Начальный флаг состояния
volatile encoder_direction_t encoder_event_flag = ENCODER_STOP;

// Таблица переходов для детектирования направления
// Индекс: (старое_состояние << 2) | новое_состояние
// Значение: -1 = обратное направление, 1 = прямое направление, 0 = невалидный переход
static const signed char transition_table[16] = {
     0, // 0000: 00 -> 00
    -1, // 0001: 00 -> 01
     1, // 0010: 00 -> 10
     0, // 0011: 00 -> 11
     1, // 0100: 01 -> 00
     0, // 0101: 01 -> 01
     0, // 0110: 01 -> 10
    -1, // 0111: 01 -> 11
    -1, // 1000: 10 -> 00
     0, // 1001: 10 -> 01
     0, // 1010: 10 -> 10
     1, // 1011: 10 -> 11
     0, // 1100: 11 -> 00
     1, // 1101: 11 -> 01
    -1, // 1110: 11 -> 10
     0  // 1111: 11 -> 11
};

void encoder_init(void) {
    // Настройка портов на вход
    ENCODER_A_TRIS = 1;
    ENCODER_B_TRIS = 1;
    // Чтение начального состояния
    encoder_last_state = (ENCODER_A_PORT << 1) | ENCODER_B_PORT;
}

void encoder_manager(void) {
    // Считываем текущее состояние энкодера.
    unsigned char current_state = (ENCODER_A_PORT << 1) | ENCODER_B_PORT;
    // Проверяем, произошло ли изменение состояния.
    if (current_state != encoder_last_state) {
        // Формируем 4-битный код перехода (transition).
        // 4-битное число, объединяющее предыдущее и текущее состояния:
        // Биты 3 и 2: Предыдущее состояние (last_state)
        // Биты 1 и 0: Текущее состояние (current_state)
        // Например, переход из 00 в 01 даст transition = 0b0001
        unsigned char transition = (encoder_last_state << 2) | current_state;
        // Используем таблицу переходов для определения направления
        signed char direction = transition_table[transition];
        // Если переход валидный
        if (direction != 0) {
            // Движение против часовой стрелки, уменьшаем общий счетчик
            // Движение по часовой стрелке, увеличиваем общий счетчик
            encoder_raw_counter += direction;
            // Проверяем достижение детента
            // Вычисляем разницу (diff) между общим количеством шагов (raw_counter)
            // и последним зарегистрированным щелчком (last_detent).
            // Показывает, сколько шагов было сделано с последнего щелчка.
            signed char diff = (signed char)(encoder_raw_counter - encoder_last_detent);
            // Проверяем, достигли ли мы порога для одного щелчка (detent).
            // Если 'diff' больше или равен STEPS_PER_DETENT, произошел "правый" щелчок.
            if (diff >= STEPS_PER_DETENT) {
                // Устанавливаем флаг направления движения эекодера
                encoder_event_flag = ENCODER_RIGHT;
                // Сбрасываем точку отсчета щелчка.
                encoder_last_detent = encoder_raw_counter;
            // Если 'diff' меньше или равен -STEPS_PER_DETENT, произошел "левый" щелчок.
            } else if (diff <= -STEPS_PER_DETENT) {
                // Устанавливаем флаг направления движения эекодера
                encoder_event_flag = ENCODER_LEFT;
                // Сбрасываем точку отсчета щелчка.
                encoder_last_detent = encoder_raw_counter;
            }
        }
        // Обновляем состояние
        encoder_last_state = current_state;
    } else {
        // Устанавливаем флаг направления движения эекодера
        encoder_event_flag = ENCODER_STOP;
    }
}

// Дополнительные функции для удобства использования
#if ENCODER_GET_EVENT
encoder_direction_t encoder_get_event(void) {
    encoder_direction_t event;
    // Запрещаем прерывания на время чтения
    GIE = 0;
    event = encoder_event_flag;
    GIE = 1;
    return event;
}
#endif

#if ENCODER_CLEAR_EVENT
void encoder_clear_event(void) {
    GIE = 0;
    encoder_event_flag = ENCODER_STOP;
    GIE = 1;
}
#endif

#if ENCODER_GET_COUNTER
signed int encoder_get_counter(void) {
    signed int counter;
    GIE = 0;
    counter = encoder_raw_counter;
    GIE = 1;
    return counter;
}
#endif
