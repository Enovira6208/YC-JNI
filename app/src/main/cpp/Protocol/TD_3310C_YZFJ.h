#ifndef _TD_3310C_YZFJ_H_
#define _TD_3310C_YZFJ_H_

#include "../public/public.h"
/*保定泰达TD-3310c型号的直流电阻测试仪*/


/*有载分接*/
typedef struct {
    uint8_t head[3];
    uint8_t length[4];
    uint8_t cmd[2];
    uint8_t dataLength[4];
    uint8_t data[87];
} YZFJ_RecvMessage;

typedef struct {
    uint8_t A_transient_time[4];              /*A相过渡时间*/
    uint8_t B_transient_time[4];
    uint8_t C_transient_time[4];
} transient_time;

typedef struct {
    double A_transient_time;              /*A相过渡时间*/
    double B_transient_time;
    double C_transient_time;
} transient_time_value;

typedef struct {
    uint8_t A_transient_resistance[4];         /*A相过渡电阻*/
    uint8_t B_transient_resistance[4];
    uint8_t C_transient_resistance[4];
} transient_resistance;

typedef struct {
    double A_transient_resistance;         /*A相过渡电阻*/
    double B_transient_resistance;
    double C_transient_resistance;
} transient_resistance_value;

typedef struct {
    uint8_t time[7];
    uint8_t testType;
    transient_time TT[3];
    uint8_t TT_unit;                            /*过渡时间单位*/
    transient_resistance TR[3];
    uint8_t TR_unit;                            /*过渡电阻单位*/
    uint8_t Bridging_resistance_unit;           /*桥接电阻单位*/
    uint8_t N[4];
    uint8_t electricity[4];
    uint8_t electricity_unit;
} YZFJ_DataMessage;

typedef struct {
    uint8_t time[7];
    int testType;
    transient_time_value TT[3];
    uint8_t TT_unit;                            /*过渡时间单位*/
    transient_resistance_value TR[3];
    uint8_t TR_unit;                            /*过渡电阻单位*/
    uint8_t Bridging_resistance_unit;           /*桥接电阻单位*/
    double N;
    double electricity;
    uint8_t electricity_unit;
} YZFJ_DataVALUE;

uint16_t TD_3310C_YZFJ_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *TD_3310C_YZFJ_RecvMessage(uint8_t *buff, uint16_t size);

#endif