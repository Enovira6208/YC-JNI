/*
 * jh6000.c
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 加华 JH6000 */
#include "jh6000.h"
#include "../public/mycrc16.h"
static char returnJsonDataBuff[3000];
char *JH6000_SendData(void);


JH6000_DataValueType JH6000_Value;

FunctionalState JH6000_GetDataFlag = DISABLE;
uint16_t JH6000_DataCnt = 0;


/**
*  @breif 获取数据
*/
uint16_t JH6000_ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[10];
    uint16_t crc;

    memset(hexBuff, 0, sizeof(hexBuff));
    /* 获取数据条数 */
    if (cnt == 1) {
        /* 把数据条数清空  使用最新获取的条数 */
        JH6000_DataCnt = 0;

        hexBuff[0] = 0x65;
        hexBuff[1] = 0x01;
        hexBuff[2] = 0x02;
        hexBuff[3] = 0x00;
        hexBuff[4] = 0x00;

        crc = mycrc16_calc(hexBuff, 5);

        hexBuff[5] = (uint8_t)(crc & 0x00FF);
        hexBuff[6] = (uint8_t)(crc >> 8);
        hexBuff[7] = 0x56;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);
        return 8;

    }
    /* 获取数据 */
    else if (cnt == 2) {
        hexBuff[0] = 0x65;
        hexBuff[1] = 0x01;
        hexBuff[2] = 0x03;
        hexBuff[3] = 0x00;
        hexBuff[4] = 0x02;

        hexBuff[5] = (uint8_t)(JH6000_DataCnt >> 8);
        hexBuff[6] = (uint8_t)JH6000_DataCnt;

        crc = mycrc16_calc(hexBuff, 7);

        hexBuff[7] = (uint8_t)(crc & 0x00FF);
        hexBuff[8] = (uint8_t)(crc >> 8);
        hexBuff[9] = 0x56;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 10);
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
char *JH6000_AnalyDataCnt(uint8_t *buff, uint16_t size)
{
    JH6000_DataCnt = (buff[0] << 8) | (buff[1]);

    return "succeed";
}

/**
 *  @ brief 数据解析
 */
char *JH6000_DataAnalysis(uint8_t *buffer, uint16_t size)
{
    JH6000_DataAnalysisType *recv = (JH6000_DataAnalysisType *)buffer;

    JH6000_Value.SerialNumber = (recv->SerialNumber[0] << 8) | recv->SerialNumber[1];
    JH6000_Value.DateTime[0] = recv->DateTime[0];
    JH6000_Value.DateTime[1] = recv->DateTime[1];
    JH6000_Value.DateTime[2] = recv->DateTime[2];
    JH6000_Value.DateTime[3] = recv->DateTime[3];
    JH6000_Value.DateTime[4] = recv->DateTime[4];
    JH6000_Value.DateTime[5] = recv->DateTime[5];
    JH6000_Value.Status = recv->Status;
    JH6000_Value.DeviceNumber[0] = recv->DeviceNumber[0];
    JH6000_Value.DeviceNumber[1] = recv->DeviceNumber[1];
    JH6000_Value.DeviceNumber[2] = recv->DeviceNumber[2];
    JH6000_Value.DeviceNumber[3] = recv->DeviceNumber[3];
    JH6000_Value.DeviceNumber[4] = recv->DeviceNumber[4];
    JH6000_Value.DeviceNumber[5] = recv->DeviceNumber[5];
    JH6000_Value.SO2 = FourBytesToFloat(recv->SO2[3], recv->SO2[2], recv->SO2[1], recv->SO2[0]);
    JH6000_Value.H2S = FourBytesToFloat(recv->H2S[3], recv->H2S[2], recv->H2S[1], recv->H2S[0]);
    JH6000_Value.CO = FourBytesToFloat(recv->CO[3], recv->CO[2], recv->CO[1], recv->CO[0]);
    JH6000_Value.HF = FourBytesToFloat(recv->HF[3], recv->HF[2], recv->HF[1], recv->HF[0]);
    JH6000_Value.H2 = FourBytesToFloat(recv->H2[3], recv->H2[2], recv->H2[1], recv->H2[0]);
    JH6000_Value.CF4 = FourBytesToFloat(recv->CF4[3], recv->CF4[2], recv->CF4[1], recv->CF4[0]);
    JH6000_Value.NO = FourBytesToFloat(recv->NO[3], recv->NO[2], recv->NO[1], recv->NO[0]);
    JH6000_Value.O2 = FourBytesToFloat(recv->O2[3], recv->O2[2], recv->O2[1], recv->O2[0]);
    JH6000_Value.DewPoint = FourBytesToFloat(recv->DewPoint[3], recv->DewPoint[2], recv->DewPoint[1], recv->DewPoint[0]);
    JH6000_Value.Humi = FourBytesToFloat(recv->Humi[3], recv->Humi[2], recv->Humi[1], recv->Humi[0]);
    JH6000_Value.Humi20 = FourBytesToFloat(recv->Humi20[3], recv->Humi20[2], recv->Humi20[1], recv->Humi20[0]);
    JH6000_Value.SF6_V = FourBytesToFloat(recv->SF6_V[3], recv->SF6_V[2], recv->SF6_V[1], recv->SF6_V[0]);
    JH6000_Value.SF6_W = FourBytesToFloat(recv->SF6_W[3], recv->SF6_W[2], recv->SF6_W[1], recv->SF6_W[0]);
    JH6000_Value.CF4_V = FourBytesToFloat(recv->CF4_V[3], recv->CF4_V[2], recv->CF4_V[1], recv->CF4_V[0]);
    JH6000_Value.CF4_W = FourBytesToFloat(recv->CF4_W[3], recv->CF4_W[2], recv->CF4_W[1], recv->CF4_W[0]);
    JH6000_Value.Temp = FourBytesToFloat(recv->Temp[3], recv->Temp[2], recv->Temp[1], recv->Temp[0]);
    JH6000_Value.MPA = FourBytesToFloat(recv->MPA[3], recv->MPA[2], recv->MPA[1], recv->MPA[0]);
    JH6000_Value.N2_V = FourBytesToFloat(recv->N2_V[3], recv->N2_V[2], recv->N2_V[1], recv->N2_V[0]);
    JH6000_Value.N2_W = FourBytesToFloat(recv->N2_W[3], recv->N2_W[2], recv->N2_W[1], recv->N2_W[0]);
    JH6000_Value.AIR_V = FourBytesToFloat(recv->AIR_V[3], recv->AIR_V[2], recv->AIR_V[1], recv->AIR_V[0]);
    JH6000_Value.AIR_W = FourBytesToFloat(recv->AIR_W[3], recv->AIR_W[2], recv->AIR_W[1], recv->AIR_W[0]);
    JH6000_Value.SF6_CF4_V = FourBytesToFloat(recv->SF6_CF4_V[3], recv->SF6_CF4_V[2], recv->SF6_CF4_V[1], recv->SF6_CF4_V[0]);
    JH6000_Value.SF6_CF4_W = FourBytesToFloat(recv->SF6_CF4_W[3], recv->SF6_CF4_W[2], recv->SF6_CF4_W[1], recv->SF6_CF4_W[0]);
    JH6000_Value.SF6_N2_V = FourBytesToFloat(recv->SF6_N2_V[3], recv->SF6_N2_V[2], recv->SF6_N2_V[1], recv->SF6_N2_V[0]);
    JH6000_Value.SF6_N2_W = FourBytesToFloat(recv->SF6_N2_W[3], recv->SF6_N2_W[2], recv->SF6_N2_W[1], recv->SF6_N2_W[0]);

    /* 发送数据 */
    return JH6000_SendData();
}

/**
 *  @breif 接收信息
 */
char *JH6000_RecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x65) {
            dd = k; break;
        }
    }
    if (dd == 0 && buff[0] != 0x65) {
        return NULL;
    }
    uint16_t crc, length;
    uint8_t tail;
    JH6000_MessageType *recv = (JH6000_MessageType *)(buff + dd);

    length = (recv->Length[0] << 8) | recv->Length[1];
    /* 防止数组越界 */
    if (length >= JH6000_DATA_SIZE) {
        return NULL;
    }

    crc = (recv->Data[length + 1] << 8) | recv->Data[length];

    tail = recv->Data[length + 2];

    /* 判断头尾 */
    if ((recv->Head != JH6000_MSG_HEAD) || (tail != JH6000_MSG_TAIL))
        return NULL;

    /* 判断校验 */
    if (crc != mycrc16_calc(&recv->Head, length + 5))
        return NULL;

    switch (recv->ControlType) {
        case JH6000_CONTROL_GET_PAST_DATA_CNT:
            /* 获取到数据条数 */
            return JH6000_AnalyDataCnt(recv->Data, length);

        case JH6000_CONTROL_GET_DETECTION_DATA:
            /* 采集到数据 */
            return JH6000_DataAnalysis(recv->Data, length);
    }
}

/**
 *  @brief 发送JH6000数据
 */
char *JH6000_SendData(void)
{
    char *str;
    cJSON *cjson_all = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_all, "SO2", JH6000_Value.SO2);
    cJSON_AddNumberToObject(cjson_all, "H2S", JH6000_Value.H2S);
    cJSON_AddNumberToObject(cjson_all, "CO", JH6000_Value.CO);
    cJSON_AddNumberToObject(cjson_all, "HF", JH6000_Value.HF);
    cJSON_AddNumberToObject(cjson_all, "H2", JH6000_Value.H2);
    cJSON_AddNumberToObject(cjson_all, "CF4", JH6000_Value.CF4);
    cJSON_AddNumberToObject(cjson_all, "O2", JH6000_Value.O2);
    cJSON_AddNumberToObject(cjson_all, "dewPoint", JH6000_Value.DewPoint);
    cJSON_AddNumberToObject(cjson_all, "humidity", JH6000_Value.Humi);
    cJSON_AddNumberToObject(cjson_all, "humidity_20C", JH6000_Value.Humi20);
    cJSON_AddNumberToObject(cjson_all, "sf6PurityV", JH6000_Value.SF6_V);
    cJSON_AddNumberToObject(cjson_all, "sf6purityW", JH6000_Value.SF6_W);
    cJSON_AddNumberToObject(cjson_all, "cf4VolumeRatioV", JH6000_Value.CF4_V);
    cJSON_AddNumberToObject(cjson_all, "cf4MassRatioW", JH6000_Value.CF4_W);
    cJSON_AddNumberToObject(cjson_all, "airVolumeRatioV", JH6000_Value.AIR_V);
    cJSON_AddNumberToObject(cjson_all, "airQualityRatioW", JH6000_Value.AIR_W);
    cJSON_AddNumberToObject(cjson_all, "sf6Cf4PurityV", JH6000_Value.SF6_CF4_V);
    cJSON_AddNumberToObject(cjson_all, "sf6Cf4PurityW", JH6000_Value.SF6_CF4_W);
    cJSON_AddNumberToObject(cjson_all, "sf6N2PurityV", JH6000_Value.SF6_N2_V);
    cJSON_AddNumberToObject(cjson_all, "sf6N2PurityW", JH6000_Value.SF6_N2_W);
    cJSON_AddNumberToObject(cjson_all, "temperature", JH6000_Value.Temp);
    cJSON_AddNumberToObject(cjson_all, "pressure_20C", JH6000_Value.MPA);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);
    return returnJsonDataBuff;
}
