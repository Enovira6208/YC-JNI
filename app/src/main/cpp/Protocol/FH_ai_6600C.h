/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2021-12-29 11:47:26
 * @LastEditTime: 2022-11-02 15:21:53
 * @LastEditors:
 */

#ifndef _FH_AI_6600C_H_
#define _FH_AI_6600C_H_

#include "../public/public.h"


typedef struct
{
    uint8_t Name[8];
    uint8_t Time[16];
    uint8_t testmode[6];
    uint8_t x[8];
    uint8_t u[8];
    uint8_t i[8];
    uint8_t fj[8];
    uint8_t ij[8];
} FH_ai_6600CMessageDataType;

typedef struct
{
    uint8_t testmode[6];
    double x;
    uint8_t xUnit[2];
    double u;
    uint8_t uUnit[2];
    double i;
    uint8_t iUnit[2];
    double fj;
    uint8_t fjUnit[2];
    double ij;
    uint8_t ijUnit[2];
} FH_ai_6600CValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t READ[4];
    uint8_t Data[400];
    uint8_t Tail;
} FH_ai_6600CMessageType;

uint16_t FH_ai_6600CReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6600CRecvMessage(uint8_t *buff, uint16_t size);


#endif // _FH_AI_6600C_H_

