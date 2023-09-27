/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-05-31 14:36:01
 * @LastEditTime: 2023-05-31 14:41:08
 * @LastEditors:
 */
#ifndef APPLICATION_MIDDLEDRIVERS_JYR_40D_H_
#define APPLICATION_MIDDLEDRIVERS_JYR_40D_H_

#include "../public/public.h"

typedef struct {
    uint8_t head;
    uint8_t addr[2];
    uint8_t dataLength[2];
    uint8_t status;
    uint8_t mode;
    uint8_t way;
    uint8_t winding;
    uint8_t electricity;
    uint8_t data[100];
    uint8_t xorCheck;
    uint8_t tail;
} JYR_40DMessageType;

typedef struct {
    uint8_t status;
    uint8_t mode;
    uint8_t way;
    uint8_t winding;
    uint8_t electricity;
} JYR_40DValueType;

uint16_t JYR_40DReadData(uint8_t *buff);
char *JYR_40DRecvMessage(uint8_t *buff, uint16_t size);
#endif