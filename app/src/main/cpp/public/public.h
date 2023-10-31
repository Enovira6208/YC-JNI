/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 16:13:32
 * @LastEditTime: 2022-09-13 09:08:40
 * @LastEditors:
 */

#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
// #include <android/log.h>
#include "cJSON.h"

#define LOG_TAG "CPPLOG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef enum {
    DISABLE = 0U,
    ENABLE = !DISABLE
} FunctionalState;

typedef enum {
    PUBLIC_SD_PROTOCO_UNIT_NULL,
    PUBLIC_SD_PROTOCO_UNIT_dB,
    PUBLIC_SD_PROTOCO_UNIT_dBm,
    PUBLIC_SD_PROTOCO_UNIT_dBmV,
    PUBLIC_SD_PROTOCO_UNIT_dBuV,
    PUBLIC_SD_PROTOCO_UNIT_V,
    PUBLIC_SD_PROTOCO_UNIT_mV,
    PUBLIC_SD_PROTOCO_UNIT_uV,
    PUBLIC_SD_PROTOCO_UNIT_PERCENT,                     /* 百分号 */
    PUBLIC_SD_PROTOCO_UNIT_A,
    PUBLIC_SD_PROTOCO_UNIT_mA,
    PUBLIC_SD_PROTOCO_UNIT_uA,
    PUBLIC_SD_PROTOCO_UNIT_O,
    PUBLIC_SD_PROTOCO_UNIT_mO,
    PUBLIC_SD_PROTOCO_UNIT_uO,
    PUBLIC_SD_PROTOCO_UNIT_m_s2,
    PUBLIC_SD_PROTOCO_UNIT_mm,
    PUBLIC_SD_PROTOCO_UNIT_CENTIGRADE,                  /* 摄氏度 */
    PUBLIC_SD_PROTOCO_UNIT_FAHRENHEIT,                  /* 华氏度 */
    PUBLIC_SD_PROTOCO_UNIT_Pa,
    PUBLIC_SD_PROTOCO_UNIT_C,
    PUBLIC_SD_PROTOCO_UNIT_mC,
    PUBLIC_SD_PROTOCO_UNIT_uC,
    PUBLIC_SD_PROTOCO_UNIT_nC,
    PUBLIC_SD_PROTOCO_UNIT_pC,
    PUBLIC_SD_PROTOCO_UNIT_m_s,
    PUBLIC_SD_PROTOCO_UNIT_kO,
    PUBLIC_SD_PROTOCO_UNIT_MO,
    PUBLIC_SD_PROTOCO_UNIT_GO,
    PUBLIC_SD_PROTOCO_UNIT_TO,
    PUBLIC_SD_PROTOCO_UNIT_Hz,
    PUBLIC_SD_PROTOCO_UNIT_H,
    PUBLIC_SD_PROTOCO_UNIT_mH,

    PUBLIC_SD_PROTOCO_UNIT_F = 0x23,
    PUBLIC_SD_PROTOCO_UNIT_mF,
    PUBLIC_SD_PROTOCO_UNIT_uF,
    PUBLIC_SD_PROTOCO_UNIT_nF,
    PUBLIC_SD_PROTOCO_UNIT_pF,
    PUBLIC_SD_PROTOCO_UNIT_s,
    PUBLIC_SD_PROTOCO_UNIT_ms,
    PUBLIC_SD_PROTOCO_UNIT_us,
    PUBLIC_SD_PROTOCO_UNIT_MPa,
    PUBLIC_SD_PROTOCO_UNIT_uL_L,
    PUBLIC_SD_PROTOCO_UNIT_ANGLE,

} PUBLIC_SD_ProtocolUnitType;

typedef union {

    float f;
    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} PUBLIC_MyFloatType;

typedef struct {
    cJSON *Param;
} PUBLIC_CjsonParamType;

typedef struct {
    PUBLIC_CjsonParamType Array[100];
} PUBLIC_CjsonType;

float FourBytesToFloat(uint8_t byte4, uint8_t byte3, uint8_t byte2, uint8_t byte1);
uint8_t PUBLIC_BcdToNumb(uint8_t bcd);
uint8_t PUBLIC_NumbToBcd(uint8_t numb);
void PUBLIC_AscllToHex(uint8_t *hex, char *ascll, uint16_t len);
void PUBLIC_HexToAscll(char *ascll, uint8_t *hex, uint16_t len);
double PUBLIC_IEEE754_32(uint8_t value3, uint8_t value2, uint8_t value1, uint8_t value0);
uint8_t calc_xor_checksum(uint8_t *buff, uint16_t size);

void PUBLIC_JsonArrayLoading(cJSON *array, uint8_t cnt, char *name, char *datatype,
                             char *unit, double value, char *valueStr);

char *PUBLIC_SD_ProtocolUnitAnalysis(uint8_t value);
#endif // _PUBLIC_H_
