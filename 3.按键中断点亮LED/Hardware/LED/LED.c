#include "led.h"

u8 menu=0,i=0;
u16 t=0;

void LedInit(void){
  GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);//�������ģʽ
	GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1);
	GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);
 }

void  LedSet(u8 state){ 
 if(state==1){
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN0);//P40������ߵ�ƽ
  } 
 else if(state==2){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);//P41����ߵ�ƽ
   }
  else if(state==3){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);//P42����ߵ�ƽ
   }
	 else if(state==4){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);//P43����ߵ�ƽ
   }
	else { 
	  GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
	 }
 }

void  LedPwm(void){ 
	if(menu ==0){      //���ѣ������ģʽ
	 for(i=0;i<5;i++){ 
      GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
			delay_us(t);
	    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
		 	delay_us(501-t);
	 }
	 t++;
	if(t==500){ 
	 menu =1;
	  }
	 }
	if(menu ==1){ 
	 for(i=0;i<5;i++){ 
      GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
			delay_us(t);
	    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
		 	delay_us(501-t);
	 }
	 t--;
	if(t==1){ 
	 menu =0;
	  }
	 }


 


 }
 
 
