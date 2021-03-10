
#include "motor.h"

void Motor_Init(){

     
   TIM_PWM_Init();


   








}


void Motor_SetAngle(uint8_t motorx,uint8_t angle){

	
	    uint32_t copval=PWM_SetPuls(angle);
	    TIM3_CH12Handler.Pulse=PWM_SetPuls(angle);

	
	  switch(motorx){
     
			case 1:
			
//     TIM3_CH12Handler.Pulse=PWM_SetPuls(angle);

     HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH12Handler,TIM_CHANNEL_1);//配置 TIM1 通道 1

	   TIM_CCxChannelCmd(TIM3,TIM_CHANNEL_1,1);
     			
//		  __HAL_TIM_SET_COMPARE(&TIM3_Handler,TIM_CHANNEL_1,copval);
	
			

			 break;
			
			case 2:
			
//     TIM3_CH12Handler.Pulse=PWM_SetPuls(angle);

     HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH12Handler,TIM_CHANNEL_2);//配置 TIM1 通道 1

	   TIM_CCxChannelCmd(TIM3,TIM_CHANNEL_2,1); 
		 
//		 __HAL_TIM_SET_COMPARE(&TIM3_Handler,TIM_CHANNEL_2,copval);


			 break;

			
		}
		
		
}

