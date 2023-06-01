#include "msi.h"
#include <p33CH64MP505S1.h>

void msi_init(void)
{
    SI1FIFOCSbits.SRFEN = 1;//Enable Slave Read FIFO
}   

uint16_t fifo_pop(void)
{
    return SRMWFDATA;
}