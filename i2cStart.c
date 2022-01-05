#include "config.h"
void i2cStart(void)
{
    SSPCON2bits.SEN = HI;   //Initiate Start condition on SDA and SCL pins. Automatically cleared by hardware.
    while(SSPCON2bits.SEN == HI); // Wait until SEN is low
    PIR1bits.SSP1IF = LO;   // SSPIF cleared in software
}
