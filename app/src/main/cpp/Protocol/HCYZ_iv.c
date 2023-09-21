/*
 * HCYZ_iv.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月23日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 保定华创  有载分接开关   仪器主动上报数据*/
#include "HCYZ_iv.h"
static char returnJsonDataBuff[1000];
HCYZ_ivMessageValueType HCYZ_ivMessageValue[3];

char *HCYZ_ivBleSend(void);


/*
 *  @ brief 接收数据
 */
char *HCYZ_ivRecvMessage(uint8_t *buff, uint16_t size)
{
//  uint16_t len;
    HCYZ_ivMessageType *buffer = (HCYZ_ivMessageType *) buff;
    HCYZ_ivMessageDataType *recv = (HCYZ_ivMessageDataType *) buffer;

    if (recv->Head != 0x68)
        return NULL;

//  len = (recv->Len[0] << 8) | recv->Len[1];
    /* 判断尾 */
    if (recv->Tail != 0x16)
        return NULL;

    for (uint8_t i = 0; i < 3; i++) {

        HCYZ_ivMessageValue[i].PhasePosition = (recv->APDU[i].Obj[0].Value[0] << 24)
                                               | (recv->APDU[i].Obj[0].Value[1] << 18) | (recv->APDU[i].Obj[0].Value[2] << 8)
                                               | (recv->APDU[i].Obj[0].Value[3]);

        HCYZ_ivMessageValue[i].Type = (recv->APDU[i].Obj[1].Value[0] << 24)
                                      | (recv->APDU[i].Obj[1].Value[1] << 18) | (recv->APDU[i].Obj[1].Value[2] << 8)
                                      | (recv->APDU[i].Obj[1].Value[3]);

        HCYZ_ivMessageValue[i].Resistance = PUBLIC_IEEE754_32(recv->APDU[i].Obj[2].Value[3],
                                            recv->APDU[i].Obj[2].Value[2], recv->APDU[i].Obj[2].Value[1], recv->APDU[i].Obj[2].Value[0]);

        HCYZ_ivMessageValue[i].SwitchingTime = PUBLIC_IEEE754_32(recv->APDU[i].Obj[3].Value[3],
                                               recv->APDU[i].Obj[3].Value[2], recv->APDU[i].Obj[3].Value[1], recv->APDU[i].Obj[3].Value[0]);
    }

    /* 发送数据 */
    return HCYZ_ivBleSend();
}

/*
 * @ 通过WIFI发送数据
 */
char *HCYZ_ivBleSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;


    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "HCYZ_IV");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "testMod_A", "int", "null", HCYZ_ivMessageValue[0].Type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "resistance_A", "double", "Ω", HCYZ_ivMessageValue[0].Resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "switchingTime_A", "double", "ms", HCYZ_ivMessageValue[0].SwitchingTime, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 4, "testMode_B", "int", "null", HCYZ_ivMessageValue[1].Type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "resistance_B", "double", "Ω", HCYZ_ivMessageValue[1].Resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "switchingTime_B", "double", "ms", HCYZ_ivMessageValue[1].SwitchingTime, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 7, "testMode_C", "int", "null", HCYZ_ivMessageValue[2].Type, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "resistance_C", "double", "Ω", HCYZ_ivMessageValue[2].Resistance, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "switchingTime_C", "double", "ms", HCYZ_ivMessageValue[2].SwitchingTime, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);

    str = cJSON_PrintUnformatted(cjson_data);

    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);
    return returnJsonDataBuff;
}
