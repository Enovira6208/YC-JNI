/*
 * arrester.c
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

/* 避雷器协议 */
/* 泛华避雷器 */
#include "FH_ai_6103z.h"

static char returnJsonDataBuff[3000];
char *FH_ai_6103zBleSend(void);

FH_ai_6103z_Part1ValueType FH_ai_6103z_Part1Value;
FH_ai_6103z_Part2ValueType FH_ai_6103z_Part2Value;
FH_ai_6103z_Part3ValueType FH_ai_6103z_Part3Value;
FH_ai_6103z_Part4ValueType FH_ai_6103z_Part4Value;

uint16_t FH_ai_6103z_DataCnt = 0x3039;
uint16_t FH_ai_6103z_cnt = 0;

/*
 *  @ brief 读取仪器数据
 */
uint16_t FH_ai_6103zReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'R';
        buff[4] = 'M';
        buff[5] = '?';
        buff[6] = '?';
        buff[7] = '\r';
        buff[8] = '\n';
        FH_ai_6103z_cnt = 1;
        return 9;
    } else if (cnt == 2) {
        buff[0] = '#';
        buff[1] = '9';
        buff[2] = '9';
        buff[3] = 'R';
        buff[4] = 'M';
        if ((FH_ai_6103z_DataCnt & 0x00ff) % 16 == 0 && (FH_ai_6103z_DataCnt & 0x00ff)  > 16) {
            buff[5] = (FH_ai_6103z_DataCnt >> 8) - 1;
            buff[6] = (FH_ai_6103z_DataCnt & 0x00ff) + 9;
        } else {
            buff[5] = FH_ai_6103z_DataCnt >> 8;
            buff[6] = FH_ai_6103z_DataCnt & 0x00ff - 1;
        }
        buff[7] = '\r';
        buff[8] = '\n';
        FH_ai_6103z_cnt = 2;
        return 9;
    } else if (cnt == 3) {
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
 *  @ brief 解析第一部分
 */
void FH_ai_6103z1Analy(uint8_t *buff)
{
    uint32_t value;
    uint8_t array[20];
    FH_ai_6103z_Part1Type Part1;
    FH_ai_6103z_TimeType time;

    uint8_t str[10];
    int sign = 1;
    char temporary = 0;
    uint8_t cnt;
    uint8_t angleTemp;

    memcpy(&Part1.Format, buff, 40);

    FH_ai_6103z_Part1Value.Format = Part1.Format;

    memcpy(FH_ai_6103z_Part1Value.LineName, Part1.LineName, 8);

    value = (Part1.Time[3] << 24) | (Part1.Time[2] << 16)
            | (Part1.Time[1] << 8) | Part1.Time[0];
    time.Year  = (uint8_t)((value & 0xFC000000) >> 26);
    time.Month = (uint8_t)((value & 0x03C00000) >> 22);
    time.Date  = (uint8_t)((value & 0x003E0000) >> 17);
    time.Hours = (uint8_t)((value & 0x0001F000) >> 12);
    time.Minutes = (uint8_t)((value & 0x00000FC0) >> 6);
    time.Seconds = (uint8_t)(value & 0x0000003F);
    memcpy(array, &time.Year, sizeof(FH_ai_6103z_TimeType));
    for (uint8_t i = 0; i < 6; i++) {
        sprintf((char *)&FH_ai_6103z_Part1Value.Time[i * 2], "%02d", array[i]);
    }
    memset(array, 0, sizeof(array));
    value = 0;

    // sprintf((char*)&FH_ai_6103z_Part1Value.Number[0],"%02X", Part1.Number[2]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.Number[2],"%02X", Part1.Number[1]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.Number[4],"%02X", Part1.Number[0]);

    FH_ai_6103z_Part1Value.RS = (Part1RSEnum1)((uint8_t)((Part1.Byte16 & 0x18) >> 3));
    FH_ai_6103z_Part1Value.RP = (Part1RPEnum1)((uint8_t)(Part1.Byte16 & 0x07));
    FH_ai_6103z_Part1Value.Byte17 = Part1.WirelessStatus[0];

    // sprintf((char*)&FH_ai_6103z_Part1Value.FactryNum[0],"%02X", Part1.WirelessStatus[4]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.FactryNum[2],"%02X", Part1.WirelessStatus[3]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.FactryNum[4],"%02X", Part1.WirelessStatus[2]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.FactryNum[6],"%02X", Part1.WirelessStatus[1]);

    // sprintf((char*)&FH_ai_6103z_Part1Value.Voltage[0],"%02X", Part1.Voltage[0]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.Voltage[2],"%02X", Part1.Voltage[1]);
    // sprintf((char*)&FH_ai_6103z_Part1Value.Voltage[4],"%02X", Part1.Voltage[2]);

    value = (Part1.Freq[2] << 16) | (Part1.Freq[1] << 8) | Part1.Freq[0];
    FH_ai_6103z_Part1Value.Freq = value / 10000.00;
    value = 0;

    if ((Part1.Temp & 0x80) == 0x80) {
        FH_ai_6103z_Part1Value.Temp = (Part1.Temp & 0x7F) * (-1);
    } else {
        FH_ai_6103z_Part1Value.Temp = Part1.Temp & 0x7F;
    }

    FH_ai_6103z_Part1Value.MC = (Part1.Byte29 & 0x0C) >> 2;
    FH_ai_6103z_Part1Value.MP = Part1.Byte29 & 0x03;

    /* 补偿角计算  手动补偿 */
    for ( uint8_t n = 0; n < 3; n++) {
        memset(str, 0, sizeof(str));
        temporary = 0;

        angleTemp = Part1.Angle[n].A[0];
        sprintf((char *)&str[0], "%02X", angleTemp);
        angleTemp = Part1.Angle[n].A[1];
        sprintf((char *)&str[2], "%02X", angleTemp);
        angleTemp = Part1.Angle[n].A[2];
        sprintf((char *)&str[4], "%02X", angleTemp);

        for (uint8_t i = 0; i < 6;) {
            temporary = str[i];
            str[i] = str[i + 1];
            str[i + 1] = temporary;
            i += 2;
        }

        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        cnt = 0;
        for (uint8_t i = 0; i < 6; i++) {
            if (str[i] == 'C') {
                temporary++;
            } else if (str[i] == 'B') {
                sign = -1;
                temporary++;
            } else if (str[i] == 'A') {
                cnt = i - temporary;
            } else if (str[i] >= '0' && str[i] <= '9') {
                array[j] = str[i] - 0x30;
                j++;
            }
        }

        FH_ai_6103z_Part1Value.Angle[n].A = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part1Value.Angle[n].A += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part1Value.Angle[n].A = FH_ai_6103z_Part1Value.Angle[n].A * sign;
        memset(array, 0, sizeof(array));
    }

    /* 禁用补偿 */
    if (FH_ai_6103z_Part1Value.MC == 0) {
        switch (FH_ai_6103z_Part1Value.RP) {
            /* A */
            case 0:
                FH_ai_6103z_Part1Value.Angle[0].A = 0;
                FH_ai_6103z_Part1Value.Angle[1].A = 120;
                FH_ai_6103z_Part1Value.Angle[2].A = 240;
                break;

            /* B */
            case 1:
                FH_ai_6103z_Part1Value.Angle[0].A = 240;
                FH_ai_6103z_Part1Value.Angle[1].A = 0;
                FH_ai_6103z_Part1Value.Angle[2].A = 120;
                break;

            /* C */
            case 2:
                FH_ai_6103z_Part1Value.Angle[0].A = 120;
                FH_ai_6103z_Part1Value.Angle[1].A = 240;
                FH_ai_6103z_Part1Value.Angle[2].A = 0;
                break;

            /* AB */
            case 3:
                FH_ai_6103z_Part1Value.Angle[0].A = 30;
                FH_ai_6103z_Part1Value.Angle[1].A = 150;
                FH_ai_6103z_Part1Value.Angle[2].A = 270;
                break;

            /* BC */
            case 4:
                FH_ai_6103z_Part1Value.Angle[0].A = 90;
                FH_ai_6103z_Part1Value.Angle[1].A = 210;
                FH_ai_6103z_Part1Value.Angle[2].A = 330;
                break;

            /* ABC */
            case 5:
                FH_ai_6103z_Part1Value.Angle[0].A = 0;
                FH_ai_6103z_Part1Value.Angle[1].A = 0;
                FH_ai_6103z_Part1Value.Angle[2].A = 0;
                break;

        }
    }


    if ((Part1.Byte39 & 0x01) == 0x01) {
        FH_ai_6103z_Part1Value.REF = 0;
    } else if (((Part1.Byte39 & 0x0E) >> 1) != 0) {
        FH_ai_6103z_Part1Value.REF = 1;
    } else {
        FH_ai_6103z_Part1Value.REF = 2;
    }


    if ((Part1.Byte39 & 0x10) == 0x10) {
        FH_ai_6103z_Part1Value.DUT = 0;
    } else if (((Part1.Byte39 & 0xE0) >> 1) != 0) {
        FH_ai_6103z_Part1Value.DUT = 1;
    } else {
        FH_ai_6103z_Part1Value.DUT = 2;
    }
}

/*
 *  @ brief 解析第二部分
 */
void FH_ai_6103z2Analy(uint8_t *buff)
{
    memcpy(FH_ai_6103z_Part2Value.Data, buff, sizeof(FH_ai_6103z_Part2ValueType) - 1);
}

/*
 *  @ brief 解析第三部分
 */
void FH_ai_6103z3Analy(uint8_t *buff)
{
    uint8_t array[10];
    FH_ai_6103z_Part3Type *recv = (FH_ai_6103z_Part3Type *)buff;
    uint8_t cnt, temporary = 0;

    /* 参考幅度 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        for (uint8_t i = 0; i < 5; i++) {
            if ((recv->REF[n].str[i] >= '0') && (recv->REF[n].str[i] <= '9')) {
                array[j] = recv->REF[n].str[i] - 0x30;
                j++;
            } else if (recv->REF[n].str[i] == '.') {
                cnt = i;
            }
        }
        FH_ai_6103z_Part3Value.Data[n].Range = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part3Value.Data[n].Range += array[i] * pow(10, cnt - i - 1);
        }
        memset(array, 0, sizeof(array));
    }


    /* 电压谐波1 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        for (uint8_t i = 6; i < 10; i++) {
            if ((recv->REF[n].str[i] >= '0') && (recv->REF[n].str[i] <= '9')) {
                array[j] = recv->REF[n].str[i] - 0x30;
                j++;
            } else if (recv->REF[n].str[i] == ' ') {
                temporary++;
            } else if (recv->REF[n].str[i] == '.') {
                cnt = i - 6 - temporary;
            }
        }
        FH_ai_6103z_Part3Value.Data[n].Harmonic1 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part3Value.Data[n].Harmonic1 += array[i] * pow(10, cnt - i - 1);
        }
        memset(array, 0, sizeof(array));
    }


    /* 电压谐波2 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        for (uint8_t i = 10; i < 14; i++) {
            if ((recv->REF[n].str[i] >= '0') && (recv->REF[n].str[i] <= '9')) {
                array[j] = recv->REF[n].str[i] - 0x30;
                j++;
            } else if (recv->REF[n].str[i] == ' ') {
                temporary++;
            } else if (recv->REF[n].str[i] == '.') {
                cnt = i - 10 - temporary;
            }
        }
        FH_ai_6103z_Part3Value.Data[n].Harmonic2 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part3Value.Data[n].Harmonic2 += array[i] * pow(10, cnt - i - 1);
        }
        memset(array, 0, sizeof(array));
    }


    /* 电压谐波3 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        for (uint8_t i = 14; i < 18; i++) {
            if ((recv->REF[n].str[i] >= '0') && (recv->REF[n].str[i] <= '9')) {
                array[j] = recv->REF[n].str[i] - 0x30;
                j++;
            } else if (recv->REF[n].str[i] == ' ') {
                temporary++;
            } else if (recv->REF[n].str[i] == '.') {
                cnt = i - 14 - temporary;
            }
        }
        FH_ai_6103z_Part3Value.Data[n].Harmonic3 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part3Value.Data[n].Harmonic3 += array[i] * pow(10, cnt - i - 1);
        }
        memset(array, 0, sizeof(array));
    }

    /* 角度 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        for (uint8_t i = 18; i < 23; i++) {
            if ((recv->REF[n].str[i] >= '0') && (recv->REF[n].str[i] <= '9')) {
                array[j] = recv->REF[n].str[i] - 0x30;
                j++;
            } else if (recv->REF[n].str[i] == ' ') {
                temporary++;
            } else if (recv->REF[n].str[i] == '.') {
                cnt = i - 18 - temporary;
            }
        }
        FH_ai_6103z_Part3Value.Data[n].Angle = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part3Value.Data[n].Angle += array[i] * pow(10, cnt - i - 1);
        }
        memset(array, 0, sizeof(array));
    }
}

/*
 *  @ brief 解析第四部分
 */
uint16_t FH_ai_6103z4Analy(uint8_t *buff)
{
    uint8_t array[10];
    FH_ai_6103z_Part4Type *recv = (FH_ai_6103z_Part4Type *)buff;
    uint8_t cnt, temporary = 0;
    int sign = 1;

    /* ix */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].ix[i] >= '0') && (recv->MOA[n].ix[i] <= '9')) {
                array[j] = recv->MOA[n].ix[i] - 0x30;
                j++;
            } else if (recv->MOA[n].ix[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].ix[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].ix[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].ix = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].ix += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].ix = FH_ai_6103z_Part4Value.Data[n].ix * sign;
        FH_ai_6103z_Part4Value.Data[n].ixu[0] = recv->MOA[n].ix[6];
        memset(array, 0, sizeof(array));
    }

    /* ixp */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].ixp[i] >= '0') && (recv->MOA[n].ixp[i] <= '9')) {
                array[j] = recv->MOA[n].ixp[i] - 0x30;
                j++;
            } else if (recv->MOA[n].ixp[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].ixp[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].ixp[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].ixp = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].ixp += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].ixp = FH_ai_6103z_Part4Value.Data[n].ixp * sign;
        memset(array, 0, sizeof(array));
    }

    /* ir */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].ir[i] >= '0') && (recv->MOA[n].ir[i] <= '9')) {
                array[j] = recv->MOA[n].ir[i] - 0x30;
                j++;
            } else if (recv->MOA[n].ir[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].ir[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].ir[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].ir = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].ir += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].ir = FH_ai_6103z_Part4Value.Data[n].ir * sign;
        memset(array, 0, sizeof(array));
    }

    /* irp */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].irp[i] >= '0') && (recv->MOA[n].irp[i] <= '9')) {
                array[j] = recv->MOA[n].irp[i] - 0x30;
                j++;
            } else if (recv->MOA[n].irp[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].irp[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].irp[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].irp = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].irp += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].irp = FH_ai_6103z_Part4Value.Data[n].irp * sign;
        memset(array, 0, sizeof(array));
    }

    /* irlp */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].irlp[i] >= '0') && (recv->MOA[n].irlp[i] <= '9')) {
                array[j] = recv->MOA[n].irlp[i] - 0x30;
                j++;
            } else if (recv->MOA[n].irlp[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].irlp[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].irlp[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].irlp = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].irlp += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].irlp = FH_ai_6103z_Part4Value.Data[n].irlp * sign;
        FH_ai_6103z_Part4Value.Data[n].irlpu[0] = recv->MOA[n].irlp[6];
        memset(array, 0, sizeof(array));
    }

    /* iclp */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].iclp[i] >= '0') && (recv->MOA[n].iclp[i] <= '9')) {
                array[j] = recv->MOA[n].iclp[i] - 0x30;
                j++;
            } else if (recv->MOA[n].iclp[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].iclp[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].iclp[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].iclp = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].iclp += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].iclp = FH_ai_6103z_Part4Value.Data[n].iclp * sign;
        FH_ai_6103z_Part4Value.Data[n].iclpu[2] = recv->MOA[n].iclp[6];
        memset(array, 0, sizeof(array));
    }

    /* pl */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].pl[i] >= '0') && (recv->MOA[n].pl[i] <= '9')) {
                array[j] = recv->MOA[n].pl[i] - 0x30;
                j++;
            } else if (recv->MOA[n].pl[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].pl[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].pl[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].pl = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].pl += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].pl = FH_ai_6103z_Part4Value.Data[n].pl * sign;
        memset(array, 0, sizeof(array));
    }

    /* cx */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].cx[i] >= '0') && (recv->MOA[n].cx[i] <= '9')) {
                array[j] = recv->MOA[n].cx[i] - 0x30;
                j++;
            } else if (recv->MOA[n].cx[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].cx[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].cx[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].cx = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].cx += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].cx = FH_ai_6103z_Part4Value.Data[n].cx * sign;
        memset(array, 0, sizeof(array));
    }

    /* i3 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].i3[i] >= '0') && (recv->MOA[n].i3[i] <= '9')) {
                array[j] = recv->MOA[n].i3[i] - 0x30;
                j++;
            } else if (recv->MOA[n].i3[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].i3[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].i3[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].i3 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].i3 += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].i3 = FH_ai_6103z_Part4Value.Data[n].i3 * sign;
        FH_ai_6103z_Part4Value.Data[n].i3u[0] = recv->MOA[n].i3[6];
        memset(array, 0, sizeof(array));
    }

    /* i5 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].i5[i] >= '0') && (recv->MOA[n].i5[i] <= '9')) {
                array[j] = recv->MOA[n].i5[i] - 0x30;
                j++;
            } else if (recv->MOA[n].i5[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].i5[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].i5[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].i5 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].i5 += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].i5 = FH_ai_6103z_Part4Value.Data[n].i5 * sign;
        memset(array, 0, sizeof(array));
    }

    /* i7 */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 7; i++) {
            if ((recv->MOA[n].i7[i] >= '0') && (recv->MOA[n].i7[i] <= '9')) {
                array[j] = recv->MOA[n].i7[i] - 0x30;
                j++;
            } else if (recv->MOA[n].i7[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].i7[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].i7[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].i7 = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].i7 += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].i7 = FH_ai_6103z_Part4Value.Data[n].i7 * sign;
        memset(array, 0, sizeof(array));
    }

    /* A */
    for (uint8_t n = 0; n < 3; n++) {
        uint8_t j = 0;
        temporary = 0;
        sign = 1;
        for (uint8_t i = 0; i < 6; i++) {
            if ((recv->MOA[n].A[i] >= '0') && (recv->MOA[n].A[i] <= '9')) {
                array[j] = recv->MOA[n].A[i] - 0x30;
                j++;
            } else if (recv->MOA[n].A[i] == ' ') {
                temporary++;
            } else if (recv->MOA[n].A[i] == '.') {
                cnt = i - temporary;
            } else if (recv->MOA[n].A[i] == '-') {
                temporary++;
                sign = -1;
            }
        }
        FH_ai_6103z_Part4Value.Data[n].A = 0;
        for (uint8_t i = 0; i < j; i++) {
            FH_ai_6103z_Part4Value.Data[n].A += array[i] * pow(10, cnt - i - 1);
        }
        FH_ai_6103z_Part4Value.Data[n].A = FH_ai_6103z_Part4Value.Data[n].A * sign;
        memset(array, 0, sizeof(array));
    }
    /* C */
    FH_ai_6103z_Part4Value.Data[0].C = recv->MOA[0].C;
    FH_ai_6103z_Part4Value.Data[1].C = recv->MOA[1].C;
    FH_ai_6103z_Part4Value.Data[2].C = recv->MOA[2].C;
}

/**
 * @brief 解析数据条数
 *
 * @param buff
 * @param size
 */
char *FH_ai_6103z_AnalyDataCnt(uint8_t *buff, uint16_t size)
{
    FH_ai_6103z_DataCnt = (buff[0] << 8) | (buff[1]);
    printf("******%x\n", FH_ai_6103z_DataCnt);
    return "succeed";
}

char *FH_ai_6103zRecvMessage(uint8_t *buff, uint16_t size)
{
    uint8_t byte[40];
    FH_ai_6103z_MessageType *recv;

    if (buff[0] == '#') {
        recv = (FH_ai_6103z_MessageType *) buff;
    } else if (buff[1] == '#') {
        recv = (FH_ai_6103z_MessageType *) (buff + 1);
    }

    if (recv->Head != '#')
        return NULL;
    if (recv->Read[0] != 'R')
        return NULL;

    FH_ai_6103z_DataCnt = 0;
    if (recv->Read[1] == 'M' && FH_ai_6103z_cnt == 1) {
        return FH_ai_6103z_AnalyDataCnt(recv->Data, 2);
    }

    /* 把前面的这部分ascll码转成十六进制 */
    PUBLIC_AscllToHex(byte, recv->Data, (80));

    FH_ai_6103z1Analy(byte);
    FH_ai_6103z2Analy(&recv->Data[80]);
    FH_ai_6103z3Analy(&recv->Data[80 + 288]);
    FH_ai_6103z4Analy(&recv->Data[80 + 288 + 72]);

    return FH_ai_6103zBleSend();

}

/*
 * @ 发送数据解析完的数据
 */
char *FH_ai_6103zBleSend(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "AI_6103Z");

    /* 自动边补 */
    if (FH_ai_6103z_Part1Value.MC == 2) {
        FH_ai_6103z_Part1Value.Angle[0].A = (FH_ai_6103z_Part4Value.Data[0].A - 120) / 2;
        FH_ai_6103z_Part1Value.Angle[1].A = 0;
        FH_ai_6103z_Part1Value.Angle[2].A = -((FH_ai_6103z_Part4Value.Data[2].A - 120) / 2);
    }

    PUBLIC_JsonArrayLoading(cjson_array, 1, "Phase_A_Ix", "double", FH_ai_6103z_Part4Value.Data[0].ixu,  FH_ai_6103z_Part4Value.Data[0].ix, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 2, "A_phase_phase_angle", "double", "°", FH_ai_6103z_Part4Value.Data[0].A, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "A_phase_Irlp", "double", FH_ai_6103z_Part4Value.Data[0].irlpu, FH_ai_6103z_Part4Value.Data[0].irlp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "A_phase_Irp", "double", FH_ai_6103z_Part4Value.Data[0].irlpu, FH_ai_6103z_Part4Value.Data[0].irp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "A_phase_Iclp", "double", FH_ai_6103z_Part4Value.Data[0].iclpu, FH_ai_6103z_Part4Value.Data[0].iclp, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 4, "Phase_B_Ix", "double", FH_ai_6103z_Part4Value.Data[1].ixu,  FH_ai_6103z_Part4Value.Data[1].ix, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 5, "B_phase_Irlp", "double", FH_ai_6103z_Part4Value.Data[1].irlpu, FH_ai_6103z_Part4Value.Data[1].irlp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "A_phase_Irp", "double", FH_ai_6103z_Part4Value.Data[0].irlpu, FH_ai_6103z_Part4Value.Data[0].irp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "A_phase_Iclp", "double", FH_ai_6103z_Part4Value.Data[0].iclpu, FH_ai_6103z_Part4Value.Data[0].iclp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 6, "B_phase_phase_angle", "double", "°",  FH_ai_6103z_Part4Value.Data[1].A, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 7, "Phase_C_Ix", "double", FH_ai_6103z_Part4Value.Data[2].ixu,  FH_ai_6103z_Part4Value.Data[2].ix, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "C_phase_Irlp", "double", FH_ai_6103z_Part4Value.Data[2].irlpu, FH_ai_6103z_Part4Value.Data[2].irlp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 8, "C_phase_Irp", "double", FH_ai_6103z_Part4Value.Data[2].irlpu, FH_ai_6103z_Part4Value.Data[2].irp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 3, "C_phase_Iclp", "double", FH_ai_6103z_Part4Value.Data[2].iclpu, FH_ai_6103z_Part4Value.Data[2].iclp, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 9, "C_phase_phase_angle", "double", "°", FH_ai_6103z_Part4Value.Data[2].A, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 10, "testing_mode", "int", "null", FH_ai_6103z_Part1Value.MC, "null");

    PUBLIC_JsonArrayLoading(cjson_array, 11, "power_A", "double", "mW",   FH_ai_6103z_Part4Value.Data[0].pl, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 12, "power_B", "double", "mW",   FH_ai_6103z_Part4Value.Data[1].pl, "null");
    PUBLIC_JsonArrayLoading(cjson_array, 13, "power_C", "double", "mW",   FH_ai_6103z_Part4Value.Data[2].pl, "null");

    cJSON_AddItemToObject(cjson_data, "properties", cjson_array);
    str = cJSON_PrintUnformatted(cjson_data);
//    printf("%s\r\n", str);

    memset(returnJsonDataBuff, 0, sizeof(returnJsonDataBuff));
    memcpy(returnJsonDataBuff, str, strlen(str));

    /* 一定要释放内存 */
    free(str);
    cJSON_Delete(cjson_data);

    return returnJsonDataBuff;
}
