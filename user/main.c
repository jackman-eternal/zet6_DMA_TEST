/*
 �Ƕȴ�����ģ��: pa1
 ph��������pa3
 */
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include <string.h>
#include "delay.h"
#include "math.h"
#include "usart.h"
#include "adc.h"
#include "OLED_I2C.h"


float ADC_PH_Temp1;       //���ڱ���ת����ĵ�ѹֵ
float ADC_TU_Temp2;       //���ڱ���ת����ĵ�ѹֵ

int main(void)
{	
	
	delay_init(); 
	LED_Init(); 
    USART1_Config();
	ADC1_Multi_Init(); 

//  I2C_Configuration();
//	OLED_Init();

	while(1)
	{
	   ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
	   ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;
		
       delay_ms(2000);  		
  // printf("Value1= %f,Value2= %f\r\n",ADC_Value_Temp1,ADC_Value_Temp2)  ;
  // printf("{\"zhuo\":2.0, \"temperature\":3,\"NH3\":4,\"O2\":4,\"pH\":1.0}");		//ADC_Value_Temp1
	}
}

	
/*	
	while(1)
	{
		OLED_Fill(0xFF);//ȫ������
        delay_ms(2000); 
		for(i=0;i<5;i++)
		{
			OLED_ShowCN(22+i*16,0,i);//������ʾ����
		}
        delay_ms(2000); 
		OLED_ShowStr(0,3,"HelTec Automation",1);//����6*8�ַ�
		OLED_ShowStr(0,4,"Hello Tech",2);				//����8*16�ַ�
		delay_ms(2000); 
		OLED_CLS();//����
	}
*/
