/*
 * led.c
 *
 *  Created on: 2022��3��17��
 *      Author: Administrator
 */
#include "leds.h"

void Gpio_LedInit(void)
{
	EALLOW;									//GPIO�Ĵ����ܱ���
	//LED�˿�����
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;		//GPIO40��Ϊ��ͨIO
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;		//GPIO40����Ϊ���
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;		//ʹ��GPIO��������
//	GpioDataRegs.GPADAT.bit.GPIO3 = 1;  	//GPIO40����ߵ�ƽ

	EDIS;
}


