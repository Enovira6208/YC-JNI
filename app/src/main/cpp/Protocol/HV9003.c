/*
 * HV9003.c
 * @Author       : zhengshuo
 * @Date         : 2023年9月25日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* HV9003*/
#include "HV9003.h"
#include "../public/mycrc16.h"

static char returnJsonDataBuff[1000];
HV9003_1ValueType HV9003_Value1;
HV9003_2ValueType HV9003_Value2;
HV9003_3ValueType HV9003_Value3;
HV9003_4ValueType HV9003_Value4;

char *HV9003wifiSend(uint8_t cnt);

/*
 *  @ brief 读取仪器数据
 */
uint16_t HV9003_ReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = 0x10;
        return 1;
    }
    if (cnt == 2) {
        buff[0] = 0x20;
        return 1;
    }
    if (cnt == 3) {
        buff[0] = 0x40;
        return 1;
    }
    if (cnt == 4) {
        buff[0] = 0x50;
        return 1;
    }
    return 0;
}

/*
 *  @ brief 接收数据
 */
char *HV9003_RecvMessage(uint8_t *buff, uint16_t size)
{
    HV9003_MessageType *recv = (HV9003_MessageType *)buff;

    if (recv->Data[0] != 0xDA && recv->Data[0] != 0xFD)
        return NULL;

    if (size == 16) {
        HV9003_1MessageDataType messageData;
        memcpy(messageData.head, recv->Data, sizeof(HV9003_1MessageDataType));

        memcpy(HV9003_Value1.voltage, messageData.voltage, 7);
        memcpy(HV9003_Value1.frequency, messageData.frequency, 7);
        HV9003_Value1.percent = messageData.percent;

        /* 发送数据 */
        return HV9003wifiSend(1);
    }

    else if (size == 24) {
        HV9003_2MessageDataType messageData;
        memcpy(messageData.head, recv->Data, sizeof(HV9003_2MessageDataType));

        memcpy(HV9003_Value2.highv_voltage, messageData.highv_voltage, 7);
        memcpy(HV9003_Value2.frequency, messageData.frequency, 7);
        memcpy(HV9003_Value2.lowv_voltage, messageData.lowv_voltage, 4);
        memcpy(HV9003_Value2.current, messageData.current, 4);
        HV9003_Value2.percent = messageData.percent;

        /* 发送数据 */
        return HV9003wifiSend(2);
    }

    else if (size == 15) {
        HV9003_3MessageDataType messageData;
        memcpy(messageData.head, recv->Data, sizeof(HV9003_3MessageDataType));

        memcpy(HV9003_Value3.voltage, messageData.voltage, 7);
        memcpy(HV9003_Value3.frequency, messageData.frequency, 7);

        /* 发送数据 */
        return HV9003wifiSend(3);
    }

    else if (size == 33) {
        HV9003_4MessageDataType messageData;
        memcpy(messageData.head, recv->Data, sizeof(HV9003_4MessageDataType));

        memcpy(HV9003_Value4.voltage, messageData.voltage, 7);
        memcpy(HV9003_Value4.frequency, messageData.frequency, 4);
        memcpy(HV9003_Value4.variable_ratio, messageData.variable_ratio, 6);
        memcpy(HV9003_Value4.error_value, messageData.error_value, 7);
        HV9003_Value4.polarity[0] = messageData.polarity;
        memcpy(HV9003_Value4.phase_difference, messageData.phase_difference, 1);

        /* 发送数据 */
        return HV9003wifiSend(4);
    }

    return NULL;
}

/*
 * @ 通过蓝牙发送数据
 */
char *HV9003wifiSend(uint8_t cnt)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    if (cnt == 1) {
        cJSON_AddStringToObject(cjson_data, "device", "HV9003_1");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "string", "null", 0, HV9003_Value1.voltage);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "frequency", "string", "null", 0, HV9003_Value1.frequency);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "percent", "double", "%", HV9003_Value1.percent, "null");
    }

    if (cnt == 2) {
        cJSON_AddStringToObject(cjson_data, "device", "HV9003_2");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "highv_voltage", "string", "null", 0, HV9003_Value2.highv_voltage);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "frequency", "string", "null", 0, HV9003_Value2.frequency);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "lowv_voltage", "string", "null", 0, HV9003_Value2.lowv_voltage);
        PUBLIC_JsonArrayLoading(cjson_array, 4, "current", "string", "null", 0, HV9003_Value2.current);
        PUBLIC_JsonArrayLoading(cjson_array, 5, "percent", "double", "null", HV9003_Value2.percent, "null");

    }

    if (cnt == 3) {
        cJSON_AddStringToObject(cjson_data, "device", "HV9003_3");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "string", "null", 0, HV9003_Value3.voltage);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "frequency", "string", "null", 0, HV9003_Value3.frequency);
    }

    if (cnt == 4) {
        cJSON_AddStringToObject(cjson_data, "device", "HV9003_4");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "string", "null", 0, HV9003_Value4.voltage);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "frequency", "string", "null", 0, HV9003_Value4.frequency);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "variable_ratio", "string", "null", 0, HV9003_Value4.variable_ratio);
        PUBLIC_JsonArrayLoading(cjson_array, 4, "error_value", "string", "null", 0, HV9003_Value4.error_value);
        PUBLIC_JsonArrayLoading(cjson_array, 5, "polarity", "string", "null", 0, HV9003_Value4.polarity);
        PUBLIC_JsonArrayLoading(cjson_array, 6, "phase_difference", "string", "null", 0, HV9003_Value4.phase_difference);
    }

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
