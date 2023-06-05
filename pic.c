#include <p33CH64MP505S1.h>

#include "pic.h"
#include "pwm.h"

void pic_init(void)
{
    clock_init();
    pin_init();
    pwm_init();
    //msi_init();
}


void clock_init(void)
{
    
     CLKDIVbits.PLLPRE = 1;
    PLLFBDbits.PLLFBDIV = 100;
    PLLDIVbits.POST1DIV = 4;
    PLLDIVbits.POST2DIV = 1;
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(OSCCON | 0x01);
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK!= 1);
}

void pin_init(void)
{
    ////
    TRISC = 0;
    //////
    TRISCbits.TRISC10 = 0;
    TRISCbits.TRISC11 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
}