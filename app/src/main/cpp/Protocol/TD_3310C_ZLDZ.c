#include "TD_3310C_ZLDZ.h"
#include "../public/mycrc16.h"

static  char returnJsonDataBuff[8000];

uint16_t TD_3310C_ZLDZ_ReadData(uint8_t *ascllBuff, uint8_t cnt)
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

char *TD_3310C_SendData(ZLDZ_DataVALUE value)
{
    char *str;
    char time[20];
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;
    double a, b, c = 0;

    sprintf(&time[0], "%04d", (int)(value.time[0] | (value.time[1] << 8)));
    sprintf(&time[4], "%02d", (int)(value.time[2]));
    sprintf(&time[6], "%02d", (int)(value.time[3]));
    sprintf(&time[8], "%02d", (int)(value.time[4]));
    sprintf(&time[10], "%02d", (int)(value.time[5]));
    sprintf(&time[12], "%02d", (int)(value.time[6]));

    char e_unit[5] = "";
    if (value.electricity_unit == 0x09) {
        sprintf(e_unit, "%s", "A");
    } else if (value.electricity_unit == 0x0a) {
        sprintf(e_unit, "%s", "mA");
    } else if (value.electricity_unit == 0x0b) {
        sprintf(e_unit, "%s", "uA");
    }
    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "TD_3310C_ZLDZ");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "Test_time", "string", "null", 0, time);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "current", "double", "null",   value.electricity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "e_unit", "string", "null", 0, e_unit);
    printf("%lf\n", value.group[0].AB);
    printf("%lf\n", value.group[1].AB);
    printf("%lf\n", value.group[2].AB);
    for (int j = 0; j < 31; j++) {
        // char temp_AB[20], temp_BC[20], temp_CA[20];
        // sprintf(&temp_AB[0], "%s", "AN_AB_resistor");
        // sprintf(&temp_BC[0], "%s", "BN_BC_resistor");
        // sprintf(&temp_CA[0], "%s", "CN_CA_resistor");
        if (value.group[j].AB != -1023) {
            a = value.group[j].AB;
        }
        if (value.group[j].BC != -1023) {
            b = value.group[j].BC;
        }
        if (value.group[j].CA != -1023) {
            c = value.group[j].CA;
        }
    }
    PUBLIC_JsonArrayLoading(cjson_array, 4, "AN_AB_resistor", "double", "null", a, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "BN_BC_resistor", "double", "null", b, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "CN_CA_resistor", "double", "null", c, "null");
    char r_unit[5] = "";
    if (value.resistance_unit == 0x1a) {
        sprintf(r_unit, "%s", "kΩ");
    } else if (value.resistance_unit == 0x1b) {
        sprintf(r_unit, "%s", "MΩ");
    } else if (value.resistance_unit == 0x1c) {
        sprintf(r_unit, "%s", "GΩ");
    } else if (value.resistance_unit == 0x1d) {
        sprintf(r_unit, "%s", "TΩ");
    }
    PUBLIC_JsonArrayLoading(cjson_array, 97, "r_unit", "string", "null", 0, r_unit);

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

char *TD_3310C_ZLDZ_DataAnalysis(uint8_t *buffer, uint16_t size)
{
    ZLDZ_DataMessage *recv = (ZLDZ_DataMessage *)buffer;
    ZLDZ_DataVALUE value;
    for (int i = 0; i < 7; i++) {
        value.time[i] = recv->time[i];
    }
    value.electricity = PUBLIC_IEEE754_32(recv->electricity[0], recv->electricity[1], recv->electricity[2], recv->electricity[3]);
    value.electricity_unit = recv->electricity_unit;
    for (int j = 0; j < 31; j++) {
        value.group[j].AB = PUBLIC_IEEE754_32(recv->group[j].AB[0], recv->group[j].AB[1], recv->group[j].AB[2], recv->group[j].AB[3]);
        value.group[j].BC = PUBLIC_IEEE754_32(recv->group[j].BC[0], recv->group[j].BC[1], recv->group[j].BC[2], recv->group[j].BC[3]);
        value.group[j].CA = PUBLIC_IEEE754_32(recv->group[j].CA[0], recv->group[j].CA[1], recv->group[j].CA[2], recv->group[j].CA[3]);
    }
    value.resistance_unit = recv->resistance_unit;

    return TD_3310C_SendData(value);
}

char *TD_3310C_ZLDZ_RecvMessage(uint8_t *buff, uint16_t size)
{
    uint16_t crc, length;
    ZLDZ_RecvMessage *recv = (ZLDZ_RecvMessage *)buff;

    length = (recv->dataLength[1] << 8) | recv->dataLength[0];
    crc = (recv->crc[1] << 8) | recv->crc[0];

    return TD_3310C_ZLDZ_DataAnalysis(recv->data, length);
}


