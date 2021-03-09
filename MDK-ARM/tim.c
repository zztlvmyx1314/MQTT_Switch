
#include "tim.h"

TIM_HandleTypeDef TIM2_Handler;
TIM_HandleTypeDef TIM3_Handler;

void TIM_Init(uint8_t TIMx,uint16_t detim){

	
	switch(TIMx){ 
	
		case 2:
		
    TIM2_Handler.Instance=TIM2;
	 
		TIM2_Handler.Init.Prescaler=39999; //��Ƶϵ��

		TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //���ϼ�����

		TIM2_Handler.Init.Period=(detim*200)-1; //�Զ�װ��ֵ

		TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����
		
		 
		
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
			 
			
			 HAL_NVIC_SetPriority(TIM2_IRQn,0,3);    //�����ж����ȼ�����ռ���ȼ� 1�������ȼ� 3

       HAL_NVIC_EnableIRQ(TIM2_IRQn); //���� ITM3 �ж�
			 
//		   HAL_TIM_Base_Start_IT(&TIM2_Handler); 
//		
//	    HAL_TIM_Base_Start(&TIM2_Handler);
		 
			 
		 }
	
	
}






void TIM_PWM_Init(uint8_t arr){

/*************************��ʱ��TIM2����******************/
	
		TIM2_Handler.Instance=TIM2; //ͨ�ö�ʱ�� 3

		TIM2_Handler.Init.Prescaler= 1999; //��Ƶϵ��

		TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP; //���ϼ�����

		TIM2_Handler.Init.Period=arr; //�Զ�װ��ֵ

		TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1; //ʱ�ӷ�Ƶ����

		HAL_TIM_Base_Init(&TIM2_Handler);   // д��Ĵ���

 
//    HAL_TIM_Base_Start_IT(&TIM2_Handler);  //  ʹ �� �� ʱ �� �� �� �� �� �� ʹ �� �� ʱ ��

	   HAL_TIM_PWM_Init(&TIM2_Handler); 
	
/***********************PWM����****************/

		 
		TIM_OC_InitTypeDef TIM2_CH1Handler; //��ʱ�� 1 ͨ�� 1 ��� 

		TIM2_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ�� PWM1

		TIM2_CH1Handler.Pulse=arr/2; //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ�,Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ 50%

		TIM2_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��

		HAL_TIM_PWM_ConfigChannel(&TIM2_Handler,&TIM2_CH1Handler,TIM_CHANNEL_1);//���� TIM1 ͨ�� 1

   
   HAL_TIM_PWM_Start(&TIM2_Handler,TIM_CHANNEL_1);   // ʹ�� TIMx
 
   TIM_CCxChannelCmd(TIM2,TIM_CHANNEL_1,1); // ����ʹ�ܶ�ʱ�������ͨ������

  


}






void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* huart){


     if(huart->Instance==TIM2){
		 
		  __HAL_RCC_TIM2_CLK_ENABLE();
			
			__HAL_RCC_GPIOA_CLK_ENABLE();
					 
//     HAL_NVIC_SetPriority(TIM3_IRQn,2,0);    //�����ж����ȼ�����ռ���ȼ� 2�������ȼ� 0

//     HAL_NVIC_EnableIRQ(TIM3_IRQn); //���� ITM3 �ж�
			 
						 
			 GPIO_InitTypeDef GPIO_Struct;  // GPIO�ṹ��
			 
			 GPIO_Struct.Pin=GPIO_PIN_0;  //PA0
			 GPIO_Struct.Mode=GPIO_MODE_AF_PP; //�����������
			 GPIO_Struct.Pull=GPIO_PULLUP;  //����
			 GPIO_Struct.Speed=GPIO_SPEED_FREQ_HIGH; //����
			 HAL_GPIO_Init(GPIOA,&GPIO_Struct);
			 
			 
			 
		 
		 }



}


void TIM2_IRQHandler(void)//������
{
 
   HAL_TIM_IRQHandler(&TIM2_Handler);  // �жϷ������е����жϹ��ô�����
 
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


