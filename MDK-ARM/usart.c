
#include "usart.h"

GPIO_InitTypeDef GPIO_Struct;
UART_HandleTypeDef UART_Handler;


void USART_Init(){

    
UART_HandleTypeDef UART1_Handler; //UART ���

UART1_Handler.Instance=USART1; //USART1

UART1_Handler.Init.BaudRate=115200; //������

UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ 8 λ��ʽ

UART1_Handler.Init.StopBits=UART_STOPBITS_1; //һ��ֹͣλ

UART1_Handler.Init.Parity=UART_PARITY_NONE; //����żУ��λ

UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������

UART1_Handler.Init.Mode=UART_MODE_TX_RX; //�շ�ģʽ

HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()��ʹ�� UART1


}



void HAL_UART_MspInit(){
	
	
	
	
	
	
	
	
	
	
}