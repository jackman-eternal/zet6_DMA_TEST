/*
 �Ƕȴ�����ģ��: pa3
 ph��������pa1
 */
 
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include <string.h>
#include "delay.h"
#include "math.h"
#include "usart.h"
#include "adc.h"
#include "OLED_I2C.h"


float ADC_PH_Temp1,PH;       //���ڱ���ת����ĵ�ѹֵ
float ADC_TU_Temp2,TU;       //���ڱ���ת����ĵ�ѹֵ
void conver(void);

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
     conver();		
     delay_ms(1000);
     printf("ADC_PH_Temp1 = %f , PH = %f \r\n",ADC_PH_Temp1,PH);  
     printf("ADC_TU_Temp2 = %f , TU = %f \r\n",ADC_TU_Temp2,TU); 		
  // printf("Value1= %f,Value2= %f\r\n",ADC_Value_Temp1,ADC_Value_Temp2)  ;
  // printf("{\"zhuo\":2.0, \"temperature\":3,\"NH3\":4,\"O2\":4,\"pH\":1.0}");		//ADC_Value_Temp1
	}
}

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
