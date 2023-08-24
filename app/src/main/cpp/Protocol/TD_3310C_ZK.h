/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-07-28 16:46:50
 * @LastEditTime: 2023-07-28 17:15:57
 * @LastEditors:  
 */
#ifndef _TD_3310C_ZK_H_
#define _TD_3310C_ZK_H_

#include "../public/public.h"
/*保定泰达TD-3310c型号的直流电阻测试仪*/

/*阻抗*/
typedef struct {
    uint8_t head[3];
    uint8_t length[4];
    uint8_t cmd[2];
    uint8_t dataLength[4];
    uint8_t data[112];
} ZK_RecvMessage;

typedef struct {
    uint8_t time[7];
    uint8_t testMethod;
    uint8_t testWay;
    uint8_t Pressure_winding;      /*加压绕组*/
    uint8_t Shorting_winding;      /*短接绕组*/
    uint8_t position;           /*加压绕组分接位置*/
    uint8_t frequency[4];
    uint8_t AX_voltage[4];
    uint8_t AX_electricity[4];
    uint8_t AX_power[4];
    uint8_t AX_reactance[4];
    uint8_t AX_impedance[4];
    uint8_t AX_phase_position[4];
    uint8_t AX_percent[4];
    uint8_t BX_voltage[4];
    uint8_t BX_electricity[4];
    uint8_t BX_power[4];
    uint8_t BX_reactance[4];
    uint8_t BX_impedance[4];
    uint8_t BX_phase_position[4];
    uint8_t BX_percent[4];
    uint8_t CX_voltage[4];
    uint8_t CX_electricity[4];
    uint8_t CX_power[4];
    uint8_t CX_reactance[4];
    uint8_t CX_impedance[4];
    uint8_t CX_phase_position[4];
    uint8_t CX_percent[4];
    uint8_t three_phrase_loss[4];
    uint8_t Three_phase_impedance_voltage[4];
    uint8_t Three_phase_impedance[4];
} ZK_DataMessage;

typedef struct {
    uint8_t time[7];
    uint8_t testMethod;
    uint8_t testWay;
    int Pressure_winding;
    int Shorting_winding;
    uint8_t position;           /*加压绕组分接位置*/
    double frequency;
    double AX_voltage;
    double AX_electricity;
    double AX_power;
    double AX_reactance;
    double AX_impedance;
    double AX_phase_position;
    double AX_percent;
    double BX_voltage;
    double BX_electricity;
    double BX_power;
    double BX_reactance;
    double BX_impedance;
    double BX_phase_position;
    double BX_percent;
    double CX_voltage;
    double CX_electricity;
    double CX_power;
    double CX_reactance;
    double CX_impedance;
    double CX_phase_position;
    double CX_percent;
    double three_phrase_loss;
    double Three_phase_impedance_voltage;
    double Three_phase_impedance;
} ZK_DataValue;
uint16_t TD_3310C_ZK_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *TD_3310C_ZK_RecvMessage(uint8_t *buff, uint16_t size);

#endif