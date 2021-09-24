#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

extern __IO uint16_t ADC_Value;  //转换的电压值通过DMA传到SRAM

void ADC1_Init(void);

#endif

