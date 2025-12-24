#include <xc.h>
#include "usart.h"

/* передача одного байта */
#if PUTCH
void putch(unsigned char byte) {
        while(!TXIF)    // устанавливается, когда регистр пуст
                continue;
        TXREG = byte;
}
#endif

/* получение одного байта */
#if GETCH
unsigned char getch(void) {
        if(OERR){       // Перезапустить приемник при возникновении ошибки
                CREN = 0;
                CREN = 1;
        }
        while(!RCIF)    // устанавливается, когда регистр не пуст
                continue;
        return RCREG;
}
#endif

/*возвращает очередной символ, считанный с консоли, и выводит этот символ на экран*/
#if GETCHE
unsigned char getche(void) {
        unsigned char c;
        putch(c = getch());
        return c;
}
#endif
