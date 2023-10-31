/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:17:40
 * @LastEditors:
 */

#include "DDC8910.h"
static char returnJsonDataBuff[1000];
/* 保定金达接地电阻 */
DDC8910ValueType DDC8910Value;

char *DDC8910Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t DDC8910ReadData(uint8_t *ascllBuff, uint8_t cnt)
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
double DDC8910Count(uint8_t *buff)
{
    uint8_t ascll[10];
    uint8_t decimal, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t blank = 0, tail = 0;

    for (uint8_t i = 0; i < 8; i++) {
        if (buff[i] == 0x23) {
            blank = i;
        }
        if (buff[i] == 0x0D) {
            tail = i;
        }
    }

    memset(ascll, 0, 10);
    for (uint8_t i = 0; i < (tail - blank); i++) {
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
    return vlaue;
}


/*
 *  @ brief 接收数据
 */
char *DDC8910RecvMessage(uint8_t *buff, uint16_t size)
{
    DDC8910MessageType *recv = (DDC8910MessageType *) buff;

    if (recv->Head == 0xA0)
        return "succeed";

    if (recv->Data[0] == 0x24) {
        DDC8910Value.R = 0;
    } else {
        DDC8910Value.R = DDC8910Count(recv->Data);
    }

    if (recv->Data[6] == 0xEA && recv->Data[5] == 0xE6) {
        sprintf(DDC8910Value.Ruint, "%s", "uΩ");
    } else if (recv->Data[6] == 0xEA ) {
        sprintf(DDC8910Value.Ruint, "%s", "mΩ");
    }
    /* 发送数据 */
    return DDC8910Send();
}

/*
 * @ brief 发送数据
 */
char *DDC8910Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "DDC8910");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance", "double", DDC8910Value.Ruint, DDC8910Value.R, "null");

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

