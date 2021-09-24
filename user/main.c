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



int main(void)
{	
   
	delay_init(); 
	LED_Init(); 
    USART1_Config();


	while(1);
}

