
#ifndef _TIM_H_
#define _TIM_H_

#include "main.h"
#include "mqtt.h"

#define TIM_1 1
#define TIM_2 2
#define TIM_3 3
#define TIM_4 4


extern TIM_HandleTypeDef TIM4_Handler;
extern TIM_HandleTypeDef TIM2_Handler;


void TIM_Init(uint8_t TIMx,uint16_t detim);


#endif