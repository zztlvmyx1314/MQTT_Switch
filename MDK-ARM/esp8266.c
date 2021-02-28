
#include "esp8266.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"

uint8_t sendcount=4;

void ESP_Init(){


    USART_Init();

    ESP_SendCmd((uint8_t*)AT_RST,(uint8_t*)"OK",1500);
    
    ESP_SendCmd((uint8_t*)AT,(uint8_t*)"OK",500);

    ESP_SendCmd((uint8_t*)AT_CWMODE_Station,(uint8_t*)"OK",1000);

    ESP_SendCmd((uint8_t*)AT_CWJAP,(uint8_t*)"OK",1000);

    ESP_SendCmd((uint8_t*)AT_CIPMUX_0,(uint8_t*)"OK",500);

    ESP_SendCmd((uint8_t*)AT_CIPSTART,(uint8_t*)"OK",2000);	
	  
	  








}

void ESP_SendCmd(uint8_t* cmd,uint8_t* ack,uint32_t wtime){

     
	   uint8_t cmdsize=strlen((char*)cmd);   
	
	   
	
	   while(sendcount--){
		 
		 HAL_UART_Transmit(&UART1_Handler,cmd,cmdsize,0xffff);
	
	   HAL_Delay(wtime);
			 
			if(ESP_CheckBack(ack)==Success){
			
				return;
			}
			
			 
		 
		 }
	
	  
     


}


void ESP_SendData(uint8_t* data,uint8_t* ack){






}

uint8_t ESP_CheckBack(uint8_t* ack){

        
	   if(strstr((char*)Rx_Buf,(char*)ack)!=NULL){
		 
			 
 			 return Success;
		        
		 
		 }

		 else{
		 
		     return Failure; 
			 
		 }





}