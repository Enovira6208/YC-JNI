/*
 * PD4_840.h
 * @Author       : zhengshuo
 * @Date         : 2023年9月18日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_PDT_840_H_
#define APPLICATION_MIDDLEDRIVERS_PDT_840_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} PDT_840StrType;



typedef struct
{
    uint8_t serious_number[2];                          /* 序号 */
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    uint8_t test_code[8];                              /* 唯一测试编码(HEX) */
    uint8_t work_number[8];                           /* 工单号 */
    uint8_t test_time[6];                                   /* 测试时间 */
    uint8_t device_status;                                 /*设备状态*/
    uint8_t diagnosic_number[2];                            /*专家诊断编号(高字节前，低字节后)*/
    uint8_t abnormal_flag[3];                           /*测量组分异常标志位*/
    uint8_t so2[4];                             /*SO2(μL/L)*/
    uint8_t h2s[4];                           /*H2S(μL/L)*/
    uint8_t co[4];                             /* CO(μL/L) */
    uint8_t hf[4];                           /* HF(μL/L) */
    uint8_t h2[4];                    /* H2(μL/L) */
    uint8_t cf4[4];                                   /* CF4(μL/L) */
    uint8_t no[4];                                   /* NO(μL/L) */
    uint8_t o2[4];                                   /* O2 */
    uint8_t dew_point[4];                                   /* 露点 */
    uint8_t humidity[4];                   /* 湿度 */
    uint8_t humidity_20[4];                    /* 湿度20度 */
    uint8_t sf6_v[4];                                /* SF6纯度(%V) */
    uint8_t sf6_w[4];                               /*SF6纯度(%W)*/
    uint8_t cf4_v[4];                                /* cf4纯度(%V) */
    uint8_t cf4_w[4];                               /*cf4纯度(%W)*/
    uint8_t n2_v[4];                                /* n2纯度(%V) */
    uint8_t n2_w[4];                               /*n2纯度(%W)*/
    uint8_t air_v[4];                                /* air纯度(%V) */
    uint8_t air_w[4];                               /*air纯度(%W)*/
    uint8_t SF6_CF4_v[4];                                /* SF6+CF4纯度(%V) */
    uint8_t SF6_CF4_w[4];                               /*SF6+CF4纯度(%W)*/
    uint8_t SF6_N2_v[4];                                /* SF6+N2纯度(%V) */
    uint8_t SF6_N2_w[4];                               /*SF6+N2纯度(%W)*/
    uint8_t temp[4];                                /* 温度 */
    uint8_t pressure[4];                               /*气室压力*/

} PDT_840_1MessageDataType;

typedef struct
{
    uint8_t serious_number[2];                          /* 序号 */
    double test1;
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    double test2;
    uint8_t test_code[8];                              /* 唯一测试编码(HEX) */
    double test3;
    uint8_t work_number[8];                           /* 工单号 */
    double test4;
    uint8_t test_time[6];                                   /* 测试时间 */
    double device_status;                                 /*设备状态*/
    uint8_t diagnosic_number[2];                            /*专家诊断编号(高字节前，低字节后)*/
    double test5;
    uint8_t abnormal_flag[3];                           /*测量组分异常标志位*/
    double so2;                             /*SO2(μL/L)*/
    double h2s;                           /*H2S(μL/L)*/
    double co;                             /* CO(μL/L) */
    double hf;                           /* HF(μL/L) */
    double h2;                    /* H2(μL/L) */
    double cf4;                                   /* CF4(μL/L) */
    double no;                                   /* NO(μL/L) */
    double o2;                                   /* O2 */
    double dew_point;                                   /* 露点 */
    double humidity;                   /* 湿度 */
    double humidity_20;                    /* 湿度20度 */
    double sf6_v;                                /* SF6纯度(%V) */
    double sf6_w;                               /*SF6纯度(%W)*/
    double cf4_v;                                /* cf4纯度(%V) */
    double cf4_w;                               /*cf4纯度(%W)*/
    double n2_v;                                /* n2纯度(%V) */
    double n2_w;                               /*n2纯度(%W)*/
    double air_v;                                /* air纯度(%V) */
    double air_w;                               /*air纯度(%W)*/
    double SF6_CF4_v;                                /* SF6+CF4纯度(%V) */
    double SF6_CF4_w;                               /*SF6+CF4纯度(%W)*/
    double SF6_N2_v;                                /* SF6+N2纯度(%V) */
    double SF6_N2_w;                               /*SF6+N2纯度(%W)*/
    double temp;                                /* 温度 */
    double pressure;                               /*气室压力*/
} PDT_840_1ValueType;
/*********************************************************************************/
typedef struct
{
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    uint8_t test_code[8];                              /* 唯一测试编码(HEX) */
    uint8_t work_number[8];                           /* 工单号 */
    uint8_t sf6[4];                             /*SF6(ppmv)*/
    uint8_t temp[4];                           /*温度*/
    uint8_t humidity;                             /* 湿度 */
    uint8_t max[4];                           /* 最大值 */
    uint8_t min[4];                    /* 最小值 */
    uint8_t power[4];                                   /* 当前电量 */
    uint8_t test_satus;                                   /* 检测状态 */

} PDT_840_2MessageDataType;

typedef struct
{
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    double test1;
    uint8_t test_code[8];                       /* 唯一测试编码(HEX) */
    double test2;
    uint8_t work_number[8];                           /* 工单号 */
    double t;
    double sf6;                            /*SF6(ppmv)*/
    double temp;                           /*温度*/
    double humidity;                             /* 湿度 */
    double max;                           /* 最大值 */
    double min;                    /* 最小值 */
    double power;                                   /* 当前电量 */
    double test_satus;                                   /* 检测状态 */
} PDT_840_2ValueType;

/**********************************************************************************/
typedef struct
{
    uint8_t serious_number[2];                          /* 序号 */
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    uint8_t test_code[8];                              /* 唯一测试编码(HEX) */
    uint8_t work_number[8];                           /* 工单号 */
    uint8_t test_time[6];                                   /* 测试时间 */
    uint8_t verify_mode;                                 /*校验模式*/
    
    uint8_t alarm1[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock1_1[4];                           /*闭锁值1*/
    uint8_t lock1_2[4];                             /* 闭锁值2 */
    uint8_t alarm2[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock2_1[4];                           /*闭锁值1*/
    uint8_t lock2_2[4];                             /* 闭锁值2 */
    uint8_t alarm3[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock3_1[4];                           /*闭锁值1*/
    uint8_t lock3_2[4];                             /* 闭锁值2 */
    uint8_t alarm4[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock4_1[4];                           /*闭锁值1*/
    uint8_t lock4_2[4];                             /* 闭锁值2 */

    uint8_t alarm_ask1[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask1_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask1_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask2[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask2_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask2_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask3[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask3_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask3_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask4[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask4_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask4_2[4];                             /* 闭锁回复值2 */

    uint8_t alarm5[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock5_1[4];                           /*闭锁值1*/
    uint8_t lock5_2[4];                             /* 闭锁值2 */
    uint8_t alarm6[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock6_1[4];                           /*闭锁值1*/
    uint8_t lock6_2[4];                             /* 闭锁值2 */
    uint8_t alarm7[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock7_1[4];                           /*闭锁值1*/
    uint8_t lock7_2[4];                             /* 闭锁值2 */
    uint8_t alarm8[4];                             /*报警值（当触点类型为3时该单元为超压值）*/
    uint8_t lock8_1[4];                           /*闭锁值1*/
    uint8_t lock8_2[4];                             /* 闭锁值2 */

    uint8_t alarm_ask5[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask5_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask5_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask6[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask6_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask6_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask7[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask7_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask7_2[4];                             /* 闭锁回复值2 */
    uint8_t alarm_ask8[4];                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    uint8_t lock_ask8_1[4];                           /*闭锁回复值1*/
    uint8_t lock_ask8_2[4];                             /* 闭锁回复值2 */

    uint8_t alarm_r1[4];                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    uint8_t lock_r1_1[4];                           /*闭锁1触点电阻值*/
    uint8_t lock_r1_2[4];                             /* 闭锁2触点电阻值 */
    uint8_t alarm_r2[4];                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    uint8_t lock_r2_1[4];                           /*闭锁1触点电阻值*/
    uint8_t lock_r2_2[4];                             /* 闭锁2触点电阻值 */
    uint8_t alarm_r3[4];                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    uint8_t lock_r3_1[4];                           /*闭锁1触点电阻值*/
    uint8_t lock_r3_2[4];                             /* 闭锁2触点电阻值 */
    uint8_t alarm_r4[4];                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    uint8_t lock_r4_1[4];                           /*闭锁1触点电阻值*/
    uint8_t lock_r4_2[4];                             /* 闭锁2触点电阻值 */

    uint8_t output_pressure[4];                           /* 指示值校验当前输出压力值 */
    uint8_t ambient_temp[4];                    /* 环境温度 */
    uint8_t atmospheric_pressure[4];                                   /* 大气压力 */
    uint8_t device_status;                                   /* 设备状态 */
    uint8_t test_result;                                   /* 密度继电器校验检测结果 */

} PDT_840_3MessageDataType;

typedef struct
{
    uint8_t serious_number[2];                          /* 序号 */
    double test1;
    uint8_t UUID_number[48];                           /* UUID编号(HEX) */
    double test2;
    uint8_t test_code[8];                              /* 唯一测试编码(HEX) */
    double test3;
    uint8_t work_number[8];                           /* 工单号 */
    double test4;
    uint8_t test_time[6];                                   /* 测试时间 */
    double test5;
    double verify_mode;                                 /*校验模式*/
    
    double alarm1;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock1_1;                           /*闭锁值1*/
    double lock1_2;                             /* 闭锁值2 */
    double alarm2;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock2_1;                           /*闭锁值1*/
    double lock2_2;                             /* 闭锁值2 */
    double alarm3;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock3_1;                           /*闭锁值1*/
    double lock3_2;                             /* 闭锁值2 */
    double alarm4;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock4_1;                           /*闭锁值1*/
    double lock4_2;                             /* 闭锁值2 */

    double alarm_ask1;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask1_1;                           /*闭锁回复值1*/
    double lock_ask1_2;                             /* 闭锁回复值2 */
    double alarm_ask2;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask2_1;                           /*闭锁回复值1*/
    double lock_ask2_2;                             /* 闭锁回复值2 */
    double alarm_ask3;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask3_1;                           /*闭锁回复值1*/
    double lock_ask3_2;                             /* 闭锁回复值2 */
    double alarm_ask4;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask4_1;                           /*闭锁回复值1*/
    double lock_ask4_2;                             /* 闭锁回复值2 */

    double alarm5;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock5_1;                           /*闭锁值1*/
    double lock5_2;                             /* 闭锁值2 */
    double alarm6;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock6_1;                           /*闭锁值1*/
    double lock6_2;                             /* 闭锁值2 */
    double alarm7;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock7_1;                           /*闭锁值1*/
    double lock7_2;                             /* 闭锁值2 */
    double alarm8;                             /*报警值（当触点类型为3时该单元为超压值）*/
    double lock8_1;                           /*闭锁值1*/
    double lock8_2;                             /* 闭锁值2 */

    double alarm_ask5;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask5_1;                           /*闭锁回复值1*/
    double lock_ask5_2;                             /* 闭锁回复值2 */
    double alarm_ask6;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask6_1;                           /*闭锁回复值1*/
    double lock_ask6_2;                             /* 闭锁回复值2 */
    double alarm_ask7;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask7_1;                           /*闭锁回复值1*/
    double lock_ask7_2;                             /* 闭锁回复值2 */
    double alarm_ask8;                             /*报警回复值（当触点类型为3时该单元为超压值）*/
    double lock_ask8_1;                           /*闭锁回复值1*/
    double lock_ask8_2;                             /* 闭锁回复值2 */

    double alarm_r1;                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    double lock_r1_1;                           /*闭锁1触点电阻值*/
    double lock_r1_2;                             /* 闭锁2触点电阻值 */
    double alarm_r2;                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    double lock_r2_1;                           /*闭锁1触点电阻值*/
    double lock_r2_2;                             /* 闭锁2触点电阻值 */
    double alarm_r3;                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    double lock_r3_1;                           /*闭锁1触点电阻值*/
    double lock_r3_2;                             /* 闭锁2触点电阻值 */
    double alarm_r4;                             /*报警触点电阻值（当触点类型为3时该单元为超压触点电阻值）*/
    double lock_r4_1;                           /*闭锁1触点电阻值*/
    double lock_r4_2;                             /* 闭锁2触点电阻值 */

    double output_pressure;                           /* 指示值校验当前输出压力值 */
    double ambient_temp;                    /* 环境温度 */
    double atmospheric_pressure;                                   /* 大气压力 */
    double device_status;                                   /* 设备状态 */
    double test_result;                                   /* 密度继电器校验检测结果 */
} PDT_840_3ValueType;
/***************************************************************************************/
typedef struct
{
    uint8_t Head;
    uint8_t type;
    uint8_t contrl;
    uint8_t len[2];
    uint8_t Data[327];
} PDT_840MessageType;

uint16_t PDT_840ReadData(uint8_t *buff, uint8_t cnt);
char *PDT_840RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_PDT_840_H_ */
