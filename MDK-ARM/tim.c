
#include "tim.h"

TIM_HandleTypeDef TIM2_Handler;
TIM_HandleTypeDef TIM3_Handler;

void TIM_Init(uint8_t TIMx,uint16_t detim){

	
	switch(TIMx){ 
	
		case 2:
		
    TIM2_Handler.Instance=TIM2;
	 
		TIM2_Handler.Init.Prescaler=39999; //分频系数

		TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数器

		TIM2_Handler.Init.Period=(detim*200)-1; //自动装载值

		TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //时钟分频因子
		
		 
		
	  if(HAL_TIM_Base_Init(&TIM2_Handler)!=HAL_OK){
		
		
		     Error_Handler();
		
		}
		
		HAL_TIM_Base_Start_IT(&TIM2_Handler);
		
		HAL_TIM_Base_Start(&TIM2_Handler);
	 
   

    break;
		
		

	}


}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim){
	
	   if(htim->Instance==TIM2){
		 
			 __HAL_RCC_TIM2_CLK_ENABLE();
			 
			
			 HAL_NVIC_SetPriority(TIM2_IRQn,0,3);    //设置中断优先级，抢占优先级 1，子优先级 3

       HAL_NVIC_EnableIRQ(TIM2_IRQn); //开启 ITM3 中断
			 
//		   HAL_TIM_Base_Start_IT(&TIM2_Handler); 
//		
//	    HAL_TIM_Base_Start(&TIM2_Handler);
		 
			 
		 }
	
	
}






void TIM_PWM_Init(uint8_t arr){

/*************************定时器TIM2配置******************/
	
		TIM2_Handler.Instance=TIM2; //通用定时器 3

		TIM2_Handler.Init.Prescaler= 1999; //分频系数

		TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //向上计数器

		TIM2_Handler.Init.Period=arr; //自动装载值

		TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //时钟分频因子

		HAL_TIM_Base_Init(&TIM2_Handler);   // 写入寄存器

 
//    HAL_TIM_Base_Start_IT(&TIM2_Handler);  //  使 能 定 时 器 更 新 中 断 和 使 能 定 时 器

	   HAL_TIM_PWM_Init(&TIM2_Handler); 
	
/***********************PWM配置****************/

		 
		TIM_OC_InitTypeDef TIM2_CH1Handler; //定时器 1 通道 1 句柄 

		TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择 PWM1

		TIM2_CH1Handler.Pulse=arr/2; //设置比较值,此值用来确定占空比,默认比较值为自动重装载值的一半,即占空比为 50%

		TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低

		HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//配置 TIM1 通道 1

   
   HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_1);   // 使能 TIMx
 
   TIM_CCxChannelCmd(TIM2,TIM_CHANNEL_1,1); // 单独使能定时器的输出通道函数

  


}






void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* huart){


     if(huart->Instance==TIM2){
		 
		  __HAL_RCC_TIM2_CLK_ENABLE();
			
			__HAL_RCC_GPIOA_CLK_ENABLE();
					 
//     HAL_NVIC_SetPriority(TIM3_IRQn,2,0);    //设置中断优先级，抢占优先级 2，子优先级 0

//     HAL_NVIC_EnableIRQ(TIM3_IRQn); //开启 ITM3 中断
			 
						 
			 GPIO_InitTypeDef GPIO_Struct;  // GPIO结构体
			 
			 GPIO_Struct.Pin=GPIO_PIN_0;  //PA0
			 GPIO_Struct.Mode=GPIO_MODE_AF_PP; //复用推挽输出
			 GPIO_Struct.Pull=GPIO_PULLUP;  //上拉
			 GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //高速
			 HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
			 
			 
		 
		 }



}


void TIM2_IRQHandler(void)//服务函数
{
 
   HAL_TIM_IRQHandler(&TIM2_Handler);  // 中断服务函数中调用中断共用处理函数
 
//	if(__HAL_TIM_GET_FLAG(&TIM2_Handler,TIM_FLAG_UPDATE)!=RESET){
//	
//		   MQTT_Mes(PING,2);
//		
//		__HAL_TIM_CLEAR_FLAG(&TIM2_Handler,TIM_FLAG_UPDATE);
//		 
//	
//	}
	
	
	
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){


     if(htim->Instance==TIM2){
		 
			 
//			 MQTT_Mes(PING,2);
			 
			   HAL_UART_Transmit(&UART2_Handler,(uint8_t*)"OK!",3,0xffff);
		 
			 __HAL_TIM_CLEAR_FLAG(&TIM2_Handler,TIM_FLAG_UPDATE);
		 
		 }






}


