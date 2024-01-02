/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-05-30 09:36:01
 * @LastEditTime: 2023-05-31 14:46:55
 * @LastEditors:
 */
#include "JYR_40D.h"

static char returnJsonDataBuff[1000];

JYR_40DValueType value;

char *JYR_40DSend(void);

uint16_t JYR_40DReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[20];
    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x51;
    hexBuff[2] = 0x51;
    hexBuff[3] = 0x35;
    hexBuff[4] = 0x70;
    hexBuff[5] = 0x20;
    hexBuff[6] = 0x20;
    hexBuff[7] = 0x20;
    hexBuff[8] = 0x20;
    hexBuff[9] = 0x3B;
    hexBuff[10] = 0x0D;
    PUBLIC_HexToAscll(ascllBuff, hexBuff, 11);

    return 11;
}

double JYR_40DCount(uint8_t *buff)
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

char *JYR_40DRecvMessage(uint8_t *buff, uint16_t size)
{

    JYR_40DMessageType *recv = (JYR_40DMessageType *) buff;

    // value.status = JYR_40DCount(recv->status);
    // value.mode = JYR_40DCount(recv->mode);
    // value.way = JYR_40DCount(recv->way);
    // value.winding = JYR_40DCount(recv->winding);
    // value.electricity = JYR_40DCount(recv->winding);

    value.status = recv->status;
    value.mode = recv->mode;
    value.way = recv->way;
    value.winding = recv->winding;
    value.electricity = recv->winding;
    // memcpy(&Data.I_Info, recv->Data, sizeof(JYR_40CDataType));

    // if (recv->Cmd != 0x45 && recv->Cmd != 0x44 && recv->Cmd != 0x48)
    //     return NULL;

    // JYL_100BValue.R = JYR_40CCount(Data.R_Data);
    // JYL_100BValue.Ruint[0] = Data.R_Data[6];

    /* 发送数据 */
    return JYR_40DSend();
}


char *JYR_40DSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYR_40D");

    // PUBLIC_JsonArrayLoading(cjson_array, 1, "mode", "int", "null", value.mode, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 2, "electricity", "int", "A", value.electricity, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 3, "mode", "int", "null", value.mode, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 4, "way", "int", "null", value.way, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 5, "status", "int", "null", value.status, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "current", "int", "A", value.electricity, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}