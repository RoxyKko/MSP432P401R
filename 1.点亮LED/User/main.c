#include "main.h"

/*  ȫ�ֱ���������  */

/* �������������� */

int main(void)
{
  SystemClockInit(HFXT); // ϵͳʱ�ӳ�ʼ��
  RtcInit();             // ��ʼ��RTCʵʱʱ��

  volatile uint32_t i = 0;

  MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // ����P1.0Ϊ���

  while (1)
  {

    MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); // ��תP1.0
	delay_ms(200);

  }
}
