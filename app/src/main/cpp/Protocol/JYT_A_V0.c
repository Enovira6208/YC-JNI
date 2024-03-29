/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:17:55
 * @LastEditors:
 */

/* 保定金源变比旧版 */
#include "JYT_A_V0.h"

static char returnJsonDataBuff[1000];

JYT_A_V0ValueType JYT_A_V0Value;

char *JYT_A_V0Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYT_A_V0ReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[10];

    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x31;
    hexBuff[2] = 0x31;
    hexBuff[3] = 0x30;
    hexBuff[4] = 0x31;
    hexBuff[5] = 0x46;
    hexBuff[6] = 0x39;
    hexBuff[7] = 0x0D;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

    return 16;
}

/**
 * @brief
 *
 */
double JYT_A_V0Count(uint8_t *buff, uint8_t cnt)
{
    uint8_t ascll[10];
    uint8_t decimal = 0, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t num = 0, letter = 0;

    decimal = cnt;
    memset(ascll, 0, 10);
    for (uint8_t i = 0; i < cnt; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
            /* 最后一个数字 */
            num = i;
        } else if (buff[i] == '.') {
            decimal = i;
        } else {
            temp++;
            /* 最后一个字符 */
            letter = i;
        }
    }
    if (letter > num) {
        temp = temp - (letter - num);
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1 - temp);
    }
    return vlaue;
}

/*
 *  @ brief 接收数据
 */
char *JYT_A_V0RecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x7e) {
            dd = k; break;
        }
    }
    if (dd == 0 && buff[0] != 0x7e) {
        return NULL;
    }
    JYT_A_V0MessageType *recv = (JYT_A_V0MessageType *) (buff + dd);
    /*
    *   旧版协议 ：报文头  地址高  地址低 数据长度高 数据长度低 状态 命令(分类三相或是单向相) 数据(N位) 校验 尾
    */
    if (recv->Head != 0x7E)
        return NULL;

    if (recv->Addr[0] != 0x31)
        return NULL;

    if (recv->Addr[1] != 0x31)
        return NULL;

    if (recv->Cmd == 0x64) {
        JYT_A_V0Value.voltageRatio_A = JYT_A_V0Count(&recv->Data[0], 6);
        JYT_A_V0Value.difference_A = JYT_A_V0Count(&recv->Data[6], 5);
        JYT_A_V0Value.tranches = recv->Data[11] - 0x30;
        JYT_A_V0Value.branching = ((recv->Data[12] - 0x30) << 8) | (recv->Data[13] - 0x30);
    } else if (recv->Cmd == 0x73) {
        JYT_A_V0Value.voltageRatio_A = JYT_A_V0Count(&recv->Data[0], 6);
        JYT_A_V0Value.difference_A = JYT_A_V0Count(&recv->Data[6], 5);
        JYT_A_V0Value.voltageRatio_B = JYT_A_V0Count(&recv->Data[11], 6);
        JYT_A_V0Value.difference_B = JYT_A_V0Count(&recv->Data[17], 5);
        JYT_A_V0Value.voltageRatio_C = JYT_A_V0Count(&recv->Data[22], 6);
        JYT_A_V0Value.difference_C = JYT_A_V0Count(&recv->Data[28], 5);
        /* 加两位的高压方式 */
        JYT_A_V0Value.tranches = recv->Data[35] - 0x30;
        JYT_A_V0Value.branching = ((recv->Data[36] - 0x30) << 8) | (recv->Data[37] - 0x30);
    }

    /* 发送数据 */
    return JYT_A_V0Send();
}

/*
 * @ brief 发送数据
 */
char *JYT_A_V0Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYT_A_V0");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "voltageRatio_A", "double", "%",   JYT_A_V0Value.voltageRatio_A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "voltageRatio_B", "double", "%",   JYT_A_V0Value.voltageRatio_B, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "voltageRatio_C", "double", "%",   JYT_A_V0Value.voltageRatio_C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "difference_A", "double", "%", JYT_A_V0Value.difference_A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "difference_B", "double", "%", JYT_A_V0Value.difference_B, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "difference_C", "double", "%", JYT_A_V0Value.difference_C, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 7, "tranches", "int", "", JYT_A_V0Value.tranches, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 8, "branching", "int", "", JYT_A_V0Value.branching, "null");


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

