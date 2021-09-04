

#include "ad7705.h"
#include <stdio.h>
#include "spi.h"

//extern uint8_t DRDY;

uint8_t SPI1_SendByte(uint8_t data);

//Communication Register
//   7   6   5   4   3   2   1   0
//
void setNextOperation(RegDef reg, ChDef channel, uint8_t readWrite){
	uint8_t r = 0;
	r = reg << 4 | readWrite << 3 | channel;
	SPI1_SendByte(r);
	}

//Clock Register
//   7      6       5        4        3        	2      1      	9
//ZERO(0) ZERO(0) ZERO(0) CLKDIS(0) CLKDIV(0)	CLK(1)	FS1(0)	FS0(1)
void writeClockRegister(uint8_t CLKDIS, uint8_t CLKDIV, RateDef outputUpdateRate){
	uint8_t r = CLKDIS << 4 | CLKDIV << 3 | outputUpdateRate;
	SPI1_SendByte(r);
}
	 
//Setup Register
//  7     6     5     4     3      2      1      0
//MD10) MD0(0) G2(0) G1(0) G0(0) B/U(0) BUF(0) FSYNC(1)
void writeSetupRegister(ModeDef operationMode, GainDef gain, PolarityDef unipolar, uint8_t buffered, uint8_t fsync){
	uint8_t r = operationMode << 6 | gain << 3 | unipolar << 2 | buffered << 1 | fsync;
	SPI1_SendByte(r);
}

uint16_t readADResult(ChDef channel){
	uint8_t dataH=0;
	uint8_t dataL=0;
	setNextOperation(REG_DATA, channel, 1);
			dataH = SPI1_SendByte(0x00);
			dataL = SPI1_SendByte(0x00);
			return (dataH<<8 | dataL);	
}

void AD770Xreset() {
	HAL_GPIO_WritePin(AD_RESET_GPIO_Port,AD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(5);
	for(uint8_t i=0;i<5;i++)
	{
		SPI1_SendByte(0xff);
  }
	HAL_Delay(1);
}	
	
void ad7705_Init(ChDef ch, GainDef gain, RateDef rate, PolarityDef Polarity){
	AD770Xreset();
	setNextOperation(REG_CLOCK, ch, 0);
	writeClockRegister(0, 0, rate);
	setNextOperation(REG_SETUP, ch, 0);
	writeSetupRegister(MODE_SELF_CAL, gain, Polarity, 0, 1);
	setNextOperation(REG_SETUP, ch, 0);
	writeSetupRegister(MODE_SELF_CAL, gain, Polarity, 0, 0);
}

uint8_t SPI1_SendByte(uint8_t data)
{
	uint8_t rxdata;
    HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1,&data,&rxdata,1,100);
    HAL_GPIO_WritePin(AD_CS_GPIO_Port,AD_CS_Pin,GPIO_PIN_SET);
    return rxdata;
}

