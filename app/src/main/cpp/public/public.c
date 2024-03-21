/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 16:13:20
 * @LastEditTime: 2022-11-17 17:00:38
 * @LastEditors:
 */

#include "public.h"
#include "time.h"

/**
 * @brief BCD码转十进制
 */
uint8_t PUBLIC_BcdToNumb(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/**
 * @brief 十进制码转BCD
 */
uint8_t PUBLIC_NumbToBcd(uint8_t numb)
{
    return (((numb / 10) << 4) | (numb % 10));
}

/*
 *  @brief ASCLL转十六进制
 */
void PUBLIC_AscllToHex(uint8_t *hex, char *ascll, uint16_t len)
{
    uint8_t buff[len];
    for (uint16_t i = 0; i < len; i++) {
        if ((ascll[i] >= 0x30) && (ascll[i] <= 0x39)) {
            buff[i] = ascll[i] - 0x30;
        } else if ((ascll[i] >= 0x41) && (ascll[i] <= 0x46)) {
            buff[i] = ascll[i] - 0x37;
        }
        /* 小写字母 */
        else if ((ascll[i] >= 0x61) && (ascll[i] <= 0x66)) {
            buff[i] = ascll[i] - 0x57;
        } else {
            buff[i] = 0xFF;
        }
    }
    uint16_t j = 0;
    for (uint16_t i = 0; i < len;) {
        j = i / 2;
        hex[j] = ((buff[i] << 4) | (buff[i + 1] & 0x0F));
        i += 2;
    }
}

/*
 *  @brief 十六进制转ASCLL
 */
void PUBLIC_HexToAscll(char *ascll, uint8_t *hex, uint16_t len)
{

    uint16_t j = 0;
    for (uint16_t i = 0; i < len; i++) {
        ascll[j] = (hex[i] >> 4) & 0x0F;
        ascll[j + 1] = hex[i] & 0x0F;
        j += 2;
    }
    for (uint16_t i = 0; i < len * 2; i++) {
        if (ascll[i] <= 9) {
            ascll[i] += 0x30;
        } else if (ascll[i] >= 10) {
            ascll[i] += 0x37;
        }
    }
}

/*******************************************************************************/
/* 32位浮点数计算 */

uint32_t PUBLIC_convertToInt(uint8_t *arr, uint8_t  low, uint8_t high)
{
    uint32_t f = 0, i;
    for (i = high; i >= low; i--) {
        f = f + arr[i] * pow(2, high - i);
    }
    return f;
}

/**
 *  @ IEEE754 32位浮点数计算
 */
double PUBLIC_IEEE754_32(uint8_t value3, uint8_t value2, uint8_t value1, uint8_t value0)
{
    uint32_t valueU;
    uint8_t table[32];
    PUBLIC_MyFloatType var;
    int valueI;
    double valueDob;

    valueU = (value0 << 24) | (value1 << 16) | (value2 << 8) | (value3);
    if (valueU == 0xFFFFFFFF)
        return -1023;
    for (int i = 31; i >= 0; i--) {
        table[i] = (uint8_t)(valueU & 0x00000001);
        valueU >>= 1;
    }
    unsigned f = PUBLIC_convertToInt(table, 9, 31);
    var.raw.mantissa = f;
    f = PUBLIC_convertToInt(table, 1, 8);
    var.raw.exponent = f;
    var.raw.sign = table[0];

    valueI = var.f * 10000;
    valueDob = valueI / 10000.0;
    return valueDob;
}
/***************************************************************************/

float FourBytesToFloat (uint8_t byte4, uint8_t byte3, uint8_t byte2, uint8_t byte1)
{
    unsigned int bits = ( byte1 << 24 ) + ( byte2 << 16 ) + ( byte3 << 8) + byte4;
    int s = ( bits >> 31 ) == 0 ? 1 : -1;
    int e = ( bits >> 23 ) & 0xff;
    int m = ( e == 0 ) ?
            ( bits & 0x7fffff ) << 1 :
            ( bits & 0x7fffff ) | 0x800000;
    return s * m * ( float ) pow( 2, e - 150 );
}

/**
 * @brief 异或校验
 *
 * @param buff
 * @param size
 * @return uint8_t
 */
uint8_t calc_xor_checksum(uint8_t *buff, uint16_t size)
{
    uint8_t checksum = 0;

    for (uint8_t i = 0; i < size; i++) {
        checksum ^= *(buff + i);
    }

    return checksum;
}

/**
 * @brief json数组装载
 *
 * @param array             数据链表节点
 * @param cnt               当前数据的位数
 * @param name              当前数据命名
 * @param datatype          当前数据类型 string  double
 * @param unit              当前数据单位
 * @param value             当前数据的值  double类型
 * @param valueStr          当前数据的值  string类型
 */
void PUBLIC_JsonArrayLoading(cJSON *array, uint8_t cnt, char *name, char *datatype,
                             char *unit, double value, char *valueStr)
{
    PUBLIC_CjsonType cjson;

    cnt -= 1;
    /* 防止数组越界 */
    if ((cnt >= 100) || (cnt  < 0))
        return;

    cjson.Array[cnt].Param = NULL;
    cjson.Array[cnt].Param = cJSON_CreateObject();

    cJSON_AddItemToArray(array, cjson.Array[cnt].Param);

    cJSON_AddStringToObject(cjson.Array[cnt].Param, "name", name);
    cJSON_AddStringToObject(cjson.Array[cnt].Param, "datatype", datatype);
    cJSON_AddStringToObject(cjson.Array[cnt].Param, "unit", unit);
    if (strstr(datatype, "str") !=  NULL) {
        cJSON_AddStringToObject(cjson.Array[cnt].Param, "value", valueStr);
    } else if ((strstr(datatype, "double") !=  NULL) || (strstr(datatype, "int") !=  NULL)) {
        cJSON_AddNumberToObject(cjson.Array[cnt].Param, "value", value);
    }
}

float Char2Float2(unsigned char *chReceive)
{
    float fReceive;

    *((char *)(&fReceive))     = chReceive[3];
    *((char *)(&fReceive) + 1) = chReceive[2];
    *((char *)(&fReceive) + 2) = chReceive[1];
    *((char *)(&fReceive) + 3) = chReceive[0];

    return fReceive;
}

float Char2Float(unsigned char *chReceive)
{
    float fReceive;

    *((char *)(&fReceive))     = chReceive[0];
    *((char *)(&fReceive) + 1) = chReceive[1];
    *((char *)(&fReceive) + 2) = chReceive[2];
    *((char *)(&fReceive) + 3) = chReceive[3];

    return fReceive;
}
void Float2Char (float fSend, unsigned char *chSend)
{
    chSend[0] = *((char *)(&fSend));
    chSend[1] = *((char *)(&fSend) + 1);
    chSend[2] = *((char *)(&fSend) + 2);
    chSend[3] = *((char *)(&fSend) + 3);
}

/**
 * @brief 山东省协议单位解析
 *
 * @param value 枚举值
 * @return char* 单位
 */
char *PUBLIC_SD_ProtocolUnitAnalysis(uint8_t value)
{
    switch (value) {
        case PUBLIC_SD_PROTOCO_UNIT_NULL:
            return " ";

        case PUBLIC_SD_PROTOCO_UNIT_dB:
            return "dB";

        case PUBLIC_SD_PROTOCO_UNIT_dBm:
            return "dBm";

        case PUBLIC_SD_PROTOCO_UNIT_dBmV:
            return "dBmV";

        case PUBLIC_SD_PROTOCO_UNIT_dBuV:
            return "dBμV";

        case PUBLIC_SD_PROTOCO_UNIT_V:
            return "V";

        case PUBLIC_SD_PROTOCO_UNIT_mV:
            return "mV";

        case PUBLIC_SD_PROTOCO_UNIT_uV:
            return "μV";

        case PUBLIC_SD_PROTOCO_UNIT_PERCENT:
            return "%";

        case PUBLIC_SD_PROTOCO_UNIT_A:
            return "A";

        case PUBLIC_SD_PROTOCO_UNIT_mA:
            return "mA";

        case PUBLIC_SD_PROTOCO_UNIT_uA:
            return "μV";

        case PUBLIC_SD_PROTOCO_UNIT_O:
            return "Ω";

        case PUBLIC_SD_PROTOCO_UNIT_mO:
            return "mΩ";

        case PUBLIC_SD_PROTOCO_UNIT_uO:
            return "μΩ";

        case PUBLIC_SD_PROTOCO_UNIT_m_s2:
            return "m/s²";

        case PUBLIC_SD_PROTOCO_UNIT_mm:
            return "mm";

        case PUBLIC_SD_PROTOCO_UNIT_CENTIGRADE:
            return "℃";

        case PUBLIC_SD_PROTOCO_UNIT_FAHRENHEIT:
            return "℉";

        case PUBLIC_SD_PROTOCO_UNIT_Pa:
            return "Pa";

        case PUBLIC_SD_PROTOCO_UNIT_C:
            return "C";

        case PUBLIC_SD_PROTOCO_UNIT_mC:
            return "mC";

        case PUBLIC_SD_PROTOCO_UNIT_uC:
            return "μC";

        case PUBLIC_SD_PROTOCO_UNIT_nC:
            return "nC";

        case PUBLIC_SD_PROTOCO_UNIT_pC:
            return "pC";

        case PUBLIC_SD_PROTOCO_UNIT_m_s:
            return "m/s";

        case PUBLIC_SD_PROTOCO_UNIT_kO:
            return "kΩ";

        case PUBLIC_SD_PROTOCO_UNIT_MO:
            return "MΩ";

        case PUBLIC_SD_PROTOCO_UNIT_GO:
            return "GΩ";

        case PUBLIC_SD_PROTOCO_UNIT_TO:
            return "TΩ";

        case PUBLIC_SD_PROTOCO_UNIT_Hz:
            return "Hz";

        case PUBLIC_SD_PROTOCO_UNIT_H:
            return "H";

        case PUBLIC_SD_PROTOCO_UNIT_mH:
            return "mH";

        case PUBLIC_SD_PROTOCO_UNIT_F:
            return "F";

        case PUBLIC_SD_PROTOCO_UNIT_mF:
            return "mF";

        case PUBLIC_SD_PROTOCO_UNIT_uF:
            return "μF";

        case PUBLIC_SD_PROTOCO_UNIT_nF:
            return "nF";

        case PUBLIC_SD_PROTOCO_UNIT_pF:
            return "pF";

        case PUBLIC_SD_PROTOCO_UNIT_s:
            return "s";

        case PUBLIC_SD_PROTOCO_UNIT_ms:
            return "ms";

        case PUBLIC_SD_PROTOCO_UNIT_us:
            return "μs";

        case PUBLIC_SD_PROTOCO_UNIT_MPa:
            return "MPa";

        case PUBLIC_SD_PROTOCO_UNIT_uL_L:
            return "μL/L";

        case PUBLIC_SD_PROTOCO_UNIT_ANGLE:
            return "°";

        default:
            break;
    }
}

unsigned char aucCRCHi[256] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};
unsigned char aucCRCLo[256] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

/*************************************************
*函数名：CRC16
*输入参数：Frame 数据指针，Length 数据字节数
*返回值：CRC16 校验码
*功能：计算CRC 校验码
*************************************************/
unsigned short CRC16(unsigned char *Frame, int Length)
{
    unsigned char CRCHi = 0xFF;
    unsigned char CRCLo = 0xFF;
    int iIndex = 0;
    for (int i = 0; i < Length; i++) {
        iIndex = CRCLo ^ (*Frame);
        CRCLo = CRCHi ^ aucCRCHi[iIndex];
        CRCHi = aucCRCLo[iIndex];
        Frame++;
    }
    return (unsigned short)(CRCHi << 8 | CRCLo);
}