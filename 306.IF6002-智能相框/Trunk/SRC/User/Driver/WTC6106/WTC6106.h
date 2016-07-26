/***************************Copyright BestFu ***********************************
**  ��    ����  WTC6216.h
**  ��    �ܣ�  <<������>> ����������оƬWTC6216����
**  ��    �룺  Keil uVision5 V5.10
**  ��    ����  V1.0
**  ��    д��  Seven
**  �������ڣ�  2014.08.18
**  �޸����ڣ�  2014.08.18
**  ˵    ����  
**  V1.0
    >> WTC6106BSI-L  ��ͨ������оƬ
*******************************************************************************/
#ifndef _WTC6106_H
#define _WTC6106_H

#include "GPIO.h"
#include "BF_type.h"	

//#define GPIO_WTC_TouchFlag		GPIOA
//#define PORT_WTC_TouchFlag		GPIO_A
//#define PIN_WTC_TouchFlag		    (1<<0)

#define GPIO_WTC_DATA			GPIOA
#define PORT_WTC_DATA			GPIO_A

#define DATA1 		(1<<1)	//PA1
#define DATA2 		(1<<2)	//PA2
#define DATA3 		(1<<3)	//PA3
#define DATA4 		(1<<4)	//PA4
#define DATA5 		(1<<5)	//PA3
#define DATA6 		(1<<6)	//PA4

extern void WTC6106_PortInit(void);
extern u8   WTC6106_ReadKey(void);

#endif	   

/***************************Copyright BestFu **********************************/
