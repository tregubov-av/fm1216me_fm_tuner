#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "usart_debug_board.h"
#include "usart.h"
#include "fm1216me.h"

void debug_print_usart(unsigned int freq) {
    printf("%c%c%c%c",0x1B,0x5B,0x32,0x4A);
    printf("********* FM1216ME DEBUG BOARD *********\n\r");
    printf("****************************************\n\r");
    printf("            FM FREQ: %u.%uMHz\n\r", freq / 100, freq % 100);
    printf("****************************************\n\r");
    printf("********** TUNER STATUS BIT ************\n\r");
    printf("POR:   %u\n\r", fm1216me_status.power_reset);
    printf("FL:    %u\n\r", fm1216me_status.pll_lock);
    printf("AGC:   %u\n\r", fm1216me_status.agc_active);
    printf("SOUND: %u\n\r", fm1216me_status.stereo);
    printf("************ IF STATUS BIT *************\n\r");
    printf("VIFL:  %u\n\r", fm1216me_status.signal_video);
    printf("FMIFL: %u\n\r", fm1216me_status.signal_fm);
    printf("AFC:   %d\n\r", fm1216me_status.afc_offset);
}
