#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "delay.h"


//extern __IO uint16_t ADC_Value;  //转换的电压值通过DMA传到SRAM
extern   __IO uint16_t ADC_Value[2]; //多通道模式，在sram中定义两个变量
void ADC1_Init(void);

void ADC1_Multi_Init(void); 

#endif

