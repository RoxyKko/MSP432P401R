/*
 * @Author       : RoxyKko
 * @Date         : 2023-06-25 20:39:13
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-06-26 10:50:54
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
    SysInit(); 		// ϵͳʱ�ӳ�ʼ��
	LED_Init();		// 
	TimA0_Init_IT(37499,64);	//��ʱ��A 0�жϿ�ʼ
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); // ����DCOƵ��Ϊ48MHz
	
    TFT_Init();   // ��ʼ������2��������115200
	
	MAP_Interrupt_enableMaster(); // �������ж�
    while (1)
    {
        
//        Usart2_SendString("222\r\n", strlen("222\r\n"));
//        delay_ms(50);
    }
}

