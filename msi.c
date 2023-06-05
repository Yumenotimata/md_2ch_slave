#include "msi.h"
#include <p33CH64MP505S1.h>


void msi_init(void)
{
    SI1FIFOCSbits.SRFEN = 1;//Enable Slave Read FIFO
    IEC8bits.MSIDIE = 1;//Enable FIFO Data Ready interrupt
}   

int fifo_pop(void)
{
    return SRMWFDATA;
}