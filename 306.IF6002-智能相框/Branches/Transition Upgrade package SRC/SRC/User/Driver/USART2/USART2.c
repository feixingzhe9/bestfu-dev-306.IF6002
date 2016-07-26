/*******************************************************************************
**	��    ��: USART2.c
**  ��    �ܣ�����2 ���� ���Ĵ���������
**  ��    �룺Keil uVision5 V5.10
**	о    Ƭ: STM32L151xx
**  ��    ����V1.0.1
**  ��    д��Seven
**  �������ڣ�2014.04.15
**  �޸����ڣ�2014.05.06
**  ˵    ����  1.����2��ӡ����  	OK
				2.���ͺ�������timeout
********************************************************************************/

#include "STM32L1xx.h"                 
#include "sys.h"
#include "GPIO.h"
#include "USART2.h"

/*>>�������´���,֧��printf����,������Ҫѡ��use MicroLIB*/  
#if USART2_SUPPORT_PRINTF
	#pragma import(__use_no_semihosting)                           
	struct __FILE 
	{ 
		int handle; 
	}; 
	FILE __stdout;        
	void _sys_exit(int x) 
	{ 
		x = x; 
	} 
	int fputc(int ch, FILE *f)
	{   
		unsigned long timeout=0xFFFF;
		while((USART2->SR&0X40)==0)
		{
			if(0==timeout--) break;
		}
		USART2->DR = (u8) ch;      
		return ch;
	}
#endif 

#if EN_USART2_RX   //���ʹ���˽���


/*******************************************************************************
**��	��:  	USART1_IRQHandler()
**��	��:  	����1�жϷ������
**��    ��:  	null
**��	��:  	null
**˵	����	����MPU6050ģ��һ֡����
********************************************************************************/
void USART2_IRQHandler(void)
{
	if((USART2->SR&(1<<5)) != 0)//���յ�����
	{	 
		//MPU6050_RX_BUF[MPU6050_RX_Counter]=USART2->DR; 
	}	
} 
#endif										 


/*******************************************************************************
**��	��:  	USART1_Init()
**��	��:  	����1��ʼ��
**��    ��:  	pclk1		--PCLK1ʱ��Ƶ��(Mhz)  Ĭ��ʹ��32M	
				bound		--������
**��	��:  	null
**˵	����	
********************************************************************************/
void USART2_Init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	RCC->AHBENR |=1<<0;   				//ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  				//ʹ�ܴ���2ʱ�� 
	RCC->APB1RSTR|=  1<<17;   			//��λ����1
	RCC->APB1RSTR&=~(1<<17);			//ֹͣ��λ	
	
	GPIOx_Cfg(GPIO_A,pin_2,AF_PP_40M); 	//TX
	GPIOx_AF( GPIO_A,pin_2,AF_USART1);	
	GPIOx_Cfg(GPIO_A,pin_3,AF_PP_40M);	//RX     ��̬����
	GPIOx_AF( GPIO_A,pin_3,AF_USART1);
  
 	USART2->BRR = mantissa; 			// ����������	 
	USART2->CR1|=(1<<13)|(1<<3)|(1<<2);	//(UE)ʹ��usart1 (TE)ʹ�ܷ��� (RE)ʹ�ܽ���//8bit���� 1bitֹͣ,��У��λ.
	//while((USART1->SR&(1<<6))==0)  {} //�ȴ��������	
#if EN_USART2_RX		  				//���ʹ���˽���
	USART2->CR2|=(1<<5);   				//(RXNEIE)�����ж�ʹ�� 	     
	MY_NVIC_Init(2,2,USART2_IRQn,2);
#endif
}

/*******************************************************************************
**��	��:  	USART1_SendByte()
**��	��:  	����1���͵����ֽ�
**��    ��:  	ch			--���͵��ַ�
**��	��:  	null
**˵	����	
********************************************************************************/
void USART2_SendByte(u8 ch)
{
	unsigned long timeout=0xFFFF;
	while((USART2->SR&0X40)==0)//�ȴ��������
	{
		if(0==timeout--) break;
	}
	USART2->DR = (u8) ch;  
}



