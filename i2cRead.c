#include "config.h"
#include "i2cStop.h"
uchar i2cRead(void)
{
    uchar readByte = 0;
    SSPCON2bits.RCEN = HI;              // User sets the RCEN bit of the SSPCON2 register and the master clocks in a byte from the slave
      
    while(SSPSTATbits.BF == LO);        // wait until the data byte has been transmitted from slave to master, RCEN is auto cleared after bit 0 of the data byte received
                                        // After the 8th falling edge of SCL, SSPIF and BF are set
    PIR1bits.SSP1IF = LO;               // Master clears SSPIF and reads the received byte from SSPUF, clears BF.
    readByte = SSP1BUF;                 //copy received data into variable 'readByte'
    
    
    SSP1CON2bits.ACKDT = HI;    // Master sets ACK value sent to slave in ACKDT bit of the SSPCON2 register and initiates the ACK by setting the ACKEN bit
    SSP1CON2bits.ACKEN = HI;    // Masters ACK is clocked out to the slave and SSPIF is set
    while(SSP1CON2bits.ACKEN == HI); //wait for NACK to complete
    PIR1bits.SSP1IF = LO;       // User clears SSPIF
                                // Master sends a not ACK or Stop to end communication.
    return readByte;            // return received byte to calling function/ variable
}
