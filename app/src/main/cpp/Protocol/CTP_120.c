/*
 * CTP_120.c
 * @Author       : zhengshuo
 * @Date         : 2023年9月19日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* CTP_120*/
/*武汉豪迈 电压互感器和电力互感器*/
#include "CTP_120.h"
#include "../public/mycrc16.h"
static char returnJsonDataBuff[1000];
CTP_120A_ValueType CTP_120A_Value;
CTP_120V_ValueType CTP_120V_Value;

char *CTP_120wifiSend(uint8_t cnt);

/*
 *  @ brief 读取仪器数据
 */
uint16_t CTP_120ReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = 'R';
        buff[1] = 'E';
        buff[2] = 'G';
        buff[3] = 0x00;
        buff[4] = 0x00;
        buff[5] = 0x00;
        buff[6] = 0x0F;
        buff[7] = 0x00;
        buff[8] = 0x01;
        buff[9] = 0x00;
        buff[10] = 0x00;
        buff[11] = 0x00;
        buff[12] = 0x00;
        buff[13] = 0x03;
        buff[14] = 0xef;
    } else if (cnt == 2) {
        buff[0] = 'R';
        buff[1] = 'E';
        buff[2] = 'G';
        buff[3] = 0x00;
        buff[4] = 0x00;
        buff[5] = 0x00;
        buff[6] = 0x0F;
        buff[7] = 0x00;
        buff[8] = 0x03;
        buff[9] = 0x00;
        buff[10] = 0x00;
        buff[11] = 0x00;
        buff[12] = 0x00;
        buff[13] = (uint8_t)(mycrc16_calc(buff, 13) << 8);
        buff[14] = (uint8_t)(mycrc16_calc(buff, 13));
        return 15;
    }
    return 0;
}

double CTP_120count(uint8_t *buf)
{
    return PUBLIC_IEEE754_32(buf[3], buf[2], buf[1], buf[0]);
}
/*
 *  @ brief 接收数据
 */
char *CTP_120RecvMessage(uint8_t *buff, uint16_t size)
{
    CTP_120MessageType *recv = (CTP_120MessageType *)buff;

    if (recv->cmd[1] != 0x03)
        return NULL;

    if (recv->data_len[3] == 0xFD) { // 电流互感器
        CTP_120A_MessageDataType messageData;
        memcpy(messageData.test_time, recv->Data, sizeof(CTP_120A_MessageDataType));

        CTP_120A_Value.test_time[0] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 1000) + '0';
        CTP_120A_Value.test_time[1] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 100) % 10 + '0';
        CTP_120A_Value.test_time[2] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 10) % 10 + '0';
        CTP_120A_Value.test_time[3] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) % 10) + '0';
        CTP_120A_Value.test_time[4] = '/';
        CTP_120A_Value.test_time[5] = messageData.test_time[2] / 10 + '0';
        CTP_120A_Value.test_time[6] = messageData.test_time[2] % 10 + '0';
        CTP_120A_Value.test_time[7] = '/';
        CTP_120A_Value.test_time[8] = messageData.test_time[3] / 10 + '0';
        CTP_120A_Value.test_time[9] = messageData.test_time[3] % 10 + '0';
        CTP_120A_Value.test_time[10] = ' ';
        CTP_120A_Value.test_time[11] = messageData.test_time[4] / 10 + '0';
        CTP_120A_Value.test_time[12] = messageData.test_time[4] % 10 + '0';
        CTP_120A_Value.test_time[13] = ':';
        CTP_120A_Value.test_time[14] = messageData.test_time[5] / 10 + '0';
        CTP_120A_Value.test_time[15] = messageData.test_time[5] % 10 + '0';
        CTP_120A_Value.test_time[16] = ':';
        CTP_120A_Value.test_time[17] = messageData.test_time[6] / 10 + '0';
        CTP_120A_Value.test_time[18] = messageData.test_time[6] % 10 + '0';

        CTP_120A_Value.type = messageData.type;
        CTP_120A_Value.once_current = CTP_120count(messageData.once_current);
        CTP_120A_Value.second_current = CTP_120count(messageData.second_current);
        CTP_120A_Value.Rated_composite_error = messageData.Rated_composite_error;
        CTP_120A_Value.Rated_ALF = messageData.Rated_ALF;
        CTP_120A_Value.accuracy_class = messageData.accuracy_class;
        CTP_120A_Value.Rated_FS = messageData.Rated_FS;
        CTP_120A_Value.knee_voltage = CTP_120count(messageData.knee_voltage);
        CTP_120A_Value.knee_current = CTP_120count(messageData.knee_current);
        CTP_120A_Value.composite_erro = CTP_120count(messageData.composite_erro);
        CTP_120A_Value.ALF = CTP_120count(messageData.ALF);
        CTP_120A_Value.FS = CTP_120count(messageData.FS);
        CTP_120A_Value.Remanence_coefficient = CTP_120count(messageData.Remanence_coefficient);
        CTP_120A_Value.Peak_instantaneous_error = CTP_120count(messageData.Peak_instantaneous_error);
        CTP_120A_Value.Turn_ratio_error = CTP_120count(messageData.Turn_ratio_error);
        CTP_120A_Value.ratio_difference = CTP_120count(messageData.ratio_difference);
        CTP_120A_Value.phase_difference = CTP_120count(messageData.phase_difference);
        CTP_120A_Value.polarity = messageData.polarity;

        CTP_120A_Value.Excitation_current1 = CTP_120count(messageData.Excitation_current1);
        CTP_120A_Value.Excitation_voltage1 = CTP_120count(messageData.Excitation_voltage1);
        CTP_120A_Value.Excitation_current2 = CTP_120count(messageData.Excitation_current2);
        CTP_120A_Value.Excitation_voltage2 = CTP_120count(messageData.Excitation_voltage2);
        CTP_120A_Value.Excitation_current3 = CTP_120count(messageData.Excitation_current3);
        CTP_120A_Value.Excitation_voltage3 = CTP_120count(messageData.Excitation_voltage3);
        CTP_120A_Value.Excitation_current4 = CTP_120count(messageData.Excitation_current4);
        CTP_120A_Value.Excitation_voltage4 = CTP_120count(messageData.Excitation_voltage4);
        CTP_120A_Value.Excitation_current5 = CTP_120count(messageData.Excitation_current5);
        CTP_120A_Value.Excitation_voltage5 = CTP_120count(messageData.Excitation_voltage5);
        CTP_120A_Value.Excitation_current6 = CTP_120count(messageData.Excitation_current6);
        CTP_120A_Value.Excitation_voltage6 = CTP_120count(messageData.Excitation_voltage6);
        CTP_120A_Value.Excitation_current7 = CTP_120count(messageData.Excitation_current7);
        CTP_120A_Value.Excitation_voltage7 = CTP_120count(messageData.Excitation_voltage7);

        CTP_120A_Value.Excitation_current8 = CTP_120count(messageData.Excitation_current8);
        CTP_120A_Value.Excitation_voltage8 = CTP_120count(messageData.Excitation_voltage8);
        CTP_120A_Value.Excitation_current9 = CTP_120count(messageData.Excitation_current9);
        CTP_120A_Value.Excitation_voltage9 = CTP_120count(messageData.Excitation_voltage9);
        CTP_120A_Value.Excitation_current10 = CTP_120count(messageData.Excitation_current10);
        CTP_120A_Value.Excitation_voltage10 = CTP_120count(messageData.Excitation_voltage10);
        CTP_120A_Value.Excitation_current11 = CTP_120count(messageData.Excitation_current11);
        CTP_120A_Value.Excitation_voltage11 = CTP_120count(messageData.Excitation_voltage11);
        CTP_120A_Value.Excitation_current12 = CTP_120count(messageData.Excitation_current12);
        CTP_120A_Value.Excitation_voltage12 = CTP_120count(messageData.Excitation_voltage12);
        CTP_120A_Value.Excitation_current13 = CTP_120count(messageData.Excitation_current13);
        CTP_120A_Value.Excitation_voltage13 = CTP_120count(messageData.Excitation_voltage13);
        CTP_120A_Value.Excitation_current14 = CTP_120count(messageData.Excitation_current14);
        CTP_120A_Value.Excitation_voltage14 = CTP_120count(messageData.Excitation_voltage14);
        CTP_120A_Value.Excitation_current15 = CTP_120count(messageData.Excitation_current15);
        CTP_120A_Value.Excitation_voltage15 = CTP_120count(messageData.Excitation_voltage15);
        CTP_120A_Value.Excitation_current16 = CTP_120count(messageData.Excitation_current16);
        CTP_120A_Value.Excitation_voltage16 = CTP_120count(messageData.Excitation_voltage16);
        CTP_120A_Value.Excitation_current17 = CTP_120count(messageData.Excitation_current17);
        CTP_120A_Value.Excitation_voltage17 = CTP_120count(messageData.Excitation_voltage17);
        CTP_120A_Value.Excitation_current18 = CTP_120count(messageData.Excitation_current18);
        CTP_120A_Value.Excitation_voltage18 = CTP_120count(messageData.Excitation_voltage18);
        CTP_120A_Value.Excitation_current19 = CTP_120count(messageData.Excitation_current19);
        CTP_120A_Value.Excitation_voltage19 = CTP_120count(messageData.Excitation_voltage19);
        CTP_120A_Value.Excitation_current20 = CTP_120count(messageData.Excitation_current20);
        CTP_120A_Value.Excitation_voltage20 = CTP_120count(messageData.Excitation_voltage20);

        return CTP_120wifiSend(1);
    } else { // 电压互感器
        CTP_120V_MessageDataType messageData;
        memcpy(messageData.test_time, recv->Data, sizeof(CTP_120V_MessageDataType));

        CTP_120V_Value.test_time[0] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 1000) + '0';
        CTP_120V_Value.test_time[1] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 100) % 10 + '0';
        CTP_120V_Value.test_time[2] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) / 10) % 10 + '0';
        CTP_120V_Value.test_time[3] = ((messageData.test_time[0] * 256 + messageData.test_time[1]) % 10) + '0';
        CTP_120V_Value.test_time[4] = '/';
        CTP_120V_Value.test_time[5] = messageData.test_time[2] / 10 + '0';
        CTP_120V_Value.test_time[6] = messageData.test_time[2] % 10 + '0';
        CTP_120V_Value.test_time[7] = '/';
        CTP_120V_Value.test_time[8] = messageData.test_time[3] / 10 + '0';
        CTP_120V_Value.test_time[9] = messageData.test_time[3] % 10 + '0';
        CTP_120V_Value.test_time[10] = ' ';
        CTP_120V_Value.test_time[11] = messageData.test_time[4] / 10 + '0';
        CTP_120V_Value.test_time[12] = messageData.test_time[4] % 10 + '0';
        CTP_120V_Value.test_time[13] = ':';
        CTP_120V_Value.test_time[14] = messageData.test_time[5] / 10 + '0';
        CTP_120V_Value.test_time[15] = messageData.test_time[5] % 10 + '0';
        CTP_120V_Value.test_time[16] = ':';
        CTP_120V_Value.test_time[17] = messageData.test_time[6] / 10 + '0';
        CTP_120V_Value.test_time[18] = messageData.test_time[6] % 10 + '0';

        CTP_120V_Value.once_voltage = CTP_120count(messageData.once_voltage);
        CTP_120V_Value.second_voltage = CTP_120count(messageData.second_voltage);
        CTP_120V_Value.polarity = messageData.polarity;
        CTP_120V_Value.ratio_difference = CTP_120count(messageData.ratio_difference);

        CTP_120V_Value.Excitation_current1 = CTP_120count(messageData.Excitation_current1);
        CTP_120V_Value.Excitation_voltage1 = CTP_120count(messageData.Excitation_voltage1);
        CTP_120V_Value.Excitation_current2 = CTP_120count(messageData.Excitation_current2);
        CTP_120V_Value.Excitation_voltage2 = CTP_120count(messageData.Excitation_voltage2);
        CTP_120V_Value.Excitation_current3 = CTP_120count(messageData.Excitation_current3);
        CTP_120V_Value.Excitation_voltage3 = CTP_120count(messageData.Excitation_voltage3);
        CTP_120V_Value.Excitation_current4 = CTP_120count(messageData.Excitation_current4);
        CTP_120V_Value.Excitation_voltage4 = CTP_120count(messageData.Excitation_voltage4);
        CTP_120V_Value.Excitation_current5 = CTP_120count(messageData.Excitation_current5);
        CTP_120V_Value.Excitation_voltage5 = CTP_120count(messageData.Excitation_voltage5);
        CTP_120V_Value.Excitation_current6 = CTP_120count(messageData.Excitation_current6);
        CTP_120V_Value.Excitation_voltage6 = CTP_120count(messageData.Excitation_voltage6);
        CTP_120V_Value.Excitation_current7 = CTP_120count(messageData.Excitation_current7);
        CTP_120V_Value.Excitation_voltage7 = CTP_120count(messageData.Excitation_voltage7);

        CTP_120V_Value.Excitation_current8 = CTP_120count(messageData.Excitation_current8);
        CTP_120V_Value.Excitation_voltage8 = CTP_120count(messageData.Excitation_voltage8);
        CTP_120V_Value.Excitation_current9 = CTP_120count(messageData.Excitation_current9);
        CTP_120V_Value.Excitation_voltage9 = CTP_120count(messageData.Excitation_voltage9);
        CTP_120V_Value.Excitation_current10 = CTP_120count(messageData.Excitation_current10);
        CTP_120V_Value.Excitation_voltage10 = CTP_120count(messageData.Excitation_voltage10);

        return CTP_120wifiSend(2);
    }

    /* 发送数据 */
}

/*
 * @ 通过蓝牙发送数据
 */
char *CTP_120wifiSend(uint8_t cnt)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    if (cnt == 1) {
        cJSON_AddStringToObject(cjson_data, "device", "CTP_120_Current");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "test_time", "string", "null", 0, CTP_120A_Value.test_time);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "type", "double", "null", CTP_120A_Value.type, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "once_current", "double", "A", CTP_120A_Value.once_current, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 4, "second_current", "double", "A", CTP_120A_Value.second_current, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 5, "Rated_composite_error", "double", "%", CTP_120A_Value.Rated_composite_error, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 6, "Rated_ALF", "double", "null", CTP_120A_Value.Rated_ALF, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 7, "accuracy_class", "double", "null", CTP_120A_Value.accuracy_class, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 8, "Rated_FS", "double", "null", CTP_120A_Value.Rated_FS, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 9, "knee_voltage", "double", "V", CTP_120A_Value.knee_voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 10, "knee_current", "double", "A", CTP_120A_Value.knee_current, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 11, "composite_erro", "double", "%", CTP_120A_Value.composite_erro, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 12, "ALF", "double", "null", CTP_120A_Value.ALF, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 13, "FS", "double", "null", CTP_120A_Value.FS, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 14, "Remanence_coefficient", "double", "%", CTP_120A_Value.Remanence_coefficient, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 15, "Peak_instantaneous_error", "double", "%", CTP_120A_Value.Peak_instantaneous_error, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 16, "Turn_ratio_error", "double", "%", CTP_120A_Value.Turn_ratio_error, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 17, "ratio_difference", "double", "%", CTP_120A_Value.ratio_difference, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 18, "phase_difference", "double", "min", CTP_120A_Value.phase_difference, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 19, "polarity", "double", "null", CTP_120A_Value.polarity, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 20, "Excitation_current1", "double", "A", CTP_120A_Value.Excitation_current1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 21, "Excitation_voltage1", "double", "V", CTP_120A_Value.Excitation_voltage1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 22, "Excitation_current2", "double", "A", CTP_120A_Value.Excitation_current2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 23, "Excitation_voltage2", "double", "V", CTP_120A_Value.Excitation_voltage2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 24, "Excitation_current3", "double", "A", CTP_120A_Value.Excitation_current3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 25, "Excitation_voltage3", "double", "V", CTP_120A_Value.Excitation_voltage3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 26, "Excitation_current4", "double", "A", CTP_120A_Value.Excitation_current4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 27, "Excitation_voltage4", "double", "V", CTP_120A_Value.Excitation_voltage4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 28, "Excitation_current5", "double", "A", CTP_120A_Value.Excitation_current5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 29, "Excitation_voltage5", "double", "V", CTP_120A_Value.Excitation_voltage5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 30, "Excitation_current6", "double", "A", CTP_120A_Value.Excitation_current6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 31, "Excitation_voltage6", "double", "V", CTP_120A_Value.Excitation_voltage6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 32, "Excitation_current7", "double", "A", CTP_120A_Value.Excitation_current7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 33, "Excitation_voltage7", "double", "V", CTP_120A_Value.Excitation_voltage7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 34, "Excitation_current8", "double", "A", CTP_120A_Value.Excitation_current8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 35, "Excitation_voltage8", "double", "V", CTP_120A_Value.Excitation_voltage8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 36, "Excitation_current9", "double", "A", CTP_120A_Value.Excitation_current9, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 37, "Excitation_voltage9", "double", "V", CTP_120A_Value.Excitation_voltage9, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 38, "Excitation_current10", "double", "A", CTP_120A_Value.Excitation_current10, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 39, "Excitation_voltage10", "double", "V", CTP_120A_Value.Excitation_voltage10, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 40, "Excitation_current11", "double", "A", CTP_120A_Value.Excitation_current11, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 41, "Excitation_voltage11", "double", "V", CTP_120A_Value.Excitation_voltage11, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 42, "Excitation_current12", "double", "A", CTP_120A_Value.Excitation_current12, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 43, "Excitation_voltage12", "double", "V", CTP_120A_Value.Excitation_voltage12, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 44, "Excitation_current13", "double", "A", CTP_120A_Value.Excitation_current13, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 45, "Excitation_voltage13", "double", "V", CTP_120A_Value.Excitation_voltage13, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 46, "Excitation_current14", "double", "A", CTP_120A_Value.Excitation_current14, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 47, "Excitation_voltage14", "double", "V", CTP_120A_Value.Excitation_voltage14, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 48, "Excitation_current15", "double", "A", CTP_120A_Value.Excitation_current15, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 49, "Excitation_voltage15", "double", "V", CTP_120A_Value.Excitation_voltage15, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 50, "Excitation_current16", "double", "A", CTP_120A_Value.Excitation_current16, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 51, "Excitation_voltage16", "double", "V", CTP_120A_Value.Excitation_voltage16, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 52, "Excitation_current17", "double", "A", CTP_120A_Value.Excitation_current17, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 53, "Excitation_voltage17", "double", "V", CTP_120A_Value.Excitation_voltage17, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 54, "Excitation_current18", "double", "A", CTP_120A_Value.Excitation_current18, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 55, "Excitation_voltage18", "double", "V", CTP_120A_Value.Excitation_voltage18, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 56, "Excitation_current19", "double", "A", CTP_120A_Value.Excitation_current19, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 57, "Excitation_voltage19", "double", "V", CTP_120A_Value.Excitation_voltage19, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 58, "Excitation_current20", "double", "A", CTP_120A_Value.Excitation_current20, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 59, "Excitation_voltage20", "double", "V", CTP_120A_Value.Excitation_voltage20, "null");
    }

    else if (cnt == 2) {
        cJSON_AddStringToObject(cjson_data, "device", "CTP_120_Voltage");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "test_time", "string", "null", 0, CTP_120V_Value.test_time);
        PUBLIC_JsonArrayLoading(cjson_array, 2, "once_voltage", "double", "V", CTP_120V_Value.once_voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "second_voltage", "double", "V", CTP_120V_Value.second_voltage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "polarity", "double", "null", CTP_120V_Value.polarity, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "ratio_difference", "double", "%", CTP_120V_Value.ratio_difference, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current1", "double", "A", CTP_120V_Value.Excitation_current1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage1", "double", "V", CTP_120V_Value.Excitation_voltage1, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current2", "double", "A", CTP_120V_Value.Excitation_current2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage2", "double", "V", CTP_120V_Value.Excitation_voltage2, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current3", "double", "A", CTP_120V_Value.Excitation_current3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage3", "double", "V", CTP_120V_Value.Excitation_voltage3, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current4", "double", "A", CTP_120V_Value.Excitation_current4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage4", "double", "V", CTP_120V_Value.Excitation_voltage4, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current5", "double", "A", CTP_120V_Value.Excitation_current5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage5", "double", "V", CTP_120V_Value.Excitation_voltage5, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current6", "double", "A", CTP_120V_Value.Excitation_current6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage6", "double", "V", CTP_120V_Value.Excitation_voltage6, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current7", "double", "A", CTP_120V_Value.Excitation_current7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage7", "double", "V", CTP_120V_Value.Excitation_voltage7, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current8", "double", "A", CTP_120V_Value.Excitation_current8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage8", "double", "V", CTP_120V_Value.Excitation_voltage8, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current9", "double", "A", CTP_120V_Value.Excitation_current9, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage9", "double", "V", CTP_120V_Value.Excitation_voltage9, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_current10", "double", "A", CTP_120V_Value.Excitation_current10, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Excitation_voltage10", "double", "V", CTP_120V_Value.Excitation_voltage10, "null");
    }

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
