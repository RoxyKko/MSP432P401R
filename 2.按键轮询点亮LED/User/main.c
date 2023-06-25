#include "main.h"

/*  ȫ�ֱ���������  */

/* �������������� */

int main(void)
{
  SystemClockInit(HFXT); // ϵͳʱ�ӳ�ʼ��
  RtcInit();             // ��ʼ��RTCʵʱʱ��

  volatile uint32_t i = 0;

  MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);                  // ����P1.0Ϊ���
  MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); // ����P1.1Ϊ���룬����������

  MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1); // ʹ��SRAM Bank1���ֹ���

  while (1)
  {
    if (MAP_GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) // ���P1.1Ϊ�͵�ƽ
    {
      delay_ms(50);
      if (MAP_GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == GPIO_INPUT_PIN_LOW) // ���P1.1Ϊ�͵�ƽ
      {
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0); // P1.0����ߵ�ƽ
      }
      else
      {
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0); // P1.0����͵�ƽ
      }
    }
  }
}
