
#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "main.h"

#define Success 1
#define Failure 0

#define AT "AT\r\n"
#define AT_RST "AT+RST\r\n"
#define ATE "ATE\r\n"
#define AT_CWMODE_Station  "AT+CWMODE=1\r\n"
#define AT_CWJAP        "AT+CWJAP=ssid,passwd,"
#define AT_CIPMUX_0      "AT+CIPMUX=0\r\n"
#define AT_CIPSTART     "AT+CIPSTART=\"TCP\",192.168.43.1,8080\r\n"

extern UART_HandleTypeDef UART1_Handler;




void ESP_Init();

uint8_t ESP_CheckBack(uint8_t* ack);

void ESP_SendCmd(uint8_t* cmd,uint8_t* ack,uint32_t wtime);
void ESP_SendData(uint8_t* data,uint8_t* ack);


#endif
