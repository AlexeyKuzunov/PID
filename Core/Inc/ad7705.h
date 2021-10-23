#ifndef __AD7705_H
#define __AD7705_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "spi.h"
#include "cmsis_os.h"

#define GAIN 1

/*
* register selection
*/
typedef enum
{
	REG_COMM = 0x0,			//communication register 8 bit
	REG_SETUP,				//setup register 8 bit
	REG_CLOCK,				//clock register 8 bit
	REG_DATA,				//data register 16 bit, contains conversion result
	REG_TEST,				//test register 8 bit, POR 0x0
	REG_NOP,				//no operation
	REG_OFFSET,				//offset register 24 bit
	REG_GAIN				// gain register 24 bit
} RegDef;


/*
* Выбор канала
*/
typedef enum
{
	CHN_AIN1 = 0x0,			//AIN1; calibration register pair 0
	CHN_AIN2,				//AIN2; calibration register pair 1
	CHN_FULL				//common; calibration register pair 0
} ChDef;

/*
* Усиление
*/
typedef enum
{
	GAIN_1		= 0x0,	//
	GAIN_2		= 0x1,	//
	GAIN_4		= 0x2, 	//
	GAIN_8		= 0x3,	//
	GAIN_16		= 0x4, 	//
	GAIN_32		= 0x5, 	//
	GAIN_64		= 0x6, 	//
	GAIN_128	= 0x7, 	//
} GainDef;

/*
* выбор частоты обновления выхода для устройства
*/
typedef enum
{
	RATE_20		= 0x0,	// 20Gz
	RATE_25		= 0x1,	//25Gz
	RATE_100	= 0x2, 	//100Gz
	RATE_200	= 0x3,	//200Gz
	RATE_50		= 0x4, 	//50Gz
	RATE_60		= 0x5, 	//60Gz
	RATE_250	= 0x6, 	//250Gz
	RATE_500	= 0x7	//500Gz
} RateDef;

/*
* Полярность
*/
typedef enum
{
	BIPOLAR = 0x0,
	UNIPOLAR = 0x1
} PolarityDef;

/*
*	operating mode options
*/
typedef enum
{
	MODE_NORMAL = 0x0,					//normal mode
	MODE_SELF_CAL = 0x1,				//self-calibration
	MODE_ZERO_SCALE_CAL = 0x2,			//zero-scale system calibration, POR 0x1F4000,
										//set FSYNC high before calibration, FSYNC low after calibration
	MODE_FULL_SCALE_CAL = 0x3			//full-scale system calibration, POR 0x5761AB, set FSYNC high
															//before calibration, FSYNC low after calibration
} ModeDef;

void ad7705_Init(ChDef ch, GainDef gain, RateDef rate, PolarityDef Polarity);
uint16_t readADResult(ChDef channel);

#ifdef __cplusplus
}
#endif

#endif /* __AD7705_H */
