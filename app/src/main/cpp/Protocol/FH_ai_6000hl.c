/*
 * FH_ai_6000hl.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月14日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 介损仪器 */
/* 泛华介损 */
#include "FH_ai_6000hl.h"
#include <string.h>

static char returnJsonDataBuff[1000];
uint8_t FH_ai_6000hl_ParamCnt = 0;
FH_ai_6000hlValueType FH_ai_6000hlValue;

char *FH_ai_6000hlWifiSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6000hlReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'C';
        buff[4] = 'D';
        buff[5] = 'A';
        buff[6] = 'T';
        buff[7] = 'A';
        buff[8] = '\r';
        buff[9] = '\n';
        return 10;
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
double FH_ai_6000hlStrAnaly(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t cnt, j = 0;
    int sign;
    double value;

    memset(array, 0, 5);
    if (buff[4] == '-') {
        sign = -1;
    } else {
        sign = 1;
    }

    for (uint8_t i = 5; i <= 9; i++) {
        if (buff[i] == '.') {
            cnt = i - 5;
        } else {
            array[j++] = buff[i];
        }
    }

    for (uint8_t i = 0; i < 4; i++) {
        if ((array[i] >= '0') && (array[i] <= '9')) {
            array[i] = array[i] - 48;
        }
    }
    value = (array[0] * pow(10, cnt - 1) + array[1] * pow(10, cnt - 2)
             + array[2] * pow(10, cnt - 3) + array[3] * pow(10, cnt - 4)) * sign;

    return value;
}

/*
 *  @ brief 接收数据
 */
char *FH_ai_6000hlRecvMessage(uint8_t *buff, uint16_t size)
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
    char cData[] = "CDATA";
    FH_ai_6000hlMessageType *recv = (FH_ai_6000hlMessageType *) (buff + dd);
    FH_ai_6000hlMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6000hlMessageDataType));
    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->CData, cData, sizeof(recv->CData)) != 0)
        return NULL;
    /* ps 1 */
    memcpy(FH_ai_6000hlValue.Name, messageData.Name, 12);
    memcpy(FH_ai_6000hlValue.Time, messageData.Time, 16);
    FH_ai_6000hlValue.Mode = (FH_ai_6000hlModeEnum)(messageData.Name[14] - 48);

    switch (FH_ai_6000hlValue.Mode) {
        /* 单通道 */
        case FH_AI_6000HL_SINGLE:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);
            FH_ai_6000hl_ParamCnt = 1;
            break;

        /* 反接两通道 */
        case FH_AI_6000HL_CONTRARY:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);

            FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[1].Cu, &messageData.Array[2].str[10], 2);
            FH_ai_6000hlValue.Param[1].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);
            FH_ai_6000hl_ParamCnt = 2;
            break;

        /* 变比 */
        case FH_AI_6000HL_NO_LOAD:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);
            FH_ai_6000hl_ParamCnt = 1;
            break;

        /* CTV两通道 */
        case FH_AI_6000HL_CVT:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);

            FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[1].Cu, &messageData.Array[2].str[10], 2);
            FH_ai_6000hlValue.Param[1].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);
            FH_ai_6000hl_ParamCnt = 2;
            break;

        /* 正接两通道 */
        case FH_AI_6000HL_TWO:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);

            FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[1].Cu, &messageData.Array[2].str[10], 2);
            FH_ai_6000hlValue.Param[1].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);
            FH_ai_6000hl_ParamCnt = 2;
            break;

        /* 正接三通道 */
        case FH_AI_6000HL_THREE:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);

            FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[1].Cu, &messageData.Array[2].str[10], 2);
            FH_ai_6000hlValue.Param[1].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);

            FH_ai_6000hlValue.Param[2].C = FH_ai_6000hlStrAnaly(messageData.Array[4].str);
            memcpy(FH_ai_6000hlValue.Param[2].Cu, &messageData.Array[4].str[10], 2);
            FH_ai_6000hlValue.Param[2].DF = FH_ai_6000hlStrAnaly(messageData.Array[5].str);
            FH_ai_6000hl_ParamCnt = 3;
            break;

        /* 正接四通道 */
        case FH_AI_6000HL_FOUR:
            FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlStrAnaly(messageData.Array[0].str);
            memcpy(FH_ai_6000hlValue.Param[0].Cu, &messageData.Array[0].str[10], 2);
            FH_ai_6000hlValue.Param[0].DF = FH_ai_6000hlStrAnaly(messageData.Array[1].str);

            FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlStrAnaly(messageData.Array[2].str);
            memcpy(FH_ai_6000hlValue.Param[1].Cu, &messageData.Array[2].str[10], 2);
            FH_ai_6000hlValue.Param[1].DF = FH_ai_6000hlStrAnaly(messageData.Array[3].str);

            FH_ai_6000hlValue.Param[2].C = FH_ai_6000hlStrAnaly(messageData.Array[4].str);
            memcpy(FH_ai_6000hlValue.Param[2].Cu, &messageData.Array[4].str[10], 2);
            FH_ai_6000hlValue.Param[2].DF = FH_ai_6000hlStrAnaly(messageData.Array[5].str);

            FH_ai_6000hlValue.Param[3].C = FH_ai_6000hlStrAnaly(messageData.Array[6].str);
            memcpy(FH_ai_6000hlValue.Param[3].Cu, &messageData.Array[6].str[10], 2);
            FH_ai_6000hlValue.Param[3].DF = FH_ai_6000hlStrAnaly(messageData.Array[7].str);
            FH_ai_6000hl_ParamCnt = 4;
            break;
    }

    FH_ai_6000hlValue.Param[0].DFu[0] = '%';
    FH_ai_6000hlValue.Param[1].DFu[0] = '%';
    FH_ai_6000hlValue.Param[2].DFu[0] = '%';
    FH_ai_6000hlValue.Param[3].DFu[0] = '%';

    /* 发送数据 */
    return FH_ai_6000hlWifiSend();

}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6000hlWifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cjson_all = cJSON_CreateObject();

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */

    if (strcmp(FH_ai_6000hlValue.Param[0].Cu, "uF") == 0) {
        FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlValue.Param[0].C * 1000000;
    } else if (strcmp(FH_ai_6000hlValue.Param[0].Cu, "nF") == 0) {
        FH_ai_6000hlValue.Param[0].C = FH_ai_6000hlValue.Param[0].C * 1000;
    }

    if (strcmp(FH_ai_6000hlValue.Param[1].Cu, "uF") == 0) {
        FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlValue.Param[1].C * 1000000;
    } else if (strcmp(FH_ai_6000hlValue.Param[1].Cu, "nF") == 0) {
        FH_ai_6000hlValue.Param[1].C = FH_ai_6000hlValue.Param[1].C * 1000;
    }

    if (strcmp(FH_ai_6000hlValue.Param[2].Cu, "uF") == 0) {
        FH_ai_6000hlValue.Param[2].C = FH_ai_6000hlValue.Param[2].C * 1000000;
    } else if (strcmp(FH_ai_6000hlValue.Param[2].Cu, "nF") == 0) {
        FH_ai_6000hlValue.Param[2].C = FH_ai_6000hlValue.Param[2].C * 1000;
    }

    if (strcmp(FH_ai_6000hlValue.Param[3].Cu, "uF") == 0) {
        FH_ai_6000hlValue.Param[3].C = FH_ai_6000hlValue.Param[3].C * 1000000;
    } else if (strcmp(FH_ai_6000hlValue.Param[3].Cu, "nF") == 0) {
        FH_ai_6000hlValue.Param[3].C = FH_ai_6000hlValue.Param[3].C * 1000;
    }

    cJSON_AddNumberToObject(cjson_all, "capacitance", FH_ai_6000hlValue.Param[0].C);
    cJSON_AddNumberToObject(cjson_all, "dielectricLoss", FH_ai_6000hlValue.Param[0].DF);
    cJSON_AddNumberToObject(cjson_all, "capacitance_C2", FH_ai_6000hlValue.Param[1].C);
    cJSON_AddNumberToObject(cjson_all, "dielectricLoss_C2", FH_ai_6000hlValue.Param[1].DF);
    cJSON_AddNumberToObject(cjson_all, "capacitance_C3", FH_ai_6000hlValue.Param[2].C);
    cJSON_AddNumberToObject(cjson_all, "dielectricLoss_C3", FH_ai_6000hlValue.Param[2].DF);
    cJSON_AddNumberToObject(cjson_all, "capacitance_C4", FH_ai_6000hlValue.Param[3].C);
    cJSON_AddNumberToObject(cjson_all, "dielectricLoss_C4", FH_ai_6000hlValue.Param[3].DF);
    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}



