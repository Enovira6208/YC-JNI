/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:17:10
 * @LastEditors:
 */

/* 保定金达直流电阻 */
#include "BZC3395.h"
static char returnJsonDataBuff[1000];
BZC3395ValueType BZC3395Value;

char *BZC3395Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t BZC3395ReadData(uint8_t *ascllBuff, uint8_t cnt)
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
double BZC3395Count(uint8_t *buff, uint8_t cnt, uint8_t type)
{
    uint8_t ascll[10];
    uint8_t decimal, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t blank = 0;

    for (uint8_t i = 0; i < sizeof(buff); i++) {
        if (buff[i] = 0x23) {
            blank = i;
        }
    }

    memset(ascll, 0, 10);
    for (uint8_t i = 0; i < cnt; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
        } else if (buff[i] == '.') {
            decimal = i;
        } else if (buff[i] == 0x23) {
            temp++;
        }
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1 - temp);
    }

    if (type == 1) {
        /* blank + j + 1 + 1  空格+数字+小数点+位 cnt - blank - 1 - j 总数-小数点-数字*/
        memcpy(BZC3395Value.Rauint, &buff[blank + j + 1 + 1], cnt - blank - 1 - j);
    } else if (type == 2) {
        memcpy(BZC3395Value.Rbuint, &buff[blank + j + 1 + 1], cnt - blank - 1 - j);
    } else if (type == 3) {
        memcpy(BZC3395Value.Rcuint, &buff[blank + j + 1 + 1], cnt - blank - 1 - j);
    }

    return vlaue;
}


/*
 *  @ brief 接收数据
 */
char *BZC3395RecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x23) {
            dd = k; break;
        }
    }
    printf("%d\n", dd);
    if (dd == 0 && buff[0] != 0x23) {
        return NULL;
    }

    char *index1, *index2, *index3, *index4;
    uint8_t value1, value2, value3;

    BZC3395MessageType *recv = (BZC3395MessageType *) (buff + dd);

    if (recv->Head != 0x0A)
        return "succeed";

    if (recv->Head != 0x23)
        return NULL;
    /* 值为0 */
    if (recv->Data[0] == 0x24) {
        BZC3395Value.Ra = 0;
    } else if (recv->Data[0] == 'a') {
        index1 = strstr((char *)buff, "a");
        index2 = strstr((char *)buff, "b");
        index3 = strstr((char *)buff, "c");
        index4 = strstr((char *)buff, "\n");

        value1 = index2 - index1;
        value2 = index3 - index2;
        value3 = index4 - index3;
        BZC3395Value.Ra = BZC3395Count(&recv->Data[2], value1 - 2, 1);
        BZC3395Value.Rb = BZC3395Count(&recv->Data[2 + value1], value2 - 2, 1);
        BZC3395Value.Rc = BZC3395Count(&recv->Data[2 + value2], value3 - 2, 1);
    } else if (recv->Data[0] == 'A') {
        index1 = strstr((char *)buff, "A");
        index2 = strstr((char *)buff, "B");
        index3 = strstr((char *)buff, "C");
        index4 = strstr((char *)buff, "\n");

        value1 = index2 - index1;
        value2 = index3 - index2;
        value3 = index4 - index3;
        BZC3395Value.Rb = BZC3395Count(&recv->Data[2], value1 - 2, 1);
        BZC3395Value.Rb = BZC3395Count(&recv->Data[2 + value1], value2 - 2, 1);
        BZC3395Value.Rb = BZC3395Count(&recv->Data[2 + value2], value3 - 2, 1);
    } else {
        index1 = strstr((char *)buff, " ");
        index2 = strstr((char *)buff, "\n");
        BZC3395Value.Ra = BZC3395Count(recv->Data, index2 - index1 + 1, 1);
    }

    /* 发送数据 */
    return BZC3395Send();
}

/*
 * @ brief 发送数据
 */
char *BZC3395Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "BZC3395");

    // PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance", "double", BZC3395Value.Rauint, BZC3395Value.Ra, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 2, "resistance", "double", BZC3395Value.Rbuint, BZC3395Value.Rb, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance", "double", BZC3395Value.Rcuint, BZC3395Value.Rc, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "AN_AB_resistor", "double", BZC3395Value.Rauint, BZC3395Value.Ra, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "BN_BC_resistor", "double", BZC3395Value.Rbuint, BZC3395Value.Rb, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "CN_CA_resistor", "double", BZC3395Value.Rcuint, BZC3395Value.Rc, "null");

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

