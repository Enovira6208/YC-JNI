/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:18:58
 * @LastEditors:
 */

/* 金源分接开关 */
#include "JYK_I.h"
static char returnJsonDataBuff[1000];
JYK_IValue2Type JYK_IValue2;

uint8_t Cmd;

char *JYK_ISend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYK_IReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[10];

    if (cnt == 1) {
        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x4A;
        hexBuff[2] = 0x4B;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x50;
        hexBuff[6] = 0x2E;
        hexBuff[7] = 0x0D;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

        return 16;
    } else if (cnt == 2) {
        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x4A;
        hexBuff[2] = 0x4B;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x59;
        hexBuff[6] = 0x27;
        hexBuff[7] = 0x0D;

        PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);
        return 16;
    }
    return 0;
}

/**
 * @brief
 *
 */
double JYK_ICount(uint8_t *buff)
{
    uint8_t ascll[5];
    uint8_t decimal = 0, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;

    memset(ascll, 0, 5);
    for (uint8_t i = 0; i < 5; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j++] = buff[i] - 0x30;
        } else if (buff[i] == '.') {
            decimal = i;
        } else {
            temp++;
        }
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1 - temp);
    }
    return vlaue;
}


/*
 *  @ brief 接收数据
 */
char *JYK_IRecvMessage(uint8_t *buff, uint16_t size)
{

    JYK_IMessageType *recv = (JYK_IMessageType *) buff;
    JYK_IData1Type Data1;
    JYK_IData2Type Data2;

    Cmd = recv->Cmd;

    if (recv->Cmd != 0x50) {
        if (recv->Cmd != 0x40)
            return NULL;
    }

    if (recv->Cmd == 0x40) {
        memcpy(&Data1.Motion, recv->Data, sizeof(JYK_IData1Type));

        JYK_IValue2.Ra = JYK_ICount(Data1.Ra_Data);
        JYK_IValue2.Rb = JYK_ICount(Data1.Rb_Data);
        JYK_IValue2.Rc = JYK_ICount(Data1.Rc_Data);
    } else if (recv->Cmd == 0x50) {
        memcpy(&Data2.Ra_Data, recv->Data, sizeof(JYK_IData2Type));

        JYK_IValue2.Ra = JYK_ICount(Data2.Ra_Data);
        JYK_IValue2.Rb = JYK_ICount(Data2.Rb_Data);
        JYK_IValue2.Rc = JYK_ICount(Data2.Rc_Data);
        JYK_IValue2.Time_a = JYK_ICount(Data2.Time_a);
        JYK_IValue2.Time_b = JYK_ICount(Data2.Time_b);
        JYK_IValue2.Time_c = JYK_ICount(Data2.Time_c);
    }

    /* 发送数据 */
    return JYK_ISend();
}

/*
 * @ brief 发送数据
 */
char *JYK_ISend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYK_I");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance_A", "double", "Ω", JYK_IValue2.Ra, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "resistance_B", "double", "Ω", JYK_IValue2.Rb, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance_C", "double", "Ω", JYK_IValue2.Rc, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "time_A", "double", "ms", JYK_IValue2.Time_a, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "time_B", "double", "ms", JYK_IValue2.Time_b, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "time_C", "double", "ms", JYK_IValue2.Time_c, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}

