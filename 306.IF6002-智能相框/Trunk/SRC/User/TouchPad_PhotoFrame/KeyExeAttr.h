/***************************Copyright BestFu ***********************************
**  ��    ��:   KeyExeAttr.h
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
#ifndef _KEY_EXE_ATTR_H_
#define _KEY_EXE_ATTR_H_

#include "BF_type.h"

extern const AttrExe_st KeyAttrTab[];
extern u8 IF6002_UnitAttrNum(void);
extern void  KeyInit(u8 unitID);
extern void  KeyEepromInit(u8 unitID);
extern void  KeyChecking_Attr(void);
extern MsgResult_t Get_TouchKey_Attr(UnitPara_t *pData, u8 *rlen, u8 *rpara);

#endif

/***************************Copyright BestFu **********************************/
