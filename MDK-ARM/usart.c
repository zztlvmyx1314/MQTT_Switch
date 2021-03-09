
#include "usart.h"

GPIO_InitTypeDef GPIO_Struct;
UART_HandleTypeDef UART1_Handler;
DMA_HandleTypeDef UARTRxDMA_Handler;
UART_HandleTypeDef UART2_Handler;

uint8_t Rx_Buf[RxBufSize];
uint8_t Rx_Temp[RxBufSize];

uint8_t Rx_Size=1;
uint16_t RxCounter=0;
uint16_t RxIndex=0;


void USART_Init(uint8_t USARTx){

					
			switch(USARTx){

				case 1:
					
			UART1_Handler.Instance=USART1; //USART1

			UART1_Handler.Init.BaudRate=115200; //波特率

			UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式

			UART1_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位

			UART1_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位

			UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控

			UART1_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式  

			HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()会使能 UART1
				
				break;
 
				 
				 	case 2:
					
			UART2_Handler.Instance=USART2; //USART1

			UART2_Handler.Init.BaudRate=115200; //波特率

			UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式

			UART2_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位

			UART2_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位

			UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控

			UART2_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式  

			HAL_UART_Init(&UART2_Handler);  //HAL_UART_Init()会使能 UART1
				
				break;
				 
				 
			 }
				 
}


void USART_DMA_Init(){

     USART_Init(USART_1);
	
	  __HAL_RCC_DMA1_CLK_ENABLE();   // 打开DMA1时钟
	
	
	
		
	__HAL_LINKDMA(&UART1_Handler,hdmarx,UARTRxDMA_Handler);  //将DMA与USART1联系起来(接收DMA)

	UARTRxDMA_Handler.Instance= DMA1_Channel5; //通道选择

	 UARTRxDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY; //外设->存储器

	UARTRxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE; //外设非增量模式

	UARTRxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE; //存储器增量模式

	UARTRxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;  //外设数据长度:8 位

	UARTRxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;  //存储器数据长度:8 位

	UARTRxDMA_Handler.Init.Mode=DMA_NORMAL; //外设循环

	UARTRxDMA_Handler.Init.Priority=DMA_PRIORITY_HIGH; //中等优先级

	 HAL_DMA_Init(&UARTRxDMA_Handler);  // DMA 的某个数据流各种配置参数初始化

   HAL_UART_Receive_DMA(&UART1_Handler,Rx_Buf,RxBufSize);  // 开启串口DMA接收
  
   HAL_DMA_Start(&UARTRxDMA_Handler,(uint32_t)USART1->DR,(uint32_t)Rx_Buf,RxBufSize);

   








}



void HAL_UART_MspInit(UART_HandleTypeDef* huart){
	
	  
	  
	   
	   if(huart->Instance==USART1){
		 
		 __HAL_RCC_USART1_CLK_ENABLE(); //使能 USART1 时钟
			 
			__HAL_RCC_GPIOA_CLK_ENABLE();   
			   
			 
				GPIO_Struct.Pin=GPIO_PIN_9;
				GPIO_Struct.Mode=GPIO_MODE_AF_PP;
				GPIO_Struct.Pull=GPIO_PULLUP; //上拉
				GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //高速
				HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
				
				GPIO_Struct.Pin=GPIO_PIN_10; //PA10
        GPIO_Struct.Mode=GPIO_MODE_AF_INPUT; //模式要设置为复用输入模式！
			  HAL_GPIO_Init(GPIOA,&GPIO_Struct); //初始化 PA10
			 
							
//			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //开启接收完成中断
			 
			 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);

			HAL_NVIC_EnableIRQ(USART1_IRQn); //使能 USART1 中断通道
			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //抢占优先级 3，子优先级 3
			 
		 
		 }

    if(huart->Instance==USART2){
		 
		 __HAL_RCC_USART2_CLK_ENABLE(); //使能 USART1 时钟
			 
			__HAL_RCC_GPIOA_CLK_ENABLE();   
			   
			 
				GPIO_Struct.Pin=GPIO_PIN_2;
				GPIO_Struct.Mode=GPIO_MODE_AF_PP;
				GPIO_Struct.Pull=GPIO_PULLUP; //上拉
				GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //高速
				HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
				
				GPIO_Struct.Pin=GPIO_PIN_3; //PA10
        GPIO_Struct.Mode=GPIO_MODE_AF_INPUT; //模式要设置为复用输入模式！
			  HAL_GPIO_Init(GPIOA,&GPIO_Struct); //初始化 PA10
			 
							
//			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //开启接收完成中断
			 
//			 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);

//			HAL_NVIC_EnableIRQ(USART1_IRQn); //使能 USART1 中断通道
//			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //抢占优先级 3，子优先级 3
			 
		 
		 }		 
	
	

	
}



void USART1_IRQHandler(void) // USART1中断服务函数
{

//HAL_UART_IRQHandler(&UART1_Handler); //调用 HAL 库中断处理公用函数
	
	if(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET){
	  
		
		 
		
		 
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE); // 清除标志位
		
	
	
	}
	
	if(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_IDLE)!=RESET){
	  
		 HAL_UART_DMAStop(&UART1_Handler); 
		

		 uint16_t RxCount=RxBufSize-__HAL_DMA_GET_COUNTER(&UARTRxDMA_Handler);

		 memcpy(Rx_Temp,Rx_Buf,RxCount);
		
		 HAL_UART_Transmit(&UART2_Handler,Rx_Buf,RxCount,0xffff);
		
		
		 memset(Rx_Buf,0,RxBufSize);
		
		 HAL_UART_Receive_DMA(&UART1_Handler,Rx_Buf,RxBufSize);  // 开启串口DMA接收
		
		 HAL_DMA_Start(&UARTRxDMA_Handler,(uint32_t)USART1->DR,(uint32_t)Rx_Buf,RxBufSize);
		
		 
		
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_IDLE); // 清除标志位
		
	
	
	}


}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  // 接收中断回调函数
{

   if(huart->Instance==USART1){
	 
//		  HAL_UART_Receive(huart,(uint8_t*)Rx_Buf,1,0xffff);
		  
		  Rx_Buf[RxCounter]=huart->Instance->DR;
		  RxCounter++;
		 
		  if(RxCounter>RxBufSize){
			
				 RxCounter=0;
				 
				 
				  
			}
		  
	 
	 
	 }



}


int fputc(int ch,FILE *f)
{

    uint8_t temp[1]={ch};

    HAL_UART_Transmit(&UART1_Handler,temp,1,0xffff);        //UartHandle是串口的句柄

}