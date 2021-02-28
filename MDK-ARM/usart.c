
#include "usart.h"

GPIO_InitTypeDef GPIO_Struct;
UART_HandleTypeDef UART1_Handler;

uint8_t Rx_Buf[RxBufSize];

uint8_t Rx_Size=1;
uint8_t RxCounter=0;


void USART_Init(){

					
			

			UART1_Handler.Instance=USART1; //USART1

			UART1_Handler.Init.BaudRate=115200; //������

			UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ

			UART1_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ

			UART1_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ

			UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������

			UART1_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ

			HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()��ʹ�� UART1
      
//	    HAL_UART_Receive_IT(&UART1_Handler,(uint8_t*)Rx_Buf,Rx_Size);//�ú����Ὺ�������жϣ���־λ UART_IT_RXNE���������ý��ջ����Լ����ջ���������������	    
         
				  
}



void HAL_UART_MspInit(UART_HandleTypeDef* huart){
	
	   __HAL_RCC_USART1_CLK_ENABLE(); //ʹ�� USART1 ʱ��
	  
	   
	   if(huart->Instance==USART1){
		 
		 __HAL_RCC_USART1_CLK_ENABLE(); //ʹ�� USART1 ʱ��
			 
			__HAL_RCC_GPIOA_CLK_ENABLE();   
			   
			 
				GPIO_Struct.Pin=GPIO_PIN_9;
				GPIO_Struct.Mode=GPIO_MODE_AF_PP;
				GPIO_Struct.Pull=GPIO_PULLUP; //����
				GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //����
				HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
				
				GPIO_Struct.Pin=GPIO_PIN_10; //PA10
        GPIO_Struct.Mode=GPIO_MODE_AF_INPUT; //ģʽҪ����Ϊ��������ģʽ��
			  HAL_GPIO_Init(GPIOA,&GPIO_Struct); //��ʼ�� PA10
			 
							
			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //������������ж�

			HAL_NVIC_EnableIRQ(USART1_IRQn); //ʹ�� USART1 �ж�ͨ��
			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //��ռ���ȼ� 3�������ȼ� 3
			 
		 
		 }
	
	
	

	
}



void USART1_IRQHandler(void) // USART1�жϷ�����
{

HAL_UART_IRQHandler(&UART1_Handler); //���� HAL ���жϴ����ú���


}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)  // �����жϻص�����
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