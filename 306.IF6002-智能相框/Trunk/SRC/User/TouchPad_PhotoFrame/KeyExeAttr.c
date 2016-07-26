/***************************Copyright BestFu ***********************************
**  ��    ��:   KeyExeAttr.c
**  ��    �ܣ�  <<���Բ�>>�������Բ�ӿ�
**  ��    �룺  Keil uVision5 V5.10
**  ��    ����  V1.0.0
**  ��    д��  Seven
**  �������ڣ�  2014/08/21
**  �޸����ڣ�  2014/08/21
**  ˵    ����
**  V1.0
    >> ����״̬ : 0==������   1==������   2==������
*******************************************************************************/
#include "Unitcfg.h"
#include "KeyExeAttr.h" 
#include "BatteryExeAttr.h"
#include "Key.h"
#include "Thread.h"
#include "LowPower.h"
#include "USART1.h"
#include "ShakeMotor.h"

/*���Զ�д�Ľӿ��б�*/
const AttrExe_st KeyAttrTab[] =
{
    {0x01, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x02, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x03, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x04, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x05, LEVEL_1, NULL    , Get_TouchKey_Attr },      
    {0x06, LEVEL_1, NULL    , Get_TouchKey_Attr },  

    {0xC8, LEVEL_1, NULL    , Get_PowerPercent_Attr },   //�̶�����  ��ȡ��ص���
//  {0xC9, LEVEL_1, NULL    , Get_ChargeState_Attr  },   //�̶�����  ��ȡ��س��״̬(���﮵�ز���)  
};

/*******************************************************************************
**��    ���� u8 IF6002_UnitAttrNum(void)
**��    �ܣ� ��ȡ��������������
**��    ���� ��
**��    �أ� ���ظ���
*******************************************************************************/
u8 IF6002_UnitAttrNum(void)
{
	return (BF_DIM(KeyAttrTab));
}

/*******************************************************************************
**��    ���� KeyInit
**��    �ܣ� ��ʼ��
**��    ���� unitID      --��Ԫ��
**��    �أ� void
*******************************************************************************/
void KeyInit(u8 unitID)
{
    #if USART1_SUPPORT_PRINTF
    USART1_Init(32,115200); 
    #endif
    Battery_Init();
    ShakeMotor_Init();
    Thread_Login(FOREVER, 0, 10 , &Key_Handle);           //8ms ����
    Thread_Login(FOREVER, 0, 100, &LowPower_CheckTime);   //100ms*100 = 10s  ˯��
    //Upload();
}

/*******************************************************************************
**��    ���� KeyEepromInit
**��    �ܣ� ���� eeprom ��ʼ��
**��    ���� unitID      --��Ԫ��
**��    �أ� void
*******************************************************************************/
void KeyEepromInit(u8 unitID)
{
    unitID = unitID;
}

/*******************************************************************************
**��    ���� Get_TouchKey_Attr()
**��    �ܣ� ��ȡ��������ֵ
**��    ���� *pData      --�������
             *rLen       --���ز�������
             *rData      --���ز�����ŵ�ַ
**��    �أ� TRUE/FALSE
********************************************************************************/
MsgResult_t Get_TouchKey_Attr(UnitPara_t *pData, u8 *rLen, u8 *rData)
{
    u8 ch = pData->cmd;
    
    *rLen    = 1;
    rData[0] = KeyCh[ch].Status;
    
    return COMPLETE;
}

/*******************************************************************************
**��    ��:  KeyChecking_Attr()
**��    ��:  ��֤�豸
**��    ��:  void
**��    ��:  void
********************************************************************************/
void KeyChecking_Attr(void)
{
     ShakeMotor_Start();
     Thread_Login(ONCEDELAY, 1, 800 , &ShakeMotor_Stop);
}

/***************************Copyright BestFu **********************************/

