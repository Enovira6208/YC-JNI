/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-11-16 19:35:12
 * @LastEditTime: 2022-11-17 17:14:05
 * @LastEditors:
 */

#ifndef _JYW6400_DC_H_
#define _JYW6400_DC_H_

#include "../public/public.h"

#define POINTS "points"

typedef struct
{
    uint8_t Head[3];
    uint8_t Length[4];
    uint8_t Cmd[2];                                        /* 命令 */
    uint8_t DataLength[4];
    uint8_t Data[500];
    uint8_t verify[2];
} JYW6400_DCMessageType;

typedef struct
{
    double AN;
    uint8_t ANU[4];
    double BN;
    uint8_t BNU[4];
    double CN;
    uint8_t CNU[4];

} JYW6400_DCResistanceType;

typedef struct
{
    char testTime[10];
    double electricity;
    uint8_t electricityU[4];
    double oilTemp;
    uint8_t oilTempU[4];
    JYW6400_DCResistanceType resistance[31];
} JYW6400_DCValueType;


uint16_t JYW6400_DCReadData(uint8_t *ascllBuff);
char *JYW6400_DCRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYW6400_DC_H_

