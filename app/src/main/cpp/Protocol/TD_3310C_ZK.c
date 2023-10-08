#include "TD_3310C_ZK.h"
#include "../public/mycrc16.h"

static  char returnJsonDataBuff[1000];


uint16_t TD_3310C_ZK_ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    if (cnt == 1) { /*直流电阻测试仪*/

    } else if (cnt == 2) { /*有载分接开关测试仪*/

    } else if (cnt == 3 ) { /*阻抗测试*/

    }
    return 0;
}

char *TD_3310C_ZK_SendData(ZK_DataValue value)
{
    char *str;
    char time[20];
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    sprintf(&time[0], "%04d", (int)(value.time[0] | (value.time[1] << 8)));
    sprintf(&time[4], "%02d", (int)(value.time[2]));
    sprintf(&time[6], "%02d", (int)(value.time[3]));
    sprintf(&time[8], "%02d", (int)(value.time[4]));
    sprintf(&time[10], "%02d", (int)(value.time[5]));
    sprintf(&time[12], "%02d", (int)(value.time[6]));

    char testMethod[20];
    if (value.testMethod == 0x01) {
        sprintf(testMethod, "%s", "阻抗测试法");
    } else {
        printf("测试方法为空\n");
    }

    char testWay[20];
    if (value.testWay == 0x01) {
        sprintf(testWay, "%s", "单相测试");
    } else if (value.testWay == 0x02) {
        sprintf(testWay, "%s", "三相测试");
    } else {
        printf("测试方式为空\n");
    }

    char Pressure_winding[10];
    if (value.Pressure_winding == 1) {
        sprintf(Pressure_winding, "%s", "高压");
    } else if (value.Pressure_winding == 2) {
        sprintf(Pressure_winding, "%s", "中压");
    } else if (value.Pressure_winding == 3) {
        sprintf(Pressure_winding, "%s", "低压");
    }

    char Shorting_winding[10];
    if (value.Shorting_winding == 1) {
        sprintf(Shorting_winding, "%s", "高压");
    } else if (value.Shorting_winding == 2) {
        sprintf(Shorting_winding, "%s", "中压");
    } else if (value.Shorting_winding == 3) {
        sprintf(Shorting_winding, "%s", "低压");
    }

    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "TD_3310C_ZK_ZLDZ");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "time", "string", "null", 0, time);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "testMethod", "string", "null",  0, testMethod);
    PUBLIC_JsonArrayLoading(cjson_array, 3, "testWay", "string", "null",  0, testWay);
    PUBLIC_JsonArrayLoading(cjson_array, 4, "Pressure_winding", "string", "null",  0, Pressure_winding);
    PUBLIC_JsonArrayLoading(cjson_array, 5, "Shorting_winding", "string", "null",  0, Shorting_winding);
    PUBLIC_JsonArrayLoading(cjson_array, 6, "position", "int", "null",  (int)value.position, "");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "frequency", "double", "null",  value.frequency, "");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "AX_electricity", "double", "null",  value.AX_electricity, "");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "AX_impedance", "double", "null",  value.AX_impedance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 10, "AX_percent", "double", "null",  value.AX_percent, "");
    PUBLIC_JsonArrayLoading(cjson_array, 11, "AX_phase_position", "double", "null",  value.AX_phase_position, "");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "AX_power", "double", "null",  value.AX_power, "");
    PUBLIC_JsonArrayLoading(cjson_array, 13, "AX_reactance", "double", "null",  value.AX_reactance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 14, "AX_voltage", "double", "null",  value.AX_voltage, "");

    PUBLIC_JsonArrayLoading(cjson_array, 15, "BX_electricity", "double", "null",  value.BX_electricity, "");
    PUBLIC_JsonArrayLoading(cjson_array, 16, "BX_impedance", "double", "null",  value.BX_impedance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 17, "BX_percent", "double", "null",  value.BX_percent, "");
    PUBLIC_JsonArrayLoading(cjson_array, 18, "BX_phase_position", "double", "null",  value.BX_phase_position, "");
    PUBLIC_JsonArrayLoading(cjson_array, 19, "BX_power", "double", "null",  value.BX_power, "");
    PUBLIC_JsonArrayLoading(cjson_array, 20, "BX_reactance", "double", "null",  value.BX_reactance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 21, "BX_voltage", "double", "null",  value.BX_voltage, "");

    PUBLIC_JsonArrayLoading(cjson_array, 22, "CX_electricity", "double", "null",  value.CX_electricity, "");
    PUBLIC_JsonArrayLoading(cjson_array, 23, "CX_impedance", "double", "null",  value.CX_impedance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 24, "CX_percent", "double", "null",  value.CX_percent, "");
    PUBLIC_JsonArrayLoading(cjson_array, 25, "CX_phase_position", "double", "null",  value.CX_phase_position, "");
    PUBLIC_JsonArrayLoading(cjson_array, 26, "CX_power", "double", "null",  value.CX_power, "");
    PUBLIC_JsonArrayLoading(cjson_array, 27, "CX_reactance", "double", "null",  value.CX_reactance, "");
    PUBLIC_JsonArrayLoading(cjson_array, 28, "CX_voltage", "double", "null",  value.CX_voltage, "");

    PUBLIC_JsonArrayLoading(cjson_array, 29, "three_phrase_loss", "double", "null",  value.three_phrase_loss, "");
    PUBLIC_JsonArrayLoading(cjson_array, 30, "Three_phase_impedance_voltage", "double", "null",  value.Three_phase_impedance_voltage, "");
    PUBLIC_JsonArrayLoading(cjson_array, 31, "Three_phase_impedance", "double", "null",  value.Three_phase_impedance, "");

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

char *TD_3310C_ZK_DataAnalysis(uint8_t *buff, int length)
{
    ZK_DataMessage *recv = (ZK_DataMessage *)buff;
    ZK_DataValue value;

    for (int i = 0; i < 7; i++) {
        value.time[i] = recv->time[i] ;
    }
    value.testMethod = recv->testMethod;
    value.testWay = recv->testWay;

    if (recv->Pressure_winding = 72) {
        value.Pressure_winding = 1;
    } else if (recv->Pressure_winding = 77) {
        value.Pressure_winding = 2;
    } else if (recv->Pressure_winding = 77) {
        value.Pressure_winding = 3;
    }

    if (recv->Shorting_winding = 72) {
        value.Shorting_winding = 1;
    } else if (recv->Shorting_winding = 72) {
        value.Shorting_winding = 2;
    } else if (recv->Shorting_winding = 72) {
        value.Shorting_winding = 3;
    }

    value.position = recv->position;

    value.frequency = PUBLIC_IEEE754_32(recv->frequency[0], recv->frequency[1], recv->frequency[2], recv->frequency[3]);

    value.AX_voltage = PUBLIC_IEEE754_32(recv->AX_voltage[0], recv->AX_voltage[1], recv->AX_voltage[2], recv->AX_voltage[3]);
    value.AX_electricity = PUBLIC_IEEE754_32(recv->AX_electricity[0], recv->AX_electricity[1], recv->AX_electricity[2], recv->AX_electricity[3]);
    value.AX_impedance = PUBLIC_IEEE754_32(recv->AX_impedance[0], recv->AX_impedance[1], recv->AX_impedance[2], recv->AX_impedance[3]);
    value.AX_percent = PUBLIC_IEEE754_32(recv->AX_percent[0], recv->AX_percent[1], recv->AX_percent[2], recv->AX_percent[3]);
    value.AX_phase_position = PUBLIC_IEEE754_32(recv->AX_phase_position[0], recv->AX_phase_position[1], recv->AX_phase_position[2], recv->AX_phase_position[3]);
    value.AX_power = PUBLIC_IEEE754_32(recv->AX_power[0], recv->AX_power[1], recv->AX_power[2], recv->AX_power[3]);
    value.AX_reactance = PUBLIC_IEEE754_32(recv->AX_reactance[0], recv->AX_reactance[1], recv->AX_reactance[2], recv->AX_reactance[3]);

    value.BX_voltage = PUBLIC_IEEE754_32(recv->BX_voltage[0], recv->BX_voltage[1], recv->BX_voltage[2], recv->BX_voltage[3]);
    value.BX_electricity = PUBLIC_IEEE754_32(recv->BX_electricity[0], recv->BX_electricity[1], recv->BX_electricity[2], recv->BX_electricity[3]);
    value.BX_impedance = PUBLIC_IEEE754_32(recv->BX_impedance[0], recv->BX_impedance[1], recv->BX_impedance[2], recv->BX_impedance[3]);
    value.BX_percent = PUBLIC_IEEE754_32(recv->BX_percent[0], recv->BX_percent[1], recv->BX_percent[2], recv->BX_percent[3]);
    value.BX_phase_position = PUBLIC_IEEE754_32(recv->BX_phase_position[0], recv->BX_phase_position[1], recv->BX_phase_position[2], recv->BX_phase_position[3]);
    value.BX_power = PUBLIC_IEEE754_32(recv->BX_power[0], recv->BX_power[1], recv->BX_power[2], recv->BX_power[3]);
    value.BX_reactance = PUBLIC_IEEE754_32(recv->BX_reactance[0], recv->BX_reactance[1], recv->BX_reactance[2], recv->BX_reactance[3]);

    value.CX_voltage = PUBLIC_IEEE754_32(recv->CX_voltage[0], recv->CX_voltage[1], recv->CX_voltage[2], recv->CX_voltage[3]);
    value.CX_electricity = PUBLIC_IEEE754_32(recv->CX_electricity[0], recv->CX_electricity[1], recv->CX_electricity[2], recv->CX_electricity[3]);
    value.CX_impedance = PUBLIC_IEEE754_32(recv->CX_impedance[0], recv->CX_impedance[1], recv->CX_impedance[2], recv->CX_impedance[3]);
    value.CX_percent = PUBLIC_IEEE754_32(recv->CX_percent[0], recv->CX_percent[1], recv->CX_percent[2], recv->CX_percent[3]);
    value.CX_phase_position = PUBLIC_IEEE754_32(recv->CX_phase_position[0], recv->CX_phase_position[1], recv->CX_phase_position[2], recv->CX_phase_position[3]);
    value.CX_power = PUBLIC_IEEE754_32(recv->CX_power[0], recv->CX_power[1], recv->CX_power[2], recv->CX_power[3]);
    value.CX_reactance = PUBLIC_IEEE754_32(recv->CX_reactance[0], recv->CX_reactance[1], recv->CX_reactance[2], recv->CX_reactance[3]);

    value.Three_phase_impedance = PUBLIC_IEEE754_32(recv->Three_phase_impedance[0], recv->Three_phase_impedance[1], recv->Three_phase_impedance[2], recv->Three_phase_impedance[3]);

    value.three_phrase_loss = PUBLIC_IEEE754_32(recv->three_phrase_loss[0], recv->three_phrase_loss[1], recv->three_phrase_loss[2], recv->three_phrase_loss[3]);

    value.Three_phase_impedance_voltage = PUBLIC_IEEE754_32(recv->Three_phase_impedance_voltage[0], recv->Three_phase_impedance_voltage[1], recv->Three_phase_impedance_voltage[2], recv->Three_phase_impedance_voltage[3]);

    return TD_3310C_ZK_SendData(value);
}

char *TD_3310C_ZK_RecvMessage(uint8_t *buff, uint16_t size)
{
    uint16_t length;
    ZK_RecvMessage *recv = (ZK_RecvMessage *)buff;
    length = (recv->dataLength[1] << 8) | recv->dataLength[0];

    // strcpy(sbuff, recv->data + 12);
    // if ((size - 13) > sizeof(sbuff)) {
    //     printf("数组越界\n");
    // }

    return TD_3310C_ZK_DataAnalysis(recv->data, length);
}
