/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:19:14
 * @LastEditors:
 */

/* 金源回路电阻 */
#include "JYL_100B.h"
static char returnJsonDataBuff[1000];
JYL_100BValueType JYL_100BValue;

char *JYL_100BSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYL_100BReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[10];

    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x35;
    hexBuff[2] = 0x35;
    hexBuff[3] = 0x30;
    hexBuff[4] = 0x31;
    hexBuff[5] = 0x46;
    hexBuff[6] = 0x39;
    hexBuff[7] = 0x0D;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

    return 16;
}

/**
 * @brief
 *
 */
double JYL_100BCount(uint8_t *buff)
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
char *JYL_100BRecvMessage(uint8_t *buff, uint16_t size)
{

    JYL_100BMessageType *recv = (JYL_100BMessageType *) buff;
    JYL_100BDataType Data;

    memcpy(&Data.I_Info, recv->Data, sizeof(JYL_100BDataType));

    if (recv->Cmd != 0x48)
        return NULL;

    JYL_100BValue.R = JYL_100BCount(Data.R_Data);
    JYL_100BValue.Ruint[0] = Data.R_Data[6];

    /* 发送数据 */
    return JYL_100BSend();
}

/*
 * @ brief 发送数据
 */
char *JYL_100BSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYL_100B");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance", "double", JYL_100BValue.Ruint, JYL_100BValue.R, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);


    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}

