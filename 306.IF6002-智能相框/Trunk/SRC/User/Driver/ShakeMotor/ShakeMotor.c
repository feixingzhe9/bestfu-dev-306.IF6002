/***************************Copyright BestFu ***********************************
**  ��    ��:   ShakeMotor.c
**  ��    �ܣ�  <<������>>���������
**  ��    �룺  Keil uVision5 V5.10
**  ��    ����  V1.1.0
**  ��    д��  Seven
**  �������ڣ�  2014.08.20
**  �޸����ڣ�  2014.08.20
**  ˵    ����  
*******************************************************************************/
#include "ShakeMotor.h"
#include "BF_type.h"
#include "GPIO.h"
#include "delay.h"

u8 gMotorRunFlag;

/*******************************************************************************
**��    ��:  ShakeMotor_Init()
**��    ��:  ������ʼ��
**��    ��:  void                  
**��    ��:  void
*******************************************************************************/
void ShakeMotor_Init(void)
{   
    GPIOx_Cfg(MOTOR_PORT, MOTOR_PIN, OUT_PP_2M);
    GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
}

/*******************************************************************************
**��    ��:  ShakeMotor_Start()
**��    ��:  �����
**��    ��:  void                  
**��    ��:  void
*******************************************************************************/
void ShakeMotor_Start(void)
{   
    GPIOx_Set(MOTOR_PORT, MOTOR_PIN);
}

/*******************************************************************************
**��    ��:  ShakeMotor_Stop()
**��    ��:  ֹͣ���
**��    ��:  void                  
**��    ��:  void
*******************************************************************************/
void ShakeMotor_Stop(void)
{   
    GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
}
/*******************************************************************************
**��    ��:  ShakeMotor_RunState()
**��    ��:  �������״̬��
**��    ��:  void               
**��    ��:  void
**˵    ���� �ú��� ÿ�� 10ms ����һ��
             ������ʱ������ �����
*******************************************************************************/
void ShakeMotor_RunState(void)
{
    static u8 run_count;
    static u8 stop_count;
    
    if(gMotorRunFlag==1)
    {
        gMotorRunFlag = 0;
        run_count = 2;
        stop_count= 3;
    }
    else if(gMotorRunFlag==2)
    {
        gMotorRunFlag = 0;
        run_count = 6;
        stop_count= 3;
    }
    if(run_count)
    {
        run_count--;
        GPIOx_Set(MOTOR_PORT, MOTOR_PIN);
    }
    else if(stop_count)
    {
        stop_count--;
        GPIOx_Rst(MOTOR_PORT, MOTOR_PIN);
        //if(stop_count==0) GetMPU6050Flag=0;
    }
}

/***************************Copyright BestFu **********************************/
