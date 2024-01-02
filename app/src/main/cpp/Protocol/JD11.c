/*
 * JD11.c
 * @Author       : zhengshuo
 * @Date         : 2023年10月17日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* JD11*/
#include "JD11.h"

static char returnJsonDataBuff[1000];
JD11_ValueType JD11_Value;
char *JD11wifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JD11ReadData(uint8_t *buff, uint8_t cnt)
{
    return 0;
}

double jd11_count1(uint8_t *data, uint8_t *volarity)
{
    double value = 0;

    value = data[0] * 256 + data[1];
    value = value / 10;

    if (volarity[0] == 0) {
        value = -1 * value;
    }
    return value;
}

double jd11_count2(uint8_t *buf)
{
    return buf[0] * 256 + buf[1];
}

/*
 *  @ brief 接收数据
 */
char *JD11RecvMessage(uint8_t *buff, uint16_t size)
{
    JD11_MessageType *recv = (JD11_MessageType *)buff;

    if (recv->Head != 0x99)
        return NULL;

    JD11_MessageDataType messageData;
    memcpy(messageData.time, recv->Data, sizeof(JD11_MessageDataType));

    JD11_Value.time[0] = '2';
    JD11_Value.time[1] = '0';
    JD11_Value.time[2] = messageData.time[0] / 10 + '0';
    JD11_Value.time[3] = messageData.time[0] / 10 + '0';
    JD11_Value.time[4] = '/';
    JD11_Value.time[5] = messageData.time[1] / 10 + '0';
    JD11_Value.time[6] = messageData.time[1] % 10 + '0';
    JD11_Value.time[7] = '/';
    JD11_Value.time[8] = messageData.time[2] / 10 + '0';
    JD11_Value.time[9] = messageData.time[2] % 10 + '0';
    JD11_Value.time[10] = ' ';
    JD11_Value.time[11] = messageData.time[3] / 10 + '0';
    JD11_Value.time[12] = messageData.time[3] % 10 + '0';
    JD11_Value.time[13] = ':';
    JD11_Value.time[14] = messageData.time[4] / 10 + '0';
    JD11_Value.time[15] = messageData.time[4] % 10 + '0';

    JD11_Value.temp = jd11_count1(messageData.temp, messageData.temp_polarity);

    JD11_Value.contact_type = messageData.contact_type[0];



    JD11_Value.contact2_1_up_pt = jd11_count2(messageData.contact2_1_up_pt);
    JD11_Value.contact2_1_up_p20 = jd11_count2(messageData.contact2_1_up_p20);

    JD11_Value.contact2_2_up_pt = jd11_count2(messageData.contact2_2_up_pt);
    JD11_Value.contact2_2_up_p20 = jd11_count2(messageData.contact2_2_up_p20);
    JD11_Value.contact2_2_down_p20 = jd11_count2(messageData.contact2_2_down_p20);
    JD11_Value.contact2_3_down_pt = jd11_count2(messageData.contact2_3_down_pt);
    JD11_Value.contact2_3_down_p20 = jd11_count2(messageData.contact2_3_down_p20);
    JD11_Value.contact2_down_avg_pt = jd11_count2(messageData.contact2_down_avg_pt);
    JD11_Value.contact2_down_avg_p20 = jd11_count2(messageData.contact2_down_avg_p20);
    JD11_Value.contact3_1_up_pt = jd11_count2(messageData.contact3_1_up_pt);
    JD11_Value.contact3_1_up_p20 = jd11_count2(messageData.contact3_1_up_p20);
    JD11_Value.contact3_2_up_pt = jd11_count2(messageData.contact3_2_up_pt);
    JD11_Value.contact3_2_up_p20 = jd11_count2(messageData.contact3_2_up_p20);
    JD11_Value.contact3_3_up_pt = jd11_count2(messageData.contact3_3_up_pt);
    JD11_Value.contact3_3_up_p20 = jd11_count2(messageData.contact3_3_up_p20);
    JD11_Value.contact3_up_avg_pt = jd11_count2(messageData.contact3_up_avg_pt);
    JD11_Value.contact3_up_avg_p20 = jd11_count2(messageData.contact3_up_avg_p20);
    JD11_Value.contact3_1_down_pt = jd11_count2(messageData.contact3_1_down_pt);
    JD11_Value.contact3_1_down_p20 = jd11_count2(messageData.contact3_1_down_p20);
    JD11_Value.contact3_2_down_pt = jd11_count2(messageData.contact3_2_down_pt);
    JD11_Value.contact3_2_down_p20 = jd11_count2(messageData.contact3_2_down_p20);
    JD11_Value.contact3_3_down_pt = jd11_count2(messageData.contact3_3_down_pt);
    JD11_Value.contact3_3_down_p20 = jd11_count2(messageData.contact3_3_down_p20);
    JD11_Value.contact3_down_avg_pt = jd11_count2(messageData.contact3_down_avg_pt);
    JD11_Value.contact3_down_avg_p20 = jd11_count2(messageData.contact3_down_avg_p20);
    JD11_Value.contact1_1_up_pt = jd11_count2(messageData.contact1_1_up_pt);
    JD11_Value.contact1_1_up_p20 = jd11_count2(messageData.contact1_1_up_p20);
    JD11_Value.contact1_2_up_pt = jd11_count2(messageData.contact1_2_up_pt);
    JD11_Value.contact1_2_up_p20 = jd11_count2(messageData.contact1_2_up_p20);
    JD11_Value.contact1_3_up_pt = jd11_count2(messageData.contact1_3_up_pt);
    JD11_Value.contact1_3_up_p20 = jd11_count2(messageData.contact1_3_up_p20);
    JD11_Value.contact1_up_avg_pt = jd11_count2(messageData.contact1_up_avg_pt);


    JD11_Value.contact1_up_avg_p20 = jd11_count2(messageData.contact1_up_avg_p20);
    JD11_Value.contact1_1_down_pt = jd11_count2(messageData.contact1_1_down_pt);
    JD11_Value.contact1_1_down_p20 = jd11_count2(messageData.contact1_1_down_p20);
    JD11_Value.contact1_2_down_pt = jd11_count2(messageData.contact1_2_down_pt);
    JD11_Value.contact1_2_down_p20 = jd11_count2(messageData.contact1_2_down_p20);
    JD11_Value.contact1_3_down_pt = jd11_count2(messageData.contact1_3_down_pt);
    JD11_Value.contact1_3_down_p20 = jd11_count2(messageData.contact1_3_down_p20);
    JD11_Value.contact1_down_avg_pt = jd11_count2(messageData.contact1_down_avg_pt);
    JD11_Value.contact1_down_avg_p20 = jd11_count2(messageData.contact1_down_avg_p20);

    /* 发送数据 */
    return JD11wifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *JD11wifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JD11");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "test_time", "string", "null", 0, JD11_Value.time);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "temperature", "double", "℃", JD11_Value.temp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "contact_type", "double", "null", JD11_Value.contact_type, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 4, "contact2_1_up_pt", "double", "null", JD11_Value.contact2_1_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "contact2_1_up_p20", "double", "null", JD11_Value.contact2_1_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "contact2_2_up_pt", "double", "null", JD11_Value.contact2_2_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "contact2_2_up_p20", "double", "null", JD11_Value.contact2_2_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "contact2_3_up_pt", "double", "null", JD11_Value.contact2_3_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "contact2_3_up_p20", "double", "null", JD11_Value.contact2_3_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 10, "contact2_up_avg_pt", "double", "null", JD11_Value.contact2_up_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 11, "contact2_up_avg_p20", "double", "null", JD11_Value.contact2_up_avg_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "contact2_1_down_pt", "double", "null", JD11_Value.contact2_1_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 13, "contact2_1_down_p20", "double", "null", JD11_Value.contact2_1_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 14, "contact2_2_down_pt", "double", "null", JD11_Value.contact2_2_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 15, "contact2_2_down_p20", "double", "null", JD11_Value.contact2_2_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 16, "contact2_3_down_pt", "double", "null", JD11_Value.contact2_3_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 17, "contact2_3_down_p20", "double", "null", JD11_Value.contact2_3_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 18, "contact2_down_avg_pt", "double", "null", JD11_Value.contact2_down_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 19, "contact2_down_avg_p20", "double", "null", JD11_Value.contact2_down_avg_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 20, "contact3_1_up_pt", "double", "null", JD11_Value.contact3_1_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 21, "contact3_1_up_p20", "double", "null", JD11_Value.contact3_1_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 22, "contact3_2_up_pt", "double", "null", JD11_Value.contact3_2_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 23, "contact3_2_up_p20", "double", "null", JD11_Value.contact3_2_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 24, "contact3_3_up_pt", "double", "null", JD11_Value.contact3_3_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 25, "contact3_3_up_p20", "double", "null", JD11_Value.contact3_3_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 26, "contact3_up_avg_pt", "double", "null", JD11_Value.contact3_up_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 27, "contact3_up_avg_p20", "double", "null", JD11_Value.contact3_up_avg_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 28, "contact3_1_down_pt", "double", "null", JD11_Value.contact3_1_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 29, "contact3_1_down_p20", "double", "null", JD11_Value.contact3_1_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 30, "contact3_2_down_pt", "double", "null", JD11_Value.contact3_2_down_pt, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 31, "contact3_2_down_p20", "double", "null", JD11_Value.contact3_2_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 32, "contact3_3_down_pt", "double", "null", JD11_Value.contact3_3_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 33, "contact3_3_down_p20", "double", "null", JD11_Value.contact3_3_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 34, "contact3_down_avg_pt", "double", "null", JD11_Value.contact3_down_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 35, "contact3_down_avg_p20", "double", "null", JD11_Value.contact3_down_avg_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 36, "contact1_1_up_pt", "double", "null", JD11_Value.contact1_1_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 37, "contact1_1_up_p20", "double", "null", JD11_Value.contact1_1_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 38, "contact1_2_up_pt", "double", "null", JD11_Value.contact1_2_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 39, "contact1_2_up_p20", "double", "null", JD11_Value.contact1_2_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 40, "contact1_3_up_pt", "double", "null", JD11_Value.contact1_3_up_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 41, "contact1_3_up_p20", "double", "null", JD11_Value.contact1_3_up_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 42, "contact1_up_avg_pt", "double", "null", JD11_Value.contact1_up_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 43, "contact1_up_avg_p20", "double", "null", JD11_Value.contact1_up_avg_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 44, "contact1_1_down_pt", "double", "null", JD11_Value.contact1_1_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 45, "contact1_1_down_p20", "double", "null", JD11_Value.contact1_1_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 46, "contact1_2_down_pt", "double", "null", JD11_Value.contact1_2_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 47, "contact1_2_down_p20", "double", "null", JD11_Value.contact1_2_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 48, "contact1_3_down_pt", "double", "null", JD11_Value.contact1_3_down_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 49, "contact1_3_down_p20", "double", "null", JD11_Value.contact1_3_down_p20, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 50, "contact1_down_avg_pt", "double", "null", JD11_Value.contact1_down_avg_pt, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 51, "contact1_down_avg_p20", "double", "null", JD11_Value.contact1_down_avg_p20, "null");



    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
