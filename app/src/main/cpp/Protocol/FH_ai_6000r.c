/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2021-12-29 11:47:14
 * @LastEditTime: 2022-08-17 17:43:54
 * @LastEditors:
 */

/* 济南泛华 容性设备6000r */

#include "FH_ai_6000r.h"
#include <string.h>
static char returnJsonDataBuff[1000];

uint8_t FH_ai_6000r_ParamCnt = 0;
FH_ai_6000rValueType FH_ai_6000rValue;

char *FH_ai_6000rWifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6000rReadData(uint8_t *buff, uint8_t cnt)
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
double FH_ai_6000rStr_8_Analy(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t cnt, j = 0;
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
char *FH_ai_6000rRecvMessage(uint8_t *buff, uint16_t size)
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
    char read[] = "READ";
    int sign;
    uint8_t j = 0, cnt = 0;
    uint8_t array[6];
    FH_ai_6000rMessageType *recv = (FH_ai_6000rMessageType *) (buff + dd);
    FH_ai_6000rMessageDataType msgData;

    memcpy(msgData.Name, recv->Data, sizeof(FH_ai_6000rMessageDataType));
    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->READ, read, sizeof(recv->READ)) != 0)
        return NULL;

    FH_ai_6000rValue.MOA = (msgData.MOA[0] << 8) | msgData.MOA[1];
    /* FH_ai_6000rValue.Status = 0 表示电流 = 1 表示电压  */
    FH_ai_6000rValue.Status = (msgData.Status[1] - 55) & 0x01;

    if (msgData.angl[0] == '-') {
        sign = -1;
    } else {
        sign = 1;
    }
    /* m减去小数点前面多余的空格 */
    uint8_t m = 0;
    memset(array, 0, 6);
    for (uint8_t i = 1; i <= 7; i++) {
        if (msgData.angl[i] == '.') {
            cnt = i - 1 - m;
        } else if ((msgData.angl[i] >= '0') && (msgData.angl[i] <= '9')) {
            array[j++] = msgData.angl[i] - 48;
        } else {
            m++;
        }
    }

    FH_ai_6000rValue.angl = 0;
    for (uint8_t i = 0; i < 6; i++) {
        FH_ai_6000rValue.angl += array[i] * pow(10, cnt - 1 - i);
    }

    FH_ai_6000rValue.angl = FH_ai_6000rValue.angl * sign;
    FH_ai_6000rValue.ref = FH_ai_6000rStr_8_Analy(msgData.ref);
    memcpy(FH_ai_6000rValue.refu, &msgData.ref[6], 2);
    FH_ai_6000rValue.ix = FH_ai_6000rStr_8_Analy(msgData.ix);
    FH_ai_6000rValue.cx = FH_ai_6000rStr_8_Analy(msgData.cx);
    memcpy(FH_ai_6000rValue.cxu, &msgData.cx[6], 2);
    FH_ai_6000rValue.df = FH_ai_6000rStr_8_Analy(msgData.df);
    FH_ai_6000rValue.ii = FH_ai_6000rStr_8_Analy(msgData.ii);

    if (strcmp(FH_ai_6000rValue.cxu, "uF") == 0) {
        FH_ai_6000rValue.cx = FH_ai_6000rValue.cx * 1000000;
    } else if (strcmp(FH_ai_6000rValue.cxu, "nF") == 0) {
        FH_ai_6000rValue.cx = FH_ai_6000rValue.cx * 1000;
    }
    /* 发送数据 */
    return FH_ai_6000rWifiSend();
}

/*
 * @ 发送数据
 */
char *FH_ai_6000rWifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cjson_all = cJSON_CreateObject();

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cJSON_AddNumberToObject(cjson_all, "capacitance", FH_ai_6000rValue.cx);
    cJSON_AddNumberToObject(cjson_all, "dielectricLoss", FH_ai_6000rValue.df);
    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}

