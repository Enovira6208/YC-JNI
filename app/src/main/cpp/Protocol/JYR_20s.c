/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-03-03 16:24:48
 * @LastEditTime: 2022-09-02 11:20:41
 * @LastEditors:
 */

/* 金源直流电阻 */
#include "JYR_20s.h"
#include <math.h>
static char returnJsonDataBuff[1000];

JYR_20sValueType JYR_20sValue;
JYR_20sAnalyEnum JYR_20sAnaly;

char *JYR_20sSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYR_20sReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[10];

    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x45;
    hexBuff[3] = 0x30;
    hexBuff[4] = 0x31;
    hexBuff[5] = 0x48;
    hexBuff[6] = 0x37;
    hexBuff[7] = 0x0D;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

    return 16;
}

/**
 * @brief
 *
 */
double JYR_20sCount(uint8_t *buff)
{
    uint8_t ascll[5];
    uint8_t decimal;
    uint8_t j = 0;
    double vlaue = 0;

    memset(ascll, 0, 5);
    for (uint8_t i = 0; i < 7; i++) {
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

/**
 * @brief
 *
 */
double JYR_20sCount_2(uint8_t *buff)
{
    uint8_t ascll[4];
    uint8_t decimal;
    uint8_t j = 0;
    double vlaue = 0;

    memset(ascll, 0, 4);
    for (uint8_t i = 0; i < 5; i++) {
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
char *JYR_20sRecvMessage(uint8_t *buff, uint16_t size)
{

    JYR_20sMessageType *recv = (JYR_20sMessageType *) buff;
    JYR_20sDataType Data;

    memcpy(&Data.Ao, recv->Data, sizeof(JYR_20sDataType));

    switch (recv->Way) {
        /* YN三相同测 */
        case JYR_20s_WAY_YN_THREE_PHASE:
            JYR_20sAnaly = JYR_20_ANALY_3;
            break;

        /* YN逐相测试 */
        case JYR_20s_WAY_YN_CHASE_PHASE:
            JYR_20sAnaly = JYR_20_ANALY_3;
            break;

        /* D逐相测试 */
        case JYR_20s_WAY_D_CHASE_PHASE:
            JYR_20sAnaly = JYR_20_ANALY_3;
            break;

        /* 单相测试 */
        case JYR_20s_WAY_SINGLE_PHASE:
            JYR_20sAnaly = JYR_20_ANALY_1;
            break;

        /* 助磁ab */
        case JYR_20s_WAY_MAGNETISM_AB:
            JYR_20sAnaly = JYR_20_ANALY_1;
            break;

        /* 助磁bc */
        case JYR_20s_WAY_MAGNETISM_BC:
            JYR_20sAnaly = JYR_20_ANALY_1;
            break;

        /* 助磁ca */
        case JYR_20s_WAY_MAGNETISM_CA:
            JYR_20sAnaly = JYR_20_ANALY_1;
            break;

        /* 助磁逐相测试 */
        case JYR_20s_WAY_MAGNETISM_CHASE_PHASE:
            JYR_20sAnaly = JYR_20_ANALY_3;
            break;
    }

    switch (JYR_20sAnaly) {
        case JYR_20_ANALY_1:
            JYR_20sValue.Ao = JYR_20sCount(Data.Ao);
            JYR_20sValue.AoU[0] = Data.Ao[6];
            memcpy(&JYR_20sValue.AoU[1], "Ω", 2);
            break;

        case JYR_20_ANALY_2:
            JYR_20sValue.Ao = JYR_20sCount(Data.Ao);
            JYR_20sValue.Bo = JYR_20sCount(Data.Bo);
            JYR_20sValue.AoU[0] = Data.Ao[6];
            memcpy(&JYR_20sValue.AoU[1], "Ω", 2);
            JYR_20sValue.BoU[0] = Data.Bo[6];
            memcpy(&JYR_20sValue.BoU[1], "Ω", 2);
            //JYR_20sValue.Unbalance = JYR_20sCount_2(Data.Co);
            break;

        case JYR_20_ANALY_3:
            JYR_20sValue.Ao = JYR_20sCount(Data.Ao);
            JYR_20sValue.Bo = JYR_20sCount(Data.Bo);
            JYR_20sValue.Co = JYR_20sCount(Data.Co);
            JYR_20sValue.Unbalance = JYR_20sCount_2(Data.Unbalance);
            JYR_20sValue.AoU[0] = Data.Ao[6];
            memcpy(&JYR_20sValue.AoU[1], "Ω", 2);
            JYR_20sValue.BoU[0] = Data.Bo[6];
            memcpy(&JYR_20sValue.BoU[1], "Ω", 2);
            JYR_20sValue.CoU[0] = Data.Co[6];
            memcpy(&JYR_20sValue.CoU[1], "Ω", 2);
            break;
    }

    /* 发送数据 */
    return JYR_20sSend();
}

/*
 * @ brief 发送数据
 */
char *JYR_20sSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYR_20S");

    // PUBLIC_JsonArrayLoading(cjson_array, 1, "resistance_Ao", "double", JYR_20sValue.AoU, JYR_20sValue.Ao, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 2, "resistance_Bo", "double", JYR_20sValue.BoU, JYR_20sValue.Bo, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 3, "resistance_Co", "double", JYR_20sValue.CoU, JYR_20sValue.Co, "null");
    // PUBLIC_JsonArrayLoading(cjson_array, 4, "unbalanceRate", "double", "%", JYR_20sValue.Unbalance, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "AN_AB_resistor", "double", JYR_20sValue.AoU, JYR_20sValue.Ao, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "BN_BC_resistor", "double", JYR_20sValue.BoU, JYR_20sValue.Bo, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "CN_CA_resistor", "double", JYR_20sValue.CoU, JYR_20sValue.Co, "null");

    if (JYR_20sAnaly == JYR_20_ANALY_3) {
        PUBLIC_JsonArrayLoading(cjson_array, 4, "Unbalance", "double", "", JYR_20sValue.Unbalance, "null");
    }

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

