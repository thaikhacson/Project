#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

#define SPI1_NSS 	GPIO_Pin_4
#define SPI1_SCK	GPIO_Pin_5
#define SPI1_MISO 	GPIO_Pin_6
#define SPI1_MOSI 	GPIO_Pin_7
#define SPI1_GPIO 	GPIOA

#define SPI2_NSS 	GPIO_Pin_12
#define SPI2_SCK	GPIO_Pin_13
#define SPI2_MISO 	GPIO_Pin_14
#define SPI2_MOSI 	GPIO_Pin_15
#define SPI2_GPIO 	GPIOB

void SPI_Config(SPI_TypeDef *SPIx);
uint8_t SPI_Tranfer(SPI_TypeDef *SPIx, GPIO_TypeDef *SPIx_GPIO, uint16_t SPIx_NSS, uint8_t data);

#endif