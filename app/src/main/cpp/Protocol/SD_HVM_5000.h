/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-09-14 15:36:13
 * @LastEditors:
 */
#ifndef _SD_HVM_5000_H_
#define _SD_HVM_5000_H_

#include "../public/public.h"

typedef struct
{
    uint8_t Head[3];
    uint8_t Length[4];
    uint8_t Cmd[2];                                        /* 命令 */
    uint8_t DataLength[4];
    uint8_t Data[500];
    uint8_t verify[2];
} SD_HVM_5000MessageType;


typedef struct
{
    double voltage;
    uint8_t Vuint[4];
    double resistance_15s;
    uint8_t Ruint_15s[4];
    double resistance_60s;
    uint8_t Ruint_60s[4];
    double resistance_10min;
    uint8_t Ruint_10min[4];
    double absorptance;
    double polarizationIndex;
} SD_HVM_5000ValueType;

uint16_t SD_HVM_5000ReadData(uint8_t *ascllBuff);
char *SD_HVM_5000RecvMessage(uint8_t *buff, uint16_t size);

#endif // _SD_HVM_5000_H_
