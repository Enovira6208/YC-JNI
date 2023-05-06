/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-09-01 11:37:45
 * @LastEditors:
 */
#ifndef _JYT_A_V0_H_
#define _JYT_A_V0_H_

#include "../public/public.h"

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Status;                                    /* 状态 */
    uint8_t Cmd;                                        /* 命令 */
    uint8_t Data[100];
    uint8_t XorCheck;
    uint8_t Tail;
} JYT_A_V0MessageType;

typedef struct
{
    double voltageRatio_A;                              /* 电压比 */
    double voltageRatio_B;
    double voltageRatio_C;
    double difference_A;                              /* 误差 */
    double difference_B;
    double difference_C;
    int tranches;
    int branching;
} JYT_A_V0ValueType;

uint16_t JYT_A_V0ReadData(uint8_t *ascllBuff);
char *JYT_A_V0RecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYT_A_V0_H_
