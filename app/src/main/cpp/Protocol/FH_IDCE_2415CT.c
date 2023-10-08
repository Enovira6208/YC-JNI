/*
 * FH_IDCE_2415CT.c
 * @Author       : zhengshuo
 * @Date         : 2023年9月11日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 泛华 IDCE_2415CT*/
#include "FH_IDCE_2415CT.h"
#include "../public/mycrc16.h"

static char returnJsonDataBuff[1000];
FH_IDCE_2415CTValueType FH_IDCE_2415CTValue;

char *FH_IDCE_2415CTwifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_IDCE_2415CTReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1 || cnt == 2 || cnt == 0) {
        buff[0] = 0xAA;
        buff[1] = 0xAA;
        buff[2] = 0xAA;
        buff[3] = 0xAA;
        buff[4] = 0x12;
        buff[5] = 0x0A;
        buff[6] = 0x0A;
        buff[7] = 0x00;
        buff[8] = 0x00;
        buff[9] = 0x00;
        buff[10] = 0x00;
        buff[11] = cnt;         /*0：实时数据；1：实时数据并显示屏开始缓存；2 读取了缓存的数据*/
        buff[12] = 0x00;
        buff[13] = 0x00;
        buff[14] = 0x00;
        buff[15] = (uint8_t)(mycrc16_calc(buff, 15) << 8);
        buff[16] = (uint8_t)(mycrc16_calc(buff, 15));
        return 17;
    }
    return 0;
}

double FH_IDCE_2415CT_count1(uint8_t *buff, uint8_t type)   /*type表示分辨率小数点后0的个数*/
{
    double value = 0;
    if (type == 1) {
        value = buff[0] + buff[1] * 256;
        value *= 0.1;
        return value;
    } else if (type == 0) {
        value = buff[0] + buff[1] * 256;
        return value;
    } else if (type == 3) {
        value = buff[0] + buff[1] * 256;
        value *= 0.001;
        return value;
    }
    return 0;
}

void FH_IDCE_2415CT_count2(uint8_t *buff1, uint8_t *buff2, uint8_t cnt) /*1开始时间，2测试时长*/
{
    if (cnt == 1) {
        int year = 2000 + buff1[0];
        int month = buff1[1];
        int day = buff1[2];
        int hour = buff1[3];
        int minute = buff1[4];
        int second = buff1[5];
        buff2[0] = '0' + year / 1000;
        buff2[1] = '0' + (year / 100) % 10;
        buff2[2] = '0' + (year / 10) % 10;
        buff2[3] = '0' + year % 10 ;
        buff2[4] = '/';
        buff2[5] = '0' + month / 10;
        buff2[6] = '0' + month % 10;
        buff2[7] = '/';
        buff2[8] = '0' + day / 10;
        buff2[9] = '0' + day % 10;
        buff2[10] = ' ';
        buff2[11] = '0' + hour / 10;
        buff2[12] = '0' + hour % 10;
        buff2[13] = ':';
        buff2[14] = '0' + minute / 10;
        buff2[15] = '0' + minute % 10;
        buff2[16] = ':';
        buff2[17] = '0' + second / 10;
        buff2[18] = '0' + second % 10;
    } else if (cnt == 2) {
        int hour = buff1[0];
        int minute = buff1[1];
        int second = buff1[2];
        buff2[0] = '0' + hour / 10;
        buff2[1] = '0' + hour % 10;
        buff2[2] = ':';
        buff2[3] = '0' + minute / 10;
        buff2[4] = '0' + minute % 10;
        buff2[5] = ':';
        buff2[6] = '0' + second / 10;
        buff2[7] = '0' + second % 10;
    }
}

/*
 *  @ brief 接收数据
 */
char *FH_IDCE_2415CTRecvMessage(uint8_t *buff, uint16_t size)
{
    FH_IDCE_2415CTMessageType *recv = (FH_IDCE_2415CTMessageType *) buff;
    FH_IDCE_2415CTMessageDataType messageData;

    memcpy(messageData.online_voltage, recv->Data, sizeof(FH_IDCE_2415CTMessageDataType));
    if (recv->Head[0] != 0xAA)
        return NULL;

    FH_IDCE_2415CTValue.online_voltage = FH_IDCE_2415CT_count1(messageData.online_voltage, 1);
    FH_IDCE_2415CTValue.total_voltage = FH_IDCE_2415CT_count1(messageData.total_voltage, 1);

    FH_IDCE_2415CT_count2(messageData.start_time, FH_IDCE_2415CTValue.start_time, 1);
    FH_IDCE_2415CT_count2(messageData.test_duration, FH_IDCE_2415CTValue.test_duration, 2);

    FH_IDCE_2415CTValue.keystate = messageData.keystate;
    FH_IDCE_2415CTValue.monomer =  FH_IDCE_2415CT_count1(messageData.monomer, 0);
    FH_IDCE_2415CTValue.test_current = FH_IDCE_2415CT_count1(messageData.test_current, 1);
    FH_IDCE_2415CTValue.test_capacity = FH_IDCE_2415CT_count1(messageData.test_capacity, 0);
    FH_IDCE_2415CTValue.max_monomer = FH_IDCE_2415CT_count1(messageData.max_monomer, 0);
    FH_IDCE_2415CTValue.max_monomer_v = FH_IDCE_2415CT_count1(messageData.max_monomer_v, 3);
    FH_IDCE_2415CTValue.min_monomer = FH_IDCE_2415CT_count1(messageData.min_monomer, 0);
    FH_IDCE_2415CTValue.min_monomer_v = FH_IDCE_2415CT_count1(messageData.min_monomer_v, 3);
    FH_IDCE_2415CTValue.activation_frequency = FH_IDCE_2415CT_count1(messageData.activation_frequency, 0);
    FH_IDCE_2415CTValue.temp1 = FH_IDCE_2415CT_count1(messageData.temp1, 1);
    FH_IDCE_2415CTValue.temp2 = FH_IDCE_2415CT_count1(messageData.temp2, 1);
    FH_IDCE_2415CTValue.temp3 = FH_IDCE_2415CT_count1(messageData.temp3, 1);
    FH_IDCE_2415CTValue.temp4 = FH_IDCE_2415CT_count1(messageData.temp4, 1);
    FH_IDCE_2415CTValue.module_online_voltage = FH_IDCE_2415CT_count1(messageData.module_online_voltage, 1);
    FH_IDCE_2415CTValue.module_total_voltage = FH_IDCE_2415CT_count1(messageData.module_total_voltage, 1);
    FH_IDCE_2415CTValue.diode_state = messageData.diode_state;
    FH_IDCE_2415CTValue.charge_stage = messageData.charge_stage;

    /* 发送数据 */
    return FH_IDCE_2415CTwifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_IDCE_2415CTwifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "IDCE_2415CT");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "online_voltage", "double", "V", FH_IDCE_2415CTValue.online_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "total_voltage", "double", "V", FH_IDCE_2415CTValue.total_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "start_time", "string", "null", 0, FH_IDCE_2415CTValue.start_time);
    PUBLIC_JsonArrayLoading(cjson_array, 4, "test_duration", "string", "null", 0, FH_IDCE_2415CTValue.test_duration);
    PUBLIC_JsonArrayLoading(cjson_array, 5, "keystate", "double", "null", FH_IDCE_2415CTValue.keystate, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "monomer", "double", "节", FH_IDCE_2415CTValue.monomer, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "test_current", "double", "A", FH_IDCE_2415CTValue.test_current, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "test_capacity", "double", "AH", FH_IDCE_2415CTValue.test_capacity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "max_monomer", "double", "null", FH_IDCE_2415CTValue.max_monomer, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 10, "max_monomer_v", "double", "V", FH_IDCE_2415CTValue.max_monomer_v, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 11, "min_monomer", "double", "null", FH_IDCE_2415CTValue.min_monomer, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "min_monomer_v", "double", "V", FH_IDCE_2415CTValue.min_monomer_v, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 13, "activation_frequency", "double", "null", FH_IDCE_2415CTValue.activation_frequency, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 14, "temp1", "double", "℃", FH_IDCE_2415CTValue.temp1, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 15, "temp2", "double", "℃", FH_IDCE_2415CTValue.temp2, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 16, "temp3", "double", "℃", FH_IDCE_2415CTValue.temp3, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 17, "temp4", "double", "℃", FH_IDCE_2415CTValue.temp4, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 18, "module_online_voltage", "double", "V", FH_IDCE_2415CTValue.module_online_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 19, "module_total_voltage", "double", "V", FH_IDCE_2415CTValue.module_total_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 20, "diode_state", "double", "", FH_IDCE_2415CTValue.diode_state, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 21, "charge_stage", "double", "", FH_IDCE_2415CTValue.charge_stage, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
