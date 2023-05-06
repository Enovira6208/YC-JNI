/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-31 17:14:08
 * @LastEditors:
 */
#ifndef _HLC5501_H_
#define _HLC5501_H_

#include "../public/public.h"

typedef struct
{
    uint8_t R_Data[10];
} HLC5501DataType;


typedef struct
{
    uint8_t Head;                                 /* 命令 */
    uint8_t Data[10];
} HLC5501MessageType;

typedef struct
{
    double R;
    uint8_t Ruint[4];                                  /* 单位 */
} HLC5501ValueType;

uint16_t HLC5501ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *HLC5501RecvMessage(uint8_t *buff, uint16_t size);

#endif // _HLC5501_H_
