/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-04-20 14:41:18
 * @LastEditTime: 2022-09-02 11:20:15
 * @LastEditors:
 */

/* 泛华介损6000H */
#include "FH_ai_6000h.h"

FH_ai_6000hValueType FH_ai_6000hValue;

char *FH_ai_6000hWifiSend(void);


/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6000hReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1)
    {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'R';
        buff[4] = 'E';
        buff[5] = 'A';
        buff[6] = 'D';
        buff[7] = '\r';
        buff[8] = '\n';
        return 9;
    }
    else if (cnt == 2)
    {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'O';
        buff[4] = 'V';
        buff[5] = 'E';
        buff[6] = 'R';
        buff[7] = '\r';
        buff[8] = '\n';
        return 9;
    }
    return 0;
}

/*
 *  @ brief 字符串解析
 */
double FH_ai_6000hStrAnaly(uint8_t *buff)
{
    uint8_t temp_array[6];
    uint8_t array[5];
    uint8_t cnt, j = 0, temp = 0;
    double value = 0;

    temp_array[0] = buff[4];
    temp_array[1] = buff[5];
    temp_array[2] = buff[2];
    temp_array[3] = buff[3];
    temp_array[4] = buff[0];
    temp_array[5] = buff[1];

    memset(array, 0, 5);
    for (uint8_t i = 0; i <= 4; i++)
    {
        if (temp_array[i] == 'A')
        {
            cnt = i;
        }
        else if (temp_array[i] >= 'B' && temp_array[i] <= 'F')
        {
            temp++;
        }
        else if (temp_array[i] >= '0' && temp_array[i] <= '9')
        {
            array[j] = temp_array[i] - 48;
            j++;
        }
    }

    for (uint8_t i = 0; i < j; i++)
    {
        value += array[i] * pow(10, cnt - i - 1 - temp);
    }
    return value;
}

/*
*   @ brief 解析单位
*/
void FH_ai_6000hStrAnaly_Cu(uint8_t buff, uint8_t index)
{
    if (((buff - 48) & 0x03) == 0)
    {
        FH_ai_6000hValue.Param[index].Cu[0] = 'p';
    }
    else if (((buff - 48) & 0x03) == 1)
    {
        FH_ai_6000hValue.Param[index].Cu[0] = 'n';
    }
    else if (((buff - 48) & 0x03) == 2)
    {
        FH_ai_6000hValue.Param[index].Cu[0] = 'u';
    }
    FH_ai_6000hValue.Param[index].Cu[1] = 'F';
}

/*
*   @ brief 解析单位
*/
void FH_ai_6000hStrAnaly_DFu(uint8_t buff, uint8_t index)
{
    if (((buff - 48) & 0x03) == 0)
    {
        FH_ai_6000hValue.Param[index].DFu[0] = '%';
    }
    else if (((buff - 48) & 0x03) == 1)
    {
        FH_ai_6000hValue.Param[index].DFu[0] = ' ';
    }
    else if (((buff - 48) & 0x03) == 2)
    {
        FH_ai_6000hValue.Param[index].DFu[0] = 'k';
    }
}

/*
 *  @ brief 解析四通道数据
 */
double FH_ai_6000hStrAnaly_four(uint8_t *buff)
{
    uint8_t temp_array[6];
    uint8_t array[5];
    uint8_t cnt, j = 0, temp = 0;
    double value = 0;

    temp_array[0] = buff[4];
    temp_array[1] = buff[5];
    temp_array[2] = buff[2];
    temp_array[3] = buff[3];
    temp_array[4] = buff[0];
    temp_array[5] = buff[1];

    memset(array, 0, 5);
    cnt = temp_array[0] - 48;
    for (uint8_t i = 1; i <= 4; i++)
    {
        if (temp_array[i] >= 'A' && temp_array[i] <= 'F')
        {
            temp++;
        }
        else if (temp_array[i] >= '0' && temp_array[i] <= '9')
        {
            array[j] = temp_array[i] - 48;
            j++;
        }
    }

    for (uint8_t i = 0; i < j; i++)
    {
        value += array[i] * pow(10, cnt - i - 1 - temp);
    }
    return value;
}

/*
 *  @ brief 接收数据
 */
char *FH_ai_6000hRecvMessage(uint8_t *buff, uint16_t size)
{
    char cD[] = "CD";
    FH_ai_6000hMessageType *recv = (FH_ai_6000hMessageType *) buff;
    FH_ai_6000hMessageDataType messageData;

    memcpy(messageData.Name, recv->Data, sizeof(FH_ai_6000hMessageDataType));
    if (recv->Head != '#')
        return NULL;

    /*   memcmp返回0表示相等*/
    if (memcmp(recv->CD, cD, sizeof(recv->CD)) != 0)
        return NULL;



    /* ps 1 */
    //memcpy(FH_ai_6000hValue.Name, messageData.Name, 12);
    //memcpy(FH_ai_6000hValue.Time, messageData.Time, 16);

    /* D3002759  低地址在前 高地址在后  实际值为 59 27 00 D3*/

    if ((((messageData.Param[1] - 48) & 0x07 == 0)) || (((messageData.Param[1] - 48) & 0x07) == 1))
    {
        FH_ai_6000hValue.Mode = FH_AI_6000H_SINGLE;
    }
    else if (((messageData.Param[1] - 48) & 0x07) == 4)
    {
        FH_ai_6000hValue.Mode = FH_AI_6000H_TWO;
    }
    else if (((messageData.Param[1] - 48) & 0x07) == 2)
    {
        FH_ai_6000hValue.Mode = FH_AI_6000H_THREE;
    }
    else if (((messageData.Param[1] - 48) & 0x07) == 3)
    {
        FH_ai_6000hValue.Mode = FH_AI_6000H_FOUR;
    }


    switch (FH_ai_6000hValue.Mode)
    {
        /* 单通道 */
        case FH_AI_6000H_SINGLE:
            FH_ai_6000hValue.Param[0].C = FH_ai_6000hStrAnaly(messageData.Array[0].str);
            FH_ai_6000hValue.Param[0].DF = FH_ai_6000hStrAnaly(messageData.Array[1].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[0].str[1], 0);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[1].str[1], 0);
            break;

        /* 两通道 */
        case FH_AI_6000H_TWO:
            FH_ai_6000hValue.Param[0].C = FH_ai_6000hStrAnaly(messageData.Array[0].str);
            FH_ai_6000hValue.Param[0].DF = FH_ai_6000hStrAnaly(messageData.Array[1].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[0].str[1], 0);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[1].str[1], 0);

            FH_ai_6000hValue.Param[1].C = FH_ai_6000hStrAnaly(messageData.Array[2].str);
            FH_ai_6000hValue.Param[1].DF = FH_ai_6000hStrAnaly(messageData.Array[3].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[2].str[1], 1);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[3].str[1], 1);
            break;

        /* 三通道 */
        case FH_AI_6000H_THREE:
            FH_ai_6000hValue.Param[0].C = FH_ai_6000hStrAnaly(messageData.Array[0].str);
            FH_ai_6000hValue.Param[0].DF = FH_ai_6000hStrAnaly(messageData.Array[1].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[0].str[1], 0);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[1].str[1], 0);

            FH_ai_6000hValue.Param[1].C = FH_ai_6000hStrAnaly(messageData.Array[2].str);
            FH_ai_6000hValue.Param[1].DF = FH_ai_6000hStrAnaly(messageData.Array[3].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[2].str[1], 1);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[3].str[1], 1);

            FH_ai_6000hValue.Param[2].C = FH_ai_6000hStrAnaly(messageData.Array[4].str);
            FH_ai_6000hValue.Param[2].DF = FH_ai_6000hStrAnaly(messageData.Array[5].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[4].str[1], 2);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[5].str[1], 2);
            break;

        /* 四通道 */
        case FH_AI_6000H_FOUR:
            FH_ai_6000hValue.Param[0].C = FH_ai_6000hStrAnaly_four(messageData.Array[0].str);
            FH_ai_6000hValue.Param[0].DF = FH_ai_6000hStrAnaly_four(messageData.Array[1].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[0].str[1], 0);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[1].str[1], 0);

            FH_ai_6000hValue.Param[1].C = FH_ai_6000hStrAnaly_four(messageData.Array[2].str);
            FH_ai_6000hValue.Param[1].DF = FH_ai_6000hStrAnaly_four(messageData.Array[3].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[2].str[1], 1);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[3].str[1], 1);

            FH_ai_6000hValue.Param[2].C = FH_ai_6000hStrAnaly_four(messageData.Array[4].str);
            FH_ai_6000hValue.Param[2].DF = FH_ai_6000hStrAnaly_four(messageData.Array[5].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[4].str[1], 2);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[5].str[1], 2);

            FH_ai_6000hValue.Param[3].C = FH_ai_6000hStrAnaly_four(messageData.Array[6].str);
            FH_ai_6000hValue.Param[3].DF = FH_ai_6000hStrAnaly_four(messageData.Array[7].str);
            FH_ai_6000hStrAnaly_Cu(messageData.Array[6].str[1], 3);
            FH_ai_6000hStrAnaly_DFu(messageData.Array[7].str[1], 3);
            break;
    }
    /* 发送数据 */
    return FH_ai_6000hWifiSend();
}

/*
 * @ 通过蓝牙发送数据
 */
char *FH_ai_6000hWifiSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;


    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "AI_6000H");

    PUBLIC_JsonArrayLoading(cjson_array, 1, "testMode", "int", "null",  FH_ai_6000hValue.Mode, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "capacitance_A", "double", FH_ai_6000hValue.Param[0].Cu, FH_ai_6000hValue.Param[0].C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "dielectricLoss_A", "double", "%", FH_ai_6000hValue.Param[0].DF, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 4, "capacitance_B", "double", FH_ai_6000hValue.Param[1].Cu, FH_ai_6000hValue.Param[1].C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "dielectricLoss_B", "double", "%", FH_ai_6000hValue.Param[1].DF, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "capacitance_C", "double", FH_ai_6000hValue.Param[2].Cu, FH_ai_6000hValue.Param[2].C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 7, "dielectricLoss_C", "double", "%", FH_ai_6000hValue.Param[2].DF, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "capacitance_D", "double", FH_ai_6000hValue.Param[3].Cu, FH_ai_6000hValue.Param[3].C, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "dielectricLoss_D", "double", "%", FH_ai_6000hValue.Param[3].DF, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);

    str = cJSON_PrintUnformatted(cjson_data);
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);
    return returnJsonDataBuff;
}



