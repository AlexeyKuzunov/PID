/*
 * ds18b20.c
 *
 *  Created on: 5 мая 2019 г.
 *      Author: istarik.ru
 */


#include "ds18b20.h"

#define MY_PORT DS18B20_GPIO_Port
#define MY_PIN  DS18B20_Pin

uint32_t DELAY_WAIT_CONVERT = DELAY_T_CONVERT;

void ds18b20_Init(DS18B20_Resolution resolution)
{
	setResolution(resolution);
}

void reset()
{
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_RESET);
	delay_us(DELAY_RESET);
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_SET);
	delay_us(DELAY_RESET);
}

uint8_t getDevider(DS18B20_Resolution resolution)
{
	uint8_t devider;
	switch (resolution)
	{
		case DS18B20_Resolution_9_bit:
			devider = 8;
			break;
		case DS18B20_Resolution_10_bit:
			devider = 4;
			break;
		case DS18B20_Resolution_11_bit:
			devider = 2;
			break;
		case DS18B20_Resolution_12_bit:
		default:
			devider = 1;
			break;
	}

	return devider;
}

void writeBit(uint8_t bit)
{
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_RESET);
	delay_us(bit ? DELAY_WRITE_1 : DELAY_WRITE_0);
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_SET);
	delay_us(bit ? DELAY_WRITE_1_PAUSE : DELAY_WRITE_0_PAUSE);
}

void writeByte(uint8_t data)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		writeBit(data >> i & 1);
		delay_us(DELAT_PROTECTION);
	}
}

uint8_t readBit()
{
	uint8_t bit = 0;
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_RESET);
	delay_us(DELAY_READ_SLOT);
	HAL_GPIO_WritePin(MY_PORT, MY_PIN, GPIO_PIN_SET);
	delay_us(DELAY_BUS_RELAX);
	bit = (HAL_GPIO_ReadPin(MY_PORT, MY_PIN) ? 1 : 0);
	delay_us(DELAY_READ_PAUSE);
	return bit;
}

int16_t readTemperature()
{
	
	int16_t data = 0;
	for (uint8_t i = 0; i < 16; i++)
	{
		data += (int16_t) readBit() << i;
	}

	//return  (uint16_t)(((float) data / 16.0) * 10.0);
	return data;
}

int16_t ds18b20_getTemperature()
{
	reset();
	writeByte(SKIP_ROM);
	writeByte(CONVERT_T);
	delay_us(DELAY_WAIT_CONVERT);

	reset();
	writeByte(SKIP_ROM);
	writeByte(READ_SCRATCHPAD);
	return readTemperature();
}

void setResolution(DS18B20_Resolution resolution)
{
	reset();
	writeByte(SKIP_ROM);
	writeByte(WRITE_SCRATCHPAD);
	writeByte(TH_REGISTER);
	writeByte(TL_REGISTER);
	writeByte(resolution);
	DELAY_WAIT_CONVERT = DELAY_T_CONVERT / getDevider(resolution);
}
