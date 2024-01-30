/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-01-11 16:18:22
 * @LastEditTime: 2023-05-06 14:00:44
 * @LastEditors:
 */

/* 山东达顺短路阻抗 */
#include "DS_2000D.h"
static char returnJsonDataBuff[2000];
uint8_t DS_2000D_ParamCnt = 0;
DS_2000DValueType DS_2000DValue;

char *DS_2000DWifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t DS_2000DReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = 'A';
    } else if (cnt == 2) {
        buff[0] = 'C';
    }
    return 1;
}


/*
 *  @ brief 字符串解析
 */
double DS_2000DStr_8_Analy(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t cnt, j = 0;
    double value = 0;

    memcpy(array, buff, 5);
    memset(array, 0, 5);

    for (uint8_t i = 0; i < 5; i++) {
        if (buff[i] == '.') {
            cnt = i;
        } else {
            array[j++] = buff[i] - 48;
        }
    }

    value = 0;
    for (uint8_t i = 0; i < 4; i++) {
        value += array[i] * pow(10, cnt - 1 - i);
    }

    return value;
}

double DS_2000DStr_8_Analy2(uint8_t *buff)
{
    uint8_t array[6];
    uint8_t cnt, j = 0;
    double value = 0;

    memcpy(array, buff, 6);
    memset(array, 0, 6);

    for (uint8_t i = 0; i < 6; i++) {
        if (buff[i] == '.') {
            cnt = i;
        } else {
            array[j++] = buff[i] - 48;
        }
    }

    value = 0;
    for (uint8_t i = 0; i < 5; i++) {
        value += array[i] * pow(10, cnt - 1 - i);
    }

    return value;
}
/*
 *  @ brief 接收数据
 */
char *DS_2000DRecvMessage(uint8_t *buff, uint16_t size)
{
    char *index;
    char *index2;
    char *index3;
    char *index4;
    char *index5;
    if (NULL != strstr((char *)buff, "A\r\n")) {
        return "succeed";
    }

    index = strstr((char *)buff, "Ukj");
    index2 = strstr((char *)buff, "[A]");
    index3 = strstr((char *)buff, "[V]");
    index4 = strstr((char *)buff, "C0相--");
    index5 = strstr((char *)buff, "Zkj");

    if (index == NULL) {
        return NULL;
    }
    printf("DS_2000DRecvMessage %s\n", index );

    DS_2000DValue.AX_voltage = DS_2000DStr_8_Analy2((uint8_t *)index4 + 7);
    DS_2000DValue.BX_voltage = DS_2000DStr_8_Analy2((uint8_t *)index4 + 7 + 7);
    DS_2000DValue.CX_voltage = DS_2000DStr_8_Analy2((uint8_t *)index4 + 7 + 7 + 7);

    DS_2000DValue.AX_electricity = DS_2000DStr_8_Analy2((uint8_t *)index3 + 3);
    DS_2000DValue.BX_electricity = DS_2000DStr_8_Analy2((uint8_t *)index3 + 3 + 7);
    DS_2000DValue.CX_electricity = DS_2000DStr_8_Analy2((uint8_t *)index3 + 3 + 7 + 7);

    DS_2000DValue.ukj_a = DS_2000DStr_8_Analy((uint8_t *)index + 3);
    DS_2000DValue.ukj_b = DS_2000DStr_8_Analy((uint8_t *)index + 3 + 6);
    DS_2000DValue.ukj_c = DS_2000DStr_8_Analy((uint8_t *)index + 3 + 6 + 6);

    DS_2000DValue.power_a = DS_2000DStr_8_Analy2((uint8_t *)index2 + 3);
    DS_2000DValue.power_b = DS_2000DStr_8_Analy2((uint8_t *)index2 + 3 + 7);
    DS_2000DValue.power_c = DS_2000DStr_8_Analy2((uint8_t *)index2  + 3 + 7 + 7);

    DS_2000DValue.zkj_a = DS_2000DStr_8_Analy((uint8_t *)index5 + 3);
    DS_2000DValue.zkj_b = DS_2000DStr_8_Analy((uint8_t *)index5 + 3 + 6);
    DS_2000DValue.zkj_c = DS_2000DStr_8_Analy((uint8_t *)index5 + 3 + 6 + 6);

    printf("DS_2000DRecvMessage \n");
    /* 发送数据 */
    return DS_2000DWifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *DS_2000DWifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "DS_2000D");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "AX_electricity", "double", "A", DS_2000DValue.AX_electricity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "BX_electricity", "double", "A", DS_2000DValue.BX_electricity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "CX_electricity", "double", "A", DS_2000DValue.CX_electricity, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 4, "ukj_A", "double", "%", DS_2000DValue.ukj_a, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "ukj_B", "double", "%", DS_2000DValue.ukj_b, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "ukj_C", "double", "%", DS_2000DValue.ukj_c, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 7, "power_a", "double", "W", DS_2000DValue.power_a, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "power_b", "double", "W", DS_2000DValue.power_b, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "power_c", "double", "W", DS_2000DValue.power_c, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 10, "AX_voltage", "double", "V", DS_2000DValue.AX_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 11, "BX_voltage", "double", "V", DS_2000DValue.BX_voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "CX_voltage", "double", "V", DS_2000DValue.CX_voltage, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 13, "zkj_A", "double", "Ω", DS_2000DValue.zkj_a, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 14, "zkj_B", "double", "Ω", DS_2000DValue.zkj_b, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 15, "zkj_C", "double", "Ω", DS_2000DValue.zkj_c, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}





