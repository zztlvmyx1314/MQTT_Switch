
#include "usart.h"

GPIO_InitTypeDef GPIO_Struct;
UART_HandleTypeDef UART1_Handler;

uint8_t Rx_Buf[RxBufSize];

uint8_t Rx_Size=1;
uint8_t RxCounter=0;


void USART_Init(){

					
			

			UART1_Handler.Instance=USART1; //USART1

			UART1_Handler.Init.BaudRate=115200; //波特率

			UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式

			UART1_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位

			UART1_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位

			UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控

			UART1_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式

			HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()会使能 UART1
      
//	    HAL_UART_Receive_IT(&UART1_Handler,(uint8_t*)Rx_Buf,Rx_Size);//该函数会开启接收中断：标志位 UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量	    
         
				  
}



void HAL_UART_MspInit(UART_HandleTypeDef* huart){
	
	   __HAL_RCC_USART1_CLK_ENABLE(); //使能 USART1 时钟
	  
	   
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
			 
							
			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //开启接收完成中断

			HAL_NVIC_EnableIRQ(USART1_IRQn); //使能 USART1 中断通道
			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //抢占优先级 3，子优先级 3
			 
		 
		 }
	
	
	

	
}



void USART1_IRQHandler(void) // USART1中断服务函数
{

HAL_UART_IRQHandler(&UART1_Handler); //调用 HAL 库中断处理公用函数


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