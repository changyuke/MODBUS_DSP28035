/***********************************************************************
 *                                  ���հ�
 *************************************************************************/
#include "../OnChip_Driver/OnChip_Driver_Inc.h"
#include "../MyBSP/MyBspInc.h"

//�궨��������

//����������
void Gpio_LedInit(void);

#if DEBUG_EN	> 0
#else
#pragma CODE_SECTION(Gpio_LedInit, "ramfuncs");	//��Ϊ��ʾ,������Gpio_LedInit()������RAM������

extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;
#endif

//����������

Uint16 buffer[9] = {0};
unsigned char test[5] = {0};

//��������ڴ�(modbus��)
void main(void)
{
// ��һ��: ��ʼ��ϵͳϵͳʱ��,������PLL, ���Ź�ʱ��, ����ʱ�ӵĿ���;
  	InitSysCtrl();

// �ڶ���: ��������жϱ�־����ʼ��PIE�ж�������
   	DINT;			//�Ƚ�ֹCPU�ж�
   	InitPieCtrl();	//��PIE�Ĵ�������ֵ
   	IER = 0x0000;	//��ֹCPU���жϲ����������ص��жϱ�־
   	IFR = 0x0000;
   	InitPieVectTable();//��ʼ���ж�������

	#if DEBUG_EN	> 0				/* ������ݺ궨���ж���ʹ������ģʽ,���DEBUG_EN > 0��ʲô������,
										 �������Flash�̻�ģʽ,��Ҫִ��flash�ĳ�ʼ�������趨�Ĳ�����
										 RAM�������еĴ��뿽����flash����*/
	#else
		MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
		InitFlash();			//��ʼ��flash
	#endif

// ����������ʼ������ʹ�õ�����
   	Gpio_LedInit();			//��ʼ��GPIO(��Ϊ��ͨIOʹ��,����Ϊ���)
	USARTA_Init(57600);
//	Prints("hello wrold!");
//	Prints("USART Test Begin:\r\n");
//	Prints("Send DSP Some data,It Will Send Them Bcak!\r\n");
	TIM0_Init(60,500);//��ʱ����ʼ��--500us
	Flash_Modbus_ADDR = 0x0001;
	Flash_Usart_BaudRate = 0x0007;
	LED_ON;
	Delay_nMS(1000);
	LED_OFF;
	while(1)
	{
		MODBUS_event();
	}
}
