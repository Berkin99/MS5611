/*
 *  ms5611.h
 *
 *  Created on: Oct 3, 2023
 *  Author: BerkN
 *
 *  TE Connectivity MS5611 sensor driver. 
 *  Platform independent C API. 
 *  Calibration and raw data transformation.
 *  SPI or I2C based communication.
 *  Adaptive to changed settings.
 *
 *  Updates and bug reports :  @ https://github.com/Berkin99/MS5611
 *
 *  03.11.2023 : Created for STM32 HAL library.
 *  05.01.2024 : Test Connection Routine Change.
 *  07.04.2024 : Generic I2C functions used.
 *  04.10.2024 : Object system.
 *
 *  References:
 *  [0] ENG_DS_MS5611-01BA03_B3.pdf (Datasheet)
 *
 */

#ifndef MS5611_H_
#define MS5611_H_

#include <stdint.h>

#define MS5611_OK             0
#define MS5611_ERROR          1

#define MS5611_I2C_ADDRESS    0x77

typedef enum{
    MS5611_INTF_SPI,
    MS5611_INTF_I2C
}MS5611_Intf_e;

typedef enum
{
    MS5611_ULTRA_LOW_POWER  = 0,        /* 1 ms conversion time. */
    MS5611_LOW_POWER,                   /* 2 ms conversion time. */
    MS5611_STANDARD,                    /* 3 ms conversion time. */
    MS5611_HIGH_RES,                    /* 5 ms conversion time. */
    MS5611_ULTRA_HIGH_RES,              /* 10 ms conversion time.*/
} MS5611_OSRate_t;                      /* Output Sampling Rate  */

typedef struct MS5611_Data_s{
    int32_t temperature;  /* celcius * 10^2 */
    int32_t pressure;     /* mbar * 10^2 */
}MS5611_Data_t;

typedef int8_t (*MS5611_Read_t)(void* intf, uint8_t reg, uint8_t *pRxData, uint8_t len);
typedef int8_t (*MS5611_Write_t)(void* intf, uint8_t reg, const uint8_t *pTxData, uint8_t len);
typedef void   (*MS5611_Delay_t)(uint32_t ms); /* Delay Microseconds function pointer */

typedef struct MS5611_Config_s
{
    MS5611_OSRate_t osRate; /* Output Sampling Rate */
    uint8_t ct;             /* Conversion Time */
    float C[7];             /* Coefficients */
}MS5611_Config_t;

typedef struct MS5611_Device_s
{
    void* intf;
    MS5611_Intf_e intf_type;
    MS5611_Read_t read;
    MS5611_Write_t write;
    MS5611_Delay_t delay;
    MS5611_Config_t config;
}MS5611_Device_t;

MS5611_Device_t MS5611_NewDevice(void* intf, MS5611_Intf_e intf_type, MS5611_Read_t readf, MS5611_Write_t writef, MS5611_Delay_t delayf);
int8_t MS5611_Init(MS5611_Device_t* dev);
int8_t MS5611_Test(MS5611_Device_t* dev);
void MS5611_Reset(MS5611_Device_t* dev);
void MS5611_InitConstants(MS5611_Device_t* dev, int8_t mathMode);
int8_t MS5611_PROM(MS5611_Device_t* dev);
uint16_t MS5611_ReadPROM(MS5611_Device_t* dev, uint8_t reg);
void MS5611_SetOSRate(MS5611_Device_t* dev, MS5611_OSRate_t osr);
MS5611_OSRate_t MS5611_GetOSRate(MS5611_Device_t* dev);
int8_t MS5611_GetData(MS5611_Device_t* dev, float* pTemp, float* pPress);
void MS5611_Convert(MS5611_Device_t* dev);
int8_t MS5611_AdcRead(MS5611_Device_t* dev, uint32_t* buffer);
MS5611_Data_t MS5611_RawDataProcess(MS5611_Device_t* dev, uint32_t D1 , uint32_t D2, int8_t compensation);

#endif /* MS5611_H_ */
