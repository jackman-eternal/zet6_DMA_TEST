#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

#define SENDBUFF_SIZE 30

extern uint8_t SendBuff[SENDBUFF_SIZE];
void USART1_Config(void);
void LED_Init(void);
void DMA_Config(void);
void MTM_DMA_Config(void);
uint8_t BufferCom(const  uint8_t* pBuffer, uint8_t *pBuffer1,uint16_t BufferLength );

#endif 
