#include "rtc.h"

volatile RTC_C_Calendar newTime;

 const RTC_C_Calendar currentTime =
 {
     00,       //��
     06,       //��
     20,       //ʱ
     00,       //����
     03,       //��
	   06,       //��
	   2018      //��
 };


unsigned int sec ;
 
void RtcInit(void){
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,GPIO_PIN0 | GPIO_PIN1, 
	  GPIO_PRIMARY_MODULE_FUNCTION);//�����ⲿʱ�ӹܽ�
	
    CS_setExternalClockSourceFrequency(32768,48000000);//�����ⲿʱ��ԴƵ��

    /* Starting LFXT in non-bypass mode without a timeout. */
    CS_startLFXT(false);

    RTC_C_initCalendar(&currentTime,RTC_C_FORMAT_BINARY );//��ȡʱ�䣬�����Ƹ�ʽ

	/*����ʱ�䣺12:40 */
    RTC_C_setCalendarAlarm(40, 12, RTC_C_ALARMCONDITION_OFF, RTC_C_ALARMCONDITION_OFF);//��������

    /* Specify an interrupt to assert every minute */
    RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);//ָ���ж�ÿ�����ж�һ��

    /* Enable interrupt for RTC Ready Status, which asserts when the RTC
     * Calendar registers are ready to read.
     * Also, enable interrupts for the Calendar alarm and Calendar event. */
    RTC_C_clearInterruptFlag(RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT| RTC_C_CLOCK_ALARM_INTERRUPT);//ѡ������жϵ�����
    RTC_C_enableInterrupt( RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT | RTC_C_CLOCK_ALARM_INTERRUPT);

    /* Start RTC Clock */
    RTC_C_startClock();  //����RTCʱ��
    Interrupt_enableInterrupt(INT_RTC_C);//ʹ��RTC�ж�
    Interrupt_enableMaster();//ʹ���ж�  

 }

/* RTC ISR */
void RTC_C_IRQHandler(void) //RTC�жϺ���
{
    uint32_t status;

    status = RTC_C_getEnabledInterruptStatus();//��ȡRTC�жϵ�״̬
    RTC_C_clearInterruptFlag(status);          //����ж�״̬

    if (status & RTC_C_CLOCK_READ_READY_INTERRUPT)
    {
        newTime = RTC_C_getCalendarTime();    //��ȡʱ��
    }

    if (status & RTC_C_TIME_EVENT_INTERRUPT)  //ÿ���Ӵ������¼�
    {
      
			
			
    }

    if (status & RTC_C_CLOCK_ALARM_INTERRUPT)  //��������ʱ�� �������¼�
    {
      
		
			
    }

}

 
 
