/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-07-28 16:44:41
 * @LastEditTime: 2023-07-28 17:16:00
 * @LastEditors:
 */
#ifndef _TD_3310C_ZLDZ_H_
#define _TD_3310C_ZLDZ_H_

#include "../public/public.h"
/*保定泰达TD-3310c型号的直流电阻测试仪*/

/*直流电阻*/

typedef struct {
    uint8_t AB[4];
    uint8_t BC[4];
    uint8_t CA[4];
} ZLDZ_resistance;

typedef struct {
    uint8_t head[3];
    uint8_t length[4];
    uint8_t cmd[2];
    uint8_t dataLength[4];
    uint8_t data[421];
    uint8_t crc[2];
} ZLDZ_RecvMessage;

typedef struct  {
    uint8_t time[7];
    uint8_t electricity[4];
    uint8_t electricity_unit;
    ZLDZ_resistance group[31];          /*31组*/
    uint8_t resistance_unit;
    uint8_t data2[36];                  /*预留*/
} ZLDZ_DataMessage;

typedef struct {
    double AB;                          /*float类型用double上传*/
    double BC;
    double CA;
} ZLDZ_resistance_value;

typedef struct  {
    uint8_t time[7];
    double electricity;
    uint8_t electricity_unit;
    ZLDZ_resistance_value group[31];          /*31组*/
    uint8_t resistance_unit;
} ZLDZ_DataVALUE;


uint16_t TD_3310C_ZLDZ_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *TD_3310C_ZLDZ_RecvMessage(uint8_t *buff, uint16_t size);

#endif