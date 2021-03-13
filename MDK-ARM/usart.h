#ifndef  _USART_H_
#define _USART_H_

#include "main.h"
#include "stdio.h"
#include "string.h"


#define USART_1 1
#define USART_2 2
#define USART_3 3

#define RxBufSize 255
#define ON 1
#define OFF 0

extern UART_HandleTypeDef UART1_Handler;
extern DMA_HandleTypeDef UARTRxDMA_Handler;
extern UART_HandleTypeDef UART2_Handler;

extern uint8_t Rx_Buf[RxBufSize];
extern uint8_t Rx_Temp[RxBufSize];
extern uint16_t RxCounter;
extern uint16_t RxIndex;




void USART_Init(uint8_t USARTx);

void USART_DMA_Init();

void USART_IsEnable(uint8_t flag);



#endif
