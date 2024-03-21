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
#include <string.h>
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
    /*去除包前面的干扰数据*/
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x42 && buff[k + 1] == 0x45 && buff[k + 2] == 0x47) {
            dd = k; break;
        }
    }
    if (dd == 0 && buff[0] != 0x42) {
        return NULL;
    }
    SD_HVM_5000MessageType *recv = (SD_HVM_5000MessageType *) (buff + dd);
    /*判断crc是否正确*/
    uint32_t b;
    b = (recv->DataLength[3] << 24) | (recv->DataLength[2] << 16) | (recv->DataLength[1] << 8) | recv->DataLength[0];
    unsigned short crc = CRC16(buff + dd, 13 + b);

    if ((buff + dd)[(int)b + 14] != ((crc & 0xff00) >> 8) || (buff + dd)[(int)b + 13] != (crc & 0xff)) {
        return NULL;
    }

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

    SD_HVM_5000Value.voltage = Char2Float(recv->Data + 7);
    memcpy(SD_HVM_5000Value.Vuint, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[11]), sizeof(SD_HVM_5000Value.Vuint));

    SD_HVM_5000Value.resistance_15s = Char2Float(recv->Data + 12);
    memcpy(SD_HVM_5000Value.Ruint_15s, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_15s));

    SD_HVM_5000Value.resistance_60s = Char2Float(recv->Data + 16);
    memcpy(SD_HVM_5000Value.Ruint_60s, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_60s));

    SD_HVM_5000Value.resistance_10min = Char2Float(recv->Data + 20);
    memcpy(SD_HVM_5000Value.Ruint_10min, PUBLIC_SD_ProtocolUnitAnalysis(recv->Data[24]), sizeof(SD_HVM_5000Value.Ruint_10min));

    SD_HVM_5000Value.absorptance = Char2Float(recv->Data + 25);

    SD_HVM_5000Value.polarizationIndex = Char2Float(recv->Data + 29);

    /* 发送数据 */
    return SD_HVM_5000Send();
}

/*
 * @ brief 发送数据
 */
char *SD_HVM_5000Send(void)
{
    char *str;
    cJSON *cjson_all = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();

    if (strcmp(SD_HVM_5000Value.Ruint_15s, "GΩ") == 0) {
        SD_HVM_5000Value.resistance_15s = SD_HVM_5000Value.resistance_15s * 1000;
    } else if (strcmp(SD_HVM_5000Value.Ruint_15s, "TΩ") == 0) {
        SD_HVM_5000Value.resistance_15s = SD_HVM_5000Value.resistance_15s * 1000000;
    }

    cJSON_AddNumberToObject(cjson_all, "testVoltage", SD_HVM_5000Value.voltage);
    cJSON_AddNumberToObject(cjson_all, "resistanceR15", SD_HVM_5000Value.resistance_15s);
    cJSON_AddNumberToObject(cjson_all, "resistanceR60", SD_HVM_5000Value.resistance_60s);
    cJSON_AddNumberToObject(cjson_all, "resistanceR600", SD_HVM_5000Value.resistance_10min);
    cJSON_AddNumberToObject(cjson_all, "absorptance", SD_HVM_5000Value.absorptance);
    cJSON_AddNumberToObject(cjson_all, "polarizationIndex", SD_HVM_5000Value.polarizationIndex);

    str = cJSON_PrintUnformatted(cjson_all);
    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}

