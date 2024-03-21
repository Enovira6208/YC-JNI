#include "JYW6100.h"

static char returnJsonDataBuff[1000];

JYW6100DataType JYW6100Value;

char *JYW6100Send(int type);

uint16_t JYW6100ReadData(uint8_t *ascllBuff, int cnt)
{
    /*复位命令*/
    if (cnt == 1) {
        uint8_t hexBuff[10];

        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x41;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x31;
        hexBuff[5] = 0x40;
        hexBuff[6] = 0x3F;
        hexBuff[7] = 0x0D;

        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 8);
    } else if (cnt == 2) {              /*空载实验*/
        uint8_t hexBuff[10];

        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x41;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x32;
        hexBuff[5] = 0x41;
        hexBuff[6] = 0x30;
        hexBuff[7] = 0x0D;
        hexBuff[8] = 0x0D;

        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 9);
    } else if (cnt == 3) {              /*负载实验*/
        uint8_t hexBuff[10];

        hexBuff[0] = 0x7E;
        hexBuff[1] = 0x41;
        hexBuff[2] = 0x41;
        hexBuff[3] = 0x30;
        hexBuff[4] = 0x32;
        hexBuff[5] = 0x41;
        hexBuff[6] = 0x31;
        hexBuff[7] = 0x0D;
        hexBuff[8] = 0x0D;

        PUBLIC_HexToAscll((char *)ascllBuff, hexBuff, 9);
    }

    return 16;
}

double JYW6100Count(uint8_t *buff, uint8_t cnt)
{
    uint8_t ascll[10];
    uint8_t decimal, temp = 0;
    uint8_t j = 0;
    double vlaue = 0;
    uint8_t blank = 0;
    int sign = 1;


    if (buff[0]  == '-')
        sign = -1;

    memset(ascll, 0, 10);
    for (uint8_t i = 0; i < cnt; i++) {
        if ((buff[i] >= 0x30) && (buff[i] <= 0x39)) {
            ascll[j] = buff[i] - 0x30;
            j++;
        } else if (buff[i] == '.') {
            decimal = i;
        } else {
            temp++;
        }
    }
    for (uint8_t i = 0; i < j; i++) {
        vlaue += ascll[i] * pow(10, decimal - i - 1 - temp);
    }

    return vlaue * sign;
}

char *JYW6100RecvMessage(uint8_t *buff, uint16_t size)
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
    JYW6100MessageType *recv = (JYW6100MessageType *) (buff + dd);

    if (recv->head != 0x7E)
        return NULL;

    if (recv->status == 0x25) {
        uint8_t con[10];
        int n = 0;

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_a = JYW6100Count(con, 7);
        memset(con, 0, sizeof(con));

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_ab = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_bc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_ca = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_mean_abc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_ab = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_bc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_ca = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Um_mean_abc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.p_ = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.io = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Umean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.D = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.F = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Iorms = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Uorms = JYW6100Count(con, 7);
        memset(con, 0, 9);
        return JYW6100Send(1);

    } else if (recv->status == 0x35) {
        uint8_t con[10];
        int n = 0;

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_a = JYW6100Count(con, 7);
        memset(con, 0, sizeof(con));

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ir_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_a = JYW6100Count(con, 7);
        memset(con, 0, sizeof(con));

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_a = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_b = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_c = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y_mean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_ab = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_bc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_ca = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Ur_mean_abc = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.p_ = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Uk = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.Imean = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.P = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.y = JYW6100Count(con, 7);
        memset(con, 0, 9);

        memcpy(con, recv->data  + (9 * n), 7);
        n++;
        JYW6100Value.F = JYW6100Count(con, 7);
        memset(con, 0, 9);

        return JYW6100Send(2);
    }

}

char *JYW6100Send(int type)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "JYW6100");

    if (type == 1) {
        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ur_a", "double", "%",   JYW6100Value.Ur_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ur_b", "double", "%",   JYW6100Value.Ur_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_c", "double", "%",   JYW6100Value.Ur_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_mean", "double", "%",   JYW6100Value.Ur_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Um_a", "double", "%",   JYW6100Value.Um_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Um_b", "double", "%",   JYW6100Value.Um_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Um_c", "double", "%",   JYW6100Value.Um_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Um_mean", "double", "%",   JYW6100Value.Um_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ir_a", "double", "%",   JYW6100Value.Ir_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ir_b", "double", "%",   JYW6100Value.Ir_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ir_c", "double", "%",   JYW6100Value.Ir_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ir_mean", "double", "%",   JYW6100Value.Ir_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "P_a", "double", "%",   JYW6100Value.P_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "P_b", "double", "%",   JYW6100Value.P_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P_c", "double", "%",   JYW6100Value.P_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P_mean", "double", "%",   JYW6100Value.P_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "y_a", "double", "%",   JYW6100Value.y_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "y_b", "double", "%",   JYW6100Value.y_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y_c", "double", "%",   JYW6100Value.y_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y_mean", "double", "%",   JYW6100Value.y_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ur_ab", "double", "%",   JYW6100Value.Ur_ab, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ur_bc", "double", "%",   JYW6100Value.Ur_bc, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_ca", "double", "%",   JYW6100Value.Ur_ca, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_mean_abc", "double", "%",   JYW6100Value.Ur_mean_abc, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Um_ab", "double", "%",   JYW6100Value.Um_ab, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Um_bc", "double", "%",   JYW6100Value.Um_bc, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Um_ca", "double", "%",   JYW6100Value.Um_ca, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Um_mean_abc", "double", "%",   JYW6100Value.Um_mean_abc, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "P_", "double", "%",   JYW6100Value.p_, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "io", "double", "%",   JYW6100Value.io, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Umean", "double", "%",   JYW6100Value.Umean, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P", "double", "%",   JYW6100Value.P, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "D", "double", "%",   JYW6100Value.D, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y", "double", "%",   JYW6100Value.y, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "F", "double", "%",   JYW6100Value.F, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Iorms", "double", "%",   JYW6100Value.Iorms, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Uorms", "double", "%",   JYW6100Value.Uorms, "null");
    } else if (type == 2) {
        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ir_a", "double", "%",   JYW6100Value.Ir_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ir_b", "double", "%",   JYW6100Value.Ir_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ir_c", "double", "%",   JYW6100Value.Ir_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ir_mean", "double", "%",   JYW6100Value.Ir_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ur_a", "double", "%",   JYW6100Value.Ur_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ur_b", "double", "%",   JYW6100Value.Ur_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_c", "double", "%",   JYW6100Value.Ur_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_mean", "double", "%",   JYW6100Value.Ur_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "P_a", "double", "%",   JYW6100Value.P_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "P_b", "double", "%",   JYW6100Value.P_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P_c", "double", "%",   JYW6100Value.P_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P_mean", "double", "%",   JYW6100Value.P_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "y_a", "double", "%",   JYW6100Value.y_a, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "y_b", "double", "%",   JYW6100Value.y_b, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y_c", "double", "%",   JYW6100Value.y_c, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y_mean", "double", "%",   JYW6100Value.y_mean, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "Ur_ab", "double", "%",   JYW6100Value.Ur_ab, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Ur_bc", "double", "%",   JYW6100Value.Ur_bc, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_ca", "double", "%",   JYW6100Value.Ur_ca, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Ur_mean_abc", "double", "%",   JYW6100Value.Ur_mean_abc, "null");

        PUBLIC_JsonArrayLoading(cjson_array, 1, "P_", "double", "%",   JYW6100Value.p_, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 2, "Uk", "double", "%",   JYW6100Value.Uk, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Imean", "double", "%",   JYW6100Value.Imean, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "P", "double", "%",   JYW6100Value.P, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "y", "double", "%",   JYW6100Value.y, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "F", "double", "%",   JYW6100Value.F, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Iorms", "double", "%",   JYW6100Value.Iorms, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "Uorms", "double", "%",   JYW6100Value.Uorms, "null");
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
