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



int main(void)
{	
    uint8_t status;
	delay_init(); 
	LED_Init(); 
    USART1_Config();
	//DMA_Config();
	MTM_DMA_Config();

//  while(1)
//	{	
//      // printf("USART1->DR = %x  \r\n",(uint32_t)&(USART1->DR)); 
//		delay_ms(1000);
//	}	
	status = BufferCom(SendBuff_FLASH,SendBuff, SENDBUFF_SIZE);
    if(status == 1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
	
	while(1);
}

