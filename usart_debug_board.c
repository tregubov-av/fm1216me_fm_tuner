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
#include "usart_debug_board.h"
#include "usart.h"
#include "fm1216me.h"

#if PRINTF_OR_PUTCH_USE
#include <stdio.h>
#endif

#if PRINTF_OR_PUTCH_USE
void debug_print_usart(unsigned int freq) {
    // Очистка терминала TODO работает только в minicom
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
    printf("****************************************\n\r");
}
#endif

#if !PRINTF_OR_PUTCH_USE
void debug_print_usart(unsigned int freq) {
    // Очистка терминала (ESC [ 2 J)
    putch(0x1B);
    putch(0x5B);
    putch(0x32);
    putch(0x4A);

    PUTSTR("********* FM1216ME DEBUG BOARD *********\n\r"
           "****************************************\n\r"
           "            FM FREQ: ");
    PUTNUM(freq / 100);
    putch('.');
    PUTNUM(freq % 100);
    PUTSTR("MHz\n\r"
           "****************************************\n\r"
           "********** TUNER STATUS BIT ************\n\r");

    PUTSTR("POR:   "); PUTNUM(fm1216me_status.power_reset); PUTSTR("\n\r");
    PUTSTR("FL:    "); PUTNUM(fm1216me_status.pll_lock);   PUTSTR("\n\r");
    PUTSTR("AGC:   "); PUTNUM(fm1216me_status.agc_active); PUTSTR("\n\r");
    PUTSTR("SOUND: "); PUTNUM(fm1216me_status.stereo);     PUTSTR("\n\r");

    PUTSTR("************ IF STATUS BIT *************\n\r");
    PUTSTR("VIFL:  "); PUTNUM(fm1216me_status.signal_video); PUTSTR("\n\r");
    PUTSTR("FMIFL: "); PUTNUM(fm1216me_status.signal_fm);    PUTSTR("\n\r");
    PUTSTR("AFC:   "); PUTNUM_SIGNED(fm1216me_status.afc_offset); PUTSTR("\n\r");

    PUTSTR("****************************************\n\r");
}
#endif
