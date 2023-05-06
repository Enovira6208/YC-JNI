/*
 * FH_ai_6000hl.h
 * @Author       : chuhouzhong
 * @Date         : 2021年9月14日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_PROTOCOL_FH_AI_6000HL_H_
#define APPLICATION_PROTOCOL_FH_AI_6000HL_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[16];
} FH_ai_6000hlStrType;

typedef struct
{
    uint8_t Name[16];
    uint8_t Time[16];
    uint8_t Param[16];
    FH_ai_6000hlStrType Array[8];
} FH_ai_6000hlMessageDataType;

typedef enum
{
    FH_AI_6000HL_SINGLE,                        /* 单通道 */
    FH_AI_6000HL_CONTRARY,                      /* 反接两通道 */
    FH_AI_6000HL_NO_LOAD,                       /* 变比 */
    FH_AI_6000HL_CVT,                           /* CTV两通道 */
    FH_AI_6000HL_TWO,                           /* 正接两通道 */
    FH_AI_6000HL_THREE,                         /* 正接三通道 */
    FH_AI_6000HL_FOUR,                          /* 正接四通道 */
} FH_ai_6000hlModeEnum;

typedef struct
{
    double C;
    uint8_t Cu[2];
    double DF;
    uint8_t DFu[2];

} FH_ai_6000hlParamType;

typedef struct
{
    uint8_t Name[13];
    uint8_t Time[16];
    FH_ai_6000hlModeEnum Mode;
    FH_ai_6000hlParamType Param[4];
} FH_ai_6000hlValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t CData[5];
    uint8_t Data[200];
    uint8_t Tail;
} FH_ai_6000hlMessageType;


uint16_t FH_ai_6000hlReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6000hlRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_PROTOCOL_FH_AI_6000HL_H_ */
