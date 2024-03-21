/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-11-16 19:34:52
 * @LastEditTime: 2022-11-18 09:00:24
 * @LastEditors:
 */
/* 保定金源变比旧版 */
#include "JYW6400_IM.h"

static char returnJsonDataBuff[1000];

JYW6400_IMValueType JYW6400_IMValue;

char *JYW6400_IMSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYW6400_IMReadData(uint8_t *ascllBuff)
{
    return 0;
}

/*
 *  @ brief 接收数据
 */
char *JYW6400_IMRecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x42 && buff[k + 1] == 0x45 && buff[k + 2] == 0x47) {
            dd = k; break;
        }
    }
    if (dd == 0 && buff[0] != 0x42) {
        return NULL;
    }
    JYW6400_IMMessageType *recv = (JYW6400_IMMessageType *) (buff + dd);

    if ((recv->Head[0] != 0x42) || (recv->Head[1] != 0x45) || (recv->Head[2] != 0x47))
        return NULL;

    memset(JYW6400_IMValue.testTime, 0, 10);
    sprintf(JYW6400_IMValue.testTime, "%02d%02d%02d%02d%02d%02d%02d", 20, ((recv->Data[0] | (recv->Data[1] << 8)) % 100),
            recv->Data[2], recv->Data[3], recv->Data[4], recv->Data[5], recv->Data[6]);

    JYW6400_IMValue.testMethod = recv->Data[7];
    JYW6400_IMValue.testMode = recv->Data[8];
    memset(JYW6400_IMValue.highPressureWinding, 0, 2);
    memset(JYW6400_IMValue.shortJointedWinding, 0, 2);
    sprintf(JYW6400_IMValue.highPressureWinding, "%c", recv->Data[9]);
    sprintf(JYW6400_IMValue.shortJointedWinding, "%c", recv->Data[10]);
    JYW6400_IMValue.switchingGearPosition = recv->Data[11];

    JYW6400_IMValue.frequency = PUBLIC_IEEE754_32(recv->Data[12], recv->Data[13], recv->Data[14], recv->Data[15]);
    for (uint8_t i = 0; i < 3; i++) {
        JYW6400_IMValue.value[i].voltage = PUBLIC_IEEE754_32(recv->Data[16 + 28 * i],
                                           recv->Data[17 + 28 * i], recv->Data[18 + 28 * i], recv->Data[19 + 28 * i]);
        JYW6400_IMValue.value[i].electricity = PUBLIC_IEEE754_32(recv->Data[20 + 28 * i],
                                               recv->Data[21 + 28 * i], recv->Data[22 + 28 * i], recv->Data[23 + 28 * i]);
        JYW6400_IMValue.value[i].power = PUBLIC_IEEE754_32(recv->Data[24 + 28 * i],
                                         recv->Data[25 + 28 * i], recv->Data[26 + 28 * i], recv->Data[27 + 28 * i]);
        JYW6400_IMValue.value[i].reactance = PUBLIC_IEEE754_32(recv->Data[28 + 28 * i],
                                             recv->Data[29 + 28 * i], recv->Data[30 + 28 * i], recv->Data[31 + 28 * i]);
        JYW6400_IMValue.value[i].impedance = PUBLIC_IEEE754_32(recv->Data[32 + 28 * i],
                                             recv->Data[33 + 28 * i], recv->Data[34 + 28 * i], recv->Data[35 + 28 * i]);
        JYW6400_IMValue.value[i].phasePosition = PUBLIC_IEEE754_32(recv->Data[36 + 28 * i],
                recv->Data[37 + 28 * i], recv->Data[38 + 28 * i], recv->Data[39 + 28 * i]);
        JYW6400_IMValue.value[i].shortCircuitImpedance = PUBLIC_IEEE754_32(recv->Data[40 + 28 * i],
                recv->Data[41 + 28 * i], recv->Data[42 + 28 * i], recv->Data[43 + 28 * i]);
    }
    JYW6400_IMValue.dissipationImpedance = PUBLIC_IEEE754_32(recv->Data[100], recv->Data[101], recv->Data[102], recv->Data[103]);
    JYW6400_IMValue.impedanceVoltage = PUBLIC_IEEE754_32(recv->Data[104], recv->Data[105], recv->Data[106], recv->Data[107]);
    JYW6400_IMValue.shortCircuitImpedance_ABC = PUBLIC_IEEE754_32(recv->Data[108], recv->Data[109], recv->Data[110], recv->Data[111]);

    /* 发送数据 */
    return JYW6400_IMSend();
}

/*
 * @ brief 发送数据
 */
char *JYW6400_IMSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_properties = NULL;
    cJSON *cjson_array1 = NULL;
    cJSON *cjson_array2 = NULL;
    cJSON *cjson_array3 = NULL;

    char buff[10];
    memset(buff, 0, 10);

    printf("JYW6400_IMSend  \r\n");

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_properties = cJSON_CreateObject();
    cjson_array1 = cJSON_CreateArray();
    cjson_array3 = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYW6400_IM");

    PUBLIC_JsonArrayLoading(cjson_array1, 1, "testTime", "string", "", 0, JYW6400_IMValue.testTime);
    PUBLIC_JsonArrayLoading(cjson_array1, 2, "testMethod", "double", "", JYW6400_IMValue.testMethod, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 3, "testMode", "double", "", JYW6400_IMValue.testMode, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 4, "highPressureWinding", "string", "", 0, JYW6400_IMValue.highPressureWinding);
    PUBLIC_JsonArrayLoading(cjson_array1, 5, "shortJointedWinding", "string", "", 0, JYW6400_IMValue.shortJointedWinding);
    PUBLIC_JsonArrayLoading(cjson_array1, 6, "switchingGearPosition", "double", "", JYW6400_IMValue.switchingGearPosition, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 7, "frequency", "double", "Hz", JYW6400_IMValue.frequency, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 8, "dissipationImpedance", "double", "W", JYW6400_IMValue.dissipationImpedance, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 9, "impedanceVoltage", "double", "", JYW6400_IMValue.impedanceVoltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array1, 10, "shortCircuitImpedance_ABC", "double", "Ω", JYW6400_IMValue.shortCircuitImpedance_ABC, "null");
    cJSON_AddItemToObject(cjson_properties, "single", cjson_array1);
    printf("JYW6400_IMSend 11 \r\n");
    for (uint8_t i = 0; i < 3; i++) {
        cJSON *cjson_temp = NULL;
        cjson_array2 = cJSON_CreateArray();

        PUBLIC_JsonArrayLoading(cjson_array2, 1, "voltage", "double", "V", JYW6400_IMValue.value[i].voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 2, "electricity", "double", "A", JYW6400_IMValue.value[i].electricity, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 3, "power", "double", "W", JYW6400_IMValue.value[i].power, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 4, "reactance", "double", "Ω", JYW6400_IMValue.value[i].reactance, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 5, "impedance", "double", "Ω", JYW6400_IMValue.value[i].impedance, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 6, "phasePosition", "double", "°", JYW6400_IMValue.value[i].phasePosition, "null");
        PUBLIC_JsonArrayLoading(cjson_array2, 7, "shortCircuitImpedance", "double", "", JYW6400_IMValue.value[i].shortCircuitImpedance, "null");

        cjson_temp = cJSON_CreateObject();

        sprintf(buff, "%s%02d", POINTS, i + 1);
        cJSON_AddItemToObject(cjson_temp, buff, cjson_array2);
        cJSON_AddItemToArray(cjson_array3, cjson_temp);
    }
    printf("JYW6400_IMSend 22 \r\n");
    cJSON_AddItemToObject(cjson_properties, "list", cjson_array3);
    cJSON_AddItemToObject(cjson_data, "properties", cjson_properties);
    printf("JYW6400_IMSend  33\r\n");
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
