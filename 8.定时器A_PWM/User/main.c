/*
 * @Author       : RoxyKko
 * @Date         : 2023-06-25 20:39:13
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-06-27 19:35:57
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
 * ��ʱ���ж����ڣ�
 *
 * T_timer_a = CLKDIV * (CCR0 + 1) / f_clk 
 *           = 64 * 37500 / 48000000 
 *           = 0.05s = 20Hz
 */

int main(void)
{
    SysInit(); 		// ϵͳʱ�ӳ�ʼ��
	LED_Init();		// 
	TimA0_Init_PWM(37499,64);	//��ʱ��A 0�жϿ�ʼ
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); // ����DCOƵ��Ϊ48MHz
	
    TFT_Init();   // ��ʼ������2��������115200
	
	MAP_Interrupt_enableMaster(); // �������ж�
    while (1)
    {
        

    }
}

