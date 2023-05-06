/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-19 16:15:32
 * @LastEditors:
 */
#ifndef _JYK_I_H_
#define _JYK_I_H_

#include "../public/public.h"


typedef struct
{
    uint8_t Motion;
    uint8_t Ra_Data[5];
    uint8_t Rb_Data[5];
    uint8_t Rc_Data[5];
} JYK_IData1Type;

typedef struct
{
    uint8_t Ra_Data[5];
    uint8_t Rb_Data[5];
    uint8_t Rc_Data[5];
    uint8_t Time_a[7];
    uint8_t Time_b[7];
    uint8_t Time_c[7];
} JYK_IData2Type;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Cmd;                                    /* 命令 */
    uint8_t Data[100];
    uint8_t XorCheck;
    uint8_t Tail;
} JYK_IMessageType;

typedef struct
{
    double Ra;
    double Rb;
    double Rc;
} JYK_IValue1Type;

typedef struct
{
    double Ra;
    double Rb;
    double Rc;
    double Time_a;
    double Time_b;
    double Time_c;
} JYK_IValue2Type;

uint16_t JYK_IReadData(uint8_t *ascllBuff, uint8_t cnt);
char *JYK_IRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYK_I_H_
