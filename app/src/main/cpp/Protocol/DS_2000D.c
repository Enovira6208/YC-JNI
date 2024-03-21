/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-01-11 16:18:22
 * @LastEditTime: 2023-05-06 14:00:44
 * @LastEditors:
 */

/* 山东达顺短路阻抗 */
#include "DS_2000D.h"
#include "time.h"
static char returnJsonDataBuff[3000];
uint8_t DS_2000D_ParamCnt = 0;
DS_2000DValueType DS_2000DValue;

char *DS_2000DWifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t DS_2000DReadData(uint8_t *buff, uint8_t cnt)
{
    buff[0] = 0x34;
    buff[1] = 0x33;

    return 2;
}


/*
 *  @ brief 字符串解析
 */
double DS_2000DStr_8_Analy(uint8_t *buff)
{
    uint8_t array[5];
    uint8_t cnt, j = 0;
    double value = 0;

    memcpy(array, buff, 5);
    memset(array, 0, 5);

    for (uint8_t i = 0; i < 5; i++) {
        if (buff[i] == '.') {
            cnt = i;
        } else {
            array[j++] = buff[i] - 48;
        }
    }

    value = 0;
    for (uint8_t i = 0; i < 4; i++) {
        value += array[i] * pow(10, cnt - 1 - i);
    }

    return value;
}

double DS_2000DStr_8_Analy2(uint8_t *buff)
{
    uint8_t array[6];
    uint8_t cnt, j = 0;
    double value = 0;

    memcpy(array, buff, 6);
    memset(array, 0, 6);

    for (uint8_t i = 0; i < 6; i++) {
        if (buff[i] == '.') {
            cnt = i;
        } else {
            array[j++] = buff[i] - 48;
        }
    }

    value = 0;
    for (uint8_t i = 0; i < 5; i++) {
        value += array[i] * pow(10, cnt - 1 - i);
    }

    return value;
}
/*
 *  @ brief 接收数据
 */
char *DS_2000DRecvMessage(uint8_t *buff, uint16_t size)
{
    char *index, *index2, *index3, *index4, *index5, *index6, *index7;
    if (NULL != strstr((char *)buff, "A\r\n")) {
        return "succeed";
    }

    uint8_t no0_buf[size + 1];
    uint16_t no0_size = 0;
    for (uint16_t i = 0; i < size; i++) {
        if (buff[i] != 0) {
            no0_buf[no0_size] = buff[i];
            no0_size++;
            no0_buf[no0_size] = 0;
        }
    }

    index2 = strstr((char *)no0_buf, "[W]");
    index3 = strstr((char *)no0_buf, "[V]");
    index4 = strstr((char *)no0_buf, "[A]");
    index = strstr((char *)no0_buf, "Ukj");
    index5 = strstr((char *)no0_buf, "Zkj");
    index6 = strstr((char *)no0_buf, "Xkj");
    index7 = strstr((char *)no0_buf, "Lkj");
    if (index == NULL || index2 == NULL || index3 == NULL || index4 == NULL || index5 == NULL || index6 == NULL || index7 == NULL) {
        return NULL;
    }

    DS_2000DValue.ukj_a = DS_2000DStr_8_Analy((uint8_t *)index + 3);
    DS_2000DValue.ukj_b = DS_2000DStr_8_Analy((uint8_t *)index + 3 + 6);
    DS_2000DValue.ukj_c = DS_2000DStr_8_Analy((uint8_t *)index + 3 + 6 + 6);

    DS_2000DValue.zkj_a = DS_2000DStr_8_Analy((uint8_t *)index5 + 3);
    DS_2000DValue.zkj_b = DS_2000DStr_8_Analy((uint8_t *)index5 + 3 + 6);
    DS_2000DValue.zkj_c = DS_2000DStr_8_Analy((uint8_t *)index5 + 3 + 6 + 6);

    DS_2000DValue.xkj_a = DS_2000DStr_8_Analy((uint8_t *)index6 + 3);
    DS_2000DValue.xkj_b = DS_2000DStr_8_Analy((uint8_t *)index6 + 3 + 6);
    DS_2000DValue.xkj_c = DS_2000DStr_8_Analy((uint8_t *)index6 + 3 + 6 + 6);

    DS_2000DValue.lkj_a = DS_2000DStr_8_Analy((uint8_t *)index7 + 3);
    DS_2000DValue.lkj_b = DS_2000DStr_8_Analy((uint8_t *)index7 + 3 + 6);
    DS_2000DValue.lkj_c = DS_2000DStr_8_Analy((uint8_t *)index7 + 3 + 6 + 6);

    DS_2000DValue.power_a = DS_2000DStr_8_Analy2((uint8_t *)index2 - 20);
    DS_2000DValue.power_b = DS_2000DStr_8_Analy2((uint8_t *)index2 - 20 + 7);
    DS_2000DValue.power_c = DS_2000DStr_8_Analy2((uint8_t *)index2 - 20 + 7 + 7);

    DS_2000DValue.voltage_a = DS_2000DStr_8_Analy2((uint8_t *)index3 - 20);
    DS_2000DValue.voltage_b = DS_2000DStr_8_Analy2((uint8_t *)index3 - 20 + 7);
    DS_2000DValue.voltage_c = DS_2000DStr_8_Analy2((uint8_t *)index3  - 20 + 7 + 7);

    DS_2000DValue.current_a = DS_2000DStr_8_Analy2((uint8_t *)index4 - 20);
    DS_2000DValue.current_b = DS_2000DStr_8_Analy2((uint8_t *)index4 - 20 + 7);
    DS_2000DValue.current_c = DS_2000DStr_8_Analy2((uint8_t *)index4  - 20 + 7 + 7);
    printf("DS_2000DRecvMessage \n");
    /* 发送数据 */
    return DS_2000DWifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *DS_2000DWifiSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();
    cJSON_AddNumberToObject(cjson_all, "shortCircuitImpedancePercentage_AX", DS_2000DValue.ukj_a);
    cJSON_AddNumberToObject(cjson_all, "shortCircuitImpedancePercentage_BX", DS_2000DValue.ukj_b);
    cJSON_AddNumberToObject(cjson_all, "shortCircuitImpedancePercentage_CX", DS_2000DValue.ukj_c);
    cJSON_AddNumberToObject(cjson_all, "impedance_AX", DS_2000DValue.zkj_a);
    cJSON_AddNumberToObject(cjson_all, "impedance_BX", DS_2000DValue.zkj_b);
    cJSON_AddNumberToObject(cjson_all, "impedance_CX", DS_2000DValue.zkj_c);
    cJSON_AddNumberToObject(cjson_all, "reactance_AX", DS_2000DValue.xkj_a);
    cJSON_AddNumberToObject(cjson_all, "reactance_BX", DS_2000DValue.xkj_b);
    cJSON_AddNumberToObject(cjson_all, "reactance_CX", DS_2000DValue.xkj_c);
    cJSON_AddNumberToObject(cjson_all, "inductance_AX", DS_2000DValue.lkj_a);
    cJSON_AddNumberToObject(cjson_all, "inductance_BX", DS_2000DValue.lkj_b);
    cJSON_AddNumberToObject(cjson_all, "inductance_CX", DS_2000DValue.lkj_c);
    cJSON_AddNumberToObject(cjson_all, "power_AX", DS_2000DValue.power_a);
    cJSON_AddNumberToObject(cjson_all, "power_BX", DS_2000DValue.power_b);
    cJSON_AddNumberToObject(cjson_all, "power_CX", DS_2000DValue.power_c);
    cJSON_AddNumberToObject(cjson_all, "voltage_AX", DS_2000DValue.voltage_a);
    cJSON_AddNumberToObject(cjson_all, "voltage_BX", DS_2000DValue.voltage_b);
    cJSON_AddNumberToObject(cjson_all, "voltage_CX", DS_2000DValue.voltage_c);
    cJSON_AddNumberToObject(cjson_all, "current_AX", DS_2000DValue.current_a);
    cJSON_AddNumberToObject(cjson_all, "current_BX", DS_2000DValue.current_b);
    cJSON_AddNumberToObject(cjson_all, "current_CX", DS_2000DValue.current_c);

    str = cJSON_PrintUnformatted(cjson_all);
    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);
    printf("1111111111\n");
    return returnJsonDataBuff;
}





