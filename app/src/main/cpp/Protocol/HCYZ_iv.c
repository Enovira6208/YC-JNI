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
#include "time.h"
static char returnJsonDataBuff[5000];
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
    time_t current_time;
    char *c_time_string;
    /* 获取当前时间 */
    current_time = time(NULL);
    /* 转换为本地时间格式 */
    c_time_string = ctime(&current_time);

    char *str;
    cJSON *cjson_all = NULL;
    cJSON *cjson_array = NULL;
    cJSON *cjson_request = NULL;
    cJSON *cjson_services = NULL;
    cJSON *cjson_data = NULL;
    cJSON *cjson_data1 = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_data1 = cJSON_CreateObject();
    cjson_all = cJSON_CreateObject();
    cjson_request = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();
    cjson_services = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_request, "deviceId", "DS_2000D");
    cJSON_AddItemToObject(cjson_all, "devices", cjson_array);
    cJSON_AddItemToObject(cjson_array, "request", cjson_request);

    cJSON_AddNumberToObject(cjson_data1, "transitionResistance1_A", HCYZ_ivMessageValue[0].Resistance);
    cJSON_AddNumberToObject(cjson_data1, "transitionResistance1_B", HCYZ_ivMessageValue[1].Resistance);
    cJSON_AddNumberToObject(cjson_data1, "transitionResistance1_C", HCYZ_ivMessageValue[2].Resistance);
    cJSON_AddNumberToObject(cjson_data1, "transitionTime_t1_A", HCYZ_ivMessageValue[0].SwitchingTime);
    cJSON_AddNumberToObject(cjson_data1, "transitionTime_t1_B", HCYZ_ivMessageValue[1].SwitchingTime);
    cJSON_AddNumberToObject(cjson_data1, "transitionTime_t1_C", HCYZ_ivMessageValue[2].SwitchingTime);

    cJSON_AddItemToArray(cjson_services, cjson_data);
    cJSON_AddItemToObject(cjson_data, "data", cjson_data1);
    cJSON_AddStringToObject(cjson_data, "eventTime", c_time_string);
    cJSON_AddStringToObject(cjson_data, "serviceId", "dynamicAttribute");
    cJSON_AddItemToObject(cjson_request, "services", cjson_services);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}
