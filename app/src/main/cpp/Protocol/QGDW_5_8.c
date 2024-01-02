/*
 * QGDW.c
 * @Author       : zhengshuo
 * @Date         : 2023年10月13日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */
/*高压开关机械特性测试仪*/
/* QGDW_5_8*/
#include "QGDW_5_8.h"
#include "../public/mycrc16.h"
static char returnJsonDataBuff[6000];
QGDW_5_8_ValueType QGDW_5_8_Value;

char *QGDW_5_8_wifiSend();
/**/
/*
 *  @ brief 读取仪器数据
 */
uint16_t QGDW_5_8_ReadData(uint8_t *buff, uint8_t cnt)
{
    uint8_t hexBuff[15];

    hexBuff[0] = 0x42;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x47;

    hexBuff[3] = 0x00;
    hexBuff[4] = 0x00;
    hexBuff[5] = 0x00;
    hexBuff[6] = 0x0F;

    hexBuff[7] = 0x00;
    hexBuff[8] = 0x03;

    hexBuff[9] = 0x00;          /* 数据区长度 */
    hexBuff[10] = 0x00;
    hexBuff[11] = 0x00;
    hexBuff[12] = 0x00;

    hexBuff[13] = 0xEF;
    hexBuff[14] = 0x03;

    PUBLIC_HexToAscll(buff, hexBuff, 15);

    return 16;
}

double QGDW_5_8_count1(uint8_t *buf)
{
    return PUBLIC_IEEE754_32(buf[3], buf[2], buf[1], buf[0]);
}

/*
 *  @ brief 接收数据
 */
char *QGDW_5_8_RecvMessage(uint8_t *buff, uint16_t size)
{
    QGDW_5_8_MessageType *recv = (QGDW_5_8_MessageType *)buff;

    QGDW_5_8_MessageDataType messageData;
    memcpy(messageData.test_time, recv->Data, sizeof(QGDW_5_8_MessageDataType));

    QGDW_5_8_Value.test_time[0] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 1000) + '0';
    QGDW_5_8_Value.test_time[1] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 100) % 10 + '0';
    QGDW_5_8_Value.test_time[2] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 10) % 10 + '0';
    QGDW_5_8_Value.test_time[3] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) % 10) + '0';
    QGDW_5_8_Value.test_time[4] = '/';
    QGDW_5_8_Value.test_time[5] = messageData.test_time[2] / 10 + '0';
    QGDW_5_8_Value.test_time[6] = messageData.test_time[2] % 10 + '0';
    QGDW_5_8_Value.test_time[7] = '/';
    QGDW_5_8_Value.test_time[8] = messageData.test_time[3] / 10 + '0';
    QGDW_5_8_Value.test_time[9] = messageData.test_time[3] % 10 + '0';
    QGDW_5_8_Value.test_time[10] = ' ';
    QGDW_5_8_Value.test_time[11] = messageData.test_time[4] / 10 + '0';
    QGDW_5_8_Value.test_time[12] = messageData.test_time[4] % 10 + '0';
    QGDW_5_8_Value.test_time[13] = ':';
    QGDW_5_8_Value.test_time[14] = messageData.test_time[5] / 10 + '0';
    QGDW_5_8_Value.test_time[15] = messageData.test_time[5] % 10 + '0';
    QGDW_5_8_Value.test_time[16] = ':';
    QGDW_5_8_Value.test_time[17] = messageData.test_time[6] / 10 + '0';
    QGDW_5_8_Value.test_time[18] = messageData.test_time[6] % 10 + '0';

    QGDW_5_8_Value.fracture_type = messageData.fracture_type[0];
    QGDW_5_8_Value.Switch_Stroke = QGDW_5_8_count1(messageData.Switch_Stroke);
    QGDW_5_8_Value.test_type = messageData.test_type[0];

    QGDW_5_8_Value.A1_fracture_type = messageData.A1_fracture_type[0];
    QGDW_5_8_Value.A1_fracture_time = QGDW_5_8_count1(messageData.A1_fracture_time);
    QGDW_5_8_Value.A1_bounce_time = QGDW_5_8_count1(messageData.A1_bounce_time);
    QGDW_5_8_Value.A1_bounce_count = messageData.A1_bounce_count[0];
    QGDW_5_8_Value.A1_short_circuit_time = QGDW_5_8_count1(messageData.A1_short_circuit_time);
    QGDW_5_8_Value.A1_no_current_time = QGDW_5_8_count1(messageData.A1_no_current_time);
    QGDW_5_8_Value.A1_closing_resistor = messageData.A1_closing_resistor[0] * 256 + messageData.A1_closing_resistor[1];
    QGDW_5_8_Value.A1_switching_time = QGDW_5_8_count1(messageData.A1_switching_time);
    QGDW_5_8_Value.A1_fracture_speed = QGDW_5_8_count1(messageData.A1_fracture_speed);
    QGDW_5_8_Value.A1_fracture_over_travel = QGDW_5_8_count1(messageData.A1_fracture_over_travel);

    QGDW_5_8_Value.B1_fracture_type = messageData.B1_fracture_type[0];
    QGDW_5_8_Value.B1_fracture_time = QGDW_5_8_count1(messageData.B1_fracture_time);
    QGDW_5_8_Value.B1_bounce_time = QGDW_5_8_count1(messageData.B1_bounce_time);
    QGDW_5_8_Value.B1_bounce_count = messageData.B1_bounce_count[0];
    QGDW_5_8_Value.B1_short_circuit_time = QGDW_5_8_count1(messageData.B1_short_circuit_time);
    QGDW_5_8_Value.B1_no_current_time = QGDW_5_8_count1(messageData.B1_no_current_time);
    QGDW_5_8_Value.B1_closing_resistor = messageData.B1_closing_resistor[0] * 256 + messageData.B1_closing_resistor[1];
    QGDW_5_8_Value.B1_switching_time = QGDW_5_8_count1(messageData.B1_switching_time);
    QGDW_5_8_Value.B1_fracture_speed = QGDW_5_8_count1(messageData.B1_fracture_speed);
    QGDW_5_8_Value.B1_fracture_over_travel = QGDW_5_8_count1(messageData.B1_fracture_over_travel);

    QGDW_5_8_Value.C1_fracture_type = messageData.C1_fracture_type[0];
    QGDW_5_8_Value.C1_fracture_time = QGDW_5_8_count1(messageData.C1_fracture_time);
    QGDW_5_8_Value.C1_bounce_time = QGDW_5_8_count1(messageData.C1_bounce_time);
    QGDW_5_8_Value.C1_bounce_count = messageData.C1_bounce_count[0];
    QGDW_5_8_Value.C1_short_circuit_time = QGDW_5_8_count1(messageData.C1_short_circuit_time);
    QGDW_5_8_Value.C1_no_current_time = QGDW_5_8_count1(messageData.C1_no_current_time);
    QGDW_5_8_Value.C1_closing_resistor = messageData.C1_closing_resistor[0] * 256 + messageData.C1_closing_resistor[1];
    QGDW_5_8_Value.C1_switching_time = QGDW_5_8_count1(messageData.C1_switching_time);
    QGDW_5_8_Value.C1_fracture_speed = QGDW_5_8_count1(messageData.C1_fracture_speed);
    QGDW_5_8_Value.C1_fracture_over_travel = QGDW_5_8_count1(messageData.C1_fracture_over_travel);

    QGDW_5_8_Value.A2_fracture_type = messageData.A2_fracture_type[0];
    QGDW_5_8_Value.A2_fracture_time = QGDW_5_8_count1(messageData.A2_fracture_time);
    QGDW_5_8_Value.A2_bounce_time = QGDW_5_8_count1(messageData.A2_bounce_time);
    QGDW_5_8_Value.A2_bounce_count = messageData.A2_bounce_count[0];
    QGDW_5_8_Value.A2_short_circuit_time = QGDW_5_8_count1(messageData.A2_short_circuit_time);
    QGDW_5_8_Value.A2_no_current_time = QGDW_5_8_count1(messageData.A2_no_current_time);
    QGDW_5_8_Value.A2_closing_resistor = messageData.A2_closing_resistor[0] * 256 + messageData.A2_closing_resistor[1];
    QGDW_5_8_Value.A2_switching_time = QGDW_5_8_count1(messageData.A2_switching_time);
    QGDW_5_8_Value.A2_fracture_speed = QGDW_5_8_count1(messageData.A2_fracture_speed);
    QGDW_5_8_Value.A2_fracture_over_travel = QGDW_5_8_count1(messageData.A2_fracture_over_travel);

    QGDW_5_8_Value.B2_fracture_type = messageData.B2_fracture_type[0];
    QGDW_5_8_Value.B2_fracture_time = QGDW_5_8_count1(messageData.B2_fracture_time);
    QGDW_5_8_Value.B2_bounce_time = QGDW_5_8_count1(messageData.B2_bounce_time);
    QGDW_5_8_Value.B2_bounce_count = messageData.B2_bounce_count[0];
    QGDW_5_8_Value.B2_short_circuit_time = QGDW_5_8_count1(messageData.B2_short_circuit_time);
    QGDW_5_8_Value.B2_no_current_time = QGDW_5_8_count1(messageData.B2_no_current_time);
    QGDW_5_8_Value.B2_closing_resistor = messageData.B2_closing_resistor[0] * 256 + messageData.B2_closing_resistor[1];
    QGDW_5_8_Value.B2_switching_time = QGDW_5_8_count1(messageData.B2_switching_time);
    QGDW_5_8_Value.B2_fracture_speed = QGDW_5_8_count1(messageData.B2_fracture_speed);
    QGDW_5_8_Value.B2_fracture_over_travel = QGDW_5_8_count1(messageData.B2_fracture_over_travel);

    QGDW_5_8_Value.C2_fracture_type = messageData.C2_fracture_type[0];
    QGDW_5_8_Value.C2_fracture_time = QGDW_5_8_count1(messageData.C2_fracture_time);
    QGDW_5_8_Value.C2_bounce_time = QGDW_5_8_count1(messageData.C2_bounce_time);
    QGDW_5_8_Value.C2_bounce_count = messageData.C2_bounce_count[0];
    QGDW_5_8_Value.C2_short_circuit_time = QGDW_5_8_count1(messageData.C2_short_circuit_time);
    QGDW_5_8_Value.C2_no_current_time = QGDW_5_8_count1(messageData.C2_no_current_time);
    QGDW_5_8_Value.C2_closing_resistor = messageData.C2_closing_resistor[0] * 256 + messageData.C2_closing_resistor[1];
    QGDW_5_8_Value.C2_switching_time = QGDW_5_8_count1(messageData.C2_switching_time);
    QGDW_5_8_Value.C2_fracture_speed = QGDW_5_8_count1(messageData.C2_fracture_speed);
    QGDW_5_8_Value.C2_fracture_over_travel = QGDW_5_8_count1(messageData.C2_fracture_over_travel);

    QGDW_5_8_Value.A_phase_coil_current = QGDW_5_8_count1(messageData.A_phase_coil_current);
    QGDW_5_8_Value.B_phase_coil_current = QGDW_5_8_count1(messageData.B_phase_coil_current);
    QGDW_5_8_Value.C_phase_coil_current = QGDW_5_8_count1(messageData.C_phase_coil_current);
    QGDW_5_8_Value.Same_period_as_A = QGDW_5_8_count1(messageData.Same_period_as_A);
    QGDW_5_8_Value.Same_period_as_B = QGDW_5_8_count1(messageData.Same_period_as_B);
    QGDW_5_8_Value.Same_period_as_C = QGDW_5_8_count1(messageData.Same_period_as_C);

    QGDW_5_8_Value.Interphase_synchronization = QGDW_5_8_count1(messageData.Interphase_synchronization);
    QGDW_5_8_Value.Number_of_samples_N = messageData.Number_of_samples_N[0] * 256 * 256 * 256 + messageData.Number_of_samples_N[0] * 256 * 256 + messageData.Number_of_samples_N[0] * 256 + messageData.Number_of_samples_N[0];
    QGDW_5_8_Value.Time_step = QGDW_5_8_count1(messageData.Time_step);
    QGDW_5_8_Value.Time_step_unit[0] = messageData.Time_step_unit[0];

    return QGDW_5_8_wifiSend();
    /* 发送数据 */
}

/*
 * @ 通过蓝牙发送数据
 */
char *QGDW_5_8_wifiSend()
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();
    cJSON_AddStringToObject(cjson_data, "device", "QGDW_5_8");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "test_time", "string", "null", 0, QGDW_5_8_Value.test_time);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "fracture_type", "double", "null", QGDW_5_8_Value.fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "Switch_Stroke", "double", "mm", QGDW_5_8_Value.Switch_Stroke, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "test_type", "double", "null", QGDW_5_8_Value.test_type, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 5, "A1_fracture_type", "double", "null", QGDW_5_8_Value.A1_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "A1_fracture_time", "double", "ms", QGDW_5_8_Value.A1_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "A1_bounce_time", "double", "ms", QGDW_5_8_Value.A1_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "A1_bounce_count", "double", "null", QGDW_5_8_Value.A1_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "A1_short_circuit_time", "double", "ms", QGDW_5_8_Value.A1_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 10, "A1_no_current_time", "double", "ms", QGDW_5_8_Value.A1_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 11, "A1_closing_resistor", "double", "Ω", QGDW_5_8_Value.A1_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "A1_switching_time", "double", "ms", QGDW_5_8_Value.A1_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 13, "A1_fracture_speed", "double", "m/s", QGDW_5_8_Value.A1_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 14, "A1_fracture_over_travel", "double", "mm", QGDW_5_8_Value.A1_fracture_over_travel, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 15, "B1_fracture_type", "double", "null", QGDW_5_8_Value.B1_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 16, "B1_fracture_time", "double", "ms", QGDW_5_8_Value.B1_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 17, "B1_bounce_time", "double", "ms", QGDW_5_8_Value.B1_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 18, "B1_bounce_count", "double", "null", QGDW_5_8_Value.B1_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 19, "B1_short_circuit_time", "double", "ms", QGDW_5_8_Value.B1_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 20, "B1_no_current_time", "double", "ms", QGDW_5_8_Value.B1_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 21, "B1_closing_resistor", "double", "Ω", QGDW_5_8_Value.B1_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 22, "B1_switching_time", "double", "ms", QGDW_5_8_Value.B1_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 23, "B1_fracture_speed", "double", "m/s", QGDW_5_8_Value.B1_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 24, "B1_fracture_over_travel", "double", "mm", QGDW_5_8_Value.B1_fracture_over_travel, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 25, "C1_fracture_type", "double", "null", QGDW_5_8_Value.C1_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 26, "C1_fracture_time", "double", "ms", QGDW_5_8_Value.C1_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 27, "C1_bounce_time", "double", "ms", QGDW_5_8_Value.C1_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 28, "C1_bounce_count", "double", "null", QGDW_5_8_Value.C1_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 29, "C1_short_circuit_time", "double", "ms", QGDW_5_8_Value.C1_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 30, "C1_no_current_time", "double", "ms", QGDW_5_8_Value.C1_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 31, "C1_closing_resistor", "double", "Ω", QGDW_5_8_Value.C1_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 32, "C1_switching_time", "double", "ms", QGDW_5_8_Value.C1_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 33, "C1_fracture_speed", "double", "m/s", QGDW_5_8_Value.C1_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 34, "C1_fracture_over_travel", "double", "mm", QGDW_5_8_Value.C1_fracture_over_travel, "null");


    PUBLIC_JsonArrayLoading(cjson_array, 35, "A2_fracture_type", "double", "null", QGDW_5_8_Value.A2_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 36, "A2_fracture_time", "double", "ms", QGDW_5_8_Value.A2_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 37, "A2_bounce_time", "double", "ms", QGDW_5_8_Value.A2_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 38, "A2_bounce_count", "double", "null", QGDW_5_8_Value.A2_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 39, "A2_short_circuit_time", "double", "ms", QGDW_5_8_Value.A2_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 40, "A2_no_current_time", "double", "ms", QGDW_5_8_Value.A2_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 41, "A2_closing_resistor", "double", "Ω", QGDW_5_8_Value.A2_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 42, "A2_switching_time", "double", "ms", QGDW_5_8_Value.A2_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 43, "A2_fracture_speed", "double", "m/s", QGDW_5_8_Value.A2_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 44, "A2_fracture_over_travel", "double", "mm", QGDW_5_8_Value.A2_fracture_over_travel, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 45, "B2_fracture_type", "double", "null", QGDW_5_8_Value.B2_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 46, "B2_fracture_time", "double", "ms", QGDW_5_8_Value.B2_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 47, "B2_bounce_time", "double", "ms", QGDW_5_8_Value.B2_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 48, "B2_bounce_count", "double", "null", QGDW_5_8_Value.B2_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 49, "B2_short_circuit_time", "double", "ms", QGDW_5_8_Value.B2_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 50, "B2_no_current_time", "double", "ms", QGDW_5_8_Value.B2_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 51, "B2_closing_resistor", "double", "Ω", QGDW_5_8_Value.B2_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 52, "B2_switching_time", "double", "ms", QGDW_5_8_Value.B2_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 53, "B2_fracture_speed", "double", "m/s", QGDW_5_8_Value.B2_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 54, "B2_fracture_over_travel", "double", "mm", QGDW_5_8_Value.B2_fracture_over_travel, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 55, "C2_fracture_type", "double", "null", QGDW_5_8_Value.C2_fracture_type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 56, "C2_fracture_time", "double", "ms", QGDW_5_8_Value.C2_fracture_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 57, "C2_bounce_time", "double", "ms", QGDW_5_8_Value.C2_bounce_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 58, "C2_bounce_count", "double", "null", QGDW_5_8_Value.C2_bounce_count, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 59, "C2_short_circuit_time", "double", "ms", QGDW_5_8_Value.C2_short_circuit_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 60, "C2_no_current_time", "double", "ms", QGDW_5_8_Value.C2_no_current_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 61, "C2_closing_resistor", "double", "Ω", QGDW_5_8_Value.C2_closing_resistor, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 62, "C2_switching_time", "double", "ms", QGDW_5_8_Value.C2_switching_time, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 63, "C2_fracture_speed", "double", "m/s", QGDW_5_8_Value.C2_fracture_speed, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 64, "C2_fracture_over_travel", "double", "mm", QGDW_5_8_Value.C2_fracture_over_travel, "null");


    PUBLIC_JsonArrayLoading(cjson_array, 65, "A_phase_coil_current", "double", "A", QGDW_5_8_Value.A_phase_coil_current, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 66, "B_phase_coil_current", "double", "A", QGDW_5_8_Value.B_phase_coil_current, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 67, "C_phase_coil_current", "double", "A", QGDW_5_8_Value.C_phase_coil_current, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 68, "Same_period_as_A", "double", "ms", QGDW_5_8_Value.Same_period_as_A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 69, "Same_period_as_B", "double", "ms", QGDW_5_8_Value.Same_period_as_B, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 70, "Same_period_as_C", "double", "ms", QGDW_5_8_Value.Same_period_as_C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 71, "Number_of_samples_N", "double", "null", QGDW_5_8_Value.Number_of_samples_N, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 72, "Time_step", "double", QGDW_5_8_Value.Time_step_unit, QGDW_5_8_Value.Time_step, "null");


    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
