/*
 * FH_IDCE_2415.h
 * @Author       : zhengshuo
 * @Date         : 2023年9月12日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_FH_IDCE_2415CT_H_
#define APPLICATION_MIDDLEDRIVERS_FH_IDCE_2415CT_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} FH_IDCE_2415CTStrType;



typedef struct
{
    uint8_t online_voltage[2];                          /* 在线电压 */
    uint8_t total_voltage[2];                           /* 总电压 */
    uint8_t start_time[6];                              /* 测试开始时间 */
    uint8_t test_duration[3];                           /* 测试时长 */
    uint8_t keystate;                                   /* 按键状态 */
    uint8_t monomer[2];                                 /*单体数量*/
    uint8_t test_current[2];                            /*测量电流*/
    uint8_t test_capacity[2];                           /*测试容量*/
    uint8_t max_monomer[2];                             /*最高单体号*/
    uint8_t max_monomer_v[2];                           /*最高单体电压*/
    uint8_t min_monomer[2];                             /* 最低单体号 */
    uint8_t min_monomer_v[2];                           /* 最低单体电压 */
    uint8_t activation_frequency[2];                    /* 活化次数 */
    uint8_t temp1[2];                                   /* 温度1 */
    uint8_t temp2[2];                                   /* 温度2 */
    uint8_t temp3[2];                                   /* 温度3 */
    uint8_t temp4[2];                                   /* 温度4 */
    uint8_t module_online_voltage[2];                   /* 在线模块在线电压 */
    uint8_t module_total_voltage[2];                    /* 在线模块组端电压 */
    uint8_t diode_state;                                /* 二极管状态 */
    uint8_t charge_stage;                               /*充电阶段*/
    uint8_t reserve[4];                                 /*预留*/

} FH_IDCE_2415CTMessageDataType;

typedef struct
{
    double online_voltage;                          /* 在线电压 */
    double total_voltage;                           /* 总电压 */
    uint8_t start_time[19];                              /* 测试开始时间 */
    double t;
    uint8_t test_duration[8];                       /* 测试时长 */
    double keystate;                                /* 按键状态 */
    double monomer;                                 /*单体数量*/
    double test_current;                            /*测量电流*/
    double test_capacity;                           /*测试容量*/
    double max_monomer;                             /*最高单体号*/
    double max_monomer_v;                           /*最高单体电压*/
    double min_monomer;                             /* 最低单体号 */
    double min_monomer_v;                           /* 最低单体电压 */
    double activation_frequency;                    /* 活化次数 */
    double temp1;                                   /* 温度1 */
    double temp2;                                   /* 温度2 */
    double temp3;                                   /* 温度3 */
    double temp4;                                   /* 温度4 */
    double module_online_voltage;                   /* 在线模块在线电压 */
    double module_total_voltage;                    /* 在线模块组端电压 */
    double diode_state;                             /* 二极管状态 */
    double charge_stage;                            /*充电阶段*/
    double reserve;                                 /*预留*/
} FH_IDCE_2415CTValueType;

typedef struct
{
    uint8_t Head[4];
    uint8_t Others[14];
    uint8_t Data[48];
} FH_IDCE_2415CTMessageType;

uint16_t FH_IDCE_2415CTReadData(uint8_t *buff, uint8_t cnt);
char *FH_IDCE_2415CTRecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_FH_IDCE_2415CT_H_ */
