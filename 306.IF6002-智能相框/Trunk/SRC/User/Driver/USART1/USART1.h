#ifndef __USART1_H
#define __USART1_H

#include <stdio.h>	
#include "BF_type.h"

#define EN_USART1_RX 			0		//ʹ�ܴ���1����
#define USART1_SUPPORT_PRINTF	0		//ʹ�ܴ���1֧��printf()����
	  	

extern void USART1_Init(u32 pclk2,u32 bound);
extern void USART1_SendByte(u8 ch);

#endif	   

