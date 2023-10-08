/*
 * PDT_840.c
 * @Author       : zhengshuo
 * @Date         : 2023年9月18日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* PDT_840*/
#include "PDT_840.h"
#include "../public/mycrc16.h"

static char returnJsonDataBuff[1000];
PDT_840_1ValueType PDT_840Value1;
PDT_840_2ValueType PDT_840Value2;
PDT_840_3ValueType PDT_840Value3;
char *PDT_840wifiSend(uint8_t cnt);

/*
 *  @ brief 读取仪器数据
 */
uint16_t PDT_840ReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1 || cnt == 2 || cnt == 3) {
        buff[0] = 0x65;
        buff[1] = cnt;
        buff[2] = 0x03;
        buff[3] = 0x00;
        buff[4] = 0x00;
        buff[5] = (uint8_t)(mycrc16_calc(buff, 5) << 8);
        buff[6] = (uint8_t)(mycrc16_calc(buff, 5));
        buff[7] = 0x56;
        return 8;
    }
    return 0;
}

void PDT_840count1(uint8_t *buf, uint8_t *buf1, uint8_t len)
{
    for (int i = 0; i < len; i++) {
        buf[i] = buf1[i];
    }
}
double PDT_840count2(uint8_t *buf)
{
    return PUBLIC_IEEE754_32(buf[3], buf[2], buf[1], buf[0]);
}

/*
 *  @ brief 接收数据
 */
char *PDT_840RecvMessage(uint8_t *buff, uint16_t size)
{
    PDT_840MessageType *recv = (PDT_840MessageType *)buff;

    if (recv->len[1] == 0x01)
        return NULL;

    if (recv->type == 0x01) {
        PDT_840_1MessageDataType messageData;
        memcpy(messageData.serious_number, recv->Data, sizeof(PDT_840_1MessageDataType));

        PDT_840count1(PDT_840Value1.serious_number, messageData.serious_number, 2);
        PDT_840count1(PDT_840Value1.UUID_number, messageData.UUID_number, 48);
        PDT_840count1(PDT_840Value1.test_code, messageData.test_code, 8);
        PDT_840count1(PDT_840Value1.work_number, messageData.work_number, 8);
        PDT_840count1(PDT_840Value1.test_time, messageData.test_time, 6);
        PDT_840Value1.device_status = messageData.device_status;
        PDT_840count1(PDT_840Value1.diagnosic_number, messageData.diagnosic_number, 2);
        PDT_840count1(PDT_840Value1.abnormal_flag, messageData.abnormal_flag, 2);

        PDT_840Value1.so2 = PDT_840count2(messageData.so2);
        PDT_840Value1.h2s = PDT_840count2(messageData.h2s);
        PDT_840Value1.co = PDT_840count2(messageData.co);
        PDT_840Value1.hf = PDT_840count2(messageData.hf);
        PDT_840Value1.h2 = PDT_840count2(messageData.h2);
        PDT_840Value1.cf4 = PDT_840count2(messageData.cf4);
        PDT_840Value1.no = PDT_840count2(messageData.no);
        PDT_840Value1.o2 = PDT_840count2(messageData.o2);
        PDT_840Value1.dew_point = PDT_840count2(messageData.dew_point);
        PDT_840Value1.humidity = PDT_840count2(messageData.humidity);
        PDT_840Value1.humidity_20 = PDT_840count2(messageData.humidity_20);
        PDT_840Value1.sf6_v = PDT_840count2(messageData.sf6_v);
        PDT_840Value1.sf6_w = PDT_840count2(messageData.sf6_w);
        PDT_840Value1.cf4_v = PDT_840count2(messageData.cf4_v);
        PDT_840Value1.cf4_w = PDT_840count2(messageData.cf4_w);
        PDT_840Value1.n2_v = PDT_840count2(messageData.n2_v);
        PDT_840Value1.n2_w = PDT_840count2(messageData.n2_w);
        PDT_840Value1.air_v = PDT_840count2(messageData.air_v);
        PDT_840Value1.air_w = PDT_840count2(messageData.air_w);
        PDT_840Value1.SF6_CF4_v = PDT_840count2(messageData.SF6_CF4_v);
        PDT_840Value1.SF6_CF4_w = PDT_840count2(messageData.SF6_CF4_w);
        PDT_840Value1.SF6_N2_v = PDT_840count2(messageData.SF6_N2_v);
        PDT_840Value1.SF6_N2_w = PDT_840count2(messageData.SF6_N2_w);
        PDT_840Value1.temp = PDT_840count2(messageData.temp);
        PDT_840Value1.pressure = PDT_840count2(messageData.pressure);

        /* 发送数据 */
        return PDT_840wifiSend(1);
    }

    else if (recv->type == 0x02) {
        PDT_840_2MessageDataType messageData;
        memcpy(messageData.UUID_number, recv->Data, sizeof(PDT_840_2MessageDataType));

        PDT_840count1(PDT_840Value2.UUID_number, messageData.UUID_number, 48);
        PDT_840count1(PDT_840Value2.test_code, messageData.test_code, 8);
        PDT_840count1(PDT_840Value2.work_number, messageData.work_number, 8);

        PDT_840Value2.sf6 = PDT_840count2(messageData.sf6);
        PDT_840Value2.temp = PDT_840count2(messageData.temp);
        PDT_840Value2.humidity = messageData.humidity;
        PDT_840Value2.max = PDT_840count2(messageData.max);
        PDT_840Value2.min = PDT_840count2(messageData.min);
        PDT_840Value2.power = PDT_840count2(messageData.power);
        PDT_840Value2.test_satus = messageData.test_satus;

        /* 发送数据 */
        return PDT_840wifiSend(2);
    }

    else if (recv->type == 0x03) {
        PDT_840_3MessageDataType messageData;
        memcpy(messageData.serious_number, recv->Data, sizeof(PDT_840_1MessageDataType));

        PDT_840count1(PDT_840Value3.serious_number, messageData.serious_number, 2);
        PDT_840count1(PDT_840Value3.UUID_number, messageData.UUID_number, 48);
        PDT_840count1(PDT_840Value3.test_code, messageData.test_code, 8);
        PDT_840count1(PDT_840Value3.work_number, messageData.work_number, 8);
        PDT_840count1(PDT_840Value3.test_time, messageData.test_time, 6);
        PDT_840Value3.verify_mode = messageData.verify_mode;

        PDT_840Value3.alarm1 = PDT_840count2(messageData.alarm1);
        PDT_840Value3.lock1_1 = PDT_840count2(messageData.lock1_1);
        PDT_840Value3.lock1_2 = PDT_840count2(messageData.lock1_2);
        PDT_840Value3.alarm2 = PDT_840count2(messageData.alarm2);
        PDT_840Value3.lock2_1 = PDT_840count2(messageData.lock2_1);
        PDT_840Value3.lock2_2 = PDT_840count2(messageData.lock2_2);
        PDT_840Value3.alarm3 = PDT_840count2(messageData.alarm3);
        PDT_840Value3.lock3_1 = PDT_840count2(messageData.lock3_1);
        PDT_840Value3.lock3_2 = PDT_840count2(messageData.lock3_2);
        PDT_840Value3.alarm4 = PDT_840count2(messageData.alarm4);
        PDT_840Value3.lock4_1 = PDT_840count2(messageData.lock4_1);
        PDT_840Value3.lock4_2 = PDT_840count2(messageData.lock4_2);
        PDT_840Value3.alarm_ask1 = PDT_840count2(messageData.alarm_ask1);
        PDT_840Value3.lock_ask1_1 = PDT_840count2(messageData.lock_ask1_1);
        PDT_840Value3.lock_ask1_2 = PDT_840count2(messageData.lock_ask1_2);
        PDT_840Value3.alarm_ask2 = PDT_840count2(messageData.alarm_ask2);
        PDT_840Value3.lock_ask2_1 = PDT_840count2(messageData.lock_ask2_1);
        PDT_840Value3.lock_ask2_2 = PDT_840count2(messageData.lock_ask2_2);
        PDT_840Value3.alarm_ask3 = PDT_840count2(messageData.alarm_ask3);
        PDT_840Value3.lock_ask3_1 = PDT_840count2(messageData.lock_ask3_1);
        PDT_840Value3.lock_ask3_2 = PDT_840count2(messageData.lock_ask3_2);
        PDT_840Value3.alarm_ask4 = PDT_840count2(messageData.alarm_ask4);
        PDT_840Value3.lock_ask4_1 = PDT_840count2(messageData.lock_ask4_1);
        PDT_840Value3.lock_ask4_2 = PDT_840count2(messageData.lock_ask4_2);

        PDT_840Value3.alarm5 = PDT_840count2(messageData.alarm5);
        PDT_840Value3.lock5_1 = PDT_840count2(messageData.lock5_1);
        PDT_840Value3.lock5_2 = PDT_840count2(messageData.lock5_2);
        PDT_840Value3.alarm6 = PDT_840count2(messageData.alarm6);
        PDT_840Value3.lock6_1 = PDT_840count2(messageData.lock6_1);
        PDT_840Value3.lock6_2 = PDT_840count2(messageData.lock6_2);
        PDT_840Value3.alarm7 = PDT_840count2(messageData.alarm7);
        PDT_840Value3.lock7_1 = PDT_840count2(messageData.lock7_1);
        PDT_840Value3.lock7_2 = PDT_840count2(messageData.lock7_2);
        PDT_840Value3.alarm8 = PDT_840count2(messageData.alarm8);
        PDT_840Value3.lock8_1 = PDT_840count2(messageData.lock8_1);
        PDT_840Value3.lock8_2 = PDT_840count2(messageData.lock8_2);
        PDT_840Value3.alarm_ask5 = PDT_840count2(messageData.alarm_ask5);
        PDT_840Value3.lock_ask5_1 = PDT_840count2(messageData.lock_ask5_1);
        PDT_840Value3.lock_ask5_2 = PDT_840count2(messageData.lock_ask5_2);
        PDT_840Value3.alarm_ask6 = PDT_840count2(messageData.alarm_ask6);
        PDT_840Value3.lock_ask6_1 = PDT_840count2(messageData.lock_ask6_1);
        PDT_840Value3.lock_ask6_2 = PDT_840count2(messageData.lock_ask6_2);
        PDT_840Value3.alarm_ask7 = PDT_840count2(messageData.alarm_ask7);
        PDT_840Value3.lock_ask7_1 = PDT_840count2(messageData.lock_ask7_1);
        PDT_840Value3.lock_ask7_2 = PDT_840count2(messageData.lock_ask7_2);
        PDT_840Value3.alarm_ask8 = PDT_840count2(messageData.alarm_ask8);
        PDT_840Value3.lock_ask8_1 = PDT_840count2(messageData.lock_ask8_1);
        PDT_840Value3.lock_ask8_2 = PDT_840count2(messageData.lock_ask8_2);

        PDT_840Value3.alarm_r1 = PDT_840count2(messageData.alarm_r1);
        PDT_840Value3.lock_r1_1 = PDT_840count2(messageData.lock_r1_1);
        PDT_840Value3.lock_r1_2 = PDT_840count2(messageData.lock_r1_2);
        PDT_840Value3.alarm_r2 = PDT_840count2(messageData.alarm_r2);
        PDT_840Value3.lock_r2_1 = PDT_840count2(messageData.lock_r2_1);
        PDT_840Value3.lock_r2_2 = PDT_840count2(messageData.lock_r2_2);
        PDT_840Value3.alarm_r3 = PDT_840count2(messageData.alarm_r3);
        PDT_840Value3.lock_r3_1 = PDT_840count2(messageData.lock_r3_1);
        PDT_840Value3.lock_r3_2 = PDT_840count2(messageData.lock_r3_2);
        PDT_840Value3.alarm_r4 = PDT_840count2(messageData.alarm_r4);
        PDT_840Value3.lock_r4_1 = PDT_840count2(messageData.lock_r4_1);
        PDT_840Value3.lock_r4_2 = PDT_840count2(messageData.lock_r4_2);
        PDT_840Value3.output_pressure = PDT_840count2(messageData.output_pressure);
        PDT_840Value3.ambient_temp = PDT_840count2(messageData.ambient_temp);
        PDT_840Value3.atmospheric_pressure = PDT_840count2(messageData.atmospheric_pressure);

        PDT_840Value3.device_status = messageData.device_status;
        PDT_840Value3.test_result = messageData.test_result;

        /* 发送数据 */
        return PDT_840wifiSend(3);
    }
    return NULL;
}

/*
 * @ 通过蓝牙发送数据
 */
char *PDT_840wifiSend(uint8_t cnt)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    if (cnt == 1) {
        cJSON_AddStringToObject(cjson_data, "device", "PDT_840_1");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "serious_number", "string", "null", 0, PDT_840Value1.serious_number);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "UUID_number", "string", "null", 0, PDT_840Value1.UUID_number);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "test_code", "string", "null", 0, PDT_840Value1.test_code);
        PUBLIC_JsonArrayLoading(cjson_array, 4, "work_number", "string", "null", 0, PDT_840Value1.work_number);
        PUBLIC_JsonArrayLoading(cjson_array, 5, "test_time", "string", "null", 0, PDT_840Value1.test_time);
        PUBLIC_JsonArrayLoading(cjson_array, 6, "device_status", "double", "null", PDT_840Value1.device_status, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 7, "diagnosic_number", "string", "null", 0, PDT_840Value1.diagnosic_number);
        PUBLIC_JsonArrayLoading(cjson_array, 8, "abnormal_flag", "string", "null", 0, PDT_840Value1.abnormal_flag);
        PUBLIC_JsonArrayLoading(cjson_array, 9, "so2", "double", "μL/L", PDT_840Value1.so2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 10, "h2s", "double", "μL/L", PDT_840Value1.h2s, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 11, "co", "double", "μL/L", PDT_840Value1.co, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 12, "hf", "double", "μL/L", PDT_840Value1.hf, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 13, "h2", "double", "μL/L", PDT_840Value1.h2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 14, "cf4", "double", "μL/L", PDT_840Value1.cf4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 15, "no", "double", "μL/L", PDT_840Value1.no, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 16, "o2", "double", "μL/L", PDT_840Value1.o2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "dew_point", "double", "null", PDT_840Value1.dew_point, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "humidity", "double", "null", PDT_840Value1.humidity, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "humidity_20", "double", "null", PDT_840Value1.humidity_20, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 20, "sf6_v", "double", "%V", PDT_840Value1.sf6_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 21, "sf6_w", "double", "%W", PDT_840Value1.sf6_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 22, "cf4_v", "double", "%V", PDT_840Value1.cf4_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 23, "cf4_w", "double", "%W", PDT_840Value1.cf4_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 24, "n2_v", "double", "%V", PDT_840Value1.n2_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 25, "n2_w", "double", "%W", PDT_840Value1.n2_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 26, "air_v", "double", "%V", PDT_840Value1.air_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 27, "air_w", "double", "%W", PDT_840Value1.air_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 28, "SF6_CF4_v", "double", "%V", PDT_840Value1.SF6_CF4_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 29, "SF6_CF4_w", "double", "%W", PDT_840Value1.SF6_CF4_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 30, "SF6_N2_v", "double", "%V", PDT_840Value1.SF6_N2_v, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 31, "SF6_N2_w", "double", "%W", PDT_840Value1.SF6_N2_w, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 32, "temp", "double", "null", PDT_840Value1.temp, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 33, "pressure", "double", "null", PDT_840Value1.pressure, "null");
    }

    if (cnt == 2) {
        cJSON_AddStringToObject(cjson_data, "device", "PDT_840_2");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "UUID_number", "string", "null", 0, PDT_840Value2.UUID_number);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "test_code", "string", "null", 0, PDT_840Value2.test_code);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "work_number", "string", "null", 0, PDT_840Value2.work_number);
        PUBLIC_JsonArrayLoading(cjson_array, 4, "sf6", "double", "ppmv", PDT_840Value2.sf6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 5, "temp", "double", "null", PDT_840Value2.temp, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 6, "humidity", "double", "null", PDT_840Value2.humidity, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 7, "max", "double", "null", PDT_840Value2.max, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 8, "min", "double", "null", PDT_840Value2.min, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 9, "power", "double", "null", PDT_840Value2.power, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 10, "test_satus", "double", "null", PDT_840Value2.test_satus, "null");
    }

    if (cnt == 3) {
        cJSON_AddStringToObject(cjson_data, "device", "PDT_840_3");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "serious_number", "string", "null", 0, PDT_840Value3.serious_number);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "UUID_number", "string", "null", 0, PDT_840Value3.UUID_number);
        PUBLIC_JsonArrayLoading(cjson_array, 3, "test_code", "string", "null", 0, PDT_840Value3.test_code);
        PUBLIC_JsonArrayLoading(cjson_array, 4, "work_number", "string", "null", 0, PDT_840Value3.work_number);
        PUBLIC_JsonArrayLoading(cjson_array, 5, "test_time", "string", "null", 0, PDT_840Value3.test_time);
        PUBLIC_JsonArrayLoading(cjson_array, 6, "verify_mode", "double", "null", PDT_840Value3.verify_mode, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm1", "double", "MPa", PDT_840Value3.alarm1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock1_1", "double", "MPa", PDT_840Value3.lock1_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock1_2", "double", "MPa", PDT_840Value3.lock1_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm2", "double", "MPa", PDT_840Value3.alarm2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock2_1", "double", "MPa", PDT_840Value3.lock2_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock2_2", "double", "MPa", PDT_840Value3.lock2_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm3", "double", "MPa", PDT_840Value3.alarm3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock3_1", "double", "MPa", PDT_840Value3.lock3_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock3_2", "double", "MPa", PDT_840Value3.lock3_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm4", "double", "MPa", PDT_840Value3.alarm4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock4_1", "double", "MPa", PDT_840Value3.lock4_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock4_2", "double", "MPa", PDT_840Value3.lock4_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask1", "double", "MPa", PDT_840Value3.alarm_ask1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask1_1", "double", "MPa", PDT_840Value3.lock_ask1_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask1_2", "double", "MPa", PDT_840Value3.lock_ask1_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask2", "double", "MPa", PDT_840Value3.alarm_ask2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask2_1", "double", "MPa", PDT_840Value3.lock_ask2_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask2_2", "double", "MPa", PDT_840Value3.lock_ask2_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask3", "double", "MPa", PDT_840Value3.alarm_ask3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask3_1", "double", "MPa", PDT_840Value3.lock_ask3_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask3_2", "double", "MPa", PDT_840Value3.lock_ask3_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask4", "double", "MPa", PDT_840Value3.alarm_ask4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask4_1", "double", "MPa", PDT_840Value3.lock_ask4_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask4_2", "double", "MPa", PDT_840Value3.lock_ask4_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm5", "double", "MPa", PDT_840Value3.alarm5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock5_1", "double", "MPa", PDT_840Value3.lock5_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock5_2", "double", "MPa", PDT_840Value3.lock5_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm6", "double", "MPa", PDT_840Value3.alarm6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock6_1", "double", "MPa", PDT_840Value3.lock6_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock6_2", "double", "MPa", PDT_840Value3.lock6_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm7", "double", "MPa", PDT_840Value3.alarm7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock7_1", "double", "MPa", PDT_840Value3.lock7_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock7_2", "double", "MPa", PDT_840Value3.lock7_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm8", "double", "MPa", PDT_840Value3.alarm8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock8_1", "double", "MPa", PDT_840Value3.lock8_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock8_2", "double", "MPa", PDT_840Value3.lock8_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask5", "double", "MPa", PDT_840Value3.alarm_ask5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask5_1", "double", "MPa", PDT_840Value3.lock_ask5_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask5_2", "double", "MPa", PDT_840Value3.lock_ask5_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask6", "double", "MPa", PDT_840Value3.alarm_ask6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask6_1", "double", "MPa", PDT_840Value3.lock_ask6_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask6_2", "double", "MPa", PDT_840Value3.lock_ask6_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask7", "double", "MPa", PDT_840Value3.alarm_ask7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask7_1", "double", "MPa", PDT_840Value3.lock_ask7_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask7_2", "double", "MPa", PDT_840Value3.lock_ask7_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_ask8", "double", "MPa", PDT_840Value3.alarm_ask8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "lock_ask8_1", "double", "MPa", PDT_840Value3.lock_ask8_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "lock_ask8_2", "double", "MPa", PDT_840Value3.lock_ask8_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_r1", "double", "mΩ", PDT_840Value3.alarm_r1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r1_1", "double", "mΩ", PDT_840Value3.lock_r1_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r1_2", "double", "mΩ", PDT_840Value3.lock_r1_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_r2", "double", "mΩ", PDT_840Value3.alarm_r2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r2_1", "double", "mΩ", PDT_840Value3.lock_r2_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r2_2", "double", "mΩ", PDT_840Value3.lock_r2_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_r3", "double", "mΩ", PDT_840Value3.alarm_r3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r3_1", "double", "mΩ", PDT_840Value3.lock_r3_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r3_2", "double", "mΩ", PDT_840Value3.lock_r3_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "alarm_r4", "double", "mΩ", PDT_840Value3.alarm_r4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r4_1", "double", "mΩ", PDT_840Value3.lock_r4_1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "lock_r4_2", "double", "mΩ", PDT_840Value3.lock_r4_2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "output_pressure", "double", "null", PDT_840Value3.output_pressure, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "ambient_temp", "double", "null", PDT_840Value3.ambient_temp, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "atmospheric_pressure", "double", "null", PDT_840Value3.atmospheric_pressure, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "device_status", "double", "null", PDT_840Value3.device_status, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 17, "test_result", "double", "null", PDT_840Value3.test_result, "null");
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
