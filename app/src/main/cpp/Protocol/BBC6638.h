/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-09-02 16:30:07
 * @LastEditors:
 */
#ifndef _BBC6638_H_
#define _BBC6638_H_

#include "../public/public.h"


typedef struct
{
    uint8_t Head;
    uint8_t Mode;                                        /* 模式 */
    uint8_t Data[50];
} BBC6638MessageType;

typedef struct
{
    double voltageRatio_rated;
    double voltageRatio_A;                              /* 电压比 */
    double difference_A;
    double voltageRatio_B;
    double difference_B;
    double voltageRatio_C;                                 /* 误差 */
    double difference_C;
    int tranches;                                       /* 组别 */
    int branching;                                      /* 分接 */
} BBC6638ValueType;

uint16_t BBC6638ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *BBC6638RecvMessage(uint8_t *buff, uint16_t size);

#endif // _BBC6638_H_
