#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "delay.h"
#include "math.h"
#include "adc.h"

float ADC_PH_Temp1;       //���ڱ���ת����ĵ�ѹֵ
float ADC_TU_Temp2;       //���ڱ���ת����ĵ�ѹֵ
float ADC_Buffer[0xff] = {0.0}; //���ͻ�����

int main(void)
{	
	uint8_t  num = 0; 
	delay_init(); 
	LED_Init(); 
    USART1_Config();
	ADC1_Multi_Init(); 

	while(1)
	{
	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;
     if(num<0xff)
	   {
        ADC_Buffer[num] =  ADC_PH_Temp1;
		num++;
	   }
	 else
	 {
		 for(num=0;num<0xff;num++)
		 {
		   printf("ADC_Buffer[%d] = %f \r\n ",num,ADC_Buffer[num]);
         }	
         break ;		 
	 }		 
     		
//	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;	
//   delay_ms(1000);
//	 delay_ms(1000); 
//   printf("ADC_PH_Temp1 = %f  \r\n",ADC_PH_Temp1);  
//  printf("ADC_TU_Temp2 = %f  \r\n",ADC_TU_Temp2); 		
//  printf("Value1= %f,Value2= %f\r\n",ADC_Value_Temp1,ADC_Value_Temp2)  ;
//  printf("{\"zhuo\":2.0,\"temperature\":3,\"NH3\":4,\"O2\":4,\"pH\":%f}",ADC_PH_Temp1);		//ADC_Value_Temp1
	}
}

