/*
 * @Author       : RoxyKko
 * @Date         : 2023-06-25 20:39:13
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-06-25 22:00:49
 * @Description  : �����жϣ������������õĿ��װ����λ�ڹ���Ŀ¼��Basic\Usart��
 */
#include "main.h"
#include "string.h"

/*  ȫ�ֱ���������  */

/* �������������� */

/* MSP432P401R ���� :
 *               MSP432P401
 *             -----------------
 *            |                 |
 *            |                 |
 *            |                 |
 *       RST -|     P3.3/UCA0TXD|----> PC (echo)
 *            |                 |
 *            |                 |
 *            |     P3.2/UCA0RXD|<---- PC
 *            |                 |
 *
 */

int main(void)
{
    SystemClockInit(HFXT); // ϵͳʱ�ӳ�ʼ��
    RtcInit();             // ��ʼ��RTCʵʱʱ��

    volatile uint32_t i = 0;

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); // ����DCOƵ��Ϊ48MHz

    Usart2_Init_It();   // ��ʼ������2��������115200

    while (1)
    {
        
//        Usart2_SendString("222\r\n", strlen("222\r\n"));
//        delay_ms(50);
    }
}

