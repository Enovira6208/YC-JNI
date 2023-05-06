/*
 * arrester.h
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_FH_AI_6106S_H_
#define APPLICATION_MIDDLEDRIVERS_FH_AI_6106S_H_

#include "../public/public.h"


typedef struct
{
    uint8_t Year;
    uint8_t Month;
    uint8_t Date;
    uint8_t Hours;
    uint8_t Minutes;
    uint8_t Seconds;
} FH_ai_6106s_TimeType;

typedef struct
{
    uint8_t A[3];                   /* 补偿角 */
} FH_ai_6106s_AngleType;

typedef struct
{
    uint8_t Format;                 /* 解读格式 */
    uint8_t LineName[8];            /* 线路名称 */
    uint8_t Time[4];                /* 时间 */
    uint8_t Number[3];              /* 仪器编号 */
    uint8_t Byte16;                 /* 参考电源 参考相 */
    uint8_t WirelessStatus[5];      /* 无线接收状态 */
    uint8_t Voltage[3];             /* 电压变比 */
    uint8_t Freq[3];                /* 频率 */
    uint8_t Temp;                   /* 温度 */
    uint8_t Byte29;                 /* 补偿方式 待测相 */
    FH_ai_6106s_AngleType Angle[3]; /* 补偿角度 */
    uint8_t Byte39;                 /* 显示参考 */
} FH_ai_6106s_Part1Type;

typedef enum
{
    PART_ONE_RS_WIRED,              /* 有线 */
    PART_ONE_RS_WIRELESS,           /* 无线 */
    PART_ONE_RS_REACTION,           /* 感应 */
    PART_ONE_RS_NULL,               /* 无(单电流方式) */
} Part1RSEnum;

typedef enum
{
    PART_ONE_RP_A,
    PART_ONE_RP_B,
    PART_ONE_RP_C,
    PART_ONE_RP_A_B,
    PART_ONE_RP_C_B,
    PART_ONE_RP_A_B_C,
} Part1RPEnum;

typedef struct
{
    double A;                       /* 补偿角 */
} FH_ai_6106s_AngleDoubleType;

typedef struct
{
    uint8_t Format;                 /* 解读格式 */
    uint8_t LineName[9];            /* 线路名称 */
    uint8_t Time[20];               /* 时间 */
    uint8_t Number[6];              /* 仪器编号 */
    Part1RSEnum RS;                 /* 参考源 */
    Part1RPEnum RP;                 /* 参考相 */
    uint8_t Byte17;
    uint8_t FactryNum[8];           /* 出厂编号 */
    uint8_t Voltage[6];             /* 电压变比 */
    double  Freq;                   /* 频率 */
    int Temp;                       /* 温度 */
    uint8_t MC;                     /* 补偿方式 */
    uint8_t MP;                     /* 待测相 */
    FH_ai_6106s_AngleDoubleType Angle[3];
    uint8_t REF;                    /* 参考显示 */
    uint8_t DUT;                    /* 待测显示 */
} FH_ai_6106s_Part1ValueType;

typedef struct
{
    uint8_t Data[250];              /* 图谱的288字节 */
} FH_ai_6106s_Part2ValueType;

typedef struct
{
    uint8_t str[24];
} Part3StrType;

typedef struct
{
    Part3StrType REF[3];        /* 三组参考相 */
} FH_ai_6106s_Part3Type;

typedef struct
{
    double Range;                   /* 参考幅度 */
    double Harmonic1;               /* 电压谐波 */
    double Harmonic2;
    double Harmonic3;
    double Angle;                   /* 角度 */
} FH_ai_6106s_Part3DataType;

typedef struct
{
    FH_ai_6106s_Part3DataType Data[3];
} FH_ai_6106s_Part3ValueType;

typedef struct
{
    uint8_t ix[7];
    uint8_t ixp[7];
    uint8_t ir[7];
    uint8_t irp[7];
    uint8_t irlp[7];
    uint8_t iclp[7];
    uint8_t pl[7];
    uint8_t cx[7];
    uint8_t i3[7];
    uint8_t i5[7];
    uint8_t i7[7];
    uint8_t A[6];
    uint8_t C;

} Part4Type;

typedef struct
{
    Part4Type MOA[3];       /* 三组MOA电流数据 */
} FH_ai_6106s_Part4Type;

typedef struct
{
    double ix;
    uint8_t ixu[2];

    double ixp;
    double ir;
    double irp;
    double irlp;
    uint8_t irlpu[2];

    double iclp;
    uint8_t iclpu[2];

    double pl;
    double cx;
    double i3;
    uint8_t i3u[2];

    double i5;
    double i7;
    double A;
    uint8_t C;
} Part4DataType;

typedef struct
{
    Part4DataType Data[3];      /* 三组MOA电流数据 */
} FH_ai_6106s_Part4ValueType;

typedef struct
{
    cJSON *Param;
} FH_ai_6106s_CjsonParamType;

typedef struct
{
    FH_ai_6106s_CjsonParamType Array[3];
} FH_ai_6106s_Cjson1Type;


typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Read[4];
    uint8_t Data[800];
    uint8_t Tail;
} FH_ai_6106s_MessageType;

uint16_t FH_ai_6106sReadData(uint8_t *buff, uint8_t cnt);
char *FH_ai_6106sRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_FH_AI_6106S_H_ */
