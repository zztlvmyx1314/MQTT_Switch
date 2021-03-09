
#ifndef _MQTT_H_
#define _MQTT_H_
#include "main.h"

extern uint8_t PING[2];
extern uint8_t MQTTCONN[120];
extern uint8_t Ping;

void MQTT_Mes(uint8_t* data,uint16_t len);

uint16_t MesLen(uint8_t mes[]);

void MQTT_Init();

void MQTTPING(uint16_t interval);




#endif