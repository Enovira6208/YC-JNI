/*
 * FH_ai_6301B.h
 * @Author       : zhengshuo
 * @Date         : 2023年9月11日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_FH_AI_6301B_H_
#define APPLICATION_MIDDLEDRIVERS_FH_AI_6301B_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} FH_ai_6301BStrType;



typedef struct
{
    uint8_t Name[8];                           /* 名称 */
    uint8_t Time[19];                           /* 时间 */
    uint8_t TestMode;                           /* 测试模式 */
    uint8_t Rab;        /*电阻率是否等距*/
    uint8_t TimeMode[2];        /*测量时间*/
    uint8_t AAA[3];        /*电阻率间距a*/
    uint8_t BBB[3];        /*电阻率间距b*/
    uint8_t Jam;        /*y有无干扰*/
    uint8_t Z[9];                               /* 阻抗 */
    uint8_t R[9];                               /* 电阻 */
    uint8_t U[9];                               /* 电压 */
    uint8_t I[9];                               /* 电流 */
    uint8_t N[9];                               /* 干扰电压 */
    uint8_t F[9];                               /* 频率 */
    uint8_t Fai[9];                               /* 超前角度 */

} FH_ai_6301BMessageDataType;

typedef struct
{
    uint8_t Name[8];                           /* 名称 */
    double t;
    uint8_t Time[19];                          /* 时间 */
    double TestMode;                           /* 测试模式 */
    double Rab;        /*电阻率是否等距*/
    double TimeMode;        /*测量时间*/
    double AAA;        /*电阻率间距a*/
    double BBB;        /*电阻率间距b*/
    double Jam;        /*y有无干扰*/
    double Z;                                   /* 阻抗 */
    uint8_t Zuint[4];                           /* 阻抗单位 */
    double R;                                   /* 电阻 */
    uint8_t Ruint[4];                           /* 阻抗单位 */
    double U;                                   /* 电压 */
    uint8_t Uuint[4];                           /* 阻抗单位 */
    double I;                                   /* 电流 */
    uint8_t Iuint[4];                           /* 阻抗单位 */
    double N;                                   /* 功率 */
    uint8_t Nuint[4];                           /* 阻抗单位 */
    double F;                                   /* 频率 */
    uint8_t Fuint[4];                           /* 阻抗单位 */
    double Fai;                                   /* 超前角度 */
    uint8_t Faiuint[4];                           /* 超前电压角度单位 */
} FH_ai_6301BValueType;

typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Data[101];
    uint8_t Tail;
} FH_ai_6301BMessageType;

uint16_t FH_ai_6301BReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6301BRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_FH_AI_6301B_H_ */
