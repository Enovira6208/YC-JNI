#include "TD_3310C_YZFJ.h"
#include "../public/mycrc16.h"

static char returnJsonDataBuff[2500];


uint16_t TD_3310C_YZFJ_ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[15];
    hexBuff[0] = 0x42;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x47;
    hexBuff[3] = 0x0f;
    hexBuff[4] = 0x00;
    hexBuff[5] = 0x00;
    hexBuff[6] = 0x00;
    hexBuff[7] = 0x03;
    hexBuff[8] = 0x00;
    hexBuff[9] = 0x00;
    hexBuff[10] = 0x00;
    hexBuff[11] = 0x00;
    hexBuff[12] = 0x00;
    hexBuff[13] = 0x88;
    hexBuff[14] = 0xec;
    PUBLIC_HexToAscll(ascllBuff, hexBuff, 15);

    return 16;
}


char *TD_3310C_YZFJ_SendData(YZFJ_DataVALUE value)
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

    char testName[20];
    if (value.testType == 0x01) {
        sprintf(testName, "%s", "直流测试");
    } else if (value.testType == 0x02) {
        sprintf(testName, "%s", "交流测试");
    }

    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "TD_3310C_YZFJ");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "time", "string", "null", 0, time);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "testName", "string", "null",  0, testName);

    for (int j = 0; j < 3; j++) {
        char temp_A[30], temp_B[30], temp_C[30];
        sprintf(&temp_A[0], "%s", "A_transient_time");
        sprintf(&temp_A[16], "%d", j);
        sprintf(&temp_B[0], "%s", "B_transient_time");
        sprintf(&temp_B[16], "%d", j);
        sprintf(&temp_C[0], "%s", "C_transient_time");
        sprintf(&temp_C[16], "%d", j);

        PUBLIC_JsonArrayLoading(cjson_array, 3 + j * 3, temp_A, "double", "null", value.TT[j].A_transient_time, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 4 + j * 3, temp_B, "double", "null", value.TT[j].B_transient_time, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 5 + j * 3, temp_C, "double", "null", value.TT[j].C_transient_time, "null");
    }

    char TT_unit[5];
    if (value.TT_unit == 0x28) {
        sprintf(TT_unit, "%s", "s");
    } else if (value.TT_unit == 0x29) {
        sprintf(TT_unit, "%s", "ms");
    } else if (value.TT_unit == 0x2a) {
        sprintf(TT_unit, "%s", "us");
    }

    PUBLIC_JsonArrayLoading(cjson_array, 12, "TT_unit", "string", "null", 0, TT_unit);


    // for (int j = 0; j < 3; j++) {
    //     char temp_A[30], temp_B[30], temp_C[30];
    //     sprintf(&temp_A[0], "%s", "A_transient_resistance");
    //     sprintf(&temp_A[22], "%d", j);
    //     sprintf(&temp_B[0], "%s", "B_transient_resistance");
    //     sprintf(&temp_B[22], "%d", j);
    //     sprintf(&temp_C[0], "%s", "C_transient_resistance");
    //     sprintf(&temp_C[22], "%d", j);

    //     PUBLIC_JsonArrayLoading(cjson_array, 13 + j * 3, temp_A, "double", "null", value.TR[j].A_transient_resistance, "null");
    //     PUBLIC_JsonArrayLoading(cjson_array, 14 + j * 3, temp_B, "double", "null", value.TR[j].B_transient_resistance, "null");
    //     PUBLIC_JsonArrayLoading(cjson_array, 15 + j * 3, temp_C, "double", "null", value.TR[j].C_transient_resistance, "null");
    // }

    PUBLIC_JsonArrayLoading(cjson_array, 16, "A_transient_resistance1", "double", "null", value.TR[0].A_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 17, "A_transient_resistance2", "double", "null", value.TR[0].B_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 18, "A_bridging_resistance", "double", "null", value.TR[0].C_transient_resistance, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 19, "B_transient_resistance1", "double", "null", value.TR[1].A_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 20, "B_transient_resistance2", "double", "null", value.TR[1].B_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 21, "B_bridging_resistance", "double", "null", value.TR[1].C_transient_resistance, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 22, "C_transient_resistance1", "double", "null", value.TR[2].A_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 23, "C_transient_resistance2", "double", "null", value.TR[2].B_transient_resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 24, "C_bridging_resistance", "double", "null", value.TR[2].C_transient_resistance, "null");


    char TR_unit[5] = "";
    if (value.TR_unit == 0x1a) {
        sprintf(TR_unit, "%s", "kΩ");
    } else if (value.TR_unit == 0x1b) {
        sprintf(TR_unit, "%s", "MΩ");
    } else if (value.TR_unit == 0x1c) {
        sprintf(TR_unit, "%s", "GΩ");
    } else if (value.TR_unit == 0x1d) {
        sprintf(TR_unit, "%s", "TΩ");
    }

    char Bridging_resistance_unit[5] = "";
    if (value.Bridging_resistance_unit == 0x1a) {
        sprintf(Bridging_resistance_unit, "%s", "kΩ");
    } else if (value.Bridging_resistance_unit == 0x1b) {
        sprintf(Bridging_resistance_unit, "%s", "MΩ");
    } else if (value.Bridging_resistance_unit == 0x1c) {
        sprintf(Bridging_resistance_unit, "%s", "GΩ");
    } else if (value.Bridging_resistance_unit == 0x1d) {
        sprintf(Bridging_resistance_unit, "%s", "TΩ");
    }
    PUBLIC_JsonArrayLoading(cjson_array, 22, "TR_unit", "string", "null", 0, TR_unit);
    PUBLIC_JsonArrayLoading(cjson_array, 23, "Bridging_resistance_unit", "string", "null", 0, Bridging_resistance_unit);
    PUBLIC_JsonArrayLoading(cjson_array, 24, "N", "double", "null", value.N, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 25, "electricity", "double", "null", value.electricity, "null");


    char e_unit[5] = "";
    if (value.electricity_unit == 0x09) {
        sprintf(e_unit, "%s", "A");
    } else if (value.electricity_unit == 0x0a) {
        sprintf(e_unit, "%s", "mA");
    } else if (value.electricity_unit == 0x0b) {
        sprintf(e_unit, "%s", "uA");
    }

    PUBLIC_JsonArrayLoading(cjson_array, 26, "electricity_unit", "string", "null", 0, e_unit);

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

char *TD_3310C_YZFJ_DataAnalysis(uint8_t *buffer, int length)
{
    YZFJ_DataMessage *recv = (YZFJ_DataMessage *)buffer;
    YZFJ_DataVALUE value;
    for (int i = 0; i < 7; i++) {
        value.time[i] = recv->time[i];
    }
    value.testType = recv->testType;

    for (int j = 0; j < 3; j++) {
        value.TT[j].A_transient_time = PUBLIC_IEEE754_32(recv->TT[j].A_transient_time[0], recv->TT[j].A_transient_time[1], recv->TT[j].A_transient_time[2], recv->TT[j].A_transient_time[3]);
        value.TT[j].B_transient_time = PUBLIC_IEEE754_32(recv->TT[j].B_transient_time[0], recv->TT[j].B_transient_time[1], recv->TT[j].B_transient_time[2], recv->TT[j].B_transient_time[3]);
        value.TT[j].C_transient_time = PUBLIC_IEEE754_32(recv->TT[j].C_transient_time[0], recv->TT[j].C_transient_time[1], recv->TT[j].C_transient_time[2], recv->TT[j].C_transient_time[3]);
    }
    value.TT_unit = recv->TT_unit;
    for (int j = 0; j < 3; j++) {
        value.TR[j].A_transient_resistance = PUBLIC_IEEE754_32(recv->TR[j].A_transient_resistance[0], recv->TR[j].A_transient_resistance[1], recv->TR[j].A_transient_resistance[2], recv->TR[j].A_transient_resistance[3]);
        value.TR[j].B_transient_resistance = PUBLIC_IEEE754_32(recv->TR[j].B_transient_resistance[0], recv->TR[j].B_transient_resistance[1], recv->TR[j].B_transient_resistance[2], recv->TR[j].B_transient_resistance[3]);
        value.TR[j].C_transient_resistance = PUBLIC_IEEE754_32(recv->TR[j].C_transient_resistance[0], recv->TR[j].C_transient_resistance[1], recv->TR[j].C_transient_resistance[2], recv->TR[j].C_transient_resistance[3]);
    }
    value.TR_unit = recv->TR_unit;
    value.Bridging_resistance_unit = recv->Bridging_resistance_unit;
    value.N = PUBLIC_IEEE754_32(recv->N[0], recv->N[1], recv->N[2], recv->N[3]);
    value.electricity = PUBLIC_IEEE754_32(recv->electricity[0], recv->electricity[1], recv->electricity[2], recv->electricity[3]);
    value.electricity_unit = recv->electricity_unit;

    return TD_3310C_YZFJ_SendData(value);
}

char *TD_3310C_YZFJ_RecvMessage(uint8_t *buffer, uint16_t size)
{
    uint16_t length;
    YZFJ_RecvMessage *recv = (YZFJ_RecvMessage *)buffer;
    length = (recv->dataLength[1] << 8) | recv->dataLength[0];

    // strcpy(sbuff, recv->data + 12);
    // if ((size - 13) > sizeof(sbuff)) {
    //     printf("数组越界\n");
    // }

    return TD_3310C_YZFJ_DataAnalysis(recv->data, length);
}




