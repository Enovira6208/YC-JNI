/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-04-20 14:41:26
 * @LastEditTime: 2022-07-22 17:34:19
 * @LastEditors:
 */

#ifndef APPLICATION_PROTOCOL_FH_AI_6000H_H_
#define APPLICATION_PROTOCOL_FH_AI_6000H_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[6];
} FH_ai_6000hStrType;

typedef struct
{
    uint8_t Name[8];
    uint8_t Time[8];
    uint8_t Param[4];
    FH_ai_6000hStrType Array[8];
    uint8_t Angle[4];
    uint8_t Temp[2];
} FH_ai_6000hMessageDataType;

typedef enum
{
    FH_AI_6000H_SINGLE,                         /* 单通道 变比 */
    FH_AI_6000H_TWO,                            /* 两通道 */
    FH_AI_6000H_THREE,                          /* 三通道 */
    FH_AI_6000H_FOUR,                           /* 四通道 */
} FH_ai_6000hModeEnum;

typedef struct
{
    double C;
    uint8_t Cu[2];
    double DF;
    uint8_t DFu[1];
} FH_ai_6000hParamType;

typedef struct
{
    uint8_t Name[13];
    uint8_t Time[16];
    uint8_t Mode;
    FH_ai_6000hParamType Param[4];
} FH_ai_6000hValueType;

/* #01CD AI-6000D3002759584581363A50060A02002A51112A62990820742A99491E */
typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t CD[2];
    uint8_t Data[200];
    uint8_t Tail;
} FH_ai_6000hMessageType;



uint16_t FH_ai_6000hReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6000hRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_PROTOCOL_FH_AI_6000H_H_ */
