/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:19:14
 * @LastEditors:
 */

/* 金源回路电阻 */
#include "JYR_40C.h"
static char returnJsonDataBuff[1000];
JYR_40CValueType JYR_40C;

char *JYR_40CSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYR_40CReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[10];

    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x39;
    hexBuff[2] = 0x39;
    hexBuff[3] = 0x30;
    hexBuff[4] = 0x31;
    hexBuff[5] = 0x46;
    hexBuff[6] = 0x39;
    hexBuff[7] = 0x0D;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

    return 16;
}

double JYR_40CCount(uint8_t *buff)
{
    uint8_t ascll[5];
    uint8_t decimal;
    uint8_t j = 0;
    double vlaue = 0;

    memset(ascll, 0, 5);
    for (uint8_t i = 0; i < 6; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
        } else if (buff[i] == '.') {
            decimal = i;
        }
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1);
    }
    return vlaue;
}


/*
 *  @ brief 接收数据
 */
char *JYR_40CRecvMessage(uint8_t *buff, uint16_t size)
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
    JYR_40CMessageType *recv = (JYR_40CMessageType *) (buff + dd);
    JYR_40CDataType Data;

    memcpy(&Data.I_Info, recv->Data, sizeof(JYR_40CDataType));

    if (recv->Cmd != 0x45 && recv->Cmd != 0x44 && recv->Cmd != 0x48)
        return NULL;

    JYR_40C.R = JYR_40CCount(Data.R_Data);
    JYR_40C.Ruint[0] = Data.R_Data[6];

    /* 发送数据 */
    return JYR_40CSend();
}

/*
 * @ brief 发送数据
 */
char *JYR_40CSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYR_40C");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "AN_AB_resistor", "double", JYR_40C.Ruint, JYR_40C.R, "null");

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

