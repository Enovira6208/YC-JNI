/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-05-30 10:48:56
 * @LastEditTime: 2023-05-30 17:19:46
 * @LastEditors:  
 */
#ifndef _JYC_
#define _JYC_

#include "../public/public.h"

typedef struct {
    uint8_t head;
    uint8_t addrHigh;
    uint8_t addrLow;
    uint8_t dataHigh;
    uint8_t dataMid;
    uint8_t dataLow;
    uint8_t cmd;
    uint8_t high_switch_status;  /*高压开关状态*/
    uint8_t device_status;       /*仪器状态*/
    uint8_t data[100];
    uint8_t xorCheck;
    uint8_t tail;
    // uint8_t dataName[3];         /*数据名称*/
    // uint8_t dataSign;            /*数据符号*/
    // uint8_t dataValue[5];        /*数据数值*/
    // uint8_t dataUnit;            /*数据单位*/
} JYCMessageType;


typedef struct {
    char name[4];
    char unitName[3];
    char sign[2];
    double dataValue;
} DataValue;

typedef struct {
    uint8_t dataLength[3];
    uint8_t high_switch_status;  /*高压开关状态*/
    uint8_t device_status;       /*仪器状态*/
    int count;
    DataValue v[20];
} JYCValueType;

uint16_t JYC_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *JYC_RecvMessage(uint8_t *buff, uint16_t size);

#endif