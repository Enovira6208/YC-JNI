/*
 * FH_ai_6310L.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月16日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 泛华回路电阻 */
#include "FH_ai_6310L.h"
static char returnJsonDataBuff[1000];
FH_ai_6310LValueType FH_ai_6310LValue;

char *FH_ai_6310LwifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6310LReadData(uint8_t *buff, uint8_t cnt)
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
double FH_ai_6310LStrAnaly(uint8_t *buff)
{
    uint8_t array[10];
    uint8_t cnt, j = 0, temp = 0;
    int sign;
    double value = 0;

    memset(array, 0, 10);
    if (buff[2] == '-') {
        sign = -1;
    } else {
        sign = 1;
    }

    for (uint8_t i = 3; i <= 9; i++) {
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
char *FH_ai_6310LRecvMessage(uint8_t *buff, uint16_t size)
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
    FH_ai_6310LMessageType *recv = (FH_ai_6310LMessageType *) (buff + dd);
    FH_ai_6310LMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6310LMessageDataType));

    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->Read, read, sizeof(recv->Read)) != 0)
        return NULL;

    FH_ai_6310LValue.U = FH_ai_6310LStrAnaly(messageData.U);
    FH_ai_6310LValue.I = FH_ai_6310LStrAnaly(messageData.I);
    FH_ai_6310LValue.R = FH_ai_6310LStrAnaly(messageData.R);

    memcpy(FH_ai_6310LValue.Uuint, &messageData.U[9], 4);
    memcpy(FH_ai_6310LValue.Iuint, &messageData.I[9], 4);
    memcpy(FH_ai_6310LValue.Ruint, &messageData.R[9], 4);


    return FH_ai_6310LwifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6310LwifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;


    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "AI_6310L");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "double", FH_ai_6310LValue.Uuint, FH_ai_6310LValue.U, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "current", "double", FH_ai_6310LValue.Iuint, FH_ai_6310LValue.I, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance", "double", FH_ai_6310LValue.Ruint, FH_ai_6310LValue.R, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
