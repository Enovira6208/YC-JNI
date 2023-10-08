
#include "BYKC_2003.h"
static char returnJsonDataBuff[1000];
/*
 *  @ brief 读取仪器数据
 */
uint16_t BYKC_2003ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[10];

    if (cnt == 1) {
        hexBuff[0] = 0xAA;
        hexBuff[1] = 0x55;
        hexBuff[2] = 0x00;
        hexBuff[3] = 0x01;
        hexBuff[4] = 0x01;
        hexBuff[5] = 0x02;
        hexBuff[6] = 0x00;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 1);

        return 2;
    } else if (cnt == 2) {
        hexBuff[0] = 0xAA;
        hexBuff[1] = 0x55;
        hexBuff[2] = 0x00;
        hexBuff[3] = 0x01;
        hexBuff[4] = 0x05;
        hexBuff[5] = 0x06;
        hexBuff[6] = 0x04;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 1);

        return 2;
    }
    return 0;
}

double count(uint8_t a, uint8_t b)
{
    return (double)(((a & 0x1f) << 8) | b); /*取低13位数据*/
}

double countState(uint8_t a, double value)
{
    if (((a >> 6) & 0x01) == 0) {
        if (((a >> 5) & 0x01) == 0) {
            return value; /*1倍正数*/
        } else {
            return (0 - value); /*1倍负数*/
        }
    } else if (((a >> 6) & 0x01) == 1) {
        if (((a >> 5) & 0x01) == 0) {
            return 4 * value; /*4倍正数*/
        } else {
            return 0 - (4 * value); /*4倍负数*/
        }
    } else if (((a >> 6) & 0x01) == 2) {
        if (((a >> 5) & 0x01) == 0) {
            return 16 * value; /*16倍正数*/
        } else {
            return 0 - (16 * value); /*16倍负数*/
        }
    }
}

char *BYKC_2003Send(BYKC_2003ValueType *recv)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "BYKC_2003");

    for (int i = 0; i < 2400; i++) {
        PUBLIC_JsonArrayLoading(cjson_array, 1, "electricity_A_state", "double", "", recv[i].electricity_A_state, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage_B_state", "double", "", recv[i].voltage_B_state, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "electricity_B_state", "double", "", recv[i].electricity_B_state, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage_C", "double", "", recv[i].voltage_C, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "electricity_C", "double", "", recv[i].electricity_C, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage_A", "double", "", recv[i].voltage_A, "null");
    }


    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}

char *BYKC_2003DataAnalysis(BYKC_2003MessageType *recv)
{
    BYKC_2003ValueType data[2400];
    for (int i = 0; i < 2400; i++) {
        data[i].electricity_A = count(recv->data[i * 12], recv->data[i * 12 + 1]);
        data[i].electricity_A_state = countState(recv->data[i * 12], data[i].electricity_A);

        data[i].voltage_B = count(recv->data[i * 12 + 2], recv->data[i * 12 + 3]);
        data[i].voltage_B = countState(recv->data[i * 12 + 2], data[i].voltage_B);

        data[i].electricity_B = count(recv->data[i * 12 + 4], recv->data[i * 12 + 5]);
        data[i].electricity_B = countState(recv->data[i * 12 + 4], data[i].electricity_B);

        data[i].voltage_C = count(recv->data[i * 12 + 6], recv->data[i * 12 + 7]);
        data[i].voltage_C = countState(recv->data[i * 12 + 6], data[i].voltage_C);

        data[i].electricity_C = count(recv->data[i * 12 + 8], recv->data[i * 12 + 9]);
        data[i].electricity_C = countState(recv->data[i * 12 + 8], data[i].electricity_C);

        data[i].voltage_A = count(recv->data[i * 12 + 10], recv->data[i * 12 + 11]);
        data[i].voltage_A = countState(recv->data[i * 12 + 10], data[i].voltage_A);
    }
    return BYKC_2003Send(data);
}

/*
 *  @ brief 接收数据
 */
char *BYKC_2003RecvMessage(uint8_t *buff, uint16_t size)
{
    int length = 0;
    BYKC_2003MessageType *recv = (BYKC_2003MessageType *)buff;

    if (recv->sync[0] != 0xAA || recv->sync[0] != 0x55)
        printf("首字节不匹配\n");

    length = recv->length[0] << 8 | recv->length[1];
    if ( length == 0) {
        printf("空数据\n");
    }
    /* 发送数据 */
    return BYKC_2003DataAnalysis(recv);

}

