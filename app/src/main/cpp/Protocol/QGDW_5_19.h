/*
 * QGDW_5_19.h
 * @Author       : zhengshuo
 * @Date         : 2023年10月13日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_QGDW_5_19_H_
#define APPLICATION_MIDDLEDRIVERS_QGDW_5_19_H_

#include "../public/public.h"

//*****************************************************************************************************
typedef struct
{
    uint8_t test_time[7];                           /* 测试时间 */
    uint8_t test_voltage[4];                        /* 试验电压 */
    uint8_t test_voltage_unit[1];                   /*试验电压单位*/
    uint8_t test_current[4];                        /*试验电流*/
    uint8_t current_unit_1[1];                        /*电流单位*/
    uint8_t p_75_voltage[4];                        /*75%电压值*/
    uint8_t voltage_unit[1];                        /*电压单位*/
    uint8_t p_75_current[4];                        /*75%电流值*/
    uint8_t current_unit_2[1];                        /*电流单位*/
    uint8_t Test_duration[2];                       /*试验维持时间*/
    uint8_t time_unit[1];                           /*时间单位*/
    uint8_t other[32];                              /*预留*/
} QGDW_5_19_MessageDataType;

typedef struct
{
    uint8_t test_time[19];                           /* 测试时间 */
    double test_voltage;                           /* 试验电压 */
    uint8_t test_voltage_unit[1];                         /*试验电压单位*/
    double test_current;                        /*试验电流*/
    uint8_t current_unit_1[1];                        /*电流单位*/
    double p_75_voltage;                        /*75%电压值*/
    uint8_t voltage_unit[1];                        /*电压单位*/
    double p_75_current;                        /*75%电流值*/
    uint8_t current_unit_2[1];                        /*电流单位*/
    double Test_duration;                        /*试验维持时间*/
    uint8_t time_unit[1];                        /*时间单位*/
} QGDW_5_19_ValueType;
//****************************************************************************************************
typedef struct
{
    uint8_t Data[62];
} QGDW_5_19_MessageType;

uint16_t QGDW_5_19_ReadData(uint8_t *buff, uint8_t cnt);
char *QGDW_5_19_RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_QGDW_5_19_H_ */
