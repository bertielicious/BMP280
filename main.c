/*
 * File:   main.c
 * Author: User
 *
 * Created on 06 December 2021, 14:11
 */


#include "config.h"
#include "configOsc.h"
#include "configPorts.h"
#include "configEUSART.h"
#include "configBaud.h"
#include "configI2C.h"
#include "i2cStart.h"
#include "i2cWrite.h"
#include "i2cRead.h"
#include "i2cReStart.h"
#include "i2cStop.h"
#include "oLedWrite.h"
#include "configSH1106.h"
#include "setPageAddress.h"
#include "setColumnAddress.h"
#include "clearSH1106.h"
#include "selectDigit.h"
#include "split0To99.h"
#include "write8x8ToOled.h"
#include "configBMP280.h"
void main(void) 
{
    splitUchar result;  // create a local structure variable (type splitUchar, defined in config.h))to receive the struct return num from split0To99 function
                        // this enables us to return two values from the split0To99 function, num.tens and num.units
    uchar id = 0;       // variable to hold the read value returning by the function uchar i2cRead() once having read register 'id' of the BMP280 (always contains '88')
    uchar  i, j;        // loop counters for the for loops
    int *number;        // pointer to int to hold the returned address of the 8x8
   // uchar pageAddress;
    
    configOsc();
    configPorts();
    configEUSART();
    configBaud();
    configI2C();
    printf("Hola\n");
    configSH1106();
    __delay_ms(100);
    
    clearSH1106();          // writes 0x00 to each column from 0 to 131, of each page 0 to 7 of the oled display, to clear random data held in display RAM
    
    
    setPageAddress(2);      // set horizontal page address to page 0 (top line of display = page 0, bottom line is page 7))
    // oLedWrite(SH1106_WRITE_ADDRESS_COMMAND, COMMAND_ONE_CTRL_BYTE_ONLY_DATA_BYTES_TO_FOLLOW, pageAddress);
    setColumnAddress(36);   // set vertical column address to 36 (column address goes from 0 to 131)
    
    for(j = 0; j < 10; j++) // test display of writing single number 0 - 9 to the display
    {
        write8x8ToOled(j, *number);
      
    }
    /***************read device id from BMP280************************/
    i2cStart();     // issue start condition to begin i2c exchange
    i2cWrite(0xec); // send slave address write mode
    i2cWrite(0xd0); // send device id register address
    i2cReStart();   // repeated start condition generated
    i2cWrite(0xed); // send slave address read mode
    id = i2cRead(); // read the data byte from the slave (id = 0x58 = d'88)
    i2cStop();      // issue the stop condition so that master can communicate to another i2c device on the bus
    
    
    result = split0To99(id);    // result contains num.tens and num.units for whatever number (id) was, (in this case d'88, the id number for the BMP280)
   
    setPageAddress(7);
   
    setColumnAddress(110);
    
    number = selectDigit(result.tens);// pass result.tens to function selectDigit, which returns the address of the 1st element of the selected 8x8 bit map array array corresponding to result.tens
    for (i = 0; i < 8; i++)// write columns 0 to 7 of the bit map array to the oLed display, incrementing the pointer on each loop to pass to the next element of the array
    {
        oLedWrite(SH1106_WRITE_ADDRESS_COMMAND, DISPLAY_DATA_ONE_CTRL_BYTE_DATA_BYTES_TO_FOLLOW, *number);
        number++;
    }
    number = selectDigit(result.units);// same functionality as above , but directed at result.units
    for (i = 0; i < 8; i++)
    {
        oLedWrite(SH1106_WRITE_ADDRESS_COMMAND, DISPLAY_DATA_ONE_CTRL_BYTE_DATA_BYTES_TO_FOLLOW, *number);
        number++;
    }
    
    while(1)
    {
        DIAGNOSTIC_LED = HI;
        __delay_ms(100);
        DIAGNOSTIC_LED = LO;
        __delay_ms(100);
    }
}
