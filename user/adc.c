#include "adc.h"

// __IO uint16_t ADC_Value;  //单通道模式，ADC数据寄存器使用低16位
__IO uint16_t ADC_Value[2]; //多通道模式，在sram中定义两个变量

void ADC1_Init(void)
{
	GPIO_InitTypeDef ADC1_GPIO;
	ADC_InitTypeDef  ADC1_Config;
	DMA_InitTypeDef  ADC1_DMA;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOA ,ENABLE );
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	ADC1_GPIO.GPIO_Mode = GPIO_Mode_AIN;
    ADC1_GPIO.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_Init(GPIOA,&ADC1_GPIO);
		
	ADC1_DMA.DMA_BufferSize = 1;  
	ADC1_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ; //外设为数据源
	ADC1_DMA.DMA_M2M = DMA_M2M_Disable;  
    ADC1_DMA.DMA_MemoryBaseAddr = (uint32_t)&ADC_Value;
	ADC1_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;//16位
	ADC1_DMA.DMA_MemoryInc  = DMA_MemoryInc_Disable ;    //内存地址固定（地址只有一个）
	ADC1_DMA.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); 
	ADC1_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    ADC1_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;  //外设地址固定（地址只有一个）
    ADC1_DMA.DMA_Priority = DMA_Priority_High ; 
    ADC1_DMA.DMA_Mode = DMA_Mode_Circular ;//循环传输	
	DMA_Init(DMA1_Channel1 ,&ADC1_DMA);
    DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC1_Config.ADC_Mode = ADC_Mode_Independent ;
	ADC1_Config.ADC_ScanConvMode =DISABLE ;
	ADC1_Config.ADC_ContinuousConvMode  =ENABLE ;
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =1;
	ADC_Init(ADC1 ,&ADC1_Config);
    ADC_ITConfig(ADC1,ADC_IT_EOC, ENABLE); 
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1 ,1,ADC_SampleTime_55Cycles5  );//55.5个采样周期
    ADC_DMACmd(ADC1 ,ENABLE );    //ADC提交DMA请求
    ADC_Cmd(ADC1 ,ENABLE );    	
     	 
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); 	
}

void ADC1_Multi_Init(void)  //开启PA0和PA3
{
	GPIO_InitTypeDef ADC1_GPIO;
	ADC_InitTypeDef  ADC1_Config;
	DMA_InitTypeDef  ADC1_DMA;
	NVIC_InitTypeDef ADC1_NVIC;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOA ,ENABLE );
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	ADC1_GPIO.GPIO_Mode = GPIO_Mode_AIN;
    ADC1_GPIO.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_3 ;
    GPIO_Init(GPIOA,&ADC1_GPIO);
	
	ADC1_NVIC.NVIC_IRQChannel = ADC1_2_IRQn;
    ADC1_NVIC.NVIC_IRQChannelPreemptionPriority  = 1;
    ADC1_NVIC.NVIC_IRQChannelSubPriority  = 1;
    ADC1_NVIC.NVIC_IRQChannelCmd  = ENABLE ;
    NVIC_Init(&ADC1_NVIC); 	
	
	ADC1_DMA.DMA_BufferSize = 2;  
	ADC1_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ; //外设为数据源
	ADC1_DMA.DMA_M2M = DMA_M2M_Disable;  
    ADC1_DMA.DMA_MemoryBaseAddr =(uint32_t)ADC_Value ;//(uint32_t)&ADC_Value;
	ADC1_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord ;//16位
	ADC1_DMA.DMA_MemoryInc  = DMA_MemoryInc_Enable ;    //内存地址固定（地址只有一个）
	ADC1_DMA.DMA_PeripheralBaseAddr = (uint32_t)(&(ADC1->DR)); 
	ADC1_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    ADC1_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;  //外设地址固定（地址只有一个）
    ADC1_DMA.DMA_Priority = DMA_Priority_High ; 
    ADC1_DMA.DMA_Mode = DMA_Mode_Circular ;//循环传输	
	DMA_Init(DMA1_Channel1 ,&ADC1_DMA);
   // DMA_Cmd(DMA1_Channel1,ENABLE);
	DMA_Cmd(DMA1_Channel1,DISABLE);
	
	ADC1_Config.ADC_Mode = ADC_Mode_Independent ;
	ADC1_Config.ADC_ScanConvMode =ENABLE ;//DISABLE ;多通道使能
	ADC1_Config.ADC_ContinuousConvMode  =ENABLE ;
	ADC1_Config.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC1_Config.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC1_Config.ADC_NbrOfChannel =2;
	ADC_Init(ADC1,&ADC1_Config);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	//每一个通道都要设置采样顺序和时间
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1 ,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3 ,2,ADC_SampleTime_55Cycles5);
  //  ADC_DMACmd(ADC1 ,ENABLE );    //ADC提交DMA请求
    ADC_Cmd(ADC1 ,ENABLE );  
       	 
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void ADC1_2_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC1 ,ADC_IT_EOC)==SET)
	{
//		ADC_Value = (uint16_t)ADC1 ->DR ;
//		delay_ms(100); 
//		printf("value = %f \r\n", ADC_Value*3.3/4096);
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC); 
	}
}

