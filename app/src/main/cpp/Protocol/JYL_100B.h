/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-18 20:44:32
 * @LastEditors:
 */
#ifndef _JYL_100B_H_
#define _JYL_100B_H_

#include "../public/public.h"

typedef struct
{
    uint8_t I_Info;
    uint8_t I_Data[5];
    uint8_t R_Data[7];
} JYL_100BDataType;


typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Cmd;                                    /* 命令 */
    uint8_t Data[30];
    uint8_t XorCheck;
    uint8_t Tail;
} JYL_100BMessageType;

typedef struct
{
    double R;
    uint8_t Ruint[2];                                  /* 单位 */
} JYL_100BValueType;

uint16_t JYL_100BReadData(uint8_t *buff);
char *JYL_100BRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYL_100B_H_
