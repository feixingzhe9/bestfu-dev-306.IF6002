/***************************Copyright BestFu ***********************************
**  文    件：  WTC6216.h
**  功    能：  <<驱动层>> 六按键触摸芯片WTC6216驱动
**  编    译：  Keil uVision5 V5.10
**  版    本：  V1.0
**  编    写：  Seven
**  创建日期：  2014.08.18
**  修改日期：  2014.08.18
**  说    明：  
**  V1.0
    >> WTC6106BSI-L  六通道触摸芯片
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
