/*
 * FH_ai_6301_general.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月2日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 地网电阻 */
/* 泛华地阻 通用协议  */
#include "FH_ai_6301_general.h"
static char returnJsonDataBuff[1000];
FH_ai_6301_generalValueType FH_ai_6301_generalValue;

char *FH_ai_6301_generalwifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6301_generalReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'C';
        buff[4] = 'D';
        buff[5] = 'A';
        buff[6] = 'T';
        buff[6] = 'A';
        buff[7] = '\r';
        buff[8] = '\n';
        return 10;
    } else if (cnt == 2) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'S';
        buff[4] = 'T';
        buff[5] = 'O';
        buff[6] = 'P';
        buff[7] = '\r';
        buff[8] = '\n';
        return 9;
    }
    return 0;
}

/*
 *  @ brief 字符串解析
 */
double FH_ai_6301_generalStrAnaly(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t cnt, j = 0, temp = 0;
    int sign;
    double value = 0;

    memset(array, 0, 5);
    if (buff[1] == '-') {
        sign = -1;
    } else {
        sign = 1;
    }

    for (uint8_t i = 2; i <= 6; i++) {
        if (buff[i] == '.') {
            cnt = i - 2;
        } else if (buff[i] >= '0' && buff[i] <= '9') {
            array[j++] = buff[i];
        } else { //if (buff[i] >= 'B' && buff[i] <= 'F')
            temp++;
        }
    }

    for (uint8_t i = 0; i < j; i++) {
        if ((array[i] >= '0') && (array[i] <= '9')) {
            array[i] = array[i] - 48;
        }
    }

    for (uint8_t i = 0; i < j; i++) {
        value += array[i] * pow(10, cnt - i - 1 - temp);
    }

    return value * sign;
}

/*
 *  @ brief 接收数据
 */
char *FH_ai_6301_generalRecvMessage(uint8_t *buff, uint16_t size)
{
    uint8_t buffer[5];
    uint8_t cnt;
    int sign;

    FH_ai_6301_generalMessageType *recv = (FH_ai_6301_generalMessageType *) buff;
    FH_ai_6301_generalMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6301_generalMessageDataType));
    if (recv->Head != '#')
        return NULL;

    memcpy(FH_ai_6301_generalValue.Mode, messageData.Mode, 16);

    FH_ai_6301_generalValue.Z = FH_ai_6301_generalStrAnaly(messageData.Z);
    memcpy(FH_ai_6301_generalValue.Zuint, &messageData.Z[7], 2);

    FH_ai_6301_generalValue.R = FH_ai_6301_generalStrAnaly(messageData.R);
    memcpy(FH_ai_6301_generalValue.Ruint, &messageData.R[7], 2);

    FH_ai_6301_generalValue.U = FH_ai_6301_generalStrAnaly(messageData.U);
    memcpy(FH_ai_6301_generalValue.Uuint, &messageData.U[7], 2);

    FH_ai_6301_generalValue.I = FH_ai_6301_generalStrAnaly(messageData.I);
    memcpy(FH_ai_6301_generalValue.Iuint, &messageData.I[7], 2);

    FH_ai_6301_generalValue.P = FH_ai_6301_generalStrAnaly(messageData.P);
    memcpy(FH_ai_6301_generalValue.Puint, &messageData.P[7], 2);

    FH_ai_6301_generalValue.A = FH_ai_6301_generalStrAnaly(messageData.A);
    memcpy(FH_ai_6301_generalValue.Auint, &messageData.A[7], 2);

    FH_ai_6301_generalValue.F = FH_ai_6301_generalStrAnaly(messageData.F);
    memcpy(FH_ai_6301_generalValue.Fuint, &messageData.F[7], 2);

    FH_ai_6301_generalValue.T = FH_ai_6301_generalStrAnaly(messageData.T);
    memcpy(FH_ai_6301_generalValue.Tuint, &messageData.T[7], 2);

    /* 发送数据 */
    return FH_ai_6301_generalwifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6301_generalwifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "AI_6301");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "testMode", "string", "null", 0, FH_ai_6301_generalValue.Mode);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "impedance", "double", FH_ai_6301_generalValue.Zuint, FH_ai_6301_generalValue.Z, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance", "double", FH_ai_6301_generalValue.Ruint, FH_ai_6301_generalValue.R, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "voltage", "double", FH_ai_6301_generalValue.Uuint, FH_ai_6301_generalValue.U, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "electricity", "double", FH_ai_6301_generalValue.Iuint, FH_ai_6301_generalValue.I, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "power", "double", FH_ai_6301_generalValue.Puint, FH_ai_6301_generalValue.P, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "angle", "double", "°", FH_ai_6301_generalValue.A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "frequency", "double", "Hz", FH_ai_6301_generalValue.F, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "Temp", "double", "℃", FH_ai_6301_generalValue.T, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
