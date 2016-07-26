/***************************Copyright BestFu ***********************************
**  ��    ����  Key.c
**  ��    �ܣ�  <<�߼���>> �������� 
**  ��    �룺  Keil uVision5 V5.10
**  ��    ����  V1.1
**  ��    д��  Seven
**  �������ڣ�  2014.08.20
**  �޸����ڣ�  2014.08.20
**  ˵    ����  
**  V1.1
    >> �̰���Ϊ�ͷ�ʱ��ִ�У�����ӳ�������Ӧ
*******************************************************************************/
#ifndef _KEY_H_
#define _KEY_H_

#include "BF_type.h"

#define MAX_TOUCH_KEY       (6+1)   //ͨ��0 ����
#define KEY_SUPPORT_PRINTF   0      //�Ƿ�֧�ִ��ڴ�ӡ

/*����״̬*/
typedef enum
{
    KEY_NONE  = 0,
    KEY_SHORT = 1,
    KEY_LONG  = 2
}KeyState_e;

typedef struct
{
    KeyState_e  Status;
}KeyProp_t;

extern KeyProp_t KeyCh[MAX_TOUCH_KEY];          //��������״̬����

extern void Key_Init(void);                     //������ʼ��
extern u8   Key_Scan(u8 *keyFlag);              //��������ɨ��
extern void Key_Handle(void);                   //��ͨ��������
extern u8   Key_FirstScan(void);                //�״ΰ���ɨ��
extern void Key_FirstHandle(u8 Key);            //�״ΰ�������

#endif

/***************************Copyright BestFu **********************************/
