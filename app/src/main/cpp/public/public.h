/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 16:13:32
 * @LastEditTime: 2022-08-09 08:39:31
 * @LastEditors:
 */

#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <android/log.h>
#include "cJSON.h"

#define LOG_TAG "CPPLOG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

typedef enum
{
    DISABLE = 0U,
    ENABLE = !DISABLE
} FunctionalState;


typedef union
{

    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} PUBLIC_MyFloatType;

typedef struct
{
    cJSON *Param;
} PUBLIC_CjsonParamType;

typedef struct
{
    PUBLIC_CjsonParamType Array[100];
} PUBLIC_CjsonType;


char returnJsonDataBuff[10000];

uint8_t PUBLIC_BcdToNumb(uint8_t bcd);
uint8_t PUBLIC_NumbToBcd(uint8_t numb);
void PUBLIC_AscllToHex(uint8_t *hex, char *ascll, uint16_t len);
void PUBLIC_HexToAscll(char *ascll, uint8_t *hex, uint16_t len);
double PUBLIC_IEEE754_32(uint8_t value3, uint8_t value2, uint8_t value1, uint8_t value0);
uint8_t calc_xor_checksum(uint8_t *buff, uint16_t size);

void PUBLIC_JsonArrayLoading(cJSON *array, uint8_t cnt, char *name, char *datatype,
                             char *unit, double value, char *valueStr);

#endif // _PUBLIC_H_
