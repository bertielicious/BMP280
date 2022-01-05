/* 
 * File:   configBMP280.h
 * Author: User
 *
 * Created on 03 January 2022, 17:37
 */

#ifndef CONFIGBMP280_H
#define	CONFIGBMP280_H

#define BMP280_WRITE_ADDR 0xEC      // write addess 0b11101100 lsb is R/W bit
#define BMP280_READ_ADDR 0xED       // read addess  0b11101101 lsb is R/W bit

const uint8_t CHIP_ID_REG = 0xD0;        // read only 8 bit register containing the chip ID, which is 0x58 (d'88)

const uint8_t RESET_REG = 0xE0;     // software reset for BMP280 achieved by writing 0xB6 to this register

const uint8_t STATUS_REG = 0xF3;    // bit 3 measuring[0] is auto set to 1 when conversion is running and back to 0 when results have been transfered to data registers 
                                    // bit 0 im_update[0] is set to 1 when NVM data are being copied to image registers and back to 0 when copying is complete.
                                    // STATUS_REG contains two bits which indicate the status of the BMP280

const uint8_t CTRL_MEAS_REG = 0xF4; // bit 7, 6, 5 osrs_t[2.0]  controls oversampling of temperature data
                                    // bit 4, 3, 2 osrs_p[2.0]  controls oversampling of pressure data
                                    // bit 1,0 mode[1.0] controls the power mode of the device

const uint8_t CONFIG_REG = 0xF5;    // bit 7, 6, 5 t_sb[2.0]  controls inactive duration of t_standby in normal mode
                                    // bit 4, 3, 2 t_sb[2.0]  controls time constant of IIR filter
                                    // bit 0 spi3w_en[0] enables 3-wire SPI interface when set

const uint8_t PRESS_MSB = 0xF7;    //contains raw 20-bit pressure measurement data, which is split over three 8-bit registers
                                   // press_msb[7:0] contains MSB part [19:12] of the raw pressure reading
const uint8_t PRESS_LSB = 0xF8;    //contains raw pressure measurement data, which is split over three 8-bit registers
                                   // press_msb[7:0] contains LSB part [11:4] of the raw pressure reading
const uint8_t PRESS_XLSB = 0xF9;    //bit 7, 6, 5, 4 contains raw  pressure measurement data, which is split over three 8-bit registers
                                   // press_msb[7:0] contains XLSB part [3:0] of the raw pressure reading

const uint8_t TEMP_MSB = 0xFA;    //contains raw 20-bit temperature measurement data, which is split over three 8-bit registers
                                  // temp_msb[7:0] contains MSB part [19:12] 
const uint8_t TEMP_LSB = 0xFB;    // contains raw temperature measurement data, which is split over three 8-bit registers
                                  // temp_msb[7:0] contains LSB part [11:4]
const uint8_t TEMP_XLSB = 0xFC;   // bit 7, 6, 5, 4 contains raw  temperature measurement data, which is split over three 8-bit registers
                                  // temp_msb[7:0] contains XLSB part [3:0] 

enum BMP280_MODE
{
  MODE_SLEEP  = 0x00,   // sleep mode = 0   // Three power modes, selected by bits [1:0] of CTRL_MEAS_REG
  MODE_FORCED = 0x01,   // forced mode = 1
  MODE_NORMAL = 0x03    // normal mode = 3
} ;

enum STANDBY_TIME
{
  STANDBY_0_5   =  0x00,  // standby time = 0.5 ms
  STANDBY_62_5  =  0x01,  // standby time = 62.5 ms
  STANDBY_125   =  0x02,  // standby time = 125 ms
  STANDBY_250   =  0x03,  // standby time = 250 ms
  STANDBY_500   =  0x04,  // standby time = 500 ms
  STANDBY_1000  =  0x05,  // standby time = 1000 ms
  STANDBY_2000  =  0x06,  // standby time = 2000 ms
  STANDBY_4000  =  0x07   // standby time = 4000 ms 
};

enum BMP280_SAMPLING
{
    SAMPLING_SKIPPED = 0x00,
    SAMPLING_X1      = 0x01,
    SAMPLING_X2      = 0x02,
    SAMPLING_X4      = 0x03,
    SAMPLING_X8      = 0x04,
    SAMPLING_X16     = 0x05,   
};

enum BMP280_FILTER
{
    FILTER_OFF = 0x00,
    FILTER_2   = 0x01,
    FILTER_4   = 0x02,
    FILTER_8   = 0x03,
    FILTER_16  = 0x04,
};

bool configBMP280(uint8_t mode, uint8_t tSampling, uint8_t pSampling, uint8_t filter, uint8_t standby);

#endif	/* CONFIGBMP280_H */

