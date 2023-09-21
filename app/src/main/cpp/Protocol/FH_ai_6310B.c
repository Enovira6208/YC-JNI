/*
 * FH_ai_6310b.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月16日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 泛华接地导通 */
#include "FH_ai_6310B.h"
static char returnJsonDataBuff[1000];
FH_ai_6310bValueType FH_ai_6310bValue;

char *FH_ai_6310bwifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6310bReadData(uint8_t *buff, uint8_t cnt)
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
double FH_ai_6310bStrAnaly(uint8_t *buff)
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
char *FH_ai_6310bRecvMessage(uint8_t *buff, uint16_t size)
{

    char read[] = "READ";
    FH_ai_6310bMessageType *recv = (FH_ai_6310bMessageType *) buff;
    FH_ai_6310bMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6310bMessageDataType));

    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->Read, read, sizeof(recv->Read)) != 0)
        return NULL;

    FH_ai_6310bValue.U = FH_ai_6310bStrAnaly(messageData.U);
    FH_ai_6310bValue.I = FH_ai_6310bStrAnaly(messageData.I);
    FH_ai_6310bValue.R = FH_ai_6310bStrAnaly(messageData.R);

    memcpy(FH_ai_6310bValue.Uuint, &messageData.U[9], 2);
    memcpy(FH_ai_6310bValue.Iuint, &messageData.I[9], 2);
    memcpy(FH_ai_6310bValue.Ruint, &messageData.R[9], 2);


    return FH_ai_6310bwifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6310bwifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;


    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "AI_6310B");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "double", FH_ai_6310bValue.Uuint, FH_ai_6310bValue.U, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "electricity", "double", FH_ai_6310bValue.Iuint, FH_ai_6310bValue.I, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance", "double", FH_ai_6310bValue.Ruint, FH_ai_6310bValue.R, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
