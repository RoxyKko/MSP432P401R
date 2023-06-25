/*
 * @Author       : RoxyKko
 * @Date         : 2023-06-25 15:22:15
 * @LastEditors  : RoxyKko
 * @LastEditTime : 2023-06-25 17:29:08
 * @Description  : ���ڵĻ���ʹ��
 */
#include "main.h"

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

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,   // ʱ��ԴΪSMCLK
    312,                              // BRDIV = 312 (SMCLK = 48MHz, ������Ϊ9600)
    0,                                // UCxBRF = 0
    0,                                // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,           // ��У��
    EUSCI_A_UART_LSB_FIRST,           // ��λ��ǰ
    EUSCI_A_UART_ONE_STOP_BIT,        // 1λֹͣλ
    EUSCI_A_UART_MODE,                // UARTģʽ
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION // ������
};

int main(void)
{
    SystemClockInit(HFXT); // ϵͳʱ�ӳ�ʼ��
    RtcInit();             // ��ʼ��RTCʵʱʱ��

    volatile uint32_t i = 0;

    // ����P3.2 P3.3Ϊ����ģʽ
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION); 

    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48); // ����DCOƵ��Ϊ48MHz

    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig); // ��ʼ������ģ��

    MAP_UART_enableModule(EUSCI_A2_BASE); // ʹ�ܴ���ģ��

    while (1)
    {
        for (i = 0; i < 100000; i++) {} // �ӳ�һ��ʱ��

        // �����ַ��� "232"
        MAP_UART_transmitData(EUSCI_A2_BASE, '2');
        MAP_UART_transmitData(EUSCI_A2_BASE, '3');
        MAP_UART_transmitData(EUSCI_A2_BASE, '2');
		MAP_UART_transmitData(EUSCI_A2_BASE, '\r');
		MAP_UART_transmitData(EUSCI_A2_BASE, '\n');
    }
}


