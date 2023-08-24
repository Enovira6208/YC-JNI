/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-09-14 17:22:32
 * @LastEditors:
 */
#ifndef _SD_Z_VI_H_
#define _SD_Z_VI_H_

#include "../public/public.h"

typedef struct
{
    uint8_t Head[3];
    uint8_t Length[4];
    uint8_t Cmd[2];                                        /* 命令 */
    uint8_t DataLength[4];
    uint8_t Data[500];
    uint8_t verify[2];
} SD_Z_VIMessageType;


typedef struct
{
    uint8_t testTime[20];
    double testVoltage;
    uint8_t testVuint[4];
    double testElectricity;
    uint8_t testEuint[4];
    double voltage_75;
    uint8_t Vuint_75[4];
    double electricity_75;
    uint8_t Iuint_75[4];
    double sustainTime;
    uint8_t sustainTuint_75[4];
} SD_Z_VIValueType;

uint16_t SD_Z_VIReadData(uint8_t *ascllBuff);
char *SD_Z_VIRecvMessage(uint8_t *buff, uint16_t size);

#endif // _SD_Z_VI_H_
