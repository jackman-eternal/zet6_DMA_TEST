# stm32zet6 dma学习和adc学习 [https://www.cnblogs.com/microxiami/p/3740935.html] 注：dma传数据不需要占用CPU
## 1、使能 DMA 时钟
　RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能 DMA 时钟
##　2、初始化 DMA 通道 4 参数
DMA 通道配置参数种类比较繁多，包括内存地址，外设地址，传输数据长度，数据宽度，通道优先级等等。这些参数的配置在库函数中都是在函数 DMA_Init 中完成，下面我们看看函数定义：void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx,DMA_InitTypeDef* DMA_InitStruct)
函数的第一个参数是指定初始化的 DMA 通道号，主要看看第二个参数。跟其他外设一样，同样是通过初始化结构体成员变量值来达到初始化的目的，下面看看 DMA_InitTypeDef 结构体的定义：
　　typedef struct
　　{
　　　　uint32_t DMA_PeripheralBaseAddr;
　　　　uint32_t DMA_MemoryBaseAddr;
　　　　uint32_t DMA_DIR;
　　　　uint32_t DMA_BufferSize;
　　　　uint32_t DMA_PeripheralInc;
　　　　uint32_t DMA_MemoryInc;
　　　　uint32_t DMA_PeripheralDataSize;
　　　　uint32_t DMA_MemoryDataSize;
　　　　uint32_t DMA_Mode;
　　　　uint32_t DMA_Priority;
　　　　uint32_t DMA_M2M;
　　}DMA_InitTypeDef;
　　第一个参数 DMA_PeripheralBaseAddr 用来设置 DMA 传输的外设基地址，比如要进行串口DMA 传输，那么外设基地址为串口接受发送数据存储器 USART1->DR 的地址，表示方法为&USART1->DR。注：外设地址为数据寄存器的基地址，内存地址可以为变量或者数组的地址
　　第二个参数 DMA_MemoryBaseAddr 为内存基地址，也就是我们存放 DMA 传输数据的内存地址。
　　第三个参数 DMA_DIR 设置数据传输方向，决定是从外设读取数据到内存还送从内存读取数据发送到外设，也就是外设是源地还是目的地，这里我们设置为从内存读取数据发送到串口，所以外设自然就是目的地了，所以选择值为 DMA_DIR_PeripheralDST（destination设定外设为目的地址，即是从内存到外设；如果选择值为DMA_DIR_PeripheralSRC，则外设为为数据源，从外设到内存ADC）
　　第四个参数 DMA_BufferSize 设置一次传输数据量的大小，这个很容易理解。
　　第五个参数 DMA_PeripheralInc 设置传输数据的时候外设地址是不变还是递增。如果设置为递增，那么下一次传输的时候地址加 1，这里因为我们是一直往固定外设地址&USART1->DR发送数据，所以地址不递增，值为 DMA_PeripheralInc_Disable；
　　第六个参数 DMA_MemoryInc 设置传输数据时候内存地址是否递增。 这个参数和DMA_PeripheralInc 意思接近，只不过针对的是内存。这里我们的场景是将内存中连续存储单元的数据发送到串口，毫无疑问内存地址是需要递增的，所以值为 DMA_MemoryInc_Enable。
　　第七个参数 DMA_PeripheralDataSize 用来设置外设的数据长度是为字节传输（8bits） ，半字传输 (16bits) 还是字传输 (32bits) ，这里我们是 8 位字节传输，所以 值设置为DMA_PeripheralDataSize_Byte。
　　第八个参数 DMA_MemoryDataSize 是用来设置内存的数据长度，和第七个参数意思接近，这里我们同样设置为字节传输 DMA_MemoryDataSize_Byte。
　　第九个参数 DMA_Mode 用来设置 DMA 模式是否循环采集，也就是说，比如我们要从内存中采集 64 个字节发送到串口，如果设置为重复采集，那么它会在 64 个字节采集完成之后继续从内存的第一个地址采集，如此循环。这里我们设置为一次连续采集完成之后不循环。所以设置值为 DMA_Mode_Normal。在我们下面的实验中，如果设置此参数为循环采集，那么你会看到串口不停的打印数据，不会中断，大家在实验中可以修改这个参数测试一下。
　　第十个参数是设置 DMA 通道的优先级，有低，中，高，超高三种模式，这个在前面讲解过，这里我们设置优先级别为中级，所以值为 DMA_Priority_Medium。如果要开启多个通道，那么这个值就非常有意义。
　　第十一个参数 DMA_M2M 设置是否是存储器到存储器模式传输，这里我们选择DMA_M2M_Disable。
　　DMA_InitTypeDef DMA_InitStructure;
　　DMA_InitStructure.DMA_PeripheralBaseAddr = &USART1->DR; //DMA 外设 USART 基地址
　　DMA_InitStructure.DMA_MemoryBaseAddr = cmar; //DMA 内存基地址
　　DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST; //从内存读取发送到外设
　　DMA_InitStructure.DMA_BufferSize = 64; //DMA 通道的 DMA 缓存的大小
　　DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不变
　　DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址递增
　　DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //8 位
　　DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 8 位
　　DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //工作在正常缓存模式
　　DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA 通道 x 拥有中优先级
　　DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //非内存到内存传输
　　DMA_Init(DMA_CHx, &DMA_InitStructure); //根据指定的参数初始化
##　3.使能串口 DMA 发送
进行 DMA 配置之后，我们就要开启串口的 DMA 发送功能，使用的函数是：USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
如果是要使能串口 DMA 接受，那么第二个参数修改为 USART_DMAReq_Rx 即可。
## 4.使能 DMA1 通道 4，启动传输。
使能串口 DMA 发送之后，我们接着就要使能 DMA 传输通道：
DMA_Cmd(DMA_CHx, ENABLE);
通过以上 3 步设置，我们就可以启动一次 USART1 的 DMA 传输了。
## 5、查询 DMA 传输状态
在 DMA 传输过程中，我们要查询 DMA 传输通道的状态，使用的函数是：FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
比如我们要查询 DMA 通道 4 传输是否完成，方法是：DMA_GetFlagStatus(DMA2_FLAG_TC4);
这里还有一个比较重要的函数就是获取当前剩余数据量大小的函数：uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx)比如我们要获取 DMA 通道 4 还有多少个数据没有传输，方法是：DMA_GetCurrDataCounter(DMA1_Channel4);
## 测试memory to memory编程
~1.在flash中定义好要传输的数据，在sram中定义好接收flash数据的变量；
~2.初始化dma,配置结构体
~3.编写比较函数和主函数
//存储在flash的数据
 const uint8_t SendBuff_FLASH[SENDBUFF_SIZE]={0xAB,0XAC,0XAD,0XAE,0XAF, 
	                                         0XA5,0XA2,0XA0,0XAE,0XA3, 
	                                         0XBA,0XCB,0XFF,0X45,0X34, 
									         0X78,0X89,0X34,0X56,0X78, 
									         0X45,0XF5,0X3D,0X3A,0X45, 
									         0X34,0X56,0X3D,0X7B,0X89}; 
uint8_t SendBuff[SENDBUFF_SIZE]; //存在sram中的数据  
void MTM_DMA_Config(void)  
{
	DMA_InitTypeDef MTM_DMA;  
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //开启DMA时钟  
	MTM_DMA.DMA_PeripheralBaseAddr=(uint32_t)SendBuff_FLASH;   
	MTM_DMA.DMA_MemoryBaseAddr=(uint32_t)SendBuff;   
	MTM_DMA.DMA_DIR = DMA_DIR_PeripheralSRC ;//设置外设-flash为源地址  
	MTM_DMA.DMA_BufferSize = SENDBUFF_SIZE ;   
	MTM_DMA.DMA_PeripheralInc =DMA_PeripheralInc_Enable  ;//自增   
	MTM_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ;  
   	MTM_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable ;//传数组，地址自增   
	MTM_DMA.DMA_MemoryDataSize =DMA_MemoryDataSize_Byte;    
	MTM_DMA.DMA_Mode = DMA_Mode_Normal ;//发送一次   
	MTM_DMA.DMA_Priority = DMA_Priority_High ;   
	MTM_DMA.DMA_M2M = DMA_M2M_Enable ;//使能内存到内存模式   
	DMA_Init(DMA1_Channel6 ,&MTM_DMA);  
    DMA_Cmd(DMA1_Channel6,ENABLE ); 	   
}     
//比较函数   
uint8_t BufferCom(const uint8_t* pBuffer,uint8_t *pBuffer1,uint16_t BufferLength )   
{   
	while(BufferLength--)   
	{    
		if(*pBuffer != *pBuffer1 )   
		{  
			return 0;  
		}   
		pBuffer ++;   
		pBuffer1 ++;   
	}    
	return 1;    
}     
用比较函数进行测试
uint8_t status;
status = BufferCom(SendBuff_FLASH,SendBuff,SENDBUFF_SIZE)
获取status的值，观察flash中的值是否存储到sram中 
# adc采集实验（使用adc采集外部模拟信号并且转化为数字信号，通过DMA方式直接将ADC中的数据存到内存中）
