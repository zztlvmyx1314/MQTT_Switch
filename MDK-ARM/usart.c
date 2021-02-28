
#include "usart.h"

GPIO_InitTypeDef GPIO_Struct;
UART_HandleTypeDef UART_Handler;


void USART_Init(){

    
UART_HandleTypeDef UART1_Handler; //UART 句柄

UART1_Handler.Instance=USART1; //USART1

UART1_Handler.Init.BaudRate=115200; //波特率

UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为 8 位格式

UART1_Handler.Init.StopBits=UART_STOPBITS_1; //一个停止位

UART1_Handler.Init.Parity=UART_PARITY_NONE; //无奇偶校验位

UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控

UART1_Handler.Init.Mode=UART_MODE_TX_RX; //收发模式

HAL_UART_Init(&UART1_Handler);  //HAL_UART_Init()会使能 UART1


}



void HAL_UART_MspInit(){
	
	
	
	
	
	
	
	
	
	
}