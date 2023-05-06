/*
 * FH_ai_6310b.h
 * @Author       : chuhouzhong
 * @Date         : 2021年9月16日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef _FH_AI_6310B_H_
#define _FH_AI_6310B_H_


#include "../public/public.h"

typedef struct
{
    uint8_t Name[16];
    uint8_t Time[16];
    uint8_t Mode[16];
    uint8_t U[16];                              /* 电压 */
    uint8_t I[16];                              /* 电流 */
    uint8_t R[16];                              /* 电阻 */
} FH_ai_6310bMessageDataType;

typedef struct
{
    double U;                                   /* 电压 */
    uint8_t Uuint[10];                                  /* 阻抗单位 */
    double I;                                   /* 电流 */
    uint8_t Iuint[10];                                  /* 阻抗单位 */
    double R;                                   /* 电阻*/
    uint8_t Ruint[10];                                  /* 电阻单位 */
} FH_ai_6310bValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Read[4];
    uint8_t Data[120];
    uint8_t Tail;
} FH_ai_6310bMessageType;

uint16_t FH_ai_6310bReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6310bRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_PROTOCOL_FH_AI_6301B_H_ */
