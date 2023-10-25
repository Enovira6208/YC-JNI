/*
 * QGDW.c
 * @Author       : zhengshuo
 * @Date         : 2023年10月13日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* QGDW*/
#include "QGDW_5_19.h"
#include "../public/mycrc16.h"
static char returnJsonDataBuff[1000];
QGDW_5_19_ValueType QGDW_Value;

char *QGDW_5_19_wifiSend();

/*
 *  @ brief 读取仪器数据
 */
uint16_t QGDW_5_19_ReadData(uint8_t *buff, uint8_t cnt)
{
    uint8_t hexBuff[15];

    hexBuff[0] = 0x42;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x47;

    hexBuff[3] = 0x0F;
    hexBuff[4] = 0x00;
    hexBuff[5] = 0x00;
    hexBuff[6] = 0x00;

    hexBuff[7] = 0x03;
    hexBuff[8] = 0x00;

    hexBuff[9] = 0x00;          /* 数据区长度 */
    hexBuff[10] = 0x00;
    hexBuff[11] = 0x00;
    hexBuff[12] = 0x00;

    hexBuff[13] = 0x88;
    hexBuff[14] = 0xEC;

    PUBLIC_HexToAscll(buff, hexBuff, 15);

    return 16;
}

double QGDW_5_19_count1(uint8_t *buf)
{
    return PUBLIC_IEEE754_32(buf[3], buf[2], buf[1], buf[0]);
}

/*
 *  @ brief 接收数据
 */
char *QGDW_5_19_RecvMessage(uint8_t *buff, uint16_t size)
{
    QGDW_5_19_MessageType *recv = (QGDW_5_19_MessageType *)buff;

        QGDW_5_19_MessageDataType messageData;
        memcpy(messageData.test_time, recv->Data, sizeof(QGDW_5_19_MessageDataType));

        QGDW_Value.test_time[0] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 1000) + '0';
        QGDW_Value.test_time[1] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 100) % 10 + '0';
        QGDW_Value.test_time[2] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 10) % 10 + '0';
        QGDW_Value.test_time[3] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) % 10) + '0';
        QGDW_Value.test_time[4] = '/';
        QGDW_Value.test_time[5] = messageData.test_time[2] / 10 + '0';
        QGDW_Value.test_time[6] = messageData.test_time[2] % 10 + '0';
        QGDW_Value.test_time[7] = '/';
        QGDW_Value.test_time[8] = messageData.test_time[3] / 10 + '0';
        QGDW_Value.test_time[9] = messageData.test_time[3] % 10 + '0';
        QGDW_Value.test_time[10] = ' ';
        QGDW_Value.test_time[11] = messageData.test_time[4] / 10 + '0';
        QGDW_Value.test_time[12] = messageData.test_time[4] % 10 + '0';
        QGDW_Value.test_time[13] = ':';
        QGDW_Value.test_time[14] = messageData.test_time[5] / 10 + '0';
        QGDW_Value.test_time[15] = messageData.test_time[5] % 10 + '0';
        QGDW_Value.test_time[16] = ':';
        QGDW_Value.test_time[17] = messageData.test_time[6] / 10 + '0';
        QGDW_Value.test_time[18] = messageData.test_time[6] % 10 + '0';

        QGDW_Value.test_voltage = QGDW_5_19_count1(messageData.test_voltage);
        QGDW_Value.test_voltage_unit[0] = messageData.test_voltage_unit[0];
        QGDW_Value.test_current = QGDW_5_19_count1(messageData.test_current);
        QGDW_Value.current_unit_1[0] = messageData.current_unit_1[0];
        QGDW_Value.p_75_voltage = QGDW_5_19_count1(messageData.p_75_voltage);
        QGDW_Value.voltage_unit[0] = messageData.voltage_unit[0];
        QGDW_Value.p_75_current = QGDW_5_19_count1(messageData.p_75_current);
        QGDW_Value.current_unit_2[0] = messageData.current_unit_2[0];

        QGDW_Value.Test_duration = messageData.Test_duration[0]*256+messageData.Test_duration[1];
        QGDW_Value.time_unit[0] = messageData.time_unit[0];

        return QGDW_5_19_wifiSend();
        /* 发送数据 */
}

/*
 * @ 通过蓝牙发送数据
 */
char *QGDW_5_19_wifiSend()
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();
        cJSON_AddStringToObject(cjson_data, "device", "QGDW_5_19");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "test_time", "string", "null", 0, QGDW_Value.test_time);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "test_voltage", "double", &QGDW_Value.test_voltage_unit[0], QGDW_Value.test_voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "test_current", "double", &QGDW_Value.current_unit_1[0], QGDW_Value.test_current, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 4, "p_75_voltage", "double", &QGDW_Value.voltage_unit[0], QGDW_Value.p_75_voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 5, "p_75_current", "double", &QGDW_Value.current_unit_2[0], QGDW_Value.p_75_current, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 6, "Test_duration", "double", &QGDW_Value.time_unit[0], QGDW_Value.Test_duration, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
