#include "systeminit.h"

/**********************************	
	ʱ�ӣ�          Ĭ��ʱ��Դ        Ĭ��Ƶ��          ����
	MCLK             DCO              3MHZ          ��ʱ�ӣ���CPU�������ṩʱ��
  HSMCLK       	   DCO              3MHZ          ��ϵͳ��ʱ�ӣ��������ṩʱ��Դ
	SMCLK            DCO              3MHZ          ����ϵͳ��ʱ�ӣ��������ṩʱ��Դ
	ACLK     LFXT(��REFOû�о���ʱ)   32.768kHz     ����ʱ�ӣ��������ṩʱ��
	BCLK     LFXT(��REFOû�о���ʱ)   32.768kHz     ���ٺ�����ʱ�ӣ��ṩLPM����
	
	********************************/
	
void SystemClockInit(u8 ClockSource ){
 /* Halting the Watchdog */
  MAP_WDT_A_holdTimer();

	if(ClockSource==LFXT ){
///////////////////////////////////////////////////////////	
	        /* �����ⲿ����ʱ������*/
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
	
    /* Setting the external clock frequency. This API is optional, but will
     * come in handy if the user ever wants to use the getMCLK/getACLK/etc
     * functions
     */
    CS_setExternalClockSourceFrequency(32768,48000000);

    /* Starting LFXT in non-bypass mode without a timeout. */
    CS_startLFXT(false);

    /* Initializing MCLK to LFXT (effectively 32khz) */ //��ʱ��
    MAP_CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Since we are operating at 32khz, we can operating in LF mode */
   // MAP_PCM_setPowerMode(PCM_LF_MODE);
	}
	else if (ClockSource==HFXT){
////////////////////////////////////////////////////////////////		
		
		    /* �����ⲿ����ʱ������ */
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Just in case the user wants to use the getACLK, getMCLK, etc. functions,
     * let's set the clock frequency in the code. 
     */
    CS_setExternalClockSourceFrequency(32000,48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support the 48MHz frequency */
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    CS_startHFXT(false);//false

    /* Initializing MCLK to HFXT (effectively 48MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
		
	}
	else  if (ClockSource==DCO){
////////////////////////////////////////////////////////////////////////////
           /*DCOʱ��Դ���ã��ڲ���������*/
    /* Enabling FPU for DCO Frequency calculation */
    FPU_enableModule();
    /* Setting the DCO Frequency to a non-standard 12MHz */
    CS_setDCOFrequency(CS_12MHZ);
		CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);//8~16MHZ
		
//	  CS_setDCOFrequency(CS_48MHZ);
//		CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);//8~16MHZ
		CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
			CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);//������ϵͳʱ��
	}
	else {
//////////////////////////////////////////////////////////////////////////////
        /*�ڲ��͹��ĵ�Ƶʱ��*/
			     /*����Ƶ��*/
    CS_setReferenceOscillatorFrequency(CS_REFO_32KHZ); 
    /* Initializing MCLK to REFO */
    MAP_CS_initClockSignal(CS_BCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Since we are operating at 32khz, we can operating in LF mode */
    MAP_PCM_setPowerMode(PCM_LF_MODE);
 
	}

 
}



