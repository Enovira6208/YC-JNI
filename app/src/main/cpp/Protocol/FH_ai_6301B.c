/*
 * FH_ai_6301B.c
 * @Author       : zhengshuo
 * @Date         : 2023年9月11日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 泛华 AI-6301B*/
#include "FH_ai_6301B.h"
static char returnJsonDataBuff[1000];
FH_ai_6301BValueType FH_ai_6301BValue;

char *FH_ai_6301BwifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6301BReadData(uint8_t *buff, uint8_t cnt)
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
        return 9;
    }
    return 0;
}

/*
 *  @ brief 字符串解析
 */
double FH_ai_6301BStrAnaly(uint8_t *buff)
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

double FH_ai_6301B_count1(uint8_t *buff, uint8_t len)
{
    double value = 0;
    double t1 = 0;
    for (uint8_t i = 0; i < len; i++) {
        t1 = buff[i] - '0';
        for (uint8_t k = 0; k < len - i - 1; k++) {
            t1 = t1 * 10;
        }
        value += t1;
    }
    return value;
}

double FH_ai_6301B_count2(uint8_t *buff)
{
    uint8_t array[7];
    uint8_t cnt, j = 0, temp = 0;
    double value = 0;

    memset(array, 0, 7);

    for (uint8_t i = 1; i <= 8; i++) {
        if (buff[i] == '.') {
            cnt = i;
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

    return value;
}

/*
 *  @ brief 接收数据
 */
char *FH_ai_6301BRecvMessage(uint8_t *buff, uint16_t size)
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
    FH_ai_6301BMessageType *recv = (FH_ai_6301BMessageType *) (buff + dd);
    FH_ai_6301BMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6301BMessageDataType));
    if (recv->Head != '#')
        return NULL;

    memcpy(FH_ai_6301BValue.Name, messageData.Name, 8);
    memcpy(FH_ai_6301BValue.Time, messageData.Time, 19);

    FH_ai_6301BValue.TestMode = messageData.TestMode - '0';
    FH_ai_6301BValue.Rab = messageData.Rab - '0';
    FH_ai_6301BValue.TimeMode = FH_ai_6301B_count1(messageData.TimeMode, 2);
    FH_ai_6301BValue.AAA =  FH_ai_6301B_count1(messageData.AAA, 3);
    FH_ai_6301BValue.BBB = FH_ai_6301B_count1(messageData.BBB, 3);
    FH_ai_6301BValue.Jam = messageData.Jam - '0';

    FH_ai_6301BValue.Z = FH_ai_6301BStrAnaly(messageData.Z);
    memcpy(FH_ai_6301BValue.Zuint, &messageData.Z[7], 2);

    FH_ai_6301BValue.R = FH_ai_6301BStrAnaly(messageData.R);
    memcpy(FH_ai_6301BValue.Ruint, &messageData.R[7], 2);

    FH_ai_6301BValue.U = FH_ai_6301BStrAnaly(messageData.U);
    memcpy(FH_ai_6301BValue.Uuint, &messageData.U[7], 2);

    FH_ai_6301BValue.I = FH_ai_6301BStrAnaly(messageData.I);
    memcpy(FH_ai_6301BValue.Iuint, &messageData.I[7], 2);

    FH_ai_6301BValue.N = FH_ai_6301BStrAnaly(messageData.N);
    memcpy(FH_ai_6301BValue.Nuint, &messageData.N[7], 2);

    FH_ai_6301BValue.F = FH_ai_6301BStrAnaly(messageData.F);
    memcpy(FH_ai_6301BValue.Fuint, &messageData.F[7], 2);

    FH_ai_6301BValue.Fai = FH_ai_6301B_count2(messageData.Fai);
    memcpy(FH_ai_6301BValue.Faiuint, &messageData.Fai[7], 2);

    /* 发送数据 */
    return FH_ai_6301BwifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6301BwifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cJSON *cjson_body = NULL;
    cJSON *cjson_datas = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_all, "current", FH_ai_6301BValue.I);
    cJSON_AddNumberToObject(cjson_all, "impedance", FH_ai_6301BValue.Z);
    cJSON_AddNumberToObject(cjson_all, "resistance", FH_ai_6301BValue.R);
    cJSON_AddNumberToObject(cjson_all, "voltage", FH_ai_6301BValue.U);
    cJSON_AddNumberToObject(cjson_all, "frequency", FH_ai_6301BValue.F);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}
