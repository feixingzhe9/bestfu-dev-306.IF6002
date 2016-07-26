/*******************************************************************************
**	��    ��: USART1.c
**  ��    �ܣ�����1 ���� ���Ĵ���������
**  ��    �룺Keil uVision5 V5.10
**	о    Ƭ: STM32L151xx
**  ��    ����V1.0.1
**  ��    д��Seven
**  �������ڣ�2014.04.15
**  �޸����ڣ�2014.05.06
**  ˵    ����  1.����1��ӡ����  	OK
				2.���ͺ�������timeout
********************************************************************************/
																				
#include "STM32L1xx.h"                 
#include "sys.h"
#include "USART1.h"	 
#include "GPIO.h"

/*>>�������´���,֧��printf����,������Ҫѡ��use MicroLIB*/  
#if USART1_SUPPORT_PRINTF
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
		while((USART1->SR&0X40)==0)
		{
			if(0==timeout--) break;
		}
		USART1->DR = (u8) ch;      
		return ch;
	}
#endif 

#if EN_USART1_RX   //���ʹ���˽���

/*******************************************************************************
**��	��:  	USART1_IRQHandler()
**��	��:  	����1�жϷ������
**��    ��:  	null
**��	��:  	null
**˵	����	����MPU6050ģ��һ֡����
********************************************************************************/
void USART1_IRQHandler(void)
{
	if((USART1->SR&(1<<5)) != 0)			//���յ�����
	{	 
//		MPU6050_RX_BUF[MPU6050_RX_Counter]=USART1->DR; 
//		if((MPU6050_RX_Counter == 0) && (MPU6050_RX_BUF[0] != 0x55)) return;      //�� 0 �����ݲ���֡ͷ������
//		MPU6050_RX_Counter++; 
//		if(11 == MPU6050_RX_Counter) 		//���յ� 11 ������
//		{ 
//			MPU6050_RX_Counter=0; 			//���¸�ֵ��׼����һ֡���ݵĽ���
//			if(0x53==MPU6050_RX_BUF[1])		MPU6050_RX_Flag=1;//ֻ���մ�����̬������
//		} 
	}	
} 
#endif										 


/*******************************************************************************
**��	��:  	USART1_Init()
**��	��:  	����1��ʼ��
**��    ��:  	pclk2		--PCLK2ʱ��Ƶ��(Mhz)  Ĭ��ʹ��32M	
				bound		--������
**��	��:  	null
**˵	����	Ĭ�����ݸ�ʽ--8λ����,1λֹͣ,��У��λ.
********************************************************************************/
void USART1_Init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 		//�õ���������
	fraction=(temp-mantissa)*16; 		//�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	
	RCC->AHBENR |=1<<0;   				//ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  				//ʹ�ܴ���1ʱ�� 
	RCC->APB2RSTR|=  1<<14;   			//��λ����1
	RCC->APB2RSTR&=~(1<<14);			//ֹͣ��λ	 	
	
	GPIOx_Cfg(GPIO_A,pin_9,AF_PP_40M);  //TX
	GPIOx_AF (GPIO_A,pin_9,AF_USART1);	
	GPIOx_Cfg(GPIO_A,pin_10,AF_PP_40M); //RX ��̬���� ��F103�����
	GPIOx_AF (GPIO_A,pin_10,AF_USART1);
	  
 	USART1->BRR=mantissa; 				// ����������	  
	USART1->CR1|=(1<<13)|(1<<3)|(1<<2); //(UE)ʹ��usart1 (TE)ʹ�ܷ��� (RE)ʹ�ܽ���//8bit���� 1bitֹͣ,��У��λ.
	//while((USART1->SR&(1<<6))== 0){}  //�ȴ��������
#if EN_USART1_RX		  				//ʹ�ܽ����ж�
	USART1->CR1|=(1<<5);    			//(RXNEIE)�����ж�ʹ�� 	    
	MY_NVIC_Init(2,1,USART1_IRQn,2);
#endif
}

/*******************************************************************************
**��	��:  	USART1_SendByte()
**��	��:  	����1���͵����ֽ�
**��    ��:  	ch			--���͵��ַ�
**��	��:  	null
**˵	����	
********************************************************************************/
void USART1_SendByte(u8 ch)
{
	unsigned long timeout=0xFFFF;
	while((USART1->SR&0X40)==0)//�ȴ��������
	{
		if(0==timeout--) break;
	}
	USART1->DR = (u8) ch;  
}



