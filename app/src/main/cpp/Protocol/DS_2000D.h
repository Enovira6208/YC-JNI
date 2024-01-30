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
    double xkj_a;
    double xkj_b;
    double xkj_c;
    double lkj_a;
    double lkj_b;
    double lkj_c;
    double voltage_a;
    double voltage_b;
    double voltage_c;
    double current_a;
    double current_b;
    double current_c;
    double power_a;
    double power_b;
    double power_c;
} DS_2000DValueType;

uint16_t DS_2000DReadData(uint8_t *buff, uint8_t cnt);
char *DS_2000DRecvMessage(uint8_t *buff, uint16_t size);

#endif // _DS_2000D_H_

