/*
 * CTP_120.h
 * @Author       : zhengshuo
 * @Date         : 2023年9月19日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_CTP_120_H_
#define APPLICATION_MIDDLEDRIVERS_CTP_120_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} CTP_120StrType;



typedef struct
{
    uint8_t test_time[7];                           /* 测试时间 */
    uint8_t type;                                   /* 类型 */
    uint8_t once_current[4];                           /* 额定一次电流 */
    uint8_t second_current[4];                         /*额定二次电流*/
    uint8_t Rated_composite_error;                            /*额定复合误差*/
    uint8_t Rated_ALF;                                 /*额定ALF*/
    uint8_t accuracy_class;                                 /*准确级*/
    uint8_t Rated_FS;                                    /*额定FS*/
    uint8_t knee_voltage[4];                                   /* 拐点电压 */
    uint8_t knee_current[4];                                   /* 拐点电流 */
    uint8_t composite_erro[4];                                   /* 复合误差 */
    uint8_t ALF[4];                                   /* 准确限制系数值 */
    uint8_t FS[4];                                   /* 仪表保安系数值 */
    uint8_t Remanence_coefficient[4];                                   /* 剩磁系数 */
    uint8_t Peak_instantaneous_error[4];                                 /* 峰值瞬时误差 */
    uint8_t Turn_ratio_error[4];                                   /* 匝数比误差 */
    uint8_t ratio_difference[4];                                   /* 比值差 */
    uint8_t phase_difference[4];                                   /* 相位差 */
    uint8_t polarity;                                   /* 极性 */
    uint8_t Excitation_current1[4];                                   /* 励磁电流 1 */
    uint8_t Excitation_voltage1[4];                                   /* 励磁电压 1 */
    uint8_t Excitation_current2[4];                                   /* 励磁电流 2 */
    uint8_t Excitation_voltage2[4];                                   /* 励磁电压 2 */
    uint8_t Excitation_current3[4];                                   /* 励磁电流 3 */
    uint8_t Excitation_voltage3[4];                                   /* 励磁电压 3 */
    uint8_t Excitation_current4[4];                                   /* 励磁电流 4 */
    uint8_t Excitation_voltage4[4];                                   /* 励磁电压 4 */
    uint8_t Excitation_current5[4];                                   /* 励磁电流 5 */
    uint8_t Excitation_voltage5[4];                                   /* 励磁电压 5 */
    uint8_t Excitation_current6[4];                                   /* 励磁电流 6 */
    uint8_t Excitation_voltage6[4];                                   /* 励磁电压 6 */
    uint8_t Excitation_current7[4];                                   /* 励磁电流 7 */
    uint8_t Excitation_voltage7[4];                                   /* 励磁电压 7 */
    uint8_t Excitation_current8[4];                                   /* 励磁电流 8 */
    uint8_t Excitation_voltage8[4];                                   /* 励磁电压 8 */
    uint8_t Excitation_current9[4];                                   /* 励磁电流 9 */
    uint8_t Excitation_voltage9[4];                                   /* 励磁电压 9 */
    uint8_t Excitation_current10[4];                                   /* 励磁电流 10 */
    uint8_t Excitation_voltage10[4];                                   /* 励磁电压 10 */
    uint8_t Excitation_current11[4];                                   /* 励磁电流 11 */
    uint8_t Excitation_voltage11[4];                                   /* 励磁电压 11 */
    uint8_t Excitation_current12[4];                                   /* 励磁电流 12*/
    uint8_t Excitation_voltage12[4];                                   /* 励磁电压 12 */
    uint8_t Excitation_current13[4];                                   /* 励磁电流 13 */
    uint8_t Excitation_voltage13[4];                                   /* 励磁电压 13 */
    uint8_t Excitation_current14[4];                                   /* 励磁电流 14 */
    uint8_t Excitation_voltage14[4];                                   /* 励磁电压 14 */
    uint8_t Excitation_current15[4];                                   /* 励磁电流 15 */
    uint8_t Excitation_voltage15[4];                                   /* 励磁电压 15 */
    uint8_t Excitation_current16[4];                                   /* 励磁电流 16 */
    uint8_t Excitation_voltage16[4];                                   /* 励磁电压 16 */
    uint8_t Excitation_current17[4];                                   /* 励磁电流 17 */
    uint8_t Excitation_voltage17[4];                                   /* 励磁电压 17 */
    uint8_t Excitation_current18[4];                                   /* 励磁电流 18 */
    uint8_t Excitation_voltage18[4];                                   /* 励磁电压 18 */
    uint8_t Excitation_current19[4];                                   /* 励磁电流 19 */
    uint8_t Excitation_voltage19[4];                                   /* 励磁电压 19 */
    uint8_t Excitation_current20[4];                                   /* 励磁电流 20 */
    uint8_t Excitation_voltage20[4];                                   /* 励磁电压 20 */   
} CTP_120A_MessageDataType;

typedef struct
{
    uint8_t test_time[19];                           /* 测试时间 */
    double type;                                   /* 类型 */
    double once_current;                           /* 额定一次电流 */
    double second_current;                         /*额定二次电流*/
    double Rated_composite_error;                            /*额定复合误差*/
    double Rated_ALF;                                 /*额定ALF*/
    double accuracy_class;                                 /*准确级*/
    double Rated_FS;                                    /*额定FS*/
    double knee_voltage;                                   /* 拐点电压 */
    double knee_current;                                   /* 拐点电流 */
    double composite_erro;                                   /* 复合误差 */
    double ALF;                                   /* 准确限制系数值 */
    double FS;                                   /* 仪表保安系数值 */
    double Remanence_coefficient;                                   /* 剩磁系数 */
    double Peak_instantaneous_error;                                 /* 峰值瞬时误差 */
    double Turn_ratio_error;                                   /* 匝数比误差 */
    double ratio_difference;                                   /* 比值差 */
    double phase_difference;                                   /* 相位差 */
    double polarity;                                   /* 极性 */
    double Excitation_current1;                                   /* 励磁电流 1 */
    double Excitation_voltage1;                                   /* 励磁电压 1 */
    double Excitation_current2;                                   /* 励磁电流 2 */
    double Excitation_voltage2;                                   /* 励磁电压 2 */
    double Excitation_current3;                                   /* 励磁电流 3 */
    double Excitation_voltage3;                                   /* 励磁电压 3 */
    double Excitation_current4;                                   /* 励磁电流 4 */
    double Excitation_voltage4;                                   /* 励磁电压 4 */
    double Excitation_current5;                                   /* 励磁电流 5 */
    double Excitation_voltage5;                                   /* 励磁电压 5 */
    double Excitation_current6;                                   /* 励磁电流 6 */
    double Excitation_voltage6;                                   /* 励磁电压 6 */
    double Excitation_current7;                                   /* 励磁电流 7 */
    double Excitation_voltage7;                                   /* 励磁电压 7 */
    double Excitation_current8;                                   /* 励磁电流 8 */
    double Excitation_voltage8;                                   /* 励磁电压 8 */
    double Excitation_current9;                                   /* 励磁电流 9 */
    double Excitation_voltage9;                                   /* 励磁电压 9 */
    double Excitation_current10;                                   /* 励磁电流 10 */
    double Excitation_voltage10;                                   /* 励磁电压 10 */
    double Excitation_current11;                                   /* 励磁电流 11 */
    double Excitation_voltage11;                                   /* 励磁电压 11 */
    double Excitation_current12;                                   /* 励磁电流 12*/
    double Excitation_voltage12;                                   /* 励磁电压 12 */
    double Excitation_current13;                                   /* 励磁电流 13 */
    double Excitation_voltage13;                                   /* 励磁电压 13 */
    double Excitation_current14;                                   /* 励磁电流 14 */
    double Excitation_voltage14;                                   /* 励磁电压 14 */
    double Excitation_current15;                                   /* 励磁电流 15 */
    double Excitation_voltage15;                                   /* 励磁电压 15 */
    double Excitation_current16;                                   /* 励磁电流 16 */
    double Excitation_voltage16;                                   /* 励磁电压 16 */
    double Excitation_current17;                                   /* 励磁电流 17 */
    double Excitation_voltage17;                                   /* 励磁电压 17 */
    double Excitation_current18;                                   /* 励磁电流 18 */
    double Excitation_voltage18;                                   /* 励磁电压 18 */
    double Excitation_current19;                                   /* 励磁电流 19 */
    double Excitation_voltage19;                                   /* 励磁电压 19 */
    double Excitation_current20;                                   /* 励磁电流 20 */
    double Excitation_voltage20;                                   /* 励磁电压 20 */
} CTP_120A_ValueType;
//*****************************************************************************************************
typedef struct
{
    uint8_t test_time[7];                           /* 测试时间 */
    uint8_t once_voltage[4];                           /* 额定一次电压 */
    uint8_t second_voltage[4];                         /*额定二次电压*/
    uint8_t polarity;                                   /* 极性 */
    uint8_t ratio_difference[4];                                   /* 比值差 */
    uint8_t Excitation_current1[4];                                   /* 励磁电流 1 */
    uint8_t Excitation_voltage1[4];                                   /* 励磁电压 1 */
    uint8_t Excitation_current2[4];                                   /* 励磁电流 2 */
    uint8_t Excitation_voltage2[4];                                   /* 励磁电压 2 */
    uint8_t Excitation_current3[4];                                   /* 励磁电流 3 */
    uint8_t Excitation_voltage3[4];                                   /* 励磁电压 3 */
    uint8_t Excitation_current4[4];                                   /* 励磁电流 4 */
    uint8_t Excitation_voltage4[4];                                   /* 励磁电压 4 */
    uint8_t Excitation_current5[4];                                   /* 励磁电流 5 */
    uint8_t Excitation_voltage5[4];                                   /* 励磁电压 5 */
    uint8_t Excitation_current6[4];                                   /* 励磁电流 6 */
    uint8_t Excitation_voltage6[4];                                   /* 励磁电压 6 */
    uint8_t Excitation_current7[4];                                   /* 励磁电流 7 */
    uint8_t Excitation_voltage7[4];                                   /* 励磁电压 7 */
    uint8_t Excitation_current8[4];                                   /* 励磁电流 8 */
    uint8_t Excitation_voltage8[4];                                   /* 励磁电压 8 */
    uint8_t Excitation_current9[4];                                   /* 励磁电流 9 */
    uint8_t Excitation_voltage9[4];                                   /* 励磁电压 9 */
    uint8_t Excitation_current10[4];                                   /* 励磁电流 10 */
    uint8_t Excitation_voltage10[4];                                   /* 励磁电压 10 */ 
} CTP_120V_MessageDataType;

typedef struct
{
    uint8_t test_time[19];                           /* 测试时间 */
    double once_voltage;                           /* 额定一次电压 */
    double second_voltage;                         /*额定二次电压*/
    double polarity;                                   /* 极性 */
    double ratio_difference;                                   /* 比值差 */
    double Excitation_current1;                                   /* 励磁电流 1 */
    double Excitation_voltage1;                                   /* 励磁电压 1 */
    double Excitation_current2;                                   /* 励磁电流 2 */
    double Excitation_voltage2;                                   /* 励磁电压 2 */
    double Excitation_current3;                                   /* 励磁电流 3 */
    double Excitation_voltage3;                                   /* 励磁电压 3 */
    double Excitation_current4;                                   /* 励磁电流 4 */
    double Excitation_voltage4;                                   /* 励磁电压 4 */
    double Excitation_current5;                                   /* 励磁电流 5 */
    double Excitation_voltage5;                                   /* 励磁电压 5 */
    double Excitation_current6;                                   /* 励磁电流 6 */
    double Excitation_voltage6;                                   /* 励磁电压 6 */
    double Excitation_current7;                                   /* 励磁电流 7 */
    double Excitation_voltage7;                                   /* 励磁电压 7 */
    double Excitation_current8;                                   /* 励磁电流 8 */
    double Excitation_voltage8;                                   /* 励磁电压 8 */
    double Excitation_current9;                                   /* 励磁电流 9 */
    double Excitation_voltage9;                                   /* 励磁电压 9 */
    double Excitation_current10;                                   /* 励磁电流 10 */
    double Excitation_voltage10;                                   /* 励磁电压 10 */ 
} CTP_120V_ValueType;



typedef struct
{
    uint8_t Head[3];
    uint8_t all_len[4];
    uint8_t cmd[2];
    uint8_t data_len[4];
    uint8_t Data[253];
    uint8_t Tail;
} CTP_120MessageType;

uint16_t CTP_120ReadData(uint8_t *buff, uint8_t cnt);
char *CTP_120RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_FH_AI_6301B_H_ */
