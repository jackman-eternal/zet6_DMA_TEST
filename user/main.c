/************************************************************************************
 * 文件名  ：main.c
 * 描述    ：        
 * 硬件连接：
 * LCD1602:RS -> PA11; RW -> PA12; E -> PA15;
 *         D0~D7 -> PB3~PB10
 * 浊度传感器模块: VCC -> 5V; GND -> GND; AO -> PA2;
 *
 * 功能描述：测量浊度值液晶显示(ADC1、PA2、DMA方式读取)；
             串口接收测量所得的浊度值（波特率115200）；
 *           可连接上位机显示浊度值；

**********************************************************************************/
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include <string.h>
#include "delay.h"
#include "math.h"
#include "usart.h"
#include "adc.h"
#include "OLED_I2C.h"


float ADC_Value_Temp;       //用于保存转换后的电压值

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
//		OLED_Fill(0xFF);//全屏点亮
//        delay_ms(2000); 
////		for(i=0;i<5;i++)
////		{
////			OLED_ShowCN(22+i*16,0,i);//测试显示中文
////		}
////        delay_ms(2000); 
////		OLED_ShowStr(0,3,"HelTec Automation",1);//测试6*8字符
////		OLED_ShowStr(0,4,"Hello Tech",2);				//测试8*16字符
////		delay_ms(2000); 
////		OLED_CLS();//清屏
//	}
}

