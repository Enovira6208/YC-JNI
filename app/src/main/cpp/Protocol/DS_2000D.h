/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-01-11 16:18:33
 * @LastEditTime: 2023-05-05 16:30:03
 * @LastEditors:
 */

#ifndef _DS_2000D_H_
#define _DS_2000D_H_

#include "../public/public.h"


typedef struct {
    double ukj_a;
    double ukj_b;
    double ukj_c;
    double zkj_a;
    double zkj_b;
    double zkj_c;
    double AX_electricity;
    double BX_electricity;
    double CX_electricity;
    double AX_voltage;
    double BX_voltage;
    double CX_voltage;
    double power_a;
    double power_b;
    double power_c;
} DS_2000DValueType;

uint16_t DS_2000DReadData(uint8_t *buff, uint8_t cnt);
char *DS_2000DRecvMessage(uint8_t *buff, uint16_t size);

#endif // _DS_2000D_H_

