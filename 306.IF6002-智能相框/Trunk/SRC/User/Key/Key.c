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
#include "Key.h"
#include "LinkAll.h"
#include "delay.h"
#include "LowPower.h"
#include "WTC6106.h"
#include "USART1.h"
#include "MsgPackage.h"
#include "ShakeMotor.h"

/*��������ֵ*/
const u8 NONE_KEY=63;       
const u8 KEY6    =62;
const u8 KEY5    =61;
const u8 KEY4    =59;
const u8 KEY3    =55;
const u8 KEY2    =47;
const u8 KEY1    =31;

/*��������ֵ--�ṩ�����Բ�ʹ��*/
KeyProp_t  KeyCh[MAX_TOUCH_KEY];        //KeyCh[0] ����

static u8  NewKey,OldKey,LstKey;
static u16 LongKeyCount;                //������������
const  u16 LONG_KEY_TIMES = 100;        //����������ʱ�� 100 *10ms = 1S

extern u32 Time_Get(void);

/*******************************************************************************
**��    ���� Key_Init()
**��    �ܣ� ����ģ���ʼ��
**��    ���� void
**��    �أ� void
*******************************************************************************/
void Key_Init(void)
{
    WTC6106_PortInit();
    NewKey=NONE_KEY;
    OldKey=NONE_KEY;
    LstKey=NONE_KEY;
}
/*******************************************************************************
**��    ���� Key_Scan()
**��    �ܣ� ״̬����ʽɨ������
**��    ���� *keyFlag    ������־    0-�ް���  1-�̰���    2-������ 
**��    �أ� ����ֵ
**˵    ���� �ú��� ÿ�� 5~20ms ����һ��
*******************************************************************************/
u8 Key_Scan(u8 *keyFlag)
{
    static u8 MidValidKey = NONE_KEY;                               //��Ч�����м䱣��ֵ
    #if USART1_SUPPORT_PRINTF
    static u8 old;    
    if( old != NewKey)
    {
        old = NewKey;
        printf("read key = %d \r\n",NewKey); 
    }
    #endif
    
    *keyFlag = 0;
    NewKey = WTC6106_ReadKey();    
    if(NewKey == OldKey)
    {
        if(NewKey==NONE_KEY)                                        //�ް��� �� �ͷŰ���    
        {   
            if((LstKey != NONE_KEY)&&(LongKeyCount<LONG_KEY_TIMES)) // �ͷŰ��� �� �ǳ�����
            {
                if(LongKeyCount>5)  //���˳��̰��� �����ȿɵ�
                {
                    LstKey  = NONE_KEY;
                    LongKeyCount = 0;
                    *keyFlag =1;
                    return MidValidKey;                             //���ض̼��ͷ�
                }
            }
            else{                                                   
                LstKey = NONE_KEY;
                LongKeyCount = 0;
                return NONE_KEY;                    
            }
        }
        else if(NewKey==LstKey)                                     //��������
        {
            if(LongKeyCount++ == LONG_KEY_TIMES)
            {
                *keyFlag =2;
                return MidValidKey;                                 //���س���ȷ��
            }
        }
        else{                                                       //����
            LstKey = NewKey;
            switch(NewKey)
            {
                case KEY1:
                    MidValidKey = 3;
                    break;
                case KEY2:
                    MidValidKey = 2;
                    break;
                case KEY3:
                    MidValidKey = 1;
                    break;
                case KEY4:
                    MidValidKey = 4;
                    break;
                case KEY5:
                    MidValidKey = 5;
                    break;
                case KEY6:
                    MidValidKey = 6;
                    break;
                default:
                    MidValidKey = NONE_KEY;
                    break;
            }
            return NONE_KEY ;         
        }
    }
    else OldKey = NewKey;               //��������
    return NONE_KEY;
}

/*******************************************************************************
**��    ���� Key_Handle()
**��    �ܣ� ��������
**��    ���� void 
**��    �أ� void
**˵    ���� �ú��� ÿ�� 5~20ms ����һ��
*******************************************************************************/
void Key_Handle(void)
{
    u8 i,ch,key_flag;
    u32 curTime;
    static u32 oldTime=0;
    
    ch = Key_Scan(&key_flag);

    if( ch != NONE_KEY)
    {
        /*����ϴ�״̬*/
        for(i=0;i<MAX_TOUCH_KEY;i++)
        {
            KeyCh[i].Status = KEY_NONE; 
        }  
        /* ���������� 500ms */
        curTime = Time_Get();          //��λms 
        if( (curTime-oldTime) < 500)   //10s ϵͳ˯�ߣ����ÿ������
        {
            oldTime = curTime;
            return;
        }
        oldTime = curTime;
        StandbyCountReset();
        ShakeMotor_Start();
        Thread_Login(ONCEDELAY, 1, 200 , &ShakeMotor_Stop);
        
        if(1 == key_flag)
        {
            KeyCh[ch].Status = KEY_SHORT; 
            PropEventFifo(1, ch, SRCEVENT , KEY_SHORT);     //50ms          
            Upload(1);                                       //2.5s//�ϱ�
        }
        else if(2 == key_flag)
        {
            KeyCh[ch].Status = KEY_LONG;    
            PropEventFifo(1, ch, SRCEVENT , KEY_LONG);        
            Upload(1);                                       //�ϱ�
        }
//        #if USART1_SUPPORT_PRINTF
//        printf("New Key = %d ,flag = %d \r\n",ch,key_flag);
//        #endif
    }
}

/*******************************************************************************
**��    ��:  Key_FirstScan()
**��    ��:  ��������ɨ��
**��    ��:  void
**��    ��:  �״���Ч����ֵ 
*******************************************************************************/
u8 Key_FirstScan(void)
{
    u8 first_key = NONE_KEY;
    u8 temp_key  = NONE_KEY;
    
    first_key = WTC6106_ReadKey();
    delay_us(200);
    if(first_key == WTC6106_ReadKey())
    {
        switch(first_key)
        {
            case KEY1:
                temp_key = 3;
                break;
            case KEY2:
                temp_key = 2;
                break;
            case KEY3:
                temp_key = 1;
                break;
            case KEY4:
                temp_key = 4;
                break;
            case KEY5:
                temp_key = 5;
                break;
            case KEY6:
                temp_key = 6;
                break;
            default:
                temp_key = NONE_KEY;
                break;
        }
    }
    return temp_key;
}

/*******************************************************************************
**��    ��:  Key_FirstHandle()
**��    ��:  �״ΰ���������
**��    ��:  ����ֵ
**��    ��:  void
********************************************************************************/
void Key_FirstHandle(u8 Key)
{
    if( Key != NONE_KEY)
    {   
        ShakeMotor_Start();
        Thread_Login(ONCEDELAY, 1, 200 , &ShakeMotor_Stop);
        KeyCh[Key].Status = KEY_SHORT; 
        PropEventFifo(1, Key, SRCEVENT , KEY_SHORT);
        Upload(1); 
        #if KEY_SUPPORT_PRINTF
        printf("First Key = %d ,ShortKey \r\n",Key);
        #endif        
    }
}

/***************************Copyright BestFu **********************************/
