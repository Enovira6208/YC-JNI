/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2023-05-30 10:48:52
 * @LastEditTime: 2023-05-30 17:19:56
 * @LastEditors:
 */
#include <stdio.h>
#include "JYC.h"
#include "math.h"
static char returnJsonDataBuff[1000];
uint16_t JYC_ReadData(uint8_t *ascllBuff, uint8_t cnt)
{
    uint8_t hexBuff[20];

    if (cnt == 1) {
        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x44;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x43;
        hexBuff[6] = 0x39;
        hexBuff[7] = 0x0D;
        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
    } else if (cnt == 2) {
        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x44;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x44;
        hexBuff[6] = 0x3E;
        hexBuff[7] = 0x0D;
        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
    } else if (cnt == 3) {
        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x44;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x45;
        hexBuff[6] = 0x3F;
        hexBuff[7] = 0x0D;
        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
    }

    return 16;
}

double JYCCount(uint8_t *buff)
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

int JYCCountLength(uint8_t *buff)
{
    uint8_t value[3];
    int vv = 0;
    int n = 0;
    for (int i = 0; i < 3; i++) {
        if (buff[i] > 0x30 && buff[i] <= 0x39) {
            value[n] = buff[i] - 0x30;
            n++;
        }
    }
    int xx = n;
    for (int j = 0; j < n; j++) {
        vv += (value[j] * pow(16, xx - 1));
        xx--;
    }
}

char *JYCSend(JYCValueType *value)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYC");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "high_switch_status", "int", "null", value->high_switch_status, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "device_status", "int", "null", value->device_status, "null");

    for (int m = 0; m < value->count; m++) {
        PUBLIC_JsonArrayLoading(cjson_array, 3 + m * 4, "name", "string", "null", 0, value->v[m].name);
        PUBLIC_JsonArrayLoading(cjson_array, 4 + m * 4, "dataSign", "string", "null", 0, value->v[m].sign);
        PUBLIC_JsonArrayLoading(cjson_array, 5 + m * 4, "dataValue", "double", "null", value->v[m].dataValue, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 6 + m * 4, "unit", "string", "null", 0, value->v[m].unitName);
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

char *JYC_RecvMessage(uint8_t *buff, uint16_t size)
{
    JYCValueType value;
    int length = 0;
    JYCMessageType *recv = (JYCMessageType *) buff;

    value.dataLength[0] = recv->addrHigh;
    value.dataLength[1] = recv->addrHigh;
    value.dataLength[2] = recv->addrHigh;
    length = JYCCountLength(value.dataLength) - 1;

    value.count = length / 10;
    value.high_switch_status = recv->high_switch_status;
    value.device_status = recv->device_status;

    for (int k = 0; k < value.count; k++) {
        if (recv->data[k * 10] == 0x43 && recv->data[k * 10 + 1] == 0x78 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "Cx");
        } else if (recv->data[k * 10] == 0x52 && recv->data[k * 10 + 1] == 0x78 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "Rx");
        } else if (recv->data[k * 10] == 0x4C && recv->data[k * 10 + 1] == 0x78 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "Lx");
        } else if (recv->data[k * 10] == 0x54 && recv->data[k * 10 + 1] == 0x67 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "Tg");
        } else if (recv->data[k * 10] == 0x55 && recv->data[k * 10 + 1] == 0x20 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "U");
        } else if (recv->data[k * 10] == 0x49 && recv->data[k * 10 + 1] == 0x20 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "I");
        } else if (recv->data[k * 10] == 0x50 && recv->data[k * 10 + 1] == 0x20 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "P");
        } else if (recv->data[k * 10] == 0xA6 && recv->data[k * 10 + 1] == 0xB5 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "Φ");
        } else if (recv->data[k * 10] == 0x56 && recv->data[k * 10 + 1] == 0x20 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "F");
        } else if (recv->data[k * 10] == 0x4B && recv->data[k * 10 + 1] == 0x20 && recv->data[k * 10 + 2] == 0x20) {
            sprintf(value.v[k].name, "%s", "K");
        } else if (recv->data[k * 10] == 0x80 && recv->data[k * 10 + 1] == 0x79 && recv->data[k * 10 + 2] == 0x76) {
            sprintf(value.v[k].name, "%s", "POL");
        }

        if (recv->data[k * 10 + 3] == 0x20) {
            sprintf(value.v[k].sign, "%s", "+");
        } else {
            sprintf(value.v[k].sign, "%s", "-");
        }

        uint8_t vv[5];
        vv[0] = recv->data[k * 10 + 4];
        vv[1] = recv->data[k * 10 + 5];
        vv[2] = recv->data[k * 10 + 6];
        vv[3] = recv->data[k * 10 + 7];
        vv[4] = recv->data[k * 10 + 8];
        value.v[k].dataValue = JYCCount(vv);

        if (recv->data[k * 10 + 9] == 0x6E) {
            sprintf(value.v[k].unitName, "%s", "nF");
        } else if (recv->data[k * 10 + 9] == 0x6B) {
            sprintf(value.v[k].unitName, "%s", "kV");
        } else if (recv->data[k * 10 + 9] == 0x20) {
            sprintf(value.v[k].unitName, "%s", "%");
        }
    }
    /* 发送数据 */
    return JYCSend(&value);
}
