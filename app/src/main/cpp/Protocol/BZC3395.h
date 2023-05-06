/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-31 17:14:46
 * @LastEditors:
 */
#ifndef _BZC3395_H_
#define _BZC3395_H_

#include "../public/public.h"



typedef struct
{
    uint8_t Head;
    uint8_t Mode;                                        /* 模式 */
    uint8_t Data[50];
} BZC3395MessageType;

typedef struct
{
    double Ra;
    uint8_t Rauint[4];                                  /* 单位 */
    double Rb;
    uint8_t Rbuint[4];                                  /* 单位 */
    double Rc;
    uint8_t Rcuint[4];                                  /* 单位 */
} BZC3395ValueType;

uint16_t BZC3395ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *BZC3395RecvMessage(uint8_t *buff, uint16_t size);

#endif // _BZC3395_H_
