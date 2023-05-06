/*
 * JYR_40s.h
 * @Author       : chuhouzhong
 * @Date         : 2021年9月11日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_JYR_40S_H_
#define APPLICATION_MIDDLEDRIVERS_JYR_40S_H_

#include "../public/public.h"

#define JYR_40S_MEG_HEAD            (0x7E)
#define JYR_40S_MEG_TAIL            (0x0D)
#define JYR_40S_MEG_ADDRH           (0x45)
#define JYR_40S_MEG_ADDRL           (0x46)


typedef enum
{
    JYR_40_ANALY_1 = 1,                         /* 单通道解析一个 */
    JYR_40_ANALY_2,                             /* 解析不带平衡率 */
    JYR_40_ANALY_3,                             /* 解析带平衡率参数 */
    JYR_40_ANALY_4,                             /* 解析八个参数 */
}
JYR_40sAnalyEnum;

typedef enum
{
    JYR_40S_WAY_SUNGLE_CHANNEL = 0x30,          /* 单通道 */
    JYR_40S_WAY_YN_THREE_PHASE,                 /* 三相 */
    JYR_40S_WAY_YN_THREE_PHASE_COMPEN,          /* 三相补偿 */
    JYR_40S_WAY_YND11,                          /* 助磁 */
    JYR_40S_WAY_YN_PHASE_SELECTION,             /* YN选相 */
    JYR_40S_WAY_DY_PHASE_SELECTION,             /* DY选相 */
} JYR_40sWayEnum;

typedef struct
{
    uint8_t AoSign;                             /* 标记 */
    uint8_t Ao[9];                              /* 电阻 */
    uint8_t BoSign;
    uint8_t Bo[9];
    uint8_t CoSign;
    uint8_t Co[9];
    uint8_t UnbSignH;
    uint8_t UnbalanceH[9];                      /* 不平衡率 */
    uint8_t CaSign;                             /* 标记 */
    uint8_t Ca[9];                              /* 电阻 */
    uint8_t AbSign;
    uint8_t Ab[9];
    uint8_t BcSign;
    uint8_t Bc[9];
    uint8_t UnbSignL;
    uint8_t UnbalanceL[9];                      /* 不平衡率 */
} JYR_40sDataType;


typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Cmd;                                    /* 命令 */
    uint8_t Way;                                /* 方式 */
    uint8_t Electricity;                            /* 电流 */
    uint8_t ElectricityData[6];                     /* 电流数据 */
    uint8_t Data[100];
    uint8_t XorCheck;
    uint8_t Tail;
} JYR_40sMessageType;

typedef struct
{
    uint8_t Way;                                    /* 实验方式 */
    uint8_t Sign;                                   /* 三相补偿中的阶段标志 */
    JYR_40sAnalyEnum AnalyEnum;
    double Ao;
    uint8_t AoU[3];                                 /* 单位 */
    double Bo;
    uint8_t BoU[3];
    double Co;
    uint8_t CoU[3];
    double UnbalanceH;                              /* 不平衡率 */
    double Ca;
    uint8_t CaU[3];
    double Ab;
    uint8_t AbU[3];
    double Bc;
    uint8_t BcU[3];
    double UnbalanceL;
} JYR_40sValueType;

uint16_t JYR_40sReadData(uint8_t *buff);
char *JYR_40sRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_JYR_40S_H_ */
