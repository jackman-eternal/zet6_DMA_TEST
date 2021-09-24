/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   重现c库printf函数到usart端口
  ******************************************************************************
  */ 
  
#include "bsp_usart1.h"
uint8_t SendBuff[SENDBUFF_SIZE];

 /**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  无
  * @retval 无
  */
void USART1_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		
		/* config USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		/* USART1 GPIO config */
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);    
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
			
		/* USART1 mode config */
		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure); 
		USART_Cmd(USART1, ENABLE);
}


int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到USART1
int fgetc(FILE *f)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
void LED_Init(void)
{
  GPIO_InitTypeDef LED_GPIO; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  LED_GPIO.GPIO_Mode = GPIO_Mode_Out_PP ;
  LED_GPIO.GPIO_Pin  = GPIO_Pin_2;
  LED_GPIO.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA ,&LED_GPIO);  
   
  //GPIO_ResetBits(GPIOA,GPIO_Pin_2);
  GPIO_SetBits(GPIOA,GPIO_Pin_2);  	
}

void DMA_Config(void)
{
	DMA_InitTypeDef USART_DMA;
//	NVIC_InitTypeDef USART_DMA_NVIC;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //开启DMA时钟
	
	USART_DMA.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR) ;//串口数据寄存器地址
	USART_DMA.DMA_MemoryBaseAddr = (uint32_t )SendBuff ; //传输变量的指针
    USART_DMA.DMA_DIR = DMA_DIR_PeripheralDST ;  //设定外设为目标地址
    USART_DMA.DMA_BufferSize = SENDBUFF_SIZE ;  //传输数目
	USART_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;//外设地址不增
	USART_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable ;//内存地址自增
	USART_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ; //外设数据宽度
	USART_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ;  //存储器数据宽度
	USART_DMA.DMA_Mode = DMA_Mode_Normal ;       //传输一次
	USART_DMA.DMA_Priority = DMA_Priority_Medium ; //
	USART_DMA.DMA_M2M = DMA_M2M_Disable ; //
	DMA_Init(DMA1_Channel4 ,&USART_DMA); 
	DMA_Cmd(DMA1_Channel4,ENABLE);
	
// 	DMA_ITConfig(DMA1_Channel4 ,DMA_IT_TC ,ENABLE );//dma发送完成后产生中断 
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
//	USART_DMA_NVIC.NVIC_IRQChannel = DMA1_Channel4_IRQn ;
//	USART_DMA_NVIC.NVIC_IRQChannelPreemptionPriority =1;
//	USART_DMA_NVIC.NVIC_IRQChannelSubPriority =1;
//	USART_DMA_NVIC.NVIC_IRQChannelCmd =ENABLE ;
//	NVIC_Init(&USART_DMA_NVIC);

}
//void DMA1_Channel4_IRQHandler(void)
//{
//	if( DMA_GetFlagStatus(DMA1_FLAG_TC4 )==SET )
//	{
//		GPIO_SetBits(GPIOA,GPIO_Pin_2);
//        
//		DMA_ClearFlag(DMA1_FLAG_TC4); 
//		
//	}		
//}	
/*********************************************END OF FILE**********************/
