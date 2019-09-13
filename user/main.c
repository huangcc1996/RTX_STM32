//头文件
#include "myheader.h"
/********************************************
								堆栈声明
*********************************************/
static uint64_t AppTaskStartStk[256/8];
static uint64_t AppTaskLEDStk[128/8];

/********************************************
								句柄声明
*********************************************/
OS_TID HandleTaskLED = 0;

/********************************************
								函数声明
*********************************************/
void GPIO_Configuration(void);
__task void AppTaskStart(void);
__task void AppTaskLED(void);

/********************************************
								主函数
*********************************************/
int main(void)
{
	  GPIO_Configuration();
		
		
		os_sys_init_user(AppTaskStart,2,&AppTaskStartStk,sizeof(AppTaskStartStk));
    while(1);

}

//=============================================================================
//文件名称：GPIO_Configuration
//功能概要：GPIO初始化
//参数说明：无
//函数返回：无
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
//文件名称：AppTaskStart
//功能概要：开始任务
//参数说明：无
//函数返回：无
//=============================================================================
__task void AppTaskStart(void)
{
		HandleTaskLED = os_tsk_create_user(AppTaskLED,1,&AppTaskLEDStk,sizeof(AppTaskLEDStk)); //创建一个LED任务
		while(1)
		{
			
			os_dly_wait(600);
			
			
		}
}

//=============================================================================
//文件名称：AppTaskStart
//功能概要：LED任务
//参数说明：无
//函数返回：无
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
