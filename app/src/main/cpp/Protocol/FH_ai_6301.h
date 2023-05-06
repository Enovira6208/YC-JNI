/*
 * FH_ai_6301.h
 * @Author       : chuhouzhong
 * @Date         : 2021年9月2日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_FH_AI_6301_H_
#define APPLICATION_MIDDLEDRIVERS_FH_AI_6301_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} FH_ai_6301StrType;



typedef struct
{
    uint8_t Name[10];                           /* 名称 */
    uint8_t Time[16];                           /* 时间 */
    uint8_t Mode[16];                           /* 模式 */
    uint8_t Z[9];                               /* 阻抗 */
    uint8_t R[9];                               /* 电阻 */
    uint8_t U[9];                               /* 电压 */
    uint8_t I[9];                               /* 电流 */
    uint8_t P[9];                               /* 功率 */
    uint8_t A[9];                               /* 角度 */
    uint8_t F[9];                               /* 频率 */
    uint8_t T[9];                               /* 温度 */

} FH_ai_6301MessageDataType;

typedef struct
{
    uint8_t Name[10];                           /* 名称 */
    uint8_t Time[16];                           /* 时间 */
    uint8_t Mode[16];                           /* 模式 */
    double Z;                                   /* 阻抗 */
    uint8_t Zuint[4];                           /* 阻抗单位 */
    double R;                                   /* 电阻 */
    uint8_t Ruint[4];                           /* 阻抗单位 */
    double U;                                   /* 电压 */
    uint8_t Uuint[4];                           /* 阻抗单位 */
    double I;                                   /* 电流 */
    uint8_t Iuint[4];                           /* 阻抗单位 */
    double P;                                   /* 功率 */
    uint8_t Puint[4];                           /* 阻抗单位 */
    double A;                                   /* 角度 */
    uint8_t Auint[4];                           /* 阻抗单位 */
    double F;                                   /* 频率 */
    uint8_t Fuint[4];                           /* 阻抗单位 */
    int T;                                      /* 温度 */
    uint8_t Tuint[4];                           /* 阻抗单位 */
} FH_ai_6301ValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Read[4];
    uint8_t Data[114];
    uint8_t Tail;
} FH_ai_6301MessageType;

uint16_t FH_ai_6301ReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6301RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_FH_AI_6301_H_ */
