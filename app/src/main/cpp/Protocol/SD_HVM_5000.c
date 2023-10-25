/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-14 16:21:57
 * @LastEditors:
 */

static char returnJsonDataBuff[1000];

/* 苏州海沃绝缘电阻 */
#include "SD_HVM_5000.h"

SD_HVM_5000ValueType SD_HVM_5000Value;

char *SD_HVM_5000Send(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t SD_HVM_5000ReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[15];

    hexBuff[0] = 0x42;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x47;

    hexBuff[3] = 0x0F;
    hexBuff[4] = 0x00;
    hexBuff[5] = 0x00;
    hexBuff[6] = 0x00;

    hexBuff[7] = 0x03;
    hexBuff[8] = 0x00;

    hexBuff[9] = 0x00;          /* 数据区长度 */
    hexBuff[10] = 0x00;
    hexBuff[11] = 0x00;
    hexBuff[12] = 0x00;

    hexBuff[13] = 0x88;
    hexBuff[14] = 0xEC;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 15);

    return 16;
}


/*
 *  @ brief 接收数据
 */
char *SD_HVM_5000RecvMessage(uint8_t *buff, uint16_t size)
{
    SD_HVM_5000MessageType *recv = (SD_HVM_5000MessageType *) buff;

    if (recv->Head[0] != 0x42)
        return NULL;

    if (recv->Head[1] != 0x45)
        return NULL;

    if (recv->Head[2] != 0x47)
        return NULL;

    if (recv->Cmd[0] != 0x03)
        return NULL;

    if (recv->Cmd[1] != 0x00)
        return NULL;

    SD_HVM_5000Value.voltage = PUBLIC_IEEE754_32(recv->Data[7], recv->Data[8], recv->Data[9], recv->Data[10]);
    memcpy(SD_HVM_5000Value.Vuint, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[11]), sizeof(SD_HVM_5000Value.Vuint));

    SD_HVM_5000Value.resistance_15s = PUBLIC_IEEE754_32(recv->Data[12], recv->Data[13], recv->Data[14], recv->Data[15]);
    memcpy(SD_HVM_5000Value.Ruint_15s, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_15s));

    SD_HVM_5000Value.resistance_60s = PUBLIC_IEEE754_32(recv->Data[16], recv->Data[17], recv->Data[18], recv->Data[19]);
    memcpy(SD_HVM_5000Value.Ruint_60s, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_60s));

    SD_HVM_5000Value.resistance_10min = PUBLIC_IEEE754_32(recv->Data[20], recv->Data[21], recv->Data[22], recv->Data[23]);
    memcpy(SD_HVM_5000Value.Ruint_10min, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_10min));

    SD_HVM_5000Value.absorptance = PUBLIC_IEEE754_32(recv->Data[25], recv->Data[26], recv->Data[27], recv->Data[28]);

    SD_HVM_5000Value.polarizationIndex = PUBLIC_IEEE754_32(recv->Data[29], recv->Data[30], recv->Data[31], recv->Data[32]);

    /* 发送数据 */
    return SD_HVM_5000Send();
}

/*
 * @ brief 发送数据
 */
char *SD_HVM_5000Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "SD_HVM_5000");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "voltage", "double", SD_HVM_5000Value.Vuint, SD_HVM_5000Value.voltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "resistanceR15", "double", SD_HVM_5000Value.Ruint_15s, SD_HVM_5000Value.resistance_15s, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "resistanceR60", "double", SD_HVM_5000Value.Ruint_60s, SD_HVM_5000Value.resistance_60s, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "resistanceR600", "double", SD_HVM_5000Value.Ruint_10min, SD_HVM_5000Value.resistance_10min, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "absorptance", "double", "",   SD_HVM_5000Value.absorptance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "polarizationIndex", "double", "", SD_HVM_5000Value.polarizationIndex, "null");

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

