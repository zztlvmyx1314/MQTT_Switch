
#include "esp8266.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"



uint8_t sendcount=4;

uint8_t IsDetect=0;

char *AT="AT\r\n";
char *AT_RST="AT+RST\r\n";
char *AT_CWMODE="AT+CWMODE=1\r\n";
char *AT_CWJAP="AT+CWJAP=\"314\",\"11111111\"\r\n";
char *AT_CWJAP_PC="AT+CWJAP=\"314\",\"11111111\"\r\n";
char *AT_CIPMUX="AT+CIPMUX=0\r\n";
char *AT_CIPSTART="AT+CIPSTART=\"TCP\",\"192.168.43.1\",8080\r\n";
char *ALY="AT+CIPSTART=\"TCP\",\"101.133.196.120\",1883\r\n";
char *AT_CWQAP="AT+CWQAP\r\n";
char *OK="OK";

char *DISCONN="link is not valid";
char *CLOSED="CLOSED";

char *AT_CIPSTATUS="AT+CIPSTATUS\r\n";



void ESP_Init(){

   
//    USART_Init(USART_1);

//    ESP_SendCmd(AT_RST,OK,3000);
	HAL_UART_Transmit(&UART2_Handler,(uint8_t*)"AT测试:\r\n",(uint8_t)strlen("AT测试:\r\n"),0xffff);
	  ESP_SendCmd(AT,OK,1000);
	  
	HAL_UART_Transmit(&UART2_Handler,(uint8_t*)"断开当前连接:\r\n",(uint8_t)strlen("断开当前连接:\r\n"),0xffff);
	  ESP_SendCmd(AT_CWQAP,"OK",1000);
	
	HAL_UART_Transmit(&UART2_Handler,(uint8_t*)"连接WIFI热点:\r\n",(uint8_t)strlen("连接WIFI热点:\r\n"),0xffff);
	  ESP_SendCmd(AT_CWJAP,"WIFI CONNECTED",1500);
	
	HAL_UART_Transmit(&UART2_Handler,(uint8_t*)"连接阿里云服务器:\r\n",(uint8_t)strlen("连接阿里云服务器:\r\n"),0xffff);
	  ESP_SendCmd(ALY,"CONNECT",2000);
//	  ESP_SendData("Hello!");
	  

    




}

void ESP_SendCmd(char* cmd,char* ack,uint32_t wtime){

     
	   uint8_t cmdsize=strlen((char*)cmd);   
	
	   uint8_t count=4;
	
	   memset(Rx_Temp,0,RxBufSize);
	
	  do {
		 
		 printf("%s",cmd);
	
	   HAL_Delay(wtime);
			 
//			if(ESP_CheckBack(ack)==Success){
//			
//				memset(Rx_Temp,0,RxBufSize);
//				
//				return;
//			}
			
			 
		 
		 } while((count--)&&(!ESP_CheckBack(ack)));
	
	  
//     memset(Rx_Temp,0,RxBufSize);


}


void ESP_SendData(char* data){

	   uint16_t num=strlen(data);
	   char* ack="OK";
     
	   uint8_t count=4;
	
	  do {
		 
		  
			printf("AT+CIPSEND=%d\r\n",num);
	
	    HAL_Delay(500);
			 
//			if(ESP_CheckBack(ack)==Success){
//			
//				break;
//			}
			
			 
		 
		 } while((count--)&&(!ESP_CheckBack(ack)));
	
    count=4;
		 
		 ack="SEND OK";
		 
		 do {
		 
		  
			printf("%s",data);
	
	    HAL_Delay(500);
			 
//			if(ESP_CheckBack("SEND OK")==Success){
//			
//				return;
//			}
			
			 
		 
		 } while((count--)&&(!ESP_CheckBack(ack)));




}

uint8_t ESP_CheckBack(char* ack){

        
//	   if(strstr((char*)Rx_Temp,ack)!=NULL){
//		 
//			 
// 			 return Success;
//		        
//		 
//		 }

//		 else{
//		 
//		     return Failure; 
//			 
//		 }
		 
		 uint8_t count=4;
		 
		 while((--count)&&(strstr((char*)Rx_Temp,ack)==NULL)){}

     if(count!=0){
		 
			 
			 return Success;
			 
		 }
		 
		 else{
		 
			 return Failure;
			 
		 }

}




void ESP_Detector(){

	    IsDisConn();

     if(IsDetect){
		 
       uint8_t count=2;

       memset(Rx_Temp,0,RxBufSize);			 
			do{ 
		   printf("%s",AT_CIPSTATUS);
			 
			 HAL_Delay(500);
			 
			}while((--count)&&(ESP_CheckBack("STATUS:4")!=NULL));
			 
			 
			 memset(Rx_Temp,0,RxBufSize);	
			
			if(!count){
			
				 ESP_SendCmd(AT_CIPSTART,"CONNECT",1000);
				 
			
			}
			
		 
			IsDetect=0;
			
			__HAL_TIM_ENABLE(&TIM4_Handler);
			
			
		 
		 }






}


void IsDisConn(){

	   uint8_t f=1;

    if((strstr((char*)Rx_Temp,CLOSED)!=NULL)||(strstr((char*)Rx_Temp,DISCONN)!=NULL)){
		
		
		   	  f=0;
			
		
		}
      

		if(f!=1){

			 
     ESP_SendCmd(ALY,"CONNECT",1500);
			
		 	if(strstr((char*)Rx_Temp,"CONNECT")!=NULL){
			
		 MQTT_Mes(MQTTCONN,CONNACK);
			
			}
			 
    

		}
		
		
		

}