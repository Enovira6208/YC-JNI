/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2021-12-29 11:47:26
 * @LastEditTime: 2022-07-22 17:48:46
 * @LastEditors:
 */

#ifndef _FH_AI_6000R_H_
#define _FH_AI_6000R_H_

#include "../public/public.h"


typedef struct
{
    uint8_t Name[10];
    uint8_t Time[16];
    uint8_t MOA[2];
    uint8_t Status[2];
    uint8_t SN[6];                                      /* 仪器编号 */
    uint8_t cn0[6];                                     /* 电流或电压 */
    uint8_t df0[7];                                     /* 补偿角度 */
    uint8_t f[8];                                       /* 频率 */
    uint8_t t[5];                                       /* 温度 */
    uint8_t ir1[8];
    uint8_t ir0[8];
    uint8_t ix1[8];
    uint8_t ix0[8];
    uint8_t angl[8];
    uint8_t ref[8];
    uint8_t ix[8];
    uint8_t cx[8];
    uint8_t df[8];
    uint8_t ii[8];
    uint8_t refrms[8];
    uint8_t ref357[12];
    uint8_t ixrms[8];
    uint8_t ixp[8];
    uint8_t irrms[8];
    uint8_t irp[8];
    uint8_t ic1p[8];
    uint8_t ir1p[8];
    uint8_t ir3p[8];
    uint8_t ir5p[8];
    uint8_t ir7p[8];
    uint8_t conclusion[2];
    uint8_t atlas[96];
    uint8_t checksum[4];

} FH_ai_6000rMessageDataType;

typedef struct
{
    int MOA;
    int Status;

    double cn0;                                         /* 电流或电压 */
    double df0;                                         /* 补偿角度 */
    double f;                                           /* 频率 */
    double t;                                           /* 温度 */
    double ir1;
    double ir0;
    double ix1;
    double ix0;
    double angl;
    double ref;
    uint8_t refu[2];
    double ix;
    double cx;
    uint8_t cxu[2];
    double df;
    double ii;
    double refrms;
    double ref357;
    double ixrms;
    double ixp;
    double irrms;
    double irp;
    double ic1p;
    double ir1p;
    double ir3p;
    double ir5p;
    double ir7p;
    double conclusion;
    double atlas[96];

} FH_ai_6000rValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t READ[4];
    uint8_t Data[400];
    uint8_t Tail;
} FH_ai_6000rMessageType;

uint16_t FH_ai_6000rReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6000rRecvMessage(uint8_t *buff, uint16_t size);


#endif // _FH_AI_6000R_H_

