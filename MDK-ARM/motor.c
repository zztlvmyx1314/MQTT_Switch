
#include "motor.h"

void Motor_Init(){

     
   TIM_PWM_Init();


   








}


void Motor_SetAngle(uint8_t angle){

     
     TIM3_CH1Handler.Pulse=PWM_SetPuls(angle);

     HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH1Handler,TIM_CHANNEL_1);//≈‰÷√ TIM1 Õ®µ¿ 1

//     HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_1);

	   TIM_CCxChannelCmd(TIM3,TIM_CHANNEL_1,1); 



}

