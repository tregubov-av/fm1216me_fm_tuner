#include <xc.h>
#include "fm1216me.h"
#include "i2c_master.h"

// Инициализация тюнера
// Сначала настраиваем на TV 150 МГц (High Band)
void fm1216me_init(){
    i2c_master_start();
    i2c_master_write(FM1216ME_FM_DIV_HIGH_50KHZ(INIT_FREQ));
    i2c_master_write(FM1216ME_FM_DIV_LOW_50KHZ(INIT_FREQ));
    i2c_master_write(FM1216ME_CB_TV_NORMAL);
    i2c_master_write(FM1216ME_BB_HIGH_BAND);
    i2c_master_write(FM1216ME_AB_RECOMMENDED_TV);
    i2c_master_stop();


    i2c_master_start();
    i2c_master_write(TDA9887_I2C_ADDR);
    i2c_master_write(TDA9887_SUBADDR);
    i2c_master_write(TDA9887_B_AUDIO_MUTE_ENABLE);
    i2c_master_write(TDA9887_CONFIG_BG_BYTE_C);
    i2c_master_write(TDA9887_CONFIG_BG_BYTE_E);
    i2c_master_stop();
}

// Настройка на частоту в FM диапазоне
void fm1216me_tune_fm(unsigned int f, unsigned char is_stereo, unsigned char is_mute){
    i2c_master_start();
    i2c_master_write(FM1216ME_I2C_ADDR);
    i2c_master_write(FM1216ME_FM_DIV_HIGH_50KHZ(f));
    i2c_master_write(FM1216ME_FM_DIV_LOW_50KHZ(f));
    i2c_master_write(FM1216ME_CB_FM_NORMAL);
    if (is_stereo) {
        i2c_master_write(FM1216ME_BB_FM_STEREO);
    } else {
        i2c_master_write(FM1216ME_BB_FM_MONO);
    }
    i2c_master_write(FM1216ME_AB_RECOMMENDED_FM);
    i2c_master_stop();


    i2c_master_start();
    i2c_master_write(TDA9887_I2C_ADDR);
    i2c_master_write(TDA9887_SUBADDR);
    if (is_stereo && !is_mute) {
        i2c_master_write(TDA9887_CONFIG_FM_STEREO_HIGH_B);
        i2c_master_write(TDA9887_CONFIG_FM_STEREO_HIGH_C);
        i2c_master_write(TDA9887_CONFIG_FM_STEREO_HIGH_E);
    } else if (!is_stereo && !is_mute) {
        i2c_master_write(TDA9887_CONFIG_FM_MONO_NORM_B);
        i2c_master_write(TDA9887_CONFIG_FM_MONO_NORM_C);
        i2c_master_write(TDA9887_CONFIG_FM_MONO_NORM_E);
    } else {
        i2c_master_write(TDA9887_B_AUDIO_MUTE_ENABLE);
    }
    i2c_master_stop();
}

// Чтение статусов
void fm1216me_read_status(fm1216me_status_t *status){
    unsigned char sb, sr;

    i2c_master_start();
    i2c_master_write(FM1216ME_I2C_ADDR|0x1);
    sb = i2c_master_read(I2C_NACK);
    i2c_master_stop();

    i2c_master_start();
    i2c_master_write(TDA9887_I2C_ADDR|0x1);
    sr = i2c_master_read(I2C_NACK);
    i2c_master_stop();

    /* Заполнение структуры статуса */
    // FM1216ME TUNER
    status->pll_lock     = (sb & 0x40) ? 1 : 0;     /* FL бит (бит 6) */
    status->power_reset  = (sb & 0x80) ? 1 : 0;     /* POR бит (бит 7) */
    status->agc_active   = (sb & 0x08) ? 1 : 0;     /* AGC бит (бит 3) */
    /* Стерео: A2=1, A1=0, A0=0 (биты 2,1,0) */
    status->stereo       = ((sb & 0x04) && !(sb & 0x03)) ? 1 : 0;
    // TDA9887 IF
    status->signal_fm    = (sr & 0x20) ? 1 : 0;     /* FMIFL бит (бит 5) */
    status->signal_video = (sr & 0x40) ? 1 : 0;     /* VIFL бит (бит 6) */
    status->afc_win      = (sr & 0x80) ? 1 : 0;     /* AFCWIN бит (бит 7) */

    /* Извлечение битов AFC: D4 D3 D2 D1 (биты 4,3,2,1) */
    unsigned char afc_bits = (sr >> 1) & 0x0F; /* Сдвигаем вправо на 1, берем 4 бита */

    /* Расшифровка AFC смещения */
    switch(afc_bits) {
        /* Отрицательные смещения (F_VIF < F0) */
        case 0x07: /* 0111 */ status->afc_offset = -188; break; /* ≤ -187.5 kHz */
        case 0x06: /* 0110 */ status->afc_offset = -163; break; /* -162.5 kHz */
        case 0x05: /* 0101 */ status->afc_offset = -138; break; /* -137.5 kHz */
        case 0x04: /* 0100 */ status->afc_offset = -113; break; /* -112.5 kHz */
        case 0x03: /* 0011 */ status->afc_offset = -88; break;  /* -87.5 kHz */
        case 0x02: /* 0010 */ status->afc_offset = -63; break;  /* -62.5 kHz */
        case 0x01: /* 0001 */ status->afc_offset = -38; break;  /* -37.5 kHz */
        case 0x00: /* 0000 */ status->afc_offset = -13; break;  /* -12.5 kHz */

        /* Положительные смещения (F_VIF > F0) */
        case 0x0F: /* 1111 */ status->afc_offset = 13; break;   /* +12.5 kHz */
        case 0x0E: /* 1110 */ status->afc_offset = 38; break;   /* +37.5 kHz */
        case 0x0D: /* 1101 */ status->afc_offset = 63; break;   /* +62.5 kHz */
        case 0x0C: /* 1100 */ status->afc_offset = 88; break;   /* +87.5 kHz */
        case 0x0B: /* 1011 */ status->afc_offset = 113; break;  /* +112.5 kHz */
        case 0x0A: /* 1010 */ status->afc_offset = 138; break;  /* +137.5 kHz */
        case 0x09: /* 1001 */ status->afc_offset = 163; break;  /* +162.5 kHz */
        case 0x08: /* 1000 */ status->afc_offset = 188; break;  /* ≥ +187.5 kHz */

        default: status->afc_offset = 0; break;
    }
}
