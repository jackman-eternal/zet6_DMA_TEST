#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "delay.h"
#include "math.h"
#include "adc.h"
//#include "ds18b20.h"

float ADC_PH_Temp1;       //用于保存转换后的电压值
float ADC_TU_Temp2;       //用于保存转换后的电压值
float ADC_Buffer[0xff] = {0.0}; //发送缓冲区

int main(void)
{	
	uint8_t  check = 1; 
	float  tem;
	delay_init(); 
	LED_Init(); 
    USART1_Config();
//	ADC1_Multi_Init(); 
	delay_us(10); 

	
	
	while(1)
	{
		
    
     delay_ms(10); 		
//	 ADC_PH_Temp1 = (float)ADC_Value[0]*3.3/4096;   		
//	 ADC_TU_Temp2 = (float)ADC_Value[1]*3.3/4096;	
//   delay_ms(1000);
//	 delay_ms(1000); 
//   printf("ADC_PH_Temp1 = %f  \r\n",ADC_PH_Temp1);  
//  printf("ADC_TU_Temp2 = %f  \r\n",ADC_TU_Temp2); 		
//  printf("Value1= %f,Value2= %f\r\n",ADC_Value_Temp1,ADC_Value_Temp2)  ;
//  printf("{\"zhuo\":2.0,\"temperature\":3,\"NH3\":4,\"O2\":4,\"pH\":%f}",ADC_PH_Temp1);		//ADC_Value_Temp1
		
		
	}
}

