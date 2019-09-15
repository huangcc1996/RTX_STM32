//ͷ�ļ�
#include "myheader.h"
/********************************************
								��ջ����
*********************************************/
static uint64_t AppTaskStartStk[512/8];
static uint64_t AppTaskLEDStk[512/8];
static uint64_t AppTaskUart1Stk[512/8];
/********************************************
								�������
*********************************************/
OS_TID HandleTaskLED   = 0;
OS_TID HandleTaskUart1 = 0;
/********************************************
								��������
*********************************************/
void GPIO_Configuration(void);
__task void AppTaskStart(void);
__task void AppTaskLED(void);
__task void AppTaskUart1(void);
u8 HexToChar(u8 chr);



u8 RECBUF[1024];
/********************************************
								������
*********************************************/
int main(void)
{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// �����ж����ȼ�����4
	  GPIO_Configuration();
		uart_init(115200);
		MYDMA_Config(DMA1_Channel6,(u32)&USART2->DR,(u32)RECBUF,sizeof(RECBUF));
	
		os_sys_init_user(AppTaskStart,2,&AppTaskStartStk,sizeof(AppTaskStartStk));
    while(1);

}

//=============================================================================
//�ļ����ƣ�GPIO_Configuration
//���ܸ�Ҫ��GPIO��ʼ��
//����˵������
//�������أ���
//=============================================================================
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
//=============================================================================
//LED -> PC13
//=============================================================================			 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


	
//=============================================================================
//�ļ����ƣ�AppTaskStart
//���ܸ�Ҫ����ʼ����
//����˵������
//�������أ���
//=============================================================================
__task void AppTaskStart(void)
{
		HandleTaskLED = os_tsk_create_user(AppTaskLED,1,&AppTaskLEDStk,sizeof(AppTaskLEDStk)); //����һ��LED����
		HandleTaskUart1 = os_tsk_create_user(AppTaskUart1,3,&AppTaskUart1Stk,sizeof(AppTaskUart1Stk)); //����һ��LED����
		while(1)
		{
			os_dly_wait(600);
			
		}
}

//=============================================================================
//�ļ����ƣ�AppTaskStart
//���ܸ�Ҫ��LED����
//����˵������
//�������أ���
//=============================================================================
__task void AppTaskLED(void)
{
		while(1)
		{
			
			PCout(13)=1;
			os_dly_wait(200);
			PCout(13)=0;
			os_dly_wait(200);
			//os_evt_set(1, HandleTaskUart1);
		}
}
__task void AppTaskUart1(void)
{
		OS_RESULT xResult;

		while(1)
		{
			xResult = os_evt_wait_and (1, 10);
			
			switch(xResult)
			{
				case OS_R_EVT:
					printf("Get uart2 Msg!\r\n");
					printf("%s ",RECBUF);
					
					break;
				case OS_R_TMO:
//					printf("Nothing Rec!\r\n");
					break;
					
			}
		}
}
/*
    ��16����ת��ASCII��
*/
u8 HexToChar(u8 chr)
{
    if (chr > 9 && chr < 16)
    {
        return chr + 55;
    }
    return chr + 48;
}
