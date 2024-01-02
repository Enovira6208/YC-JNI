/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-11-16 19:34:52
 * @LastEditTime: 2022-11-17 17:21:28
 * @LastEditors:
 */
/* 保定金源变比旧版 */
#include "JYW6400_DC.h"

static char returnJsonDataBuff[1000];

JYW6400_DCValueType JYW6400_DCValue;

char *JYW6400_DCSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYW6400_DCReadData(uint8_t *ascllBuff)
{
    return 0;
}

/*
 *  @ brief 接收数据
 */
char *JYW6400_DCRecvMessage(uint8_t *buff, uint16_t size)
{
    JYW6400_DCMessageType *recv = (JYW6400_DCMessageType *) buff;

    printf("JYW6400_DCRecvMessage  \r\n");

    if ((recv->Head[0] != 0x42) || (recv->Head[1] != 0x45) || (recv->Head[2] != 0x47))
        return NULL;
    memset(JYW6400_DCValue.testTime, 0, 10);
    sprintf(JYW6400_DCValue.testTime, "%02d%02d%02d%02d%02d%02d%02d", 20, ((recv->Data[0] | (recv->Data[1] << 8)) % 100),
            recv->Data[2], recv->Data[3], recv->Data[4], recv->Data[5], recv->Data[6]);
    JYW6400_DCValue.electricity = PUBLIC_IEEE754_32(recv->Data[7], recv->Data[8], recv->Data[9], recv->Data[10]);
    memset(JYW6400_DCValue.electricityU, 0, 4);
    memcpy(JYW6400_DCValue.electricityU, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[11]), 4);
    for (uint8_t i = 0; i < 31; i++) {
        JYW6400_DCValue.resistance[i].AN = PUBLIC_IEEE754_32(recv->Data[12 + 12 * i],
                                           recv->Data[13 + 12 * i], recv->Data[14 + 12 * i], recv->Data[15 + 12 * i]);
        JYW6400_DCValue.resistance[i].BN = PUBLIC_IEEE754_32(recv->Data[16 + 12 * i],
                                           recv->Data[17 + 12 * i], recv->Data[18 + 12 * i], recv->Data[19 + 12 * i]);
        JYW6400_DCValue.resistance[i].CN = PUBLIC_IEEE754_32(recv->Data[20 + 12 * i],
                                           recv->Data[21 + 12 * i], recv->Data[22 + 12 * i], recv->Data[23 + 12 * i]);

        memset(JYW6400_DCValue.resistance[i].ANU, 0, 4);
        memcpy(JYW6400_DCValue.resistance[i].ANU, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[384]), 4);
        memset(JYW6400_DCValue.resistance[i].BNU, 0, 4);
        memcpy(JYW6400_DCValue.resistance[i].BNU, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[384]), 4);
        memset(JYW6400_DCValue.resistance[i].CNU, 0, 4);
        memcpy(JYW6400_DCValue.resistance[i].CNU, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[384]), 4);
    }
    printf("JYW6400_DCRecvMessage 33 \r\n");
    JYW6400_DCValue.oilTemp = PUBLIC_IEEE754_32(recv->Data[385], recv->Data[386], recv->Data[387], recv->Data[388]);

    /* 发送数据 */
    return JYW6400_DCSend();
}

/*
 * @ brief 发送数据
 */
char *JYW6400_DCSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_properties = NULL;
    cJSON *cjson_array1 = NULL;
    cJSON *cjson_array2 = NULL;
    cJSON *cjson_array3 = NULL;

    char buff[10];
    memset(buff, 0, 10);

    printf("JYW6400_DCSend  \r\n");

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_properties = cJSON_CreateObject();
    cjson_array1 = cJSON_CreateArray();
    cjson_array3 = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYW6400_DC");

    PUBLIC_JsonArrayLoading(cjson_array1, 1, "Test_time", "string", "", 0, JYW6400_DCValue.testTime);
    PUBLIC_JsonArrayLoading(cjson_array1, 2, "current", "double", JYW6400_DCValue.electricityU, JYW6400_DCValue.electricity, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 3, "Oil_temperature", "double", "°", JYW6400_DCValue.oilTemp, "null");
    cJSON_AddItemToObject(cjson_properties, "single", cjson_array1);

    for (uint8_t i = 0; i < 31; i++) {
        cJSON *cjson_temp = NULL;
        cjson_array2 = cJSON_CreateArray();

        if ((JYW6400_DCValue.resistance[i].AN != -1023.0) && (JYW6400_DCValue.resistance[i].AN != -1023.0) && (JYW6400_DCValue.resistance[i].AN != -1023.0)) {
            PUBLIC_JsonArrayLoading(cjson_array2, 1, "AN_AB_resistor", "double", JYW6400_DCValue.resistance[i].ANU, JYW6400_DCValue.resistance[i].AN, "null");
            PUBLIC_JsonArrayLoading(cjson_array2, 2, "BN_BC_resistor", "double", JYW6400_DCValue.resistance[i].BNU, JYW6400_DCValue.resistance[i].AN, "null");
            PUBLIC_JsonArrayLoading(cjson_array2, 3, "CN_CA_resistor", "double", JYW6400_DCValue.resistance[i].CNU, JYW6400_DCValue.resistance[i].AN, "null");

            cjson_temp = cJSON_CreateObject();
            sprintf(buff, "%s%02d", POINTS, i + 1);

            cJSON_AddItemToObject(cjson_temp, buff, cjson_array2);
            cJSON_AddItemToArray(cjson_array3, cjson_temp);
        }
    }

    cJSON_AddItemToObject(cjson_properties, "list", cjson_array3);
    cJSON_AddItemToObject(cjson_data, "properties", cjson_properties);

    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
