/*
 * @Author       : wulongwei (longweisky@foxmail.com)
 * @Date         : 2023-02-03 15:15:45
 * @LastEditors:
 * @LastEditTime: 2023-07-28 17:11:32
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */
/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 15:46:20
 * @LastEditTime: 2022-11-17 20:20:37
 * @LastEditors:
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "public.h"

typedef enum {
    INTERFACE_DEVICE_CODE_NULL,                         /* 空 */
    INTERFACE_DEVICE_CODE_JH6000,                       /* 加华 JH6000 */
    INTERFACE_DEVICE_CODE_FH_AI_6106S,                  /* 泛华避雷器 */
    INTERFACE_DEVICE_CODE_FH_AI_6310LD,                 /* 泛华回路电阻 */
    INTERFACE_DEVICE_CODE_FH_AI_6301,                   /* 泛华地阻 */
    INTERFACE_DEVICE_CODE_FH_AI_6000K,                  /* 泛华介损 */
    INTERFACE_DEVICE_CODE_FH_AI_6000HL,                 /* 泛华介损 */
    INTERFACE_DEVICE_CODE_JYR_40S,                      /* 金源直流电阻 */
    INTERFACE_DEVICE_CODE_FH_AI_6000R,                  /* 泛华容性设备 */
    INTERFACE_DEVICE_CODE_HCYZ_IV,                      /* 华创分接开关 */
    INTERFACE_DEVICE_CODE_JYR_20S,                      /* 金源直流电阻 */
    INTERFACE_DEVICE_CODE_DS_2000D,                     /* 山东达顺短路阻抗 */
    INTERFACE_DEVICE_CODE_FH_AI_6000H,                  /* 泛华介损6000H */
    INTERFACE_DEVICE_CODE_FH_AI_6310B,                  /* 泛华接地导通 */
    INTERFACE_DEVICE_CODE_FH_AI_6310L,                  /* 泛华回路电阻 */
    INTERFACE_DEVICE_CODE_HV9003,                       /* 上海思创介损 */
    INTERFACE_DEVICE_CODE_JYL_100B,                     /* 金源回路电阻 */
    INTERFACE_DEVICE_CODE_JYL_I,                        /* 金源分接开关 */
    INTERFACE_DEVICE_CODE_HLC5501,                      /* 保定金达回路电阻 */
    INTERFACE_DEVICE_CODE_BZC3395,                      /* 保定金达直流电阻 */
    INTERFACE_DEVICE_CODE_DDC8910,                      /* 保定金达接地电阻 */
    INTERFACE_DEVICE_CODE_JYT_A_V0,                     /* 保定金源变比旧版 */
    INTERFACE_DEVICE_CODE_JYT_A_V1,                     /* 保定金源变比V1.0 */
    INTERFACE_DEVICE_CODE_JYT_A_V2,                     /* 保定金源变比V2.0 */
    INTERFACE_DEVICE_CODE_BBC6638,                      /* 保定金达变比 */
    INTERFACE_DEVICE_CODE_SD_HVM_5000,                  /* 苏州海沃绝缘电阻 */
    INTERFACE_DEVICE_CODE_SD_Z_VI,                      /* 苏州海沃直流高压发生器 */
    INTERFACE_DEVICE_CODE_FH_AI_6600C,                  /* 泛华电容电感测试仪 */
    INTERFACE_DEVICE_CODE_JYW6400_DC,                   /* 保定金源JYW6400变压器(直流电阻测试仪) */
    INTERFACE_DEVICE_CODE_JYW6400_IM,                   /* 保定金源JYW6400变压器(阻抗测试) */
    INTERFACE_DEVICE_CODE_JYR_40C,                      /* 保定金源直流电阻 */
    INTERFACE_DEVICE_CODE_JHLK_100,                     /* 加华 JH6000不同版本 jh6000 1.05版本 */
    INTERFACE_DEVICE_CODE_JHMD3,                        /* 厦门加华*/
    INTERFACE_DEVICE_CODE_JYC,                          /*金源*/
    INTERFACE_DEVICE_CODE_TD_3310C_YZFJ,                /*泰达变压器综合测试仪有载分接实验*/
    INTERFACE_DEVICE_CODE_TD_3310C_ZK,                  /*泰达变压器综合测试仪阻抗实验*/
    INTERFACE_DEVICE_CODE_TD_3310C_ZLDZ,                /*泰达变压器综合测试仪直流电阻实验*/
} INTERFACE_DeviceCodeEnum;


typedef struct {
    char *comMode;                                      /* 通信方式（232/485） */
    int baud;                                           /* 波特率 */
    int stopBit;                                        /* 停止位 */
    int dataBits;                                       /* 数据位 */
    char *checkDigit;                                    /* 校验位 */
    char *dataMsg;                                      /* 数据内容 */
    char *dataFormat;                                   /* 数据格式 */
    int dataSize;                                         /* 数据大小 */

} INTERFACE_sendMsgType;


typedef struct {
    INTERFACE_DeviceCodeEnum DeviceCode;

    INTERFACE_sendMsgType sendMsg;
    char sendDataBuff[300];
} INTERFACE_InfoType;

unsigned char *InterfaceJsonMagLoading(unsigned char *jsonBuff, int32_t cnt);
unsigned char *InterfaceDeviceDataAnalysis(unsigned char *dataBuff, int32_t size);

#endif // _INTERFACE_H_
