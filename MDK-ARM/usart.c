
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

			UART1_Handler.Init.BaudRate=115200; //������

			UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ

			UART1_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ

			UART1_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ

			UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������

			UART1_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ  

			HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()��ʹ�� UART1
				
				break;
 
				 
				 	case 2:
					
			UART2_Handler.Instance=USART2; //USART1

			UART2_Handler.Init.BaudRate=115200; //������

			UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ

			UART2_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ

			UART2_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ

			UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������

			UART2_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ  

			HAL_UART_Init(&UART2_Handler);  //HAL_UART_Init()��ʹ�� UART1
				
				break;
				 
				 
			 }
				 
}


void USART_DMA_Init(){

     USART_Init(USART_1);
	
	  __HAL_RCC_DMA1_CLK_ENABLE();   // ��DMA1ʱ��
	
	
	
		
	__HAL_LINKDMA(&UART1_Handler,hdmarx,UARTRxDMA_Handler);  //��DMA��USART1��ϵ����(����DMA)

	UARTRxDMA_Handler.Instance= DMA1_Channel5; //ͨ��ѡ��

	 UARTRxDMA_Handler.Init.Direction=DMA_PERIPH_TO_MEMORY; //����->�洢��

	UARTRxDMA_Handler.Init.PeriphInc=DMA_PINC_DISABLE; //���������ģʽ

	UARTRxDMA_Handler.Init.MemInc=DMA_MINC_ENABLE; //�洢������ģʽ

	UARTRxDMA_Handler.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;  //�������ݳ���:8 λ

	UARTRxDMA_Handler.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;  //�洢�����ݳ���:8 λ

	UARTRxDMA_Handler.Init.Mode=DMA_NORMAL; //����ѭ��

	UARTRxDMA_Handler.Init.Priority=DMA_PRIORITY_HIGH; //�е����ȼ�

	 HAL_DMA_Init(&UARTRxDMA_Handler);  // DMA ��ĳ���������������ò�����ʼ��

   HAL_UART_Receive_DMA(&UART1_Handler,Rx_Buf,RxBufSize);  // ��������DMA����
  
   HAL_DMA_Start(&UARTRxDMA_Handler,(uint32_t)USART1->DR,(uint32_t)Rx_Buf,RxBufSize);

   








}



void HAL_UART_MspInit(UART_HandleTypeDef* huart){
	
	  
	  
	   
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
			 
							
//			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //������������ж�
			 
			 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);

			HAL_NVIC_EnableIRQ(USART1_IRQn); //ʹ�� USART1 �ж�ͨ��
			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //��ռ���ȼ� 3�������ȼ� 3
			 
		 
		 }

    if(huart->Instance==USART2){
		 
		 __HAL_RCC_USART2_CLK_ENABLE(); //ʹ�� USART1 ʱ��
			 
			__HAL_RCC_GPIOA_CLK_ENABLE();   
			   
			 
				GPIO_Struct.Pin=GPIO_PIN_2;
				GPIO_Struct.Mode=GPIO_MODE_AF_PP;
				GPIO_Struct.Pull=GPIO_PULLUP; //����
				GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //����
				HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
				
				GPIO_Struct.Pin=GPIO_PIN_3; //PA10
        GPIO_Struct.Mode=GPIO_MODE_AF_INPUT; //ģʽҪ����Ϊ��������ģʽ��
			  HAL_GPIO_Init(GPIOA,&GPIO_Struct); //��ʼ�� PA10
			 
							
//			__HAL_UART_ENABLE_IT(huart,UART_IT_RXNE);  //������������ж�
			 
//			 __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);

//			HAL_NVIC_EnableIRQ(USART1_IRQn); //ʹ�� USART1 �ж�ͨ��
//			HAL_NVIC_SetPriority(USART1_IRQn,0,1); //��ռ���ȼ� 3�������ȼ� 3
			 
		 
		 }		 
	
	

	
}



void USART1_IRQHandler(void) // USART1�жϷ�����
{

//HAL_UART_IRQHandler(&UART1_Handler); //���� HAL ���жϴ����ú���
	
	if(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET){
	  
		
		 
		
		 
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE); // �����־λ
		
	
	
	}
	
	if(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_IDLE)!=RESET){
	  
		 HAL_UART_DMAStop(&UART1_Handler); 
		

		 uint16_t RxCount=RxBufSize-__HAL_DMA_GET_COUNTER(&UARTRxDMA_Handler);

		 memcpy(Rx_Temp,Rx_Buf,RxCount);
		
		 HAL_UART_Transmit(&UART2_Handler,Rx_Buf,RxCount,0xffff);
		
		
		 memset(Rx_Buf,0,RxBufSize);
		
		 HAL_UART_Receive_DMA(&UART1_Handler,Rx_Buf,RxBufSize);  // ��������DMA����
		
		 HAL_DMA_Start(&UARTRxDMA_Handler,(uint32_t)USART1->DR,(uint32_t)Rx_Buf,RxBufSize);
		
		 
		
		__HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_IDLE); // �����־λ
		
	
	
	}


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


int fputc(int ch,FILE *f)
{

    uint8_t temp[1]={ch};

    HAL_UART_Transmit(&UART1_Handler,temp,1,0xffff);        //UartHandle�Ǵ��ڵľ��

}