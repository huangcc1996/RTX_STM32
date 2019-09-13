//ͷ�ļ�
#include "myheader.h"
/********************************************
								��ջ����
*********************************************/
static uint64_t AppTaskStartStk[256/8];
static uint64_t AppTaskLEDStk[128/8];

/********************************************
								�������
*********************************************/
OS_TID HandleTaskLED = 0;

/********************************************
								��������
*********************************************/
void GPIO_Configuration(void);
__task void AppTaskStart(void);
__task void AppTaskLED(void);

/********************************************
								������
*********************************************/
int main(void)
{
	  GPIO_Configuration();
		
		
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
		}
}
