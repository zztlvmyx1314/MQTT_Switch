
#ifndef _TIM_H_
#define _TIM_H_

#include "main.h"
#include "mqtt.h"
#include "usart.h"

#define TIM_1 1
#define TIM_2 2
#define TIM_3 3
#define TIM_4 4


extern TIM_HandleTypeDef TIM3_Handler;
extern TIM_HandleTypeDef TIM2_Handler;
extern TIM_OC_InitTypeDef TIM3_CH12Handler;


void TIM_Init(uint8_t TIMx,uint16_t detim);

void TIM_PWM_Init();

uint32_t PWM_SetPuls(uint32_t angle);

#endif