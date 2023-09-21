/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-14 18:01:04
 * @LastEditors:
 */


/* 苏州海沃直流高压发生器 */
#include "SD_Z_VI.h"

static char returnJsonDataBuff[1000];

SD_Z_VIValueType SD_Z_VIValue;

char *SD_Z_VISend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t SD_Z_VIReadData(uint8_t *ascllBuff)
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
char *SD_Z_VIRecvMessage(uint8_t *buff, uint16_t size)
{
    SD_Z_VIMessageType *recv = (SD_Z_VIMessageType *) buff;

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


    sprintf((char *)&SD_Z_VIValue.testTime[0], "%04d", (recv->Data[0] | (recv->Data[1] << 8)));
    for (uint8_t i = 2; i < 7; i++) {
        sprintf((char *)&SD_Z_VIValue.testTime[i * 2], "%02d", recv->Data[i]);
    }

    SD_Z_VIValue.testVoltage = PUBLIC_IEEE754_32(recv->Data[7], recv->Data[8], recv->Data[9], recv->Data[10]);
    memcpy(SD_Z_VIValue.testVuint, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[11]), sizeof(SD_Z_VIValue.testVuint));

    SD_Z_VIValue.testElectricity = PUBLIC_IEEE754_32(recv->Data[12], recv->Data[13], recv->Data[14], recv->Data[15]);
    memcpy(SD_Z_VIValue.testEuint, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[16]), sizeof(SD_Z_VIValue.testEuint));

    SD_Z_VIValue.voltage_75 = PUBLIC_IEEE754_32(recv->Data[17], recv->Data[18], recv->Data[19], recv->Data[20]);
    memcpy(SD_Z_VIValue.Vuint_75, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[21]), sizeof(SD_Z_VIValue.Vuint_75));

    SD_Z_VIValue.electricity_75 = PUBLIC_IEEE754_32(recv->Data[22], recv->Data[23], recv->Data[24], recv->Data[25]);
    memcpy(SD_Z_VIValue.Iuint_75, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[26]), sizeof(SD_Z_VIValue.Iuint_75));

    SD_Z_VIValue.sustainTime = recv->Data[27] | (recv->Data[28] << 8);
    memcpy(SD_Z_VIValue.sustainTuint_75, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[29]), sizeof(SD_Z_VIValue.sustainTuint_75));


    /* 发送数据 */
    return SD_Z_VISend();
}

/*
 * @ brief 发送数据
 */
char *SD_Z_VISend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "SD_Z_VI");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "testTime", "string", "", 0, SD_Z_VIValue.testTime);
    PUBLIC_JsonArrayLoading(cjson_array, 2, "testVoltage", "double", SD_Z_VIValue.testVuint, SD_Z_VIValue.testVoltage, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "testElectricity", "double", SD_Z_VIValue.testEuint, SD_Z_VIValue.testElectricity, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "voltage_75", "double", SD_Z_VIValue.Vuint_75, SD_Z_VIValue.voltage_75, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "electricity_75", "double", SD_Z_VIValue.Iuint_75,   SD_Z_VIValue.electricity_75, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "sustainTime", "double", SD_Z_VIValue.sustainTuint_75, SD_Z_VIValue.sustainTime, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
    //printf("%s\r\n", str);

    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);

    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}

