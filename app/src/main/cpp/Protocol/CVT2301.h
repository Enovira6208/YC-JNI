#ifndef _CVT2301_H_
#define _CVT2301_H_

#include "../public/public.h"

typedef struct {
    uint8_t testTime[6];
    uint8_t rated_variable_ratio[4]; /*额定可变比*/
    uint8_t result[4];
    uint8_t test_error[2];
    uint8_t polarity;
    uint8_t sign;
} CVT2003_single_MessageType;

typedef struct {
    uint8_t testTime[6];
    double rated_variable_ratio;
    double result;
    double test_error;
    char polarity[2];
    char sign[2];
} CVT2003_single_ValueType;

typedef struct {
    uint8_t testTime[6];
    uint8_t rated_variable_ratio[4]; /*额定可变比*/
    uint8_t link_way;                /*连接方式*/
    uint8_t twelve;                  /*前8位为每级调压的高位BCD码，后8位为组别号 HEX*/
    uint8_t threeteen;
    uint8_t fourteen;
    uint8_t fifteen;
    uint8_t sixteen;
    uint8_t change_AB[4];
    uint8_t change_BC[4];
    uint8_t change_AC[4];
    uint8_t error_AB[2];
    uint8_t error_BC[2];
    uint8_t error_AC[2];
    uint8_t sign_AB;
    uint8_t sign_BC;
    uint8_t sign_AC;
} CVT2003_three_MessageType;

typedef struct {
    uint8_t testTime[6];
    double rated_variable_ratio; /*额定可变比*/                              /* 单位 */
    char link_way[5];                /*连接方式*/
    double group;
    double tap_mid;
    double tap_sum;
    double tap_position;
    double Pressure_adjustment_at_each_stage;
    double change_AB;
    double change_BC;
    double change_AC;
    double error_AB;
    double error_BC;
    double error_AC;
    char sign_AB[2];
    char sign_BC[2];
    char sign_AC[2];
} CVT2003_three_ValueType;

uint16_t CVT2003ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *CVT2003RecvMessage(uint8_t *buff, uint16_t size);

#endif