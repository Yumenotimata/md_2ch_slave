#include <p33CH64MP505S1.h>

#include "pwm.h"

void pwm_init(void)
{
    PCLKCON = 0x00;//PWM Master Clock Selection is Fosc = 200MHz
    PG1CONLbits.CLKSEL = 0b10;//PWM Generator uses Fosc
    PG1CONLbits.MODSEL = 0b010;//PWM Mode is Independent Edge PWM mode
    PG1IOCONHbits.PENH = 1;//Enable PWM1H Output Port 
    PG1IOCONHbits.PENL = 1;//Enable PWM1L Output Port
    PG1EVTLbits.UPDTRG = 0b01;//A write of the PGDC register automatically sets the UPDATE bit
    PG1DC = 0xFFFF/2;//Duty cycle
    PG1PER = 0x270F;//Duty Phase
    PG1DTL = 0x0000;//Dead time
    PG1DTH = 0x0000;
    PG1CONLbits.ON = 1;//Enable PWM Generator
}
