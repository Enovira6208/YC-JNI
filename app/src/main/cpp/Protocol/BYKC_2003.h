#ifndef _BYKC_2003_H_
#define _BYKC_2003_H_

#include "../public/public.h"


typedef struct {
    double electricity_A;
    double electricity_A_state;   /*状态为数值分别代表倍数和正负 11 代表倍数1，负数；  10 代表倍数1，正数； 40 代表倍数4，负数*/
    double voltage_B;
    double voltage_B_state;
    double electricity_B;
    double electricity_B_state;
    double voltage_C;
    double voltage_C_state;
    double electricity_C;
    double electricity_C_state;
    double voltage_A;
    double voltage_A_state;
} BYKC_2003ValueType;

typedef struct {
    uint8_t sync[2];
    uint8_t length[2];
    uint8_t cmd;
    uint8_t data[28800];
} BYKC_2003MessageType;




uint16_t BYKC_2003ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *BYKC_2003RecvMessage(uint8_t *buff, uint16_t size);

#endif // _BYKC_2003_H_