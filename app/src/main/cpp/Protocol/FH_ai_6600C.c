/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2021-12-29 11:47:14
 * @LastEditTime: 2024-03-21 09:31:51
 * @LastEditors:
 */

/* 济南泛华 容性设备6600C */

#include "FH_ai_6600C.h"

static char returnJsonDataBuff[1000];
uint8_t FH_ai_6600C_ParamCnt = 0;
FH_ai_6600CValueType FH_ai_6600CValue;

char *FH_ai_6600CWifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6600CReadData(uint8_t *buff, uint8_t cnt)
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
double FH_ai_6600CStr_8_Analy(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t  j = 0;
    int cnt = 4;
    int sign;
    double value = 0;

    if (buff[0] == '-') {
        sign = -1;
    } else {
        sign = 1;
    }

    for (uint8_t i = 1; i <= 5; i++) {
        if (buff[i] == '.') {
            cnt = i - 1;
        } else {
            array[j++] = buff[i] - 48;
        }
    }

    value = 0;
    for (uint8_t i = 0; i < 4; i++) {
        value += array[i] * pow(10, cnt - 1 - i);
    }
    value = value * sign;

    return value;
}

/*
 *  @ brief 接收数据
 */
char *FH_ai_6600CRecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == '#') {
            dd = k;
            break;
        }
    }
    printf("%d\n", dd);
    if (dd == 0 && buff[0] != '#') {
        return NULL;
    }
    char read[] = "READ";
    int sign;
    uint8_t j = 0, cnt = 0;
    uint8_t array[6];
    FH_ai_6600CMessageType *recv = (FH_ai_6600CMessageType *) (buff + dd);
    FH_ai_6600CMessageDataType msgData;

    memcpy(msgData.Name, recv->Data, sizeof(FH_ai_6600CMessageDataType));
    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->READ, read, sizeof(recv->READ)) != 0)
        return NULL;

    memcpy(FH_ai_6600CValue.testmode, msgData.testmode, 6);

    FH_ai_6600CValue.x = FH_ai_6600CStr_8_Analy(msgData.x);
    memcpy(FH_ai_6600CValue.xUnit, &msgData.x[6], 2);
    FH_ai_6600CValue.u = FH_ai_6600CStr_8_Analy(msgData.u);
    memcpy(FH_ai_6600CValue.uUnit, &msgData.u[6], 2);
    FH_ai_6600CValue.i = FH_ai_6600CStr_8_Analy(msgData.i);
    memcpy(FH_ai_6600CValue.iUnit, &msgData.i[6], 2);
    FH_ai_6600CValue.fj = FH_ai_6600CStr_8_Analy(msgData.fj);
    memcpy(FH_ai_6600CValue.fjUnit, &msgData.fj[6], 2);
    FH_ai_6600CValue.ij = FH_ai_6600CStr_8_Analy(msgData.ij);
    memcpy(FH_ai_6600CValue.ijUnit, &msgData.ij[6], 2);

    /* 发送数据 */
    return FH_ai_6600CWifiSend();
}

/*
 * @ 发送数据
 */
char *FH_ai_6600CWifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cjson_all = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_all, "capacitance", FH_ai_6600CValue.x);
    cJSON_AddNumberToObject(cjson_all, "voltageValue", FH_ai_6600CValue.u);
    cJSON_AddNumberToObject(cjson_all, "currentValue", FH_ai_6600CValue.i);
    cJSON_AddNumberToObject(cjson_all, "frequency", FH_ai_6600CValue.fj);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}

