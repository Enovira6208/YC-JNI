/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:18:42
 * @LastEditors:
 */

/* 保定金达回路电阻 */
#include "HLC5501.h"
static char returnJsonDataBuff[1000];
HLC5501ValueType HLC5501Value;

char *HLC5501Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t HLC5501ReadData(uint8_t *ascllBuff, uint8_t cnt)
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
double HLC5501Count(uint8_t *buff)
{
    uint8_t ascll[10];
    uint8_t decimal, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t blank = 0, tail = 0;

    for (uint8_t i = 0; i < sizeof(buff); i++) {
        if (buff[i] = 0x23) {
            blank = i;
        }
        if (buff[i] = 0x0D) {
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

    memcpy(HLC5501Value.Ruint, &buff[blank + j + 1 + 1], tail - blank - 1 - 1 - j);

    return vlaue;
}


/*
 *  @ brief 接收数据
 */
char *HLC5501RecvMessage(uint8_t *buff, uint16_t size)
{
    HLC5501MessageType *recv = (HLC5501MessageType *) buff;
    HLC5501DataType Data;

    memcpy(&Data.R_Data, recv->Data, sizeof(HLC5501DataType));

    if (recv->Head != 0x0A)
        return "succeed";

    if (recv->Head != 0x23)
        return NULL;

    if (Data.R_Data[0] == 0x24) {
        HLC5501Value.R = 0;
    } else {
        HLC5501Value.R = HLC5501Count(Data.R_Data);
    }


    /* 发送数据 */
    return HLC5501Send();
}

/*
 * @ brief 发送数据
 */
char *HLC5501Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "HLC5501");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance", "double", HLC5501Value.Ruint, HLC5501Value.R, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}

