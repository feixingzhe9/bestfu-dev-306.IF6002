/***************************Copyright BestFu ***********************************
**  ��    ��:   ShakeMotor.h
**  ��    �ܣ�  <<������>>���������
**  ��    �룺  Keil uVision5 V5.10
**  ��    ����  V1.1.0
**  ��    д��  Seven
**  �������ڣ�  2014.08.20
**  �޸����ڣ�  2014.08.20
**  ˵    ����  
*******************************************************************************/
#ifndef _SHAKE_MOTOR_H_
#define _SHAKE_MOTOR_H_

#include "BF_type.h"

#define MOTOR_PORT GPIO_B
#define MOTOR_PIN  pin_5

extern u8 gMotorRunFlag;

extern void ShakeMotor_Init(void);
extern void ShakeMotor_Run(void);
extern void ShakeMotor_Start(void);
extern void ShakeMotor_Stop(void);

#endif

/***************************Copyright BestFu **********************************/
