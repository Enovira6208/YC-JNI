/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 16:42:17
 * @LastEditors:
 */

/* 保定金达变比 */
#include "BBC6638.h"
static char returnJsonDataBuff[1000];

BBC6638ValueType BBC6638Value;

char *BBC6638Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t BBC6638ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[10];

    if (cnt == 1) {
        hexBuff[0] = 0x0A;
        PUBLIC_HexToAscll(ascllBuff, hexBuff, 1);

        return 2;
    } else if (cnt == 2) {
        hexBuff[0] = 0xAA;
        PUBLIC_HexToAscll(ascllBuff, hexBuff, 1);

        return 2;
    }
    return 0;
}


/**
 * @brief
 *
 */
double BBC6638Count(uint8_t *buff, uint8_t cnt)
{
    uint8_t ascll[10];
    uint8_t decimal, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t blank = 0;
    int sign = 1;


    if (buff[0]  == '-')
        sign = -1;

    memset(ascll, 0, 10);
    for (uint8_t i = 0; i < cnt; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
        } else if (buff[i] == '.') {
            decimal = i;
        } else {
            temp++;
        }
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1 - temp);
    }

    return vlaue * sign;
}


/*
 *  @ brief 接收数据
 */
char *BBC6638RecvMessage(uint8_t *buff, uint16_t size)
{
    char *index1, *index2;
    uint8_t value1;

    BBC6638MessageType *recv = (BBC6638MessageType *) buff;

    if (recv->Head == 0x0A)
        return "succeed";

    if (recv->Head != 0x9C)
        return NULL;


    /* 三相 */
    if (strstr((char *)buff, "ab") != NULL) {
        index1 = strstr((char *)buff, "=");
        index2 = strstr((char *)buff, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_rated = BBC6638Count(index1 + 1, value1 - 1);

        index1 = strstr((char *)index2 + 1, ":");
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_A = BBC6638Count(index1 + 1, value1 - 1);

        index1 = index2;
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.difference_A = BBC6638Count(index1 + 1, value1 - 1);

        index1 = strstr((char *)index2 + 1, ":");
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_B = BBC6638Count(index1 + 1, value1 - 1);

        index1 = index2;
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.difference_B = BBC6638Count(index1 + 1, value1 - 1);

        index1 = strstr((char *)index2 + 1, ":");
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_C = BBC6638Count(index1 + 1, value1 - 1);

        index1 = index2;
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.difference_C = BBC6638Count(index1 + 1, value1 - 1);

    }
    /* 单相 */
    else {
        index1 = strstr((char *)buff, "=");
        index2 = strstr((char *)buff, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_rated = BBC6638Count(index1 + 1, value1 - 1);

        index1 = index2;
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.voltageRatio_A = BBC6638Count(index1 + 1, value1 - 1);

        index1 = index2;
        index2 = strstr((char *)index2 + 1, "$");
        value1 = index2 - index1;
        BBC6638Value.difference_A = BBC6638Count(index1 + 1, value1 - 1);
    }

    /* 发送数据 */
    return BBC6638Send();
}

/*
 * @ brief 发送数据
 */
char *BBC6638Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "BBC6638");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "voltageRatio_rated", "double", "%", BBC6638Value.voltageRatio_rated, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "voltageRatio_A", "double", "%", BBC6638Value.voltageRatio_A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "difference_A", "double", "%", BBC6638Value.difference_A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "voltageRatio_B", "double", "%", BBC6638Value.voltageRatio_B, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "difference_B", "double", "%", BBC6638Value.difference_B, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "voltageRatio_C", "double", "%", BBC6638Value.voltageRatio_C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "difference_C", "double", "%", BBC6638Value.difference_C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "tranches", "int", "", BBC6638Value.tranches, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "branching", "int", "", BBC6638Value.branching, "null");

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

