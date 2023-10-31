/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 15:33:44
 * @LastEditTime: 2023-07-28 17:20:40
 * @LastEditors:
 */
#include "interface.h"

#include "public.h"
#include "../Protocol/DS_2000D.h"
#include "../Protocol/FH_ai_6000h.h"
#include "../Protocol/FH_ai_6000hl.h"
#include "../Protocol/FH_ai_6000r.h"
#include "../Protocol/FH_ai_6106s.h"
#include "../Protocol/FH_ai_6301.h"
#include "../Protocol/HCYZ_iv.h"
#include "../Protocol/jh6000.h"
#include "../Protocol/JYR_20s.h"
#include "../Protocol/JYR_40s.h"
#include "../Protocol/FH_ai_6310B.h"
#include "../Protocol/JYL_100B.h"
#include "../Protocol/FH_ai_6310L.h"
#include "../Protocol/JYK_I.h"
#include "../Protocol/HLC5501.h"
#include "../Protocol/BZC3395.h"
#include "../Protocol/DDC8910.h"
#include "../Protocol/JYT_A_V0.h"
#include "../Protocol/JYT_A_V1.h"
#include "../Protocol/JYT_A_V2.h"
#include "../Protocol/BBC6638.h"
#include "../Protocol/SD_HVM_5000.h"
#include "../Protocol/SD_Z_VI.h"
#include "../Protocol/FH_ai_6600C.h"
#include "../Protocol/JYW6400_DC.h"
#include "../Protocol/JYW6400_IM.h"
#include "../Protocol/JYR_40C.h"
#include "../Protocol/JHLK_100.h"
#include "../Protocol/JHMD3_jh6000.h"
#include "../Protocol/JYC.h"
#include "../Protocol/TD_3310C_YZFJ.h"
#include "../Protocol/TD_3310C_ZK.h"
#include "../Protocol/TD_3310C_ZLDZ.h"
#include "../Protocol/JYW6100.h"
#include "../Protocol/JYR_40D.h"
#include "../Protocol/FH_ai_6301B.h"
#include "../Protocol/FH_IDCE_2415CT.h"
#include "../Protocol/PDT_840.h"
#include "../Protocol/CTP_120.h"
#include "../Protocol/HV9003.h"
#include "../Protocol/QGDW_5_19.h"
#include "../Protocol/QGDW_5_8.h"
#include "../Protocol/JD11.h"


INTERFACE_InfoType INTERFACE_Info;
static char returnJsonDataBuff1[2000];

void InterfaceJsonBuff(char *jsonBuff)
{
    /* 加华 jh6000 SF6检测器 */
    if (NULL != strstr((char *)jsonBuff, "JH6000")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JH6000;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6106S")) {    /* 泛华 避雷器*/
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6106S;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6310LD")) {   /* 泛华 回来电阻 */
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6310LD;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6301")) { /* 泛华 地阻 */
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6301;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6000K")) {    /* 泛华 介损 */
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6000K;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6000HL")) {   /* 泛华  介损 */
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6000HL;
    } else if (NULL != strstr((char *)jsonBuff, "JYR_40S")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYR_40S;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6000R")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6000R;
    } else if (NULL != strstr((char *)jsonBuff, "HCYZ_IV")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_HCYZ_IV;
    } else if (NULL != strstr((char *)jsonBuff, "JYR_20S")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYR_20S;
    } else if (NULL != strstr((char *)jsonBuff, "DS_2000D")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_DS_2000D;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6000H")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6000H;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6310B")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6310B;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6310L")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6310L;
    } else if (NULL != strstr((char *)jsonBuff, "HV9003")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_HV9003;
    } else if (NULL != strstr((char *)jsonBuff, "JYL_100B")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYL_100B;
    } else if (NULL != strstr((char *)jsonBuff, "JYK_I")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYL_I;
    } else if (NULL != strstr((char *)jsonBuff, "HLC5501")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_HLC5501;
    } else if (NULL != strstr((char *)jsonBuff, "BZC3395")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_BZC3395;
    } else if (NULL != strstr((char *)jsonBuff, "DDC8910")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_DDC8910;
    } else if (NULL != strstr((char *)jsonBuff, "JYT_A_V0")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYT_A_V0;
    } else if (NULL != strstr((char *)jsonBuff, "JYT_A_V1")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYT_A_V1;
    } else if (NULL != strstr((char *)jsonBuff, "JYT_A_V2")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYT_A_V2;
    } else if (NULL != strstr((char *)jsonBuff, "BBC6638")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_BBC6638;
    } else if (NULL != strstr((char *)jsonBuff, "SD_HVM_5000")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_SD_HVM_5000;
    } else if (NULL != strstr((char *)jsonBuff, "SD_Z_VI")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_SD_Z_VI;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6600C")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6600C;
    } else if (NULL != strstr((char *)jsonBuff, "JYW6400_DC")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYW6400_DC;
    } else if (NULL != strstr((char *)jsonBuff, "JYW6400_IM")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYW6400_IM;
    } else if (NULL != strstr((char *)jsonBuff, "JYR_40C")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYR_40C;
    } else if (NULL != strstr((char *)jsonBuff, "JHLK_100")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JHLK_100;
    }   else if (NULL != strstr((char *)jsonBuff, "JHMD3")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JHMD3;
    } else if (NULL != strstr((char *)jsonBuff, "JYC")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYC;
    } else if (NULL != strstr((char *)jsonBuff, "TD_3310C_YZFJ")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_TD_3310C_YZFJ;
    } else if (NULL != strstr((char *)jsonBuff, "TD_3310C_ZK")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_TD_3310C_ZK;
    }  else if (NULL != strstr((char *)jsonBuff, "TD_3310C_ZLDZ")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_TD_3310C_ZLDZ;
    }  else if (NULL != strstr((char *)jsonBuff, "JYW6100")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYW6100;
    }   else if (NULL != strstr((char *)jsonBuff, "JYR_40D")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JYR_40D;
    } else if (NULL != strstr((char *)jsonBuff, "AI_6301B")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_AI_6301B;
    } else if (NULL != strstr((char *)jsonBuff, "IDCE_2415CT")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_FH_IDCE_2415CT;
    } else if (NULL != strstr((char *)jsonBuff, "PDT_840")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_PDT_840;
    } else if (NULL != strstr((char *)jsonBuff, "CTP_120")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_CTP_120;
    } else if (NULL != strstr((char *)jsonBuff, "HV9003")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_HV9003;
    } else if (NULL != strstr((char *)jsonBuff, "QGDW_5_19")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_QGDW_5_19;
    } else if (NULL != strstr((char *)jsonBuff, "QGDW_5_8")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_QGDW_5_8;
    } else if (NULL != strstr((char *)jsonBuff, "JD11")) {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_JD11;
    }


    else {
        INTERFACE_Info.DeviceCode = INTERFACE_DEVICE_CODE_NULL;
    }
}


/**
 * @brief           下发报文装载
 *
 * @param jsonBuff  仪器名称
 * @param cnt       采集次数
 * @return char*    下发报文内容
 */
unsigned char *InterfaceJsonMagLoading(unsigned char *jsonBuff, int32_t cnt, int baud)
{
    // LOGE("InterfaceJsonMagLoading==  %d",cnt);
    char *str;
    cJSON *cjson_test = NULL;
    cJSON *cjson_data = NULL;

    char dataMsg[200];

    unsigned int size;
    memset(dataMsg, 0, sizeof(dataMsg));

    INTERFACE_Info.sendMsg.comMode = "RS232";
    INTERFACE_Info.sendMsg.baud = 9600;
    INTERFACE_Info.sendMsg.stopBit = 1;
    INTERFACE_Info.sendMsg.dataBits = 8;
    INTERFACE_Info.sendMsg.checkDigit = "None";
    INTERFACE_Info.sendMsg.dataMsg = dataMsg;
    INTERFACE_Info.sendMsg.dataFormat = "HEX";

    memset(INTERFACE_Info.sendDataBuff, 0, sizeof(INTERFACE_Info.sendDataBuff));

    InterfaceJsonBuff(jsonBuff);
    switch (INTERFACE_Info.DeviceCode) {
        case INTERFACE_DEVICE_CODE_NULL:
            return NULL;

        case INTERFACE_DEVICE_CODE_JH6000:
            /* 要先获取数据条数 */
            size = JH6000_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 115200;
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6106S:
            size = FH_ai_6106sReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6310LD:
//      Loop_ResistanceReadData();
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6301:
            size = FH_ai_6301ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6000K:
//      FH_ai_6000kReadData();
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6000HL:
            size = FH_ai_6000hlReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_JYR_40S:
            size = JYR_40sReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6000R:
            size = FH_ai_6000rReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        /* 设备主动上报数据 所以不用发命令 */
        case INTERFACE_DEVICE_CODE_HCYZ_IV:
            size = 0;
            break;

        case INTERFACE_DEVICE_CODE_DS_2000D:
            size = DS_2000DReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_JYR_20S:
            size = JYR_20sReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6000H:
            size = FH_ai_6000hReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6310B:
            size = FH_ai_6310bReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6310L:
            size = FH_ai_6310LReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        // case INTERFACE_DEVICE_CODE_HV9003:
        //     break;

        case INTERFACE_DEVICE_CODE_JYL_100B:
            size = JYL_100BReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_JYL_I:
            size = JYK_IReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 19200;
            break;

        case INTERFACE_DEVICE_CODE_HLC5501:
            size = HLC5501ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 4800;
            break;

        case INTERFACE_DEVICE_CODE_BZC3395:
            size = BZC3395ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 4800;
            break;

        case INTERFACE_DEVICE_CODE_DDC8910:
            size = DDC8910ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 4800;
            break;

        case INTERFACE_DEVICE_CODE_JYT_A_V0:
            size = JYT_A_V0ReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_JYT_A_V1:
            size = JYT_A_V1ReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_JYT_A_V2:
            size = JYT_A_V2ReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_BBC6638:
            size = BBC6638ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 4800;
            break;

        case INTERFACE_DEVICE_CODE_SD_HVM_5000:
            size = SD_HVM_5000ReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_SD_Z_VI:
            size = SD_Z_VIReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_FH_AI_6600C:
            size = FH_ai_6600CReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = baud;
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;

        case INTERFACE_DEVICE_CODE_JYW6400_DC:
            //size = FH_ai_6600CReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);/
            break;

        case INTERFACE_DEVICE_CODE_JYW6400_IM:
            //size = FH_ai_6600CReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);/
            break;

        case INTERFACE_DEVICE_CODE_JYR_40C:
            size = JYR_40CReadData(INTERFACE_Info.sendMsg.dataMsg);
            break;

        case INTERFACE_DEVICE_CODE_JHLK_100:
            /* 要先获取数据条数 */
            size = JHLK_100_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 115200;
            break;

        case INTERFACE_DEVICE_CODE_JHMD3:
            /* 要先获取数据条数 */
            size = JHMD3_jh6000_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 115200;
            break;
        case INTERFACE_DEVICE_CODE_JYC:
            size = JYC_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_TD_3310C_YZFJ:
            size = TD_3310C_YZFJ_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_TD_3310C_ZK:
            size = TD_3310C_ZK_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_TD_3310C_ZLDZ:
            size = TD_3310C_ZLDZ_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_JYW6100:
            size = JYW6100ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_JYR_40D:
            size = JYR_40DReadData(INTERFACE_Info.sendMsg.dataMsg);
            INTERFACE_Info.sendMsg.baud = 9600;
            break;
        case INTERFACE_DEVICE_CODE_FH_AI_6301B:
            size = FH_ai_6301BReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;
        case INTERFACE_DEVICE_CODE_FH_IDCE_2415CT:
            size = FH_IDCE_2415CTReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            INTERFACE_Info.sendMsg.baud = 19200;
            break;
        case INTERFACE_DEVICE_CODE_PDT_840:
            size = PDT_840ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;
        case INTERFACE_DEVICE_CODE_CTP_120:
            size = CTP_120ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            INTERFACE_Info.sendMsg.baud = 19200;
            break;
        case INTERFACE_DEVICE_CODE_HV9003:
            size = HV9003_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;
        case INTERFACE_DEVICE_CODE_QGDW_5_19:
            size = QGDW_5_19_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;
        case INTERFACE_DEVICE_CODE_QGDW_5_8:
            size = QGDW_5_8_ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            break;
        case INTERFACE_DEVICE_CODE_JD11:
            size = JD11ReadData(INTERFACE_Info.sendMsg.dataMsg, cnt);
            INTERFACE_Info.sendMsg.dataFormat = "ASCLL";
            INTERFACE_Info.sendMsg.baud = 2400;
            break;


        default:
            return NULL;
    }

    INTERFACE_Info.sendMsg.dataSize = size;

    /* 创建一个JSON数据对象(链表头结点) */
    cjson_test = cJSON_CreateObject();

    /* 添加一条整数类型的JSON数据(添加一个链表节点) */
    cJSON_AddNumberToObject(cjson_test, "all", 1);

    /* 添加一条整数类型的JSON数据(添加一个链表节点) */
    cJSON_AddNumberToObject(cjson_test, "cur", 1);

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();

    cJSON_AddStringToObject(cjson_data, "comMode", INTERFACE_Info.sendMsg.comMode);
    cJSON_AddNumberToObject(cjson_data, "baud", INTERFACE_Info.sendMsg.baud);
    cJSON_AddNumberToObject(cjson_data, "stopBit", INTERFACE_Info.sendMsg.stopBit);
    cJSON_AddNumberToObject(cjson_data, "dataBits", INTERFACE_Info.sendMsg.dataBits);
    cJSON_AddStringToObject(cjson_data, "checkDigit", INTERFACE_Info.sendMsg.checkDigit);
    cJSON_AddStringToObject(cjson_data, "dataMsg", INTERFACE_Info.sendMsg.dataMsg);
    cJSON_AddStringToObject(cjson_data, "dataFormat", INTERFACE_Info.sendMsg.dataFormat);
    cJSON_AddNumberToObject(cjson_data, "dataSize", INTERFACE_Info.sendMsg.dataSize);


    cJSON_AddItemToObject(cjson_test, "data", cjson_data);
    /* 添加一条整数类型的JSON数据(添加一个链表节点) */
    cJSON_AddNumberToObject(cjson_test, "code", 1);

    str = cJSON_PrintUnformatted(cjson_test);
//    printf("%s\r\n", str);

    memcpy(INTERFACE_Info.sendDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_test);

    return INTERFACE_Info.sendDataBuff;
}


/**
 * @brief 报文解析
 *
 * @param dataBuff      报文内容
 * @param size          报文字节数
 * @param dataFormat    报文格式
 * @return char*        返回app所需json数据
 */
unsigned char *InterfaceDeviceDataAnalysis(unsigned char *dataBuff, int32_t size)
{
    // LOGE("InterfaceDeviceDataAnalysis=== %s",dataBuff);

    // for (uint16_t i = 0; i < size; i++)
    // {
    //     printf("InterfaceDeviceDataAnalysis %x\n", dataBuff[i]);
    // }
    unsigned char hexbuff[500];
    if (strstr(INTERFACE_Info.sendMsg.dataFormat, "HEX") != NULL) {
        PUBLIC_AscllToHex(hexbuff, dataBuff, strlen(dataBuff));
        printf("InterfaceDeviceDataAnalysis HEX %d \n", strlen(dataBuff) / 2);
        for (int i = 0; i < (strlen(dataBuff) / 2); i++) {
            printf("%02x  ", hexbuff[i]);
        }
        printf("InterfaceDeviceDataAnalysis HEX  end\n");
    } else {
        printf("InterfaceDeviceDataAnalysis ASCLL%s\n", dataBuff);
    }

    memset(returnJsonDataBuff1, 0, sizeof(returnJsonDataBuff1));
    switch (INTERFACE_Info.DeviceCode) {
        case INTERFACE_DEVICE_CODE_NULL:
            return NULL;

        case INTERFACE_DEVICE_CODE_JH6000:
            return JH6000_RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6106S:
            return FH_ai_6106sRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6310LD:
        //      return Loop_ResistanceRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6301:
            return FH_ai_6301RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6000K:
        //      return FH_ai_6000kRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6000HL:
            return FH_ai_6000hlRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_JYR_40S:
            return JYR_40sRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6000R:
            return FH_ai_6000rRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_HCYZ_IV:
            return HCYZ_ivRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_DS_2000D:
            return DS_2000DRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_JYR_20S:
            return JYR_20sRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6000H:
            return FH_ai_6000hRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6310B:
            return FH_ai_6310bRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6310L:
            return FH_ai_6310LRecvMessage(dataBuff, size);

        // case INTERFACE_DEVICE_CODE_HV9003:
        // //return HV9003RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_JYL_100B:
            return JYL_100BRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYL_I:
            return JYK_IRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_HLC5501:
            return HLC5501RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_BZC3395:
            return BZC3395RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_DDC8910:
            return DDC8910RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYT_A_V0:
            return JYT_A_V0RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYT_A_V1:
            return JYT_A_V1RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYT_A_V2:
            return JYT_A_V2RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_BBC6638:
            return BBC6638RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_SD_HVM_5000:
            return SD_HVM_5000RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_SD_Z_VI:
            return SD_Z_VIRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6600C:
            return FH_ai_6600CRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_JYW6400_DC:
            return JYW6400_DCRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYW6400_IM:
            return JYW6400_IMRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYR_40C:
            return JYR_40CRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JHLK_100:
            return JHLK_100_RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JHMD3:
            return JHMD3_jh6000_RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYC:
            return JYR_40CRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYW6100:
            return JYW6100RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_JYR_40D:
            return JYR_40DRecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_FH_AI_6301B:
            return FH_ai_6301BRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_FH_IDCE_2415CT:
            return FH_IDCE_2415CTRecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_PDT_840:
            return PDT_840RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_CTP_120:
            return CTP_120RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_HV9003:
            return HV9003_RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_QGDW_5_19:
            return QGDW_5_19_RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_QGDW_5_8:
            return QGDW_5_8_RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_JD11:
            return JD11RecvMessage(dataBuff, size);

        case INTERFACE_DEVICE_CODE_TD_3310C_ZLDZ:
            return TD_3310C_ZLDZ_RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_TD_3310C_YZFJ:
            return TD_3310C_YZFJ_RecvMessage(hexbuff, size);

        case INTERFACE_DEVICE_CODE_TD_3310C_ZK:
            return TD_3310C_ZK_RecvMessage(hexbuff, size);
        default:
            break;
    }
}




