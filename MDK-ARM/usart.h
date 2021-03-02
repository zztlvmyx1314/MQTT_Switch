#ifndef  _USART_H_
#define _USART_H_

#include "main.h"

#define RxBufSize 125

extern uint8_t Rx_Buf[RxBufSize];





void USART_Init();

void USART_DMA_Init();





#endif
