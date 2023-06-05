#include "pic.h"


#define _XTAL_FREQ 180000000
#define FCY _XTAL_FREQ/2
#include <xc.h>
#include <libpic30.h>

void main(void)
{
    pic_init();

    while(1)
    {
        
    }
}