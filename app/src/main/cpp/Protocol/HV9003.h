/*
 * HV9003.h
 * @Author       : zhengshuo
 * @Date         : 2023年9月25日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_HV9003_H_
#define APPLICATION_MIDDLEDRIVERS_HV9003_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} HV9003_StrType;


/*************************************************************************************************************************/
typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    uint8_t frequency[7];                           /* 频率 */
    uint8_t percent;                           /* 百分比 */

} HV9003_1MessageDataType;

typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    double test1;
    uint8_t frequency[7];                     /* 频率 */
    double percent;                           /* 百分比 */
} HV9003_1ValueType;

/*************************************************************************************************************************/
typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t highv_voltage[7];                              /* 高压电压值 */
    uint8_t frequency[7];                           /* 频率 */
    uint8_t lowv_voltage[4];                           /* 低压电压值 */
    uint8_t current[4];                           /* 低压电流值 */
    uint8_t percent;                           /* 百分比 */

} HV9003_2MessageDataType;

typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t highv_voltage[7];                              /* 高压电压值 */
    double test1;
    uint8_t frequency[7];                              /* 频率 */
    double test2;
    uint8_t lowv_voltage[4];                      /* 低压电压值 */
    double test3;
    uint8_t current[4];                       /* 低压电流值 */
    double percent;                           /* 百分比 */
} HV9003_2ValueType;
/*************************************************************************************************************************/
typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    uint8_t frequency[7];                           /* 频率 */
} HV9003_3MessageDataType;

typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    double test1;
    uint8_t frequency[7]; /* 频率 */
} HV9003_3ValueType;
/*************************************************************************************************************************/
typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    uint8_t frequency[4];                           /* 频率 */
    uint8_t variable_ratio[6];                           /* 测量结果变比值 */
    uint8_t error_value[7];                           /* 测量结果误差值 */
    uint8_t polarity;                           /* 测量结果极性 */
    uint8_t phase_difference[6];                           /* 测量结果相位差 */
} HV9003_4MessageDataType;

typedef struct
{
    uint8_t head[1];                           /* 数据头 */
    uint8_t voltage[7];                              /* 电压 */
    double test1;
    uint8_t frequency[4];                                /* 频率 */
    double test2;
    uint8_t variable_ratio[6];                        /* 测量结果变比值 */
    double test3;
    uint8_t error_value[7];                        /* 测量结果误差值 */
    double test4;
    uint8_t polarity[1];                                   /* 测量结果极性 */
    double test5;
    uint8_t phase_difference[6]; /* 测量结果相位差 */
} HV9003_4ValueType;
/*************************************************************************************************************************/
typedef struct
{
    uint8_t Data[40];
} HV9003_MessageType;

uint16_t HV9003_ReadData(uint8_t *buff, uint8_t cnt);
char *HV9003_RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_HV9003_H_ */
