#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
#include<string.h>

#define SENDBUFF_SIZE 30


void USART1_Config(void);
void LED_Init(void);
void DMA_Config(void);

#endif 
