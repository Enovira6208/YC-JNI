/*
 * QGDW_5_8.h
 * @Author       : zhengshuo
 * @Date         : 2023年10月13日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_QGDW_5_8_H_
#define APPLICATION_MIDDLEDRIVERS_QGDW_5_8_H_

#include "../public/public.h"

//*****************************************************************************************************
typedef struct
{
    uint8_t test_time[7];                           /* 测试时间 */
    uint8_t fracture_type[1];                        /* 断路器断口类型 */
    uint8_t Switch_Stroke[4];                        /* 开关行程 */
    uint8_t test_type[1];                        /* 测试类型 */

    uint8_t A1_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t A1_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t A1_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t A1_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t A1_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t A1_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t A1_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t A1_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t A1_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t A1_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t B1_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t B1_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t B1_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t B1_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t B1_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t B1_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t B1_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t B1_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t B1_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t B1_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t C1_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t C1_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t C1_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t C1_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t C1_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t C1_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t C1_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t C1_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t C1_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t C1_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t A2_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t A2_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t A2_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t A2_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t A2_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t A2_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t A2_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t A2_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t A2_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t A2_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t B2_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t B2_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t B2_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t B2_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t B2_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t B2_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t B2_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t B2_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t B2_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t B2_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t C2_fracture_type[1];                        /* A1 断口线圈类型 */
    uint8_t C2_fracture_time[4];                        /* A1 断口动作时间 */
    uint8_t C2_bounce_time[4];                        /* A1弹跳时间 */
    uint8_t C2_bounce_count[1];                        /* A1弹跳次数 */
    uint8_t C2_short_circuit_time[4];                        /* A1 断口金属短路时间 */
    uint8_t C2_no_current_time[4];                        /* A1 断口无电流时间 */
    uint8_t C2_closing_resistor[2];                        /* A1 断口合闸电阻值 */
    uint8_t C2_switching_time[4];                        /* A1 断口合闸电阻投切时间 */
    uint8_t C2_fracture_speed[4];                        /* A1 断口速度*/
    uint8_t C2_fracture_over_travel[4];                        /* A1 断口超程*/

    uint8_t A_phase_coil_current[4];                        /* A 相线圈电流*/
    uint8_t B_phase_coil_current[4];                        /* B 相线圈电流*/
    uint8_t C_phase_coil_current[4];                        /* C 相线圈电流*/

    uint8_t Same_period_as_A[4];                        /* A 相同相同期*/
    uint8_t Same_period_as_B[4];                        /* B 相同相同期*/
    uint8_t Same_period_as_C[4];                        /* C 相同相同期*/

    uint8_t Interphase_synchronization[4];                        /* 相间同期*/
    uint8_t Number_of_samples_N[4];                        /* 采样点数 N*/
    uint8_t Time_step[4];                        /* 时间步长△t*/
    uint8_t Time_step_unit[1];                        /* 时间步长△t单位*/

} QGDW_5_8_MessageDataType;

typedef struct
{
    uint8_t test_time[19];                           /* 测试时间 */
    double fracture_type;                        /* 断路器断口类型 */
    double Switch_Stroke;                        /* 开关行程 */
    double test_type;                        /* 测试类型 */

    double A1_fracture_type;                        /* A1 断口线圈类型 */
    double A1_fracture_time;                        /* A1 断口动作时间 */
    double A1_bounce_time;                        /* A1弹跳时间 */
    double A1_bounce_count;                        /* A1弹跳次数 */
    double A1_short_circuit_time;                        /* A1 断口金属短路时间 */
    double A1_no_current_time;                        /* A1 断口无电流时间 */
    double A1_closing_resistor;                        /* A1 断口合闸电阻值 */
    double A1_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double A1_fracture_speed;                        /* A1 断口速度*/
    double A1_fracture_over_travel;                        /* A1 断口超程*/

    double B1_fracture_type;                        /* A1 断口线圈类型 */
    double B1_fracture_time;                        /* A1 断口动作时间 */
    double B1_bounce_time;                        /* A1弹跳时间 */
    double B1_bounce_count;                        /* A1弹跳次数 */
    double B1_short_circuit_time;                        /* A1 断口金属短路时间 */
    double B1_no_current_time;                        /* A1 断口无电流时间 */
    double B1_closing_resistor;                        /* A1 断口合闸电阻值 */
    double B1_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double B1_fracture_speed;                        /* A1 断口速度*/
    double B1_fracture_over_travel;                        /* A1 断口超程*/

    double C1_fracture_type;                        /* A1 断口线圈类型 */
    double C1_fracture_time;                        /* A1 断口动作时间 */
    double C1_bounce_time;                        /* A1弹跳时间 */
    double C1_bounce_count;                        /* A1弹跳次数 */
    double C1_short_circuit_time;                        /* A1 断口金属短路时间 */
    double C1_no_current_time;                        /* A1 断口无电流时间 */
    double C1_closing_resistor;                        /* A1 断口合闸电阻值 */
    double C1_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double C1_fracture_speed;                        /* A1 断口速度*/
    double C1_fracture_over_travel;                        /* A1 断口超程*/

    double A2_fracture_type;                        /* A1 断口线圈类型 */
    double A2_fracture_time;                        /* A1 断口动作时间 */
    double A2_bounce_time;                        /* A1弹跳时间 */
    double A2_bounce_count;                        /* A1弹跳次数 */
    double A2_short_circuit_time;                        /* A1 断口金属短路时间 */
    double A2_no_current_time;                        /* A1 断口无电流时间 */
    double A2_closing_resistor;                        /* A1 断口合闸电阻值 */
    double A2_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double A2_fracture_speed;                        /* A1 断口速度*/
    double A2_fracture_over_travel;                        /* A1 断口超程*/

    double B2_fracture_type;                        /* A1 断口线圈类型 */
    double B2_fracture_time;                        /* A1 断口动作时间 */
    double B2_bounce_time;                        /* A1弹跳时间 */
    double B2_bounce_count;                        /* A1弹跳次数 */
    double B2_short_circuit_time;                        /* A1 断口金属短路时间 */
    double B2_no_current_time;                        /* A1 断口无电流时间 */
    double B2_closing_resistor;                        /* A1 断口合闸电阻值 */
    double B2_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double B2_fracture_speed;                        /* A1 断口速度*/
    double B2_fracture_over_travel;                        /* A1 断口超程*/

    double C2_fracture_type;                        /* A1 断口线圈类型 */
    double C2_fracture_time;                        /* A1 断口动作时间 */
    double C2_bounce_time;                        /* A1弹跳时间 */
    double C2_bounce_count;                        /* A1弹跳次数 */
    double C2_short_circuit_time;                        /* A1 断口金属短路时间 */
    double C2_no_current_time;                        /* A1 断口无电流时间 */
    double C2_closing_resistor;                        /* A1 断口合闸电阻值 */
    double C2_switching_time;                        /* A1 断口合闸电阻投切时间 */
    double C2_fracture_speed;                        /* A1 断口速度*/
    double C2_fracture_over_travel;                        /* A1 断口超程*/

    double A_phase_coil_current;                        /* A 相线圈电流*/
    double B_phase_coil_current;                        /* B 相线圈电流*/
    double C_phase_coil_current;                        /* C 相线圈电流*/

    double Same_period_as_A;                        /* A 相同相同期*/
    double Same_period_as_B;                        /* B 相同相同期*/
    double Same_period_as_C;                        /* C 相同相同期*/

    double Interphase_synchronization;                        /* 相间同期*/
    double Number_of_samples_N;                        /* 采样点数 N*/
    double Time_step;                        /* 时间步长△t*/
    uint8_t Time_step_unit[1];                        /* 时间步长△t单位*/
} QGDW_5_8_ValueType;
//****************************************************************************************************
typedef struct
{
    uint8_t Data[2000];
} QGDW_5_8_MessageType;

uint16_t QGDW_5_8_ReadData(uint8_t *buff, uint8_t cnt);
char *QGDW_5_8_RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_QGDW_5_8_H_ */
