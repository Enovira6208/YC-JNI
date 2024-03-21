/*
 * JYR_40s.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月11日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 变压器直流电阻 */
/* 金源直流电阻 */
#include "JYR_40s.h"

static char returnJsonDataBuff[1000];

JYR_40sValueType JYR_40sValue;
JYR_40sAnalyEnum JYR_40sAnaly;

char *JYR_40sSend(void);

/*
 *  @ brief 读取仪器数据
 */
uint16_t JYR_40sReadData(uint8_t *ascllBuff)
{
    uint8_t hexBuff[10];

    hexBuff[0] = 0x7E;
    hexBuff[1] = 0x45;
    hexBuff[2] = 0x46;
    hexBuff[3] = 0x30;
    hexBuff[4] = 0x31;
    hexBuff[5] = 0x49;
    hexBuff[6] = 0x35;
    hexBuff[7] = 0x0D;

    PUBLIC_HexToAscll(ascllBuff, hexBuff, 8);

    return 16;
}

/**
 * @brief
 *
 */
double JYR_40sCount(uint8_t *buff)
{
    uint8_t ascll[9];
    uint8_t decimal = 0;
    uint8_t j = 0;
    double value = 0;

    memset(ascll, 0, 9);
    for (uint8_t i = 0; i < 9; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
        } else if (buff[i] == '.') {
            decimal = i;
        }
    }
    for (uint8_t k = 0; k < j; k++) {
        value += ascll[k] * pow(10, decimal - k - 1);
    }
    return value;
}

/*
 *  @ brief 接收数据
 */
char *JYR_40sRecvMessage(uint8_t *buff, uint16_t size)
{
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x7e) {
            dd = k; break;
        }
    }
    if (dd == 0 && buff[0] != 0x7e) {
        return NULL;
    }

    JYR_40sMessageType *recv = (JYR_40sMessageType *)(buff + dd);
    JYR_40sDataType Data;

    JYR_40sValue.Way = recv->Way;
    switch (recv->Way) {
        /* 单通道 */
        case JYR_40S_WAY_SUNGLE_CHANNEL:
            memcpy(&Data.AoSign, recv->Data, sizeof(JYR_40sDataType));
            JYR_40sAnaly = JYR_40_ANALY_1;
            break;

        /* 三相 */
        case JYR_40S_WAY_YN_THREE_PHASE:
            memcpy(&Data.AoSign, recv->Data, sizeof(JYR_40sDataType));
            JYR_40sAnaly = JYR_40_ANALY_3;
            break;

        /* 三相补偿 */
        case JYR_40S_WAY_YN_THREE_PHASE_COMPEN:
            JYR_40sValue.Sign = recv->Data[0];
            /* 数据位中  最开始的为 阶段 标志 */
            if (recv->Data[0] == 0x30) {
                JYR_40sAnaly = JYR_40_ANALY_2;
            } else if (recv->Data[0] == 0x31) {
                JYR_40sAnaly = JYR_40_ANALY_3;
            } else {
                JYR_40sAnaly = JYR_40_ANALY_3;
            }
            memcpy(&Data.AoSign, recv->Data + 1, sizeof(JYR_40sDataType));
            break;

        /* 助磁 */
        case JYR_40S_WAY_YND11:
            memcpy(&Data.AoSign, recv->Data, sizeof(JYR_40sDataType));
            JYR_40sAnaly = JYR_40_ANALY_4;
            break;

        /* YN选相 */
        case JYR_40S_WAY_YN_PHASE_SELECTION:
            memcpy(&Data.AoSign, recv->Data, sizeof(JYR_40sDataType));
            JYR_40sAnaly = JYR_40_ANALY_3;
            break;

        /* DY选相 */
        case JYR_40S_WAY_DY_PHASE_SELECTION:
            memcpy(&Data.AoSign, recv->Data, sizeof(JYR_40sDataType));
            JYR_40sAnaly = JYR_40_ANALY_3;
            break;
    }


    switch (JYR_40sAnaly) {
        case JYR_40_ANALY_1:
            JYR_40sValue.Ao = atof((char *)Data.Ao);
            JYR_40sValue.AoU[0] = Data.Ao[6];
            if (JYR_40sValue.AoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.AoU[0], "mΩ", 4);
            } else if (JYR_40sValue.AoU[0] == 0x20) {
                memcpy(&JYR_40sValue.AoU[0], "Ω", 4);
            } else if (JYR_40sValue.AoU[0] == 0x75) {
                memcpy(&JYR_40sValue.AoU[0], "uΩ", 4);
            }
            break;

        case JYR_40_ANALY_2:
            JYR_40sValue.Ao = atof((char *)Data.Ao);
            JYR_40sValue.Bo = atof((char *)Data.Bo);
            JYR_40sValue.Co = atof((char *)Data.Co);
            JYR_40sValue.AoU[0] = Data.Ao[6];
            if (JYR_40sValue.AoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.AoU[0], "mΩ", 4);
            } else if (JYR_40sValue.AoU[0] == 0x20) {
                memcpy(&JYR_40sValue.AoU[0], "Ω", 4);
            } else if (JYR_40sValue.AoU[0] == 0x75) {
                memcpy(&JYR_40sValue.AoU[0], "uΩ", 4);
            }
            JYR_40sValue.BoU[0] = Data.Bo[6];
            if (JYR_40sValue.BoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.BoU[0], "mΩ", 4);
            } else if (JYR_40sValue.BoU[0] == 0x20) {
                memcpy(&JYR_40sValue.BoU[0], "Ω", 4);
            } else if (JYR_40sValue.BoU[0] == 0x75) {
                memcpy(&JYR_40sValue.BoU[0], "uΩ", 4);
            }
            break;

        case JYR_40_ANALY_3:
            JYR_40sValue.Ao = atof((char *)Data.Ao);
            JYR_40sValue.Bo = atof((char *)Data.Bo);
            JYR_40sValue.Co = atof((char *)Data.Co);
            JYR_40sValue.UnbalanceH = atof((char *)Data.UnbalanceH);
            JYR_40sValue.AoU[0] = Data.Ao[6];
            if (JYR_40sValue.AoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.AoU[0], "mΩ", 4);
            } else if (JYR_40sValue.AoU[0] == 0x20) {
                memcpy(&JYR_40sValue.AoU[0], "Ω", 4);
            } else if (JYR_40sValue.AoU[0] == 0x75) {
                memcpy(&JYR_40sValue.AoU[0], "uΩ", 4);
            }
            JYR_40sValue.BoU[0] = Data.Bo[6];
            if (JYR_40sValue.BoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.BoU[0], "mΩ", 4);
            } else if (JYR_40sValue.BoU[0] == 0x20) {
                memcpy(&JYR_40sValue.BoU[0], "Ω", 4);
            } else if (JYR_40sValue.BoU[0] == 0x75) {
                memcpy(&JYR_40sValue.BoU[0], "uΩ", 4);
            }
            JYR_40sValue.CoU[0] = Data.Co[6];
            if (JYR_40sValue.CoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.CoU[0], "mΩ", 4);
            } else if (JYR_40sValue.CoU[0] == 0x20) {
                memcpy(&JYR_40sValue.CoU[0], "Ω", 4);
            } else if (JYR_40sValue.CoU[0] == 0x75) {
                memcpy(&JYR_40sValue.CoU[0], "uΩ", 4);
            }
            break;

        case JYR_40_ANALY_4:
            JYR_40sValue.Ao = atof((char *)Data.Ao);
            JYR_40sValue.Bo = atof((char *)Data.Bo);
            JYR_40sValue.Co = atof((char *)Data.Co);
            JYR_40sValue.UnbalanceH = atof((char *)Data.UnbalanceH);
            JYR_40sValue.Ca = atof((char *)Data.Ca);
            JYR_40sValue.Ab = atof((char *)Data.Ab);
            JYR_40sValue.Bc = atof((char *)Data.Bc);
            JYR_40sValue.UnbalanceL = atof((char *)Data.UnbalanceL);
            JYR_40sValue.AoU[0] = Data.Ao[6];
            if (JYR_40sValue.AoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.AoU[0], "mΩ", 4);
            } else if (JYR_40sValue.AoU[0] == 0x20) {
                memcpy(&JYR_40sValue.AoU[0], "Ω", 4);
            } else if (JYR_40sValue.AoU[0] == 0x75) {
                memcpy(&JYR_40sValue.AoU[0], "uΩ", 4);
            }
            JYR_40sValue.BoU[0] = Data.Bo[6];
            if (JYR_40sValue.BoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.BoU[0], "mΩ", 4);
            } else if (JYR_40sValue.BoU[0] == 0x20) {
                memcpy(&JYR_40sValue.BoU[0], "Ω", 4);
            } else if (JYR_40sValue.BoU[0] == 0x75) {
                memcpy(&JYR_40sValue.BoU[0], "uΩ", 4);
            }
            JYR_40sValue.CoU[0] = Data.Co[6];
            if (JYR_40sValue.CoU[0] == 0x6d) {
                memcpy(&JYR_40sValue.CoU[0], "mΩ", 4);
            } else if (JYR_40sValue.CoU[0] == 0x20) {
                memcpy(&JYR_40sValue.CoU[0], "Ω", 4);
            } else if (JYR_40sValue.CoU[0] == 0x75) {
                memcpy(&JYR_40sValue.CoU[0], "uΩ", 4);
            }
            break;
    }

    /* 发送数据 */
    return JYR_40sSend();

}

/*
 * @ brief 发送数据
 */
char *JYR_40sSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_all = cJSON_CreateObject();
    if (JYR_40sAnaly == JYR_40_ANALY_1) {
        cJSON_AddNumberToObject(cjson_all, "resistance_A", JYR_40sValue.Ao);
    } else {
        cJSON_AddNumberToObject(cjson_all, "resistance_A", JYR_40sValue.Ao);
        cJSON_AddNumberToObject(cjson_all, "resistance_B", JYR_40sValue.Bo);
        cJSON_AddNumberToObject(cjson_all, "resistance_C", JYR_40sValue.Co);
    }

    if (JYR_40sAnaly == JYR_40_ANALY_3) {
        cJSON_AddNumberToObject(cjson_all, "unbalance", JYR_40sValue.UnbalanceH);
    } else if (JYR_40sAnaly == JYR_40_ANALY_4) {
        cJSON_AddNumberToObject(cjson_all, "low_voltage_Unbalance", JYR_40sValue.UnbalanceL);
        cJSON_AddNumberToObject(cjson_all, "high_voltage_Unbalance", JYR_40sValue.UnbalanceH);
    }

    str = cJSON_PrintUnformatted(cjson_all);
    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}

