#ifndef __STM32L476R_NUCLEO_SPI_H
#define __STM32L476R_NUCLEO_SPI_H

#include "stm32l476xx.h"

void SPI1_Pins_Init(void);
void SPI1_Init(void);

void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive (uint8_t *data, uint32_t size);

#endif
