/*
 * FH_ai_6301.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月2日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 地网电阻 */
/* 泛华地阻 6301B*/
#include "FH_ai_6301.h"
static char returnJsonDataBuff[1000];
FH_ai_6301ValueType FH_ai_6301Value;

char *FH_ai_6301wifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6301ReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'R';
        buff[4] = 'E';
        buff[5] = 'A';
        buff[6] = 'D';
        buff[7] = '\r';
        buff[8] = '\n';
        return 9;
    } else if (cnt == 2) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'O';
        buff[4] = 'V';
        buff[5] = 'E';
        buff[6] = 'R';
        buff[7] = '\r';
        buff[8] = '\n';
        return 9;
    }
    return 0;
}

/*
 *  @ brief 字符串解析
 */
double FH_ai_6301StrAnaly(uint8_t *buff)
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
char *FH_ai_6301RecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == '#') {
            dd = k; break;
        }
    }
    printf("%d\n", dd);
    if (dd == 0 && buff[0] != '#') {
        return NULL;
    }
    uint8_t buffer[5];
    uint8_t cnt;
    int sign;

    FH_ai_6301MessageType *recv = (FH_ai_6301MessageType *) (buff + dd);
    FH_ai_6301MessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6301MessageDataType));
    if (recv->Head != '#')
        return NULL;

    memcpy(FH_ai_6301Value.Mode, messageData.Mode, 16);

    FH_ai_6301Value.Z = FH_ai_6301StrAnaly(messageData.Z);
    memcpy(FH_ai_6301Value.Zuint, &messageData.Z[7], 2);

    FH_ai_6301Value.R = FH_ai_6301StrAnaly(messageData.R);
    memcpy(FH_ai_6301Value.Ruint, &messageData.R[7], 2);

    FH_ai_6301Value.U = FH_ai_6301StrAnaly(messageData.U);
    memcpy(FH_ai_6301Value.Uuint, &messageData.U[7], 2);

    FH_ai_6301Value.I = FH_ai_6301StrAnaly(messageData.I);
    memcpy(FH_ai_6301Value.Iuint, &messageData.I[7], 2);

    FH_ai_6301Value.P = FH_ai_6301StrAnaly(messageData.P);
    memcpy(FH_ai_6301Value.Puint, &messageData.P[7], 2);

    FH_ai_6301Value.A = FH_ai_6301StrAnaly(messageData.A);
    memcpy(FH_ai_6301Value.Auint, &messageData.A[7], 2);

    FH_ai_6301Value.F = FH_ai_6301StrAnaly(messageData.F);
    memcpy(FH_ai_6301Value.Fuint, &messageData.F[7], 2);

    FH_ai_6301Value.T = FH_ai_6301StrAnaly(messageData.T);
    memcpy(FH_ai_6301Value.Tuint, &messageData.T[7], 2);

    /* 发送数据 */
    return FH_ai_6301wifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6301wifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cJSON *cjson_body = NULL;
    cJSON *cjson_datas = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_all, "current", FH_ai_6301Value.I);
    cJSON_AddNumberToObject(cjson_all, "impedance", FH_ai_6301Value.Z);
    cJSON_AddNumberToObject(cjson_all, "resistance", FH_ai_6301Value.R);
    cJSON_AddNumberToObject(cjson_all, "voltage", FH_ai_6301Value.U);
    cJSON_AddNumberToObject(cjson_all, "frequency", FH_ai_6301Value.F);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}
