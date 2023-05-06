/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-18 20:44:32
 * @LastEditors:
 */
#ifndef _JYR_40C_H_
#define _JYR_40C_H_

#include "../public/public.h"

typedef struct {
    uint8_t I_Info[6];
    uint8_t R_Data[7];
} JYR_40CDataType;


typedef struct {
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Cmd;        /* 命令 */
    uint8_t Data[30];
    uint8_t XorCheck;
    uint8_t Tail;
} JYR_40CMessageType;

typedef struct {
    double R;
    uint8_t Ruint[2];   /* 单位 */
} JYR_40CValueType;

uint16_t JYR_40CReadData(uint8_t *buff);
char *JYR_40CRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYL_100B_H_
