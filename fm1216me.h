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

#ifndef _FM1216ME_H_
#define _FM1216ME_H_
/*************** МАКРОСЫ ДЛЯ РЕГИСТРОВ ТЮНЕРНОЙ ЧАСТИ FM1216ME*****************/
// Адрес на шине I2C
#define FM1216ME_I2C_ADDR 0xC0 // Адрес тюнера (AS=VDD) (Если AS=NC, то 0XC2)

// f - частота в единицах по 10 кГц (100.8 МГц = 10080)
// Константы промежуточных частот
#define IF_FM        1070    // 10.7 МГц = 10700 кГц = 1070 единиц
#define IF_TV        3890    // 38.9 МГц = 38900 кГц = 3890 единиц
#define IF_TV_LPRIME 3395   // 33.95 МГц = 33950 кГц = 3395 единиц

// Константы шагов PLL (умножены на 1000 для точности)
#define STEP_50_X1000      50000UL   // 50 кГц * 1000 = 50000
#define STEP_31_25_X1000   31250UL   // 31.25 кГц * 1000 = 31250
#define STEP_62_5_X1000    62500UL   // 62.5 кГц * 1000 = 62500
#define STEP_166_7_X1000   166700UL  // 166.7 кГц * 1000 = 166700

/* =================== МАКРОСЫ ДЛЯ РАСЧЕТА ЧАСТОТ DB1-DB2 =================== */
// Рассчитывает N = (F_RF + F_IF) / F_step
// Универсальный для расчета любых параметров
#define FM1216ME_CALC_N_SCALED(f, if_const, step_x1000) \
    ((unsigned int)(((unsigned long)(f) * 1000UL + (unsigned long)(if_const) * 1000UL) / (unsigned long)(step_x1000)))

// Разделение N на старший и младший байты
#define FM1216ME_DIV_HIGH_FROM_N(n) ((unsigned int)((n) >> 8))
// TODO fm1216me.c:32: warning: (751) arithmetic overflow in constant expression (возможно баг компилятора)
#define FM1216ME_DIV_LOW_FROM_N(n)  ((unsigned int)((n) & 0xFFU))

/* ---- FM РАДИО (10.7 МГц) ---- */
// Шаг 50 кГц (RSA=0, RSB=0) 
#define FM1216ME_FM_N_50KHZ(f) ((unsigned int)(((f) + IF_FM) / 5))
#define FM1216ME_FM_DIV_HIGH_50KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_FM_N_50KHZ(f))
#define FM1216ME_FM_DIV_LOW_50KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_FM_N_50KHZ(f))

// Шаг 31.25 кГц (RSA=0, RSB=1)
#define FM1216ME_FM_N_31_25KHZ(f) FM1216ME_CALC_N_SCALED(f, IF_FM, STEP_31_25_X1000)
#define FM1216ME_FM_DIV_HIGH_31_25KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_FM_N_31_25KHZ(f))
#define FM1216ME_FM_DIV_LOW_31_25KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_FM_N_31_25KHZ(f))

// Шаг 62.5 кГц (RSA=1, RSB=1)
#define FM1216ME_FM_N_62_5KHZ_INT(f) ((unsigned int)(((unsigned long)((f) + IF_FM) * 4) / 25))
#define FM1216ME_FM_DIV_HIGH_62_5KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_FM_N_62_5KHZ_INT(f))
#define FM1216ME_FM_DIV_LOW_62_5KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_FM_N_62_5KHZ_INT(f))

/* ---- TV (B/G/I/D/K, 38.9 МГц) ---- */
// Шаг 50 кГц
#define FM1216ME_TV_N_50KHZ(f) ((unsigned int)(((f) + IF_TV) / 5))
#define FM1216ME_TV_DIV_HIGH_50KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_TV_N_50KHZ(f))
#define FM1216ME_TV_DIV_LOW_50KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_TV_N_50KHZ(f))

// Шаг 62.5 кГц
#define FM1216ME_TV_N_62_5KHZ_INT(f) ((unsigned int)(((unsigned long)((f) + IF_TV) * 4) / 25))
#define FM1216ME_TV_DIV_HIGH_62_5KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_TV_N_62_5KHZ_INT(f))
#define FM1216ME_TV_DIV_LOW_62_5KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_TV_N_62_5KHZ_INT(f))

/* ---- TV L' (33.95 МГц) ---- */
// Шаг 50 кГц
#define FM1216ME_TV_LPRIME_N_50KHZ(f) ((unsigned int)(((f) + IF_TV_LPRIME) / 5))
#define FM1216ME_TV_LPRIME_DIV_HIGH_50KHZ(f) FM1216ME_DIV_HIGH_FROM_N(FM1216ME_TV_LPRIME_N_50KHZ(f))
#define FM1216ME_TV_LPRIME_DIV_LOW_50KHZ(f)  FM1216ME_DIV_LOW_FROM_N(FM1216ME_TV_LPRIME_N_50KHZ(f))

/* =========================== CONTROL BYTE (CB) =========================== */
// Бит 7: Always One - всегда 0x80
#define FM1216ME_CB_BIT7_ALWAYS_ONE    0x80
// Бит 6: Charge Pump (CP)
#define FM1216ME_CB_CP_LOW             0x00  // 0x00 = бит 6 сброшен
#define FM1216ME_CB_CP_HIGH            0x40  // 0x40 = бит 6 установлен
// Биты 5-3: Test Mode (T2, T1, T0)
#define FM1216ME_CB_TEST_NORMAL        0x08  // 0x08 = T0=1 (0b001 << 3)
#define FM1216ME_CB_TEST_AB_INSTEAD_BB 0x18  // 0x18 = T1=1, T0=1 (0b011 << 3)
// Биты 2-1: Ratio Select (RSA, RSB) - шаг PLL
#define FM1216ME_CB_RSA_0_RSB_0        0x00  // 0x00 = RSA=0, RSB=0
#define FM1216ME_CB_RSA_0_RSB_1        0x02  // 0x02 = RSB=1, RSA=0
#define FM1216ME_CB_RSA_1_RSB_0        0x04  // 0x04 = RSA=1, RSB=0
#define FM1216ME_CB_RSA_1_RSB_1        0x06  // 0x06 = RSA=1, RSB=1
/* Макросы для конкретных шагов PLL */
#define FM1216ME_CB_STEP_50KHZ         0x00  // 50 kHz
#define FM1216ME_CB_STEP_31_25KHZ      0x02  // 31.25 kHz
#define FM1216ME_CB_STEP_166_7KHZ      0x04  // 166.7 kHz
#define FM1216ME_CB_STEP_62_5KHZ       0x06  // 62.5 kHz
// Бит 0: PLL Disabling (OS)
#define FM1216ME_CB_OS_ENABLE          0x00  // 0x00 = PLL включен
#define FM1216ME_CB_OS_DISABLE         0x01  // 0x01 = PLL выключен

// ГОТОВЫЕ КОНФИГУРАЦИИ CONTROL BYTE
// Нормальный режим для FM (CP=0, шаг 50 кГц)
#define FM1216ME_CB_FM_NORMAL \
    (FM1216ME_CB_BIT7_ALWAYS_ONE | \
     FM1216ME_CB_CP_LOW | \
     FM1216ME_CB_TEST_NORMAL | \
     FM1216ME_CB_STEP_50KHZ | \
     FM1216ME_CB_OS_ENABLE)  /* = 0x88 */

// Нормальный режим для TV (CP=1, шаг 50 кГц)
#define FM1216ME_CB_TV_NORMAL \
    (FM1216ME_CB_BIT7_ALWAYS_ONE | \
     FM1216ME_CB_CP_HIGH | \
     FM1216ME_CB_TEST_NORMAL | \
     FM1216ME_CB_STEP_50KHZ | \
     FM1216ME_CB_OS_ENABLE)  /* = 0xC8 */

// Быстрая настройка TV (CP=1, шаг 62.5 кГц)
#define FM1216ME_CB_TV_FAST \
    (FM1216ME_CB_BIT7_ALWAYS_ONE | \
     FM1216ME_CB_CP_HIGH | \
     FM1216ME_CB_TEST_NORMAL | \
     FM1216ME_CB_STEP_62_5KHZ | \
     FM1216ME_CB_OS_ENABLE)  /* = 0xCE */

// Режим медленного поиска (шаг 31.25 кГц)
#define FM1216ME_CB_SLOW_SEARCH \
    (FM1216ME_CB_BIT7_ALWAYS_ONE | \
     FM1216ME_CB_CP_HIGH | \
     FM1216ME_CB_TEST_NORMAL | \
     FM1216ME_CB_STEP_31_25KHZ | \
     FM1216ME_CB_OS_ENABLE)  /* = 0xCA */

/* ========================== BANDSWITCH BYTE (BB) ========================== */
// Готовые конфигурации
// Low Band (48.25-160 МГц) - P0=1, остальные 0
#define FM1216ME_BB_LOW_BAND           0x01
// Mid Band (160-442 МГц) - P1=1, остальные 0
#define FM1216ME_BB_MID_BAND           0x02
// High Band (442-863 МГц) - P2=1, остальные 0
#define FM1216ME_BB_HIGH_BAND          0x04
// FM Band Stereo (87.5-108 МГц) - P0=1, P3=1, P4=1, P6=0
#define FM1216ME_BB_FM_STEREO          0x19
// FM Band Mono (87.5-108 МГц) - P0=1, P3=1, P4=1, P6=1
#define FM1216ME_BB_FM_MONO            0x59

// Макрос для создания полного байта BB с явными битами
#define FM1216ME_MAKE_BB(p0, p1, p2, p3, p4, p5, p6, p7) \
    ((p7 ? 0x80 : 0x00) | \
     (p6 ? 0x40 : 0x00) | \
     (p5 ? 0x20 : 0x00) | \
     (p4 ? 0x10 : 0x00) | \
     (p3 ? 0x08 : 0x00) | \
     (p2 ? 0x04 : 0x00) | \
     (p1 ? 0x02 : 0x00) | \
     (p0 ? 0x01 : 0x00))

/* ==================== AUXILIARY BYTE (AB) ================================= */
// Бит 7: AGC Time Constant (ATC)
#define FM1216ME_AB_ATC_50MS           0x80  // Время 50 мс
#define FM1216ME_AB_ATC_2S             0x00  // Время 2 с
// Биты 6-4: AGC Take Over Point (AL2, AL1, AL0)
#define FM1216ME_AB_AGC_115DBUV        0x00  // 0x00 = 115 dBµV
#define FM1216ME_AB_AGC_115DBUV_ALT    0x10  // 0x10 = 115 dBµV альтернативный
#define FM1216ME_AB_AGC_112DBUV        0x20  // 0x20 = 112 dBµV (default) */
#define FM1216ME_AB_AGC_109DBUV        0x30  // 0x30 = 109 dBµV
#define FM1216ME_AB_AGC_106DBUV        0x40  // 0x40 = 106 dBµV
#define FM1216ME_AB_AGC_103DBUV        0x50  // 0x50 = 103 dBµV
#define FM1216ME_AB_AGC_EXT            0x60  // 0x60 = External AGC
#define FM1216ME_AB_AGC_DISABLED       0x70  // 0x70 = AGC disabled
// Биты 3-0: Всегда 0
#define FM1216ME_AB_ZERO_BITS          0x00

// Рекомендации из DataSheet
#define FM1216ME_AB_RECOMMENDED_TV     0x30  // 109 dBµV для PAL B/G, D/K, I
#define FM1216ME_AB_RECOMMENDED_LL     0x40  // 106 dBµV для системы L/L'
#define FM1216ME_AB_RECOMMENDED_FM     0x50  // 103 dBµV для FM радио

// Макрос для создания полного байта AB
#define FM1216ME_MAKE_AB(atc, agc_level) \
    ((atc) | (agc_level) | 0x00)

/************** МАКРОСЫ ДЛЯ КОНФИГУРИРОВАНИЯ ПЧ-МОДУЛЯ TDA9887 ****************/
/* ==================== БАЗОВЫЕ КОНСТАНТЫ =================================== */
#define TDA9887_I2C_ADDR 0x86    // Адрес на шине I2C
#define TDA9887_SUBADDR  0x00    // Субадрес (SAD)

/* ==================== РЕГИСТР B (SWITCHING) =============================== */
// Бит 0: Video Mode (Video Trap)
#define TDA9887_B_VIDEO_TRAP_ENABLE    0x00  // 0x00 = видео-ловушка включена
#define TDA9887_B_VIDEO_TRAP_DISABLE   0x01  // 0x01 = видео-ловушка выключена
// Бит 1: Auto Mute FM
#define TDA9887_B_AUTO_MUTE_FM_DISABLE 0x00  // 0x00 = авто-мьют выключен
#define TDA9887_B_AUTO_MUTE_FM_ENABLE  0x02  // 0x02 = авто-мьют включен
// Бит 2: Carrier Mode
#define TDA9887_B_CARRIER_MODE_MANUAL  0x00  // 0x00 = ручной режим
#define TDA9887_B_CARRIER_MODE_AUTO    0x04  // 0x04 = автоматический режим
// Бит 3: FM Mode
#define TDA9887_B_TV_MODE              0x00  // 0x00 = TV режим
#define TDA9887_B_FM_MODE              0x08  // 0x08 = FM режим
// Бит 4: TV Modulation
#define TDA9887_B_TV_MOD_POSITIVE      0x00  // 0x00 = положительная модуляция
#define TDA9887_B_TV_MOD_NEGATIVE      0x10  // 0x10 = отрицательная модуляция
// Бит 5: Forced Mute Audio
#define TDA9887_B_AUDIO_MUTE_DISABLE   0x00  // 0x00 = звук включен
#define TDA9887_B_AUDIO_MUTE_ENABLE    0x20  // 0x20 = звук выключен
// Бит 6: FM Sensitivity
#define TDA9887_B_FM_SENS_NORMAL       0x00  // 0x00 = нормальная чувствительность
#define TDA9887_B_FM_SENS_HIGH         0x40  // 0x40 = высокая чувствительность
// Бит 7: L/L' Sound
#define TDA9887_B_LL_SOUND_DISABLE     0x00  // 0x00 = звук L/L' выключен
#define TDA9887_B_LL_SOUND_ENABLE      0x80  // 0x80 = звук L/L' включен

/* ==================== РЕГИСТР C (ADJUST) ================================== */
#define TDA9887_C_TOP_MASK             0x1F      // Маска для битов TOP
#define TDA9887_C_TOP_SHIFT            0         // Сдвиг битов TOP
// Макрос для установки уровня TOP (0-31)
#define TDA9887_C_TOP_VALUE(val)       (((val) & 0x1F) << TDA9887_C_TOP_SHIFT)
// Биты C5-C6: De-emphasis (предыскажение)
#define TDA9887_C_DEEMPH_50US          0x00  // 0x00 = 50 мкс
#define TDA9887_C_DEEMPH_75US          0x20  // 0x20 = 75 мкс
#define TDA9887_C_DEEMPH_DISABLE       0x40  // 0x40 = выключено
// Бит C7: Audio Gain
#define TDA9887_C_AUDIO_GAIN_NORMAL    0x00  // 0x00 = нормальное усиление
#define TDA9887_C_AUDIO_GAIN_HIGH      0x80  // 0x80 = высокое усиление

/* ==================== РЕГИСТР E (DATA) ==================================== */
// Биты E0-E1: Standard Sound Carrier (звуковая поднесущая)
#define TDA9887_E_SOUND_CARRIER_5_5MHZ 0x00  // 0x00 = 5.5 МГц (B/G)
#define TDA9887_E_SOUND_CARRIER_6_0MHZ 0x01  // 0x01 = 6.0 МГц (I)
#define TDA9887_E_SOUND_CARRIER_6_5MHZ 0x03  // 0x03 = 6.5 МГц (D/K, L)
// Биты E2-E4: Standard Video IF (видео ПЧ)
#define TDA9887_E_VIDEO_IF_38_9MHZ     0x00  // 0x00 = 38.9 МГц (B/G/I/D/K)
#define TDA9887_E_VIDEO_IF_33_95MHZ    0x04  // 0x04 = 33.95 МГц (L')
// Бит E5: VIF, SIF and Tuner Minimum Gain
#define TDA9887_E_MIN_GAIN_DISABLE     0x00  // 0x00 = минимальный коэффициент выключен
#define TDA9887_E_MIN_GAIN_ENABLE      0x20  // 0x20 = минимальный коэффициент включен
// Бит E6: L Standard PLL Gating HIGH
#define TDA9887_E_L_PLL_GATING_LOW     0x00  // 0x00 = низкий уровень
#define TDA9887_E_L_PLL_GATING_HIGH    0x40  // 0x40 = высокий уровень
// Бит E7: VIF-AGC
#define TDA9887_E_VIF_AGC_DISABLE      0x00  // 0x00 = AGC видео ПЧ выключена
#define TDA9887_E_VIF_AGC_ENABLE       0x80  // 0x80 = AGC видео ПЧ включена

/* ==================== МАКРОСЫ ДЛЯ ФОРМИРОВАНИЯ БАЙТОВ ==================== */
// Макрос для создания байта B
#define TDA9887_MAKE_BYTE_B(video_trap, auto_mute, carrier_mode, fm_mode, tv_mod, force_mute, fm_sens, ll_sound) \
    ((video_trap) | (auto_mute) | (carrier_mode) | (fm_mode) | (tv_mod) | (force_mute) | (fm_sens) | (ll_sound))
// Макрос для создания байта C
#define TDA9887_MAKE_BYTE_C(top_val, deemphasis, audio_gain) \
    ((top_val & 0x1F) | (deemphasis) | (audio_gain))
// Макрос для создания байта E
#define TDA9887_MAKE_BYTE_E(sound_carrier, video_if, min_gain, l_pll_gating, vif_agc) \
    ((sound_carrier) | (video_if) | (min_gain) | (l_pll_gating) | (vif_agc))

/* ==================== ГОТОВЫЕ КОНФИГУРАЦИИ ================================ */
// Конфигурация B/G системы (TV)
#define TDA9887_CONFIG_BG_BYTE_B   (TDA9887_B_TV_MODE | TDA9887_B_TV_MOD_POSITIVE)
#define TDA9887_CONFIG_BG_BYTE_C   (TDA9887_C_TOP_VALUE(0) | TDA9887_C_DEEMPH_DISABLE)
#define TDA9887_CONFIG_BG_BYTE_E   (TDA9887_E_SOUND_CARRIER_5_5MHZ | TDA9887_E_VIDEO_IF_38_9MHZ)

// Конфигурация I системы (TV)
#define TDA9887_CONFIG_I_BYTE_B    (TDA9887_B_TV_MODE | TDA9887_B_TV_MOD_POSITIVE)
#define TDA9887_CONFIG_I_BYTE_C    (TDA9887_C_TOP_VALUE(0) | TDA9887_C_DEEMPH_DISABLE)
#define TDA9887_CONFIG_I_BYTE_E    (TDA9887_E_SOUND_CARRIER_6_0MHZ | TDA9887_E_VIDEO_IF_38_9MHZ)

// Конфигурация D/K системы (TV)
#define TDA9887_CONFIG_DK_BYTE_B   (TDA9887_B_TV_MODE | TDA9887_B_TV_MOD_POSITIVE)
#define TDA9887_CONFIG_DK_BYTE_C   (TDA9887_C_TOP_VALUE(0) | TDA9887_C_DEEMPH_DISABLE)
#define TDA9887_CONFIG_DK_BYTE_E   (TDA9887_E_SOUND_CARRIER_6_5MHZ | TDA9887_E_VIDEO_IF_38_9MHZ)

// Конфигурация L системы (TV)
#define TDA9887_CONFIG_L_BYTE_B    (TDA9887_B_TV_MODE | TDA9887_B_TV_MOD_NEGATIVE | TDA9887_B_LL_SOUND_ENABLE)
#define TDA9887_CONFIG_L_BYTE_C    (TDA9887_C_TOP_VALUE(0) | TDA9887_C_DEEMPH_50US)
#define TDA9887_CONFIG_L_BYTE_E    (TDA9887_E_SOUND_CARRIER_6_5MHZ | TDA9887_E_VIDEO_IF_33_95MHZ | TDA9887_E_L_PLL_GATING_HIGH)

// Конфигурация L' системы (TV)
#define TDA9887_CONFIG_LPRIME_BYTE_B (TDA9887_B_TV_MODE | TDA9887_B_TV_MOD_NEGATIVE | TDA9887_B_LL_SOUND_ENABLE)
#define TDA9887_CONFIG_LPRIME_BYTE_C (TDA9887_C_TOP_VALUE(0) | TDA9887_C_DEEMPH_50US)
#define TDA9887_CONFIG_LPRIME_BYTE_E (TDA9887_E_SOUND_CARRIER_6_5MHZ | TDA9887_E_VIDEO_IF_33_95MHZ | TDA9887_E_L_PLL_GATING_HIGH)

// Конфигурация FM Стерео (высокая чувствительность)
#define TDA9887_CONFIG_FM_STEREO_HIGH_B (TDA9887_B_VIDEO_TRAP_DISABLE | TDA9887_B_FM_MODE | TDA9887_B_AUTO_MUTE_FM_ENABLE | TDA9887_B_FM_SENS_HIGH)
#define TDA9887_CONFIG_FM_STEREO_HIGH_C (TDA9887_C_AUDIO_GAIN_HIGH | TDA9887_C_DEEMPH_75US | TDA9887_C_TOP_VALUE(0))
#define TDA9887_CONFIG_FM_STEREO_HIGH_E (TDA9887_E_MIN_GAIN_ENABLE|TDA9887_E_VIF_AGC_DISABLE)

// Конфигурация FM Моно (нормальная чувствительность)
#define TDA9887_CONFIG_FM_MONO_NORM_B  (TDA9887_B_VIDEO_TRAP_DISABLE | TDA9887_B_FM_MODE | TDA9887_B_AUTO_MUTE_FM_ENABLE | TDA9887_B_FM_SENS_NORMAL)
#define TDA9887_CONFIG_FM_MONO_NORM_C  (TDA9887_C_AUDIO_GAIN_NORMAL | TDA9887_C_DEEMPH_75US | TDA9887_C_TOP_VALUE(0))
#define TDA9887_CONFIG_FM_MONO_NORM_E  (TDA9887_E_MIN_GAIN_ENABLE)

// Конфигурация FM с принудительным отключением звука
#define TDA9887_CONFIG_FM_MUTE_B       (TDA9887_CONFIG_FM_STEREO_HIGH_B | TDA9887_B_AUDIO_MUTE_ENABLE)

/************************** Макросы частот для инизиализайии ******************/
#define INIT_FREQ 15000 // 150.00 MHz

// Макросы для работы в режиме FM
#define FM_FREQ_LIMIT_L     6590   // 65.90 MHz Минимальная частота в диапазоне
#define FM_FREQ_LIMIT_H     10800  // 108.00 MHz Максимальная частота в диапазоне
#define FM_FREQ_TUNING_STEP 10     // Шаг перестройки 10 = 100kHz
#define FM_DEFAULT_FREQ     9280   // Частота по умолчанию
#define FM_STEREO           1      // 1-Stero, 0-Mono
#define FM_MUTE             0      // 1-mute, 0-no mute


// Структура статуса тюнера
typedef struct {
    unsigned char pll_lock    : 1;    /* FL бит: PLL заблокирован */
    unsigned char power_reset : 1;    /* POR бит: сброс по питанию */
    unsigned char agc_active  : 1;    /* AGC бит: внутренняя AGC активна */
    unsigned char stereo      : 1;    /* Стереосигнал (A2=1, A1=A0=0) */
    unsigned char signal_fm   : 1;    /* Уровень FM ПЧ высокий */
    unsigned char signal_video: 1;    /* Уровень видео ПЧ высокий */
    unsigned char afc_win     : 1;    /* AFC в окне (±12.5 кГц) */
    signed int    afc_offset;         /* Смещение AFC в кГц (-187...+187) */
} fm1216me_status_t;

// Статус тюнера
fm1216me_status_t fm1216me_status;

// Инициализации
void fm1216me_init(void);
// Настройка на частоту в FM диапазоне
void fm1216me_tune_fm(unsigned int freq, unsigned char is_stereo, unsigned char is_mute);
// Чтение статусов
void fm1216me_read_status(fm1216me_status_t *status);

#endif /* _FM1216ME_H_ */
