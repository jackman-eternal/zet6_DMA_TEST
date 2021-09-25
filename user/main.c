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
    int i=0;
	delay_init(); 
	LED_Init(); 
    USART1_Config();
    ADC1_Init(); 
//    I2C_Configuration();
//	OLED_Init();

	while(1)
	{
		ADC_Value_Temp = (float)ADC_Value*3.3/4096;
        delay_ms(2000);
        printf("ADC_Value_Temp = %f \r\n",ADC_Value_Temp)  ;
  //   printf("{\"zhuo\":%f, \"temperature\":3,\"NH3\":4,\"O2\":4,\"pH\":1.0}",ADC_Value_Temp);		
	}
	
	
//	while(1)
//	{
//		OLED_Fill(0xFF);//ȫ������
//        delay_ms(2000); 
////		for(i=0;i<5;i++)
////		{
////			OLED_ShowCN(22+i*16,0,i);//������ʾ����
////		}
////        delay_ms(2000); 
////		OLED_ShowStr(0,3,"HelTec Automation",1);//����6*8�ַ�
////		OLED_ShowStr(0,4,"Hello Tech",2);				//����8*16�ַ�
////		delay_ms(2000); 
////		OLED_CLS();//����
//	}
}

