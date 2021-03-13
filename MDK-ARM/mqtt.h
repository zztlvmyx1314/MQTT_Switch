
#ifndef _MQTT_H_
#define _MQTT_H_
#include "main.h"
#include "usart.h"
#include "motor.h"

extern uint8_t PING[];
extern uint8_t MQTTCONN[];
extern uint8_t Ping;
extern uint8_t MQTT_Buf[RxBufSize];
extern uint8_t SUBACK[];
extern uint8_t PINGACK[];
extern uint8_t CONNACK[];

extern uint8_t M1OFF[];
extern uint8_t M1ON[];

extern uint8_t M2OFF[];
extern uint8_t M2ON[];

void MQTT_Mes(uint8_t* data,uint8_t* mqttack);

uint16_t MesLen(uint8_t mes[]);

void MQTT_Init();

void MQTTPING(uint16_t interval);

void MQTT_SPing();

uint8_t MQTT_TestBack(uint8_t ack[]);

uint8_t MQTT_DataDeal();

#endif