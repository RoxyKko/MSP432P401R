/*
 * @Author       : RoxyKko
 * @Date         : 2023-06-25 15:08:33
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-06-25 15:20:01
 * @Description  : MSP432P401R ���ð����ж�
 */
#include "main.h"

/*  ȫ�ֱ���������  */

/* �������������� */

/* MSP432P401R ���ð����жϷ��� :
  * 1. ����P1.1Ϊ���룬����������
  * 2. ���P1.1���жϱ�־λ
  * 3. ʹ��P1.1���ж�
  * 4. ʹ��P1���ж�
  * 5. ���жϷ������У��ж�P1.1�Ƿ�Ϊ�͵�ƽ������ǣ�ִ����Ӧ�Ĳ���
  * 6. ��main�����У�ʹ�����ж�
  */


int main(void)
{
  SystemClockInit(HFXT); // ϵͳʱ�ӳ�ʼ��
  RtcInit();             // ��ʼ��RTCʵʱʱ��

  volatile uint32_t i = 0;

  MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);                  // ����P1.0Ϊ���

  MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1); // ����P1.1Ϊ���룬����������
  MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);              // ���P1.1���жϱ�־λ
  MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);                 // ʹ��P1.1���ж�
  MAP_Interrupt_enableInterrupt(INT_PORT1);                           // ʹ��P1���ж�

  MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK1); // ʹ��SRAM Bank1���ֹ���

  MAP_Interrupt_enableMaster(); // ʹ�����ж�

  while (1)
  {
    MAP_PCM_gotoLPM0(); // ����͹���ģʽ0
  }
}

/* GPIO ISR */
void PORT1_IRQHandler(void)
{
  uint32_t status;

  status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1); // ��ȡP1���ж�״̬
  MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);         // ���P1���жϱ�־λ

  /* ��ת�������LED�ĵ�ƽ */
  // ����status & GPIO_PIN1����˼�ǣ����P1.1���ŵ��жϱ�־λΪ1����ô��ִ������Ĳ���
  // ��ΪMSP432���ж����Ÿߵ͵�ƽ�Ƚ���֣�������żĴ������Լ������ź���ͬ����ô���Ǹߵ�ƽ��������ǵ͵�ƽ
  // ������ΪMSP432��GPIO�Ĵ�����32λ�ģ������ź�ֻ��5λ������������żĴ��������ź���ͬ����ô���Ǹߵ�ƽ��MSP432��GPIO�Ĳ������ǶԵ���λ���в����ģ����Ƕ�һ���Ĵ�������в�����
  // ����������status & GPIO_PIN1���ж�P1.1���ŵ��жϱ�־λ�Ƿ�Ϊ1
  if(status & GPIO_PIN1)
  {
    MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
  }

}
