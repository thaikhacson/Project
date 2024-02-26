#include "SPI.h"

void SPI_Config(SPI_TypeDef *SPIx){
	SPI_InitTypeDef SPI_InitStruct;
	
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; 
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_LSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(SPIx, &SPI_InitStruct);
	SPI_Cmd(SPIx, ENABLE);
}

uint8_t SPI_Tranfer(SPI_TypeDef *SPIx, GPIO_TypeDef *SPIx_GPIO, uint16_t SPIx_NSS, uint8_t data) {
		//Receive
		uint8_t temp;
		while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == 1){}
    temp = (uint8_t)SPI_I2S_ReceiveData(SPIx);
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == 0);
	
		//Send
    GPIO_WriteBit(SPIx_GPIO, SPIx_NSS, Bit_RESET);
    SPI_I2S_SendData(SPIx, data);
    while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == 0);
    GPIO_WriteBit(SPIx_GPIO, SPIx_NSS, Bit_SET);
	
		return temp;
}
