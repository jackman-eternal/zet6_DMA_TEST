#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "delay.h"

//extern   __IO uint32_t ADC_ConValue;
//extern   __IO uint16_t ADC_Value;  //ת���ĵ�ѹֵͨ��DMA����SRAM
extern   __IO uint16_t ADC_Value[2]; //��ͨ��ģʽ����sram�ж�����������

void ADC1_Init(void);        //��ͨ��
void ADC1_Multi_Init(void);  //��ͨ��
void ADC12_Reg_Init(void);   //˫��ADC
#endif

//void conver(void);
/*
void conver(void)
{
	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;
	 PH = -5.7541*ADC_PH_Temp1+16.654;
	if(PH<=0.0)
      {
		  PH=0.0;
	  }
	if(PH>=14.0)
      {
	      PH=14.0;
	  }
	   TU=-865.68*ADC_TU_Temp2+3291.3;
	  if(TU<=0)
      {
	      TU=0;
	  }
	  if(TU>=3000)
      {
		  TU=3000;
	  }
	  
}
*/

