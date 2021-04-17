
#include "iwdog.h"

IWDG_HandleTypeDef IWDOG_Handler;
WWDG_HandleTypeDef WWDOG_Handler;

void IWDOG_Init(uint8_t f,uint16_t reload){
	
	  

   switch(f){
	
		 
		 case 0:
		 
  IWDOG_Handler.Instance=IWDG;
	IWDOG_Handler.Init.Prescaler=IWDG_PRESCALER_64;
	IWDOG_Handler.Init.Reload=reload;
	
	 HAL_IWDG_Init(&IWDOG_Handler);

		 break;
		 
		 
		 
		 
		 case 1:
			 
		 
		 WWDOG_Handler.Instance=WWDG;
	   WWDOG_Handler.Init.Prescaler=PRE;
		 WWDOG_Handler.Init.Window=WVAL;
		 WWDOG_Handler.Init.Counter=CVAL;
		 WWDOG_Handler.Init.EWIMode=WWDG_EWI_ENABLE;
		 
		 HAL_WWDG_Init(&WWDOG_Handler);
		 
		 break;
		 

	 }

}



void IWDOG_Feed(uint8_t f){


	  if(f){
	
   HAL_IWDG_Refresh(&IWDOG_Handler);  // 喂狗

		}

    else{
		
		 
		
		
		}

}


void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{ 
	
	
	
 __HAL_RCC_WWDG_CLK_ENABLE(); //使能窗口看门狗时钟
 
 HAL_NVIC_SetPriority(WWDG_IRQn,2,3); //抢占优先级 2，子优先级为 3
 HAL_NVIC_EnableIRQ(WWDG_IRQn); //使能窗口看门狗中断
	
	
	
}



void WWDG_IRQHandler(void){


   if(__HAL_WWDG_GET_IT(&WWDOG_Handler,WWDG_FLAG_EWIF)){
		 
		 
		 __HAL_WWDG_CLEAR_IT(&WWDOG_Handler,WWDG_FLAG_EWIF);
		   
		 HLA_WWDG_Refresh(&WWDOG_Handler);
		 
		 
		 
		 
		 
	 }
		 





}



