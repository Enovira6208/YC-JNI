/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-08-31 17:15:20
 * @LastEditors:
 */
#ifndef _DDC8910_H_
#define _DDC8910_H_

#include "../public/public.h"


typedef struct {
    uint8_t Head;                                 /* 命令 */
    uint8_t mode;                                 /* 模式 */
    uint8_t Data[8];
} DDC8910MessageType;

typedef struct {
    double R;
    uint8_t Ruint[4];                                  /* 单位 */
} DDC8910ValueType;

uint16_t DDC8910ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *DDC8910RecvMessage(uint8_t *buff, uint16_t size);

#endif // _DDC8910_H_
