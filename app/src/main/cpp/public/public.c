/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-06-28 16:13:20
 * @LastEditTime: 2022-11-17 17:00:38
 * @LastEditors:
 */

#include "public.h"


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
    for (uint16_t i = 0; i < len; i++)
    {
        if ((ascll[i] >= 0x30) && (ascll[i] <= 0x39))
        {
            buff[i] = ascll[i] - 0x30;
        }
        else if ((ascll[i] >= 0x41) && (ascll[i] <= 0x46))
        {
            buff[i] = ascll[i] - 0x37;
        }
        /* 小写字母 */
        else if ((ascll[i] >= 0x61) && (ascll[i] <= 0x66))
        {
            buff[i] = ascll[i] - 0x57;
        }
        else
        {
            buff[i] = 0xFF;
        }
    }
    uint16_t j = 0;
    for (uint16_t i = 0; i < len;)
    {
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
    for (uint16_t i = 0; i < len; i++)
    {
        ascll[j] = (hex[i] >> 4) & 0x0F;
        ascll[j + 1] = hex[i] & 0x0F;
        j += 2;
    }
    for (uint16_t i = 0; i < len * 2; i++)
    {
        if (ascll[i] <= 9)
        {
            ascll[i] += 0x30;
        }
        else if (ascll[i] >= 10)
        {
            ascll[i] += 0x37;
        }
    }
}

/*******************************************************************************/
/* 32位浮点数计算 */

uint32_t PUBLIC_convertToInt(uint8_t *arr, uint8_t  low, uint8_t high)
{
    uint32_t f = 0, i;
    for (i = high; i >= low; i--)
    {
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
        return -1023.0;
    for (int i = 31; i >= 0; i--)
    {
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

    for (uint8_t i = 0; i < size; i++)
    {
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
    if (strstr(datatype, "str") !=  NULL)
    {
        cJSON_AddStringToObject(cjson.Array[cnt].Param, "value", valueStr);
    }
    else if ((strstr(datatype, "double") !=  NULL) || (strstr(datatype, "int") !=  NULL))
    {
        cJSON_AddNumberToObject(cjson.Array[cnt].Param, "value", value);
    }
}

/**
 * @brief 山东省协议单位解析
 *
 * @param value 枚举值
 * @return char* 单位
 */
char *PUBLIC_SD_ProtocolUnitAnalysis(uint8_t value)
{
    switch (value)
    {
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

