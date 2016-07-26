

#include "sys.h"
#include "TIMx.h"
#include "middle_led.h"
#include "adc.h"
#include "UnitCfg.h"

volatile u16 TIM2_MS=0;
/*******************************************************************************
**��	��:  	Init_TIMx()
**��	��:  	ͨ�ö�ʱ��TIM2/TIM3/TIM4/TIM5 ��ʼ��
**��    ��:  	TIMx	-- TIM2/TIM3/TIM4/TIM5
**				psc		-- Ԥ��Ƶֵ
**				arr		-- �Զ���װֵ
**��	��:  	null
**˵	����	Init_TIMx(TIM2,31,Count);	//1us ��λ
				Ĭ�����ϼ���
********************************************************************************/
void Init_TIMx(TIM_TypeDef *TIMx,u16 psc,u16 arr)
{
	u8 x=0;

	x = ((u32)TIMx - TIM2_BASE)/(0x0400);
	RCC->APB1ENR |= (1<<x);	

 	TIMx->ARR  = arr;  			//�Զ���װֵ
	TIMx->PSC  = psc;  			//Ԥ������    CK_CNT = fck_psc/(psc+ 1) = 32M/(psc+1)	
								// 100Khz = 10us  : psc = 320
	TIMx->CR2 &= ~(0xF<<4);		//����ģʽ
	TIMx->CR2 |= 4<<4;			//

	TIMx->DIER|=1<<0; 			//ʹ���ж�	
    MY_NVIC_Init(2,3,TIM2_IRQn,2);	
	
	TIMx->CNT  = 0;				//�������	
    //TIMx->CR1 |= 1<<0;   		//ʹ�ܶ�ʱ��
}

void TIMx_Start(TIM_TypeDef *TIMx,u16 arr)
{
	TIM2_MS = 0;
 	TIMx->ARR  = arr;  			//�Զ���װֵ
	TIMx->CNT  = 0;				//�������	
    TIMx->CR1 |= 1<<0;   		//ʹ�ܶ�ʱ��	
}

u32 TIMx_Stop(TIM_TypeDef *TIMx)
{
	u32 count=0;
	count = TIMx->CNT;
	TIMx->CR1 &=~(1<<0);   		//�رն�ʱ��
	count += TIM2_MS*1000;
	return  count;
}
/******************************************************************************
** ��������: TIM2_IRQHandler
** ��������: ��ʱ��2�жϷ������
** �䡡��:   ferq: �û����õ����Ƶ��ֵ
** ��  ��:   ��
******************************************************************************/
void TIM2_IRQHandler(void)
{   
	if(TIM2->SR&0X0001)
	{	
		TIM2_MS++;
		//TIM2->CR1 &=~(1<<0);   		//�رն�ʱ��
	}				   
	TIM2->SR&=~(1<<0);
}
void TIM3_IRQHandler(void)
{   
	if(TIM3->SR&0X0001)
	{	
		
	}				   
	TIM3->SR&=~(1<<0);
}
void TIM4_IRQHandler(void)
{   
	if(TIM4->SR&0X0001)
	{	
		
	}				   
	TIM4->SR&=~(1<<0);
}
void TIM5_IRQHandler(void)
{   
	if(TIM5->SR&0X0001)
	{	
		
	}				   
	TIM5->SR&=~(1<<0);
}

/**************************FILE*END********************************/

