#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "delay.h"


//extern __IO uint16_t ADC_Value;  //ת���ĵ�ѹֵͨ��DMA����SRAM
extern   __IO uint16_t ADC_Value[2]; //��ͨ��ģʽ����sram�ж�����������
void ADC1_Init(void);

void ADC1_Multi_Init(void); 

#endif

