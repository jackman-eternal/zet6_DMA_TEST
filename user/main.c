/************************************************************************************
 * �ļ���  ��main.c
 * ����    ��        
 * Ӳ�����ӣ�
 * LCD1602:RS -> PA11; RW -> PA12; E -> PA15;
 *         D0~D7 -> PB3~PB10
 * �Ƕȴ�����ģ��: VCC -> 5V; GND -> GND; AO -> PA2;
 *
 * ���������������Ƕ�ֵҺ����ʾ(ADC1��PA2��DMA��ʽ��ȡ)��
             ���ڽ��ղ������õ��Ƕ�ֵ��������115200����
 *           ��������λ����ʾ�Ƕ�ֵ��

**********************************************************************************/
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include <string.h>
#include "delay.h"
#include "math.h"
#include "usart.h"
#include "adc.h"
#include "OLED_I2C.h"


float ADC_Value_Temp;       //���ڱ���ת����ĵ�ѹֵ

int main(void)
{	
   
	delay_init(); 
	LED_Init(); 
    USART1_Config();
    ADC1_Init(); 
    I2C_Configuration();
	OLED_Init();
	
	while(1)
	{
		ADC_Value_Temp = (float)ADC_Value/4096*3.3;
        delay_ms(10);
        printf("ADC_Value_Temp = %f \r\n",ADC_Value_Temp)  ;		
	}
}

