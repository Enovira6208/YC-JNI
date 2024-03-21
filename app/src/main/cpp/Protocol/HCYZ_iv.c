/*
 * HCYZ_iv.c
 * @Author       : chuhouzhong
 * @Date         : 2021年9月23日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 保定华创  有载分接开关   仪器主动上报数据*/
#include "HCYZ_iv.h"
#include "time.h"
static char returnJsonDataBuff[5000];
HCYZ_ivMessageValueType HCYZ_ivMessageValue[3];

char *HCYZ_ivBleSend(void);


/*
 *  @ brief 接收数据
 */
char *HCYZ_ivRecvMessage(uint8_t *buff, uint16_t size)
{
//  uint16_t len;
    int dd = 0;
    for (int k = 0; k < size; k++) {
        if (buff[k] == 0x68) {
            dd = k;
            break;
        }
    }
    printf("%d\n", dd);
    if (dd == 0 && buff[0] != 0x68) {
        return NULL;
    }
    printf("dd:%d\n", dd);
    HCYZ_ivMessageType *buffer = (HCYZ_ivMessageType *) (buff + dd);
    HCYZ_ivMessageDataType *recv = (HCYZ_ivMessageDataType *) buffer;

    printf("%x\n", recv->APDU[0].Head);
    printf("%x\n", recv->APDU[0].Len);
    if (recv->Head != 0x68)
        return NULL;

    //  len = (recv->Len[0] << 8) | recv->Len[1];
    /* 判断尾 */
    if (recv->Tail != 0x16)
        return NULL;

    for (uint8_t i = 0; i < 3; i++) {

        HCYZ_ivMessageValue[i].PhasePosition = (recv->APDU[i].Obj[0].Value[0] << 24)
                                               | (recv->APDU[i].Obj[0].Value[1] << 18) | (recv->APDU[i].Obj[0].Value[2] << 8)
                                               | (recv->APDU[i].Obj[0].Value[3]);

        HCYZ_ivMessageValue[i].Type = (recv->APDU[i].Obj[1].Value[0] << 24)
                                      | (recv->APDU[i].Obj[1].Value[1] << 18) | (recv->APDU[i].Obj[1].Value[2] << 8)
                                      | (recv->APDU[i].Obj[1].Value[3]);

        HCYZ_ivMessageValue[i].Resistance = Char2Float2(recv->APDU[i].Obj[2].Value);
        for (int k = 0; k < 4; k++) {
            printf("va:%x\n", recv->APDU[i].Obj[2].Value[k]);
        }
        HCYZ_ivMessageValue[i].SwitchingTime = Char2Float2(recv->APDU[i].Obj[3].Value);
    }

    /* 发送数据 */
    return HCYZ_ivBleSend();
}

/*
 * @ 通过WIFI发送数据
 */
char *HCYZ_ivBleSend(void)
{
    char *str;
    cJSON *cjson_all = NULL;
    cjson_all = cJSON_CreateObject();

    cJSON_AddNumberToObject(cjson_all, "transitionResistance1_A", HCYZ_ivMessageValue[0].Resistance);
    cJSON_AddNumberToObject(cjson_all, "transitionResistance1_B", HCYZ_ivMessageValue[1].Resistance);
    cJSON_AddNumberToObject(cjson_all, "transitionResistance1_C", HCYZ_ivMessageValue[2].Resistance);
    cJSON_AddNumberToObject(cjson_all, "transitionTime_t1_A", HCYZ_ivMessageValue[0].SwitchingTime);
    cJSON_AddNumberToObject(cjson_all, "transitionTime_t1_B", HCYZ_ivMessageValue[1].SwitchingTime);
    cJSON_AddNumberToObject(cjson_all, "transitionTime_t1_C", HCYZ_ivMessageValue[2].SwitchingTime);

    str = cJSON_PrintUnformatted(cjson_all);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));
    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_all);

    return returnJsonDataBuff;
}
