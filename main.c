#include "pic.h"
#include "msi.h"
#include "uart.h"

#define _XTAL_FREQ 180000000
#define FCY _XTAL_FREQ/2
#include <xc.h>
#include <libpic30.h>
#include <stdint.h>



int64_t max(int64_t a,int64_t b)
{
    if(a > b)
    {
        return a; 
    }
    return b;
}

int64_t min(int64_t a,int64_t b)
{
    if(a < b)
    {
        return a; 
    }
    return b;
}

#define P 5
//#define I -0.001f
#define I 0
#define D 1
#define TARGET 1900

void _ISR _MSIDTInterrupt(void)
{
    static uint16_t 
            count = 0,
            duty = 9999/2,
            ruiseki[100],
            passed_e = 0;
    static uint64_t ruisekiwa = 0;
    uint16_t current;
    current = fifo_pop();
    uint16_t e;
    e = (int16_t)TARGET - (int16_t)current;
    
    if(count > 99 && ruisekiwa == 0)
    {
        for(int i=0;i=count;i++)
            {
            ruisekiwa += ruiseki[i];
            }
        count = 0;
    }
    if(count > 99)
    {
        count = 0;
    }
    ruiseki[count] = e;
    
    int index;
    if(count == 99)
    {
        index = 0;
    }else
    {
        index = count +1 ;
    }
    ruisekiwa -= ruiseki[index];

    ruisekiwa += e;
    
    count++;
    int16_t pid;
    pid = P * e + D * (passed_e - e) + I * (uint16_t)(ruisekiwa/100);
    //duty -= pid;
    duty -= e;
    if(duty > 9000)
        duty = 9000;
    if(duty < 1000)
        duty = 1000;
    passed_e = e;
    PG1DC = (uint16_t)(9999 * 0.9);
    //PG1DC = duty;
    fifo_push(current);
    IFS8bits.MSIDTIF = 0;
}

void main(void)
{
    pic_init();
    
    
    
    //uint16_t duty = 4500; 
    TRISCbits.TRISC13 = 0;
    while(1)
    {
        LATCbits.LATC13 = 1;
        __delay_ms(200);
        uart1_write(0x55);
        uart1_write(0x55);
      //  __delay_ms(500);
      // fifo_push(0x55);
//        if(IFS8bits.MSIDTIF == 1)
//        {
//            IFS8bits.MSIDTIF = 0;
//            LATCbits.LATC5 = ~LATCbits.LATC5;
//        }
//        __delay_ms(50);
//        PG1DC = duty;
//        duty ++;
        
    }
}


