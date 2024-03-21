/*
 * JHMD3_jh6000.c
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 协议版本 jh6000 1.05 */
#include "JHMD3_jh6000.h"
#include "../public/mycrc16.h"
static char returnJsonDataBuff[1000];
char *JHMD3_jh6000_SendData(void);

JHMD3_jh6000_DataValueType JHMD3_jh6000_Value;

FunctionalState JHMD3_jh6000_GetDataFlag = DISABLE;
uint16_t JHMD3_jh6000_DataCnt = 0;
uint8_t SerialNumber_int = 0;
uint8_t TestEncoding_int = 0;
uint8_t JobNumber_int = 0;
/**
 *  @breif 获取数据
 */
uint16_t JHMD3_jh6000_ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[10];
    uint16_t crc;

    memset(hexBuff, 0, sizeof(hexBuff));
    /* 获取数据条数 */
    if (cnt == 1) {
        /* 把数据条数清空  使用最新获取的条数 */
        JHMD3_jh6000_DataCnt = 0;

        hexBuff[0] = 0x65;
        hexBuff[1] = 0x02;
        hexBuff[2] = 0x05;
        hexBuff[3] = 0x00;
        hexBuff[4] = 0x00;

        crc = mycrc16_calc(hexBuff, 5);

        hexBuff[5] = (uint8_t)(crc & 0x00FF);
        hexBuff[6] = (uint8_t)(crc >> 8);
        hexBuff[7] = 0x56;

        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
        return 8;

    }
    /* 获取数据 */
    else if (cnt == 2) {
        hexBuff[0] = 0x65;
        hexBuff[1] = 0x02;
        hexBuff[2] = 0x03;
        hexBuff[3] = 0x00;
        hexBuff[4] = 0x00;

        crc = mycrc16_calc(hexBuff, 5);

        hexBuff[5] = (uint8_t)(crc & 0x00FF);
        hexBuff[6] = (uint8_t)(crc >> 8);
        hexBuff[7] = 0x56;

        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
        return 10;
    }
    return 0;
}

/**
 * @brief 解析数据条数
 *
 * @param buff
 * @param size
 */
char *JHMD3_jh6000_AnalyDataCnt(uint8_t *buff, uint16_t size)
{
    JHMD3_jh6000_DataCnt = (buff[0] << 8) | (buff[1]);

    return "succeed";
}

/**
 *  @ brief 数据解析
 */

char *JHMD3_jh6000_DataAnalysis(uint8_t *buffer, uint16_t size)
{
    JHMD3_jh6000_DataAnalysisType *recv = (JHMD3_jh6000_DataAnalysisType *)buffer;


    for (int i = 0; i < 48; i++) {
        JHMD3_jh6000_Value.SerialNumber[i] = recv->SerialNumber[i];
    }
    for (int j = 0; j < 48; j++) {
        SerialNumber_int = SerialNumber_int + JHMD3_jh6000_Value.SerialNumber[j] * pow(10, 47 - j);
    }

    JHMD3_jh6000_Value.TestEncoding[0] = recv->TestEncoding[0];
    JHMD3_jh6000_Value.TestEncoding[1] = recv->TestEncoding[1];
    JHMD3_jh6000_Value.TestEncoding[2] = recv->TestEncoding[2];
    JHMD3_jh6000_Value.TestEncoding[3] = recv->TestEncoding[3];
    JHMD3_jh6000_Value.TestEncoding[4] = recv->TestEncoding[4];
    JHMD3_jh6000_Value.TestEncoding[5] = recv->TestEncoding[5];
    JHMD3_jh6000_Value.TestEncoding[6] = recv->TestEncoding[6];
    JHMD3_jh6000_Value.TestEncoding[7] = recv->TestEncoding[7];
    for (int j = 0; j < 8; j++) {
        TestEncoding_int = TestEncoding_int + JHMD3_jh6000_Value.TestEncoding[j] * pow(10, 7 - j);
    }

    JHMD3_jh6000_Value.JobNumber[0] = recv->JobNumber[0];
    JHMD3_jh6000_Value.JobNumber[1] = recv->JobNumber[1];
    JHMD3_jh6000_Value.JobNumber[2] = recv->JobNumber[2];
    JHMD3_jh6000_Value.JobNumber[3] = recv->JobNumber[3];
    JHMD3_jh6000_Value.JobNumber[4] = recv->JobNumber[4];
    JHMD3_jh6000_Value.JobNumber[5] = recv->JobNumber[5];
    JHMD3_jh6000_Value.JobNumber[6] = recv->JobNumber[6];
    JHMD3_jh6000_Value.JobNumber[7] = recv->JobNumber[7];
    for (int j = 0; j < 8; j++) {
        JobNumber_int = JobNumber_int + JHMD3_jh6000_Value.JobNumber[j] * pow(10, 7 - j);
    }

    JHMD3_jh6000_Value.SF6 = PUBLIC_IEEE754_32(recv->SF6[3], recv->SF6[2], recv->SF6[1], recv->SF6[0]);

    JHMD3_jh6000_Value.temperature = PUBLIC_IEEE754_32(recv->temperature[3], recv->temperature[2], recv->temperature[1], recv->temperature[0]);
    JHMD3_jh6000_Value.humidity = recv->humidity;
    JHMD3_jh6000_Value.max = PUBLIC_IEEE754_32(recv->max[3], recv->max[2], recv->max[1], recv->max[0]);
    JHMD3_jh6000_Value.min = PUBLIC_IEEE754_32(recv->min[3], recv->min[2], recv->min[1], recv->min[0]);
    JHMD3_jh6000_Value.electric_quantity = PUBLIC_IEEE754_32(recv->electric_quantity[3], recv->electric_quantity[2], recv->electric_quantity[1], recv->electric_quantity[0]);

    JHMD3_jh6000_Value.status = JHMD3_jh6000_Value.status;
    /* 发送数据 */
    return JHMD3_jh6000_SendData();
}

/**
 *  @breif 接收信息
 */
char *JHMD3_jh6000_RecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x65) {
            dd = k; break;
        }
    }
    printf("%d\n", dd);
    if (dd == 0 && buff[0] != 0x65) {
        return NULL;
    }

    uint16_t crc, length;
    uint8_t tail;
    JHMD3_jh6000_MessageType *recv = (JHMD3_jh6000_MessageType *)(buff + dd);

    length = (recv->Length[0] << 8) | recv->Length[1];

    /* 防止数组越界 */
    if (length >= JHMD3_jh6000_DATA_SIZE)
        return NULL;

    crc = (recv->Data[length + 1] << 8) | recv->Data[length];

    tail = recv->Data[length + 2];

    printf("%x:%x\n", recv->Head, tail);
    /* 判断头尾 */
    if ((recv->Head != JHMD3_jh6000_MSG_HEAD) || (tail != JHMD3_jh6000_MSG_TAIL))
        return NULL;

    /* 判断校验 */
    if (crc != mycrc16_calc(&recv->Head, length + 5))
        return NULL;

    switch (recv->ControlType) {
        case JHMD3_jh6000_CONTROL_GET_PAST_DATA_CNT:
            /* 获取到数据条数 */
            return JHMD3_jh6000_AnalyDataCnt(recv->Data, length);

        case JHMD3_jh6000_CONTROL_GET_DETECTION_DATA:
            /* 采集到数据 */
            return JHMD3_jh6000_DataAnalysis(recv->Data, length);
    }
}

/**
 *  @brief 发送JHMD3_jh6000数据
 */
char *JHMD3_jh6000_SendData(void)
{
    char *str;
    char sendData[20];
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    for (uint8_t i = 0; i < 6; i++) {
        sprintf(&sendData[i * 2], "%02X", JHMD3_jh6000_Value.TestEncoding[i]);
    }

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JHMD3_jh6000");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "SerialNumber", "int", "null", SerialNumber_int, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "TestEncoding", "int", "null",   TestEncoding_int, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "JobNumber", "int", "null", JobNumber_int, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "SF6", "double", "null",  JHMD3_jh6000_Value.SF6, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "temperature", "double", "null",  JHMD3_jh6000_Value.temperature, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "humidity", "int", "null", JHMD3_jh6000_Value.humidity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "max", "double", "null",  JHMD3_jh6000_Value.max, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "min", "double", "null",  JHMD3_jh6000_Value.min, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "electric_quantity", "double", "null",  JHMD3_jh6000_Value.electric_quantity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "status", "int", "null", JHMD3_jh6000_Value.status, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);

    str = cJSON_PrintUnformatted(cjson_data);
//    printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
