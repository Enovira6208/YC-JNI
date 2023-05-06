/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:25:03
 * @LastEditTime: 2022-07-25 09:14:01
 * @LastEditors:
 */
#ifndef _JYR_20S_H_
#define _JYR_20S_H_

#include "../public/public.h"


#define JYR_20s_MEG_HEAD            (0x7E)
#define JYR_20s_MEG_TAIL            (0x0D)
#define JYR_20s_MEG_ADDRH           (0x45)
#define JYR_20s_MEG_ADDRL           (0x46)


typedef enum
{
    JYR_20_ANALY_1 = 1,                         /* 单通道解析一个 */
    JYR_20_ANALY_2,                             /* 解析不带平衡率 */
    JYR_20_ANALY_3,                             /* 解析带平衡率参数 */
} JYR_20sAnalyEnum;

typedef enum
{
    JYR_20s_WAY_YN_THREE_PHASE = 0x30,          /* YN三相同测 */
    JYR_20s_WAY_YN_CHASE_PHASE,                 /* YN逐相测试 */
    JYR_20s_WAY_D_CHASE_PHASE,                  /* D逐相测试 */
    JYR_20s_WAY_SINGLE_PHASE,                   /* 单相测试 */
    JYR_20s_WAY_MAGNETISM_AB = 35,              /* 助磁ab */
    JYR_20s_WAY_MAGNETISM_BC,                   /* 助磁bc */
    JYR_20s_WAY_MAGNETISM_CA,                   /* 助磁ca */
    JYR_20s_WAY_MAGNETISM_CHASE_PHASE,          /* 助磁逐相测试 */
} JYR_20sWayEnum;

typedef struct
{
    uint8_t Ao[7];                              /* 电阻 */
    uint8_t Bo[7];
    uint8_t Co[7];
    uint8_t Unbalance[5];                       /* 不平衡率 */
} JYR_20sDataType;


typedef struct
{
    uint8_t Head;
    uint8_t Addr[2];
    uint8_t Length[2];
    uint8_t Cmd;                                    /* 命令 */
    uint8_t Way;                                    /* 方式 */
    uint8_t ElectricityData[5];                     /* 电流数据 */
    uint8_t Data[100];
    uint8_t XorCheck;
    uint8_t Tail;
} JYR_20sMessageType;

typedef struct
{
    JYR_20sAnalyEnum AnalyEnum;
    double Ao;
    uint8_t AoU[5];                                 /* 单位 */
    double Bo;
    uint8_t BoU[5];
    double Co;
    uint8_t CoU[5];
    double Unbalance;                               /* 不平衡率 */
} JYR_20sValueType;

uint16_t JYR_20sReadData(uint8_t *ascllBuff);
char *JYR_20sRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYR_20S_H_
