#include "CVT2301.h"

static char returnJsonDataBuff[1000];
char *CVT2301Send(void);
CVT2003_single_ValueType single_ValueType;
CVT2003_three_ValueType three_ValueType;
int recv_cnt = 0;

uint16_t CVT2003ReadData(uint8_t *buff, uint8_t cnt)
{
    if (cnt == 1) {
        buff[0] = 0x23;
        recv_cnt = 1;
        return 1;
    } else if (cnt == 2) {  /*单相*/
        buff[0] = 0x01;
        recv_cnt = 2;
        return 1;
    } else if (cnt == 3) {  /*三相*/
        buff[0] = 0x02;
        recv_cnt = 3;
        return 1;
    }
    return 16;
}

int hexToint(uint8_t a)
{
    int b = a / 16;
    int c = a % 16;
    int sum = b * 10 + c;
    return sum;
}

char *CVT2003RecvMessage(uint8_t *buff, uint16_t size)
{
    if (buff[0] == 0x23) {
        return "success";
    }
    if (recv_cnt == 2) {
        CVT2003_single_MessageType *recv = (CVT2003_single_MessageType *)buff;
        int ratio1 = hexToint(recv->rated_variable_ratio[0]);
        int ratio2 = hexToint(recv->rated_variable_ratio[1]);
        int ratio3 = hexToint(recv->rated_variable_ratio[2]);
        int ratio4 = hexToint(recv->rated_variable_ratio[3]);

        int result1 = hexToint(recv->result[0]);
        int result2 = hexToint(recv->result[1]);
        int result3 = hexToint(recv->result[2]);
        int result4 = hexToint(recv->result[3]);

        int test_error1 = hexToint(recv->test_error[0]);
        int test_error2 = hexToint(recv->test_error[1]);

        if (recv->result[0] == 0xfe) {
            return NULL;
        }

        single_ValueType.rated_variable_ratio = ratio1 * 100 + ratio2 + ratio3 * 0.01 + ratio4 * 0.0001;
        single_ValueType.result = result1 * 100 + result2 + result3 * 0.01 + result4 * 0.0001;
        single_ValueType.test_error = test_error1 + test_error2 * 0.01;
        if (recv->polarity == 0x01) {
            sprintf(single_ValueType.polarity, "%s", "+");
        } else if (recv->polarity == 0x00) {
            sprintf(single_ValueType.polarity, "%s", "-");
        }

        if (recv->sign == 0x01) {
            sprintf(single_ValueType.polarity, "%s", "+");
        } else if (recv->sign == 0x00) {
            sprintf(single_ValueType.polarity, "%s", "-");
        }
    } else if (recv_cnt == 3) {
        CVT2003_three_MessageType *recv = (CVT2003_three_MessageType *)buff;

        if (buff[0] == 0xff && buff[1] == 0xff) {
            return NULL;
        }

        int ratio1 = hexToint(recv->rated_variable_ratio[0]);
        int ratio2 = hexToint(recv->rated_variable_ratio[1]);
        int ratio3 = hexToint(recv->rated_variable_ratio[2]);
        int ratio4 = hexToint(recv->rated_variable_ratio[3]);

        three_ValueType.rated_variable_ratio = ratio1 * 100 + ratio2 + ratio3 * 0.01 + ratio4 * 0.0001;

        if (recv->link_way == 0x12) {
            sprintf(three_ValueType.link_way, "%s", "YnY");
        } else if (recv->link_way == 0x13) {
            sprintf(three_ValueType.link_way, "%s", "YnD");
        } else if (recv->link_way == 0x14) {
            sprintf(three_ValueType.link_way, "%s", "YnZn");
        } else if (recv->link_way == 0x21) {
            sprintf(three_ValueType.link_way, "%s", "YYn");
        } else if (recv->link_way == 0x23) {
            sprintf(three_ValueType.link_way, "%s", "YD");
        } else if (recv->link_way == 0x24) {
            sprintf(three_ValueType.link_way, "%s", "YZn");
        } else if (recv->link_way == 0x31) {
            sprintf(three_ValueType.link_way, "%s", "DYN");
        } else if (recv->link_way == 0x32) {
            sprintf(three_ValueType.link_way, "%s", "DY");
        } else if (recv->link_way == 0x34) {
            sprintf(three_ValueType.link_way, "%s", "DZn");
        } else if (recv->link_way == 0x11) {
            sprintf(three_ValueType.link_way, "%s", "YnYn");
        } else if (recv->link_way == 0x22) {
            sprintf(three_ValueType.link_way, "%s", "YY");
        } else if (recv->link_way == 0x33) {
            sprintf(three_ValueType.link_way, "%s", "DD");
        } else if (recv->link_way == 0x44) {
            sprintf(three_ValueType.link_way, "%s", "ZnZn");
        }

        three_ValueType.group = (int)(recv->twelve & 0x0f);
        three_ValueType.tap_mid = (int)(recv->threeteen);
        int Pressure_adjustment_at_each_stage1 = (recv->twelve & 0xf0) >> 4;
        int Pressure_adjustment_at_each_stage2 = hexToint(recv->fourteen);
        three_ValueType.Pressure_adjustment_at_each_stage = Pressure_adjustment_at_each_stage1 + Pressure_adjustment_at_each_stage2 * 0.01;
        three_ValueType.tap_sum = (int)(recv->fifteen);
        three_ValueType.tap_position = (int)(recv->sixteen);

        int AB1 = hexToint(recv->change_AB[0]);
        int AB2 = hexToint(recv->change_AB[1]);
        int AB3 = hexToint(recv->change_AB[2]);
        int AB4 = hexToint(recv->change_AB[3]);
        three_ValueType.change_AB = AB1 * 100 + AB2 + AB3 * 0.01 + AB4 * 0.0001;

        int BC1 = hexToint(recv->change_BC[0]);
        int BC2 = hexToint(recv->change_BC[1]);
        int BC3 = hexToint(recv->change_BC[2]);
        int BC4 = hexToint(recv->change_BC[3]);
        three_ValueType.change_BC = BC1 * 100 + BC2 + BC3 * 0.01 + BC4 * 0.0001;

        int AC1 = hexToint(recv->change_AC[0]);
        int AC2 = hexToint(recv->change_AC[1]);
        int AC3 = hexToint(recv->change_AC[2]);
        int AC4 = hexToint(recv->change_AC[3]);
        three_ValueType.change_AC = AC1 * 100 + AC2 + AC3 * 0.01 + AC4 * 0.0001;

        int AB_error1 = hexToint(recv->error_AB[0]);
        int AB_error2 = hexToint(recv->error_AB[1]);
        three_ValueType.error_AB = AB_error1 + AB_error2 * 0.01;

        int BC_error1 = hexToint(recv->error_BC[0]);
        int BC_error2 = hexToint(recv->error_BC[1]);
        three_ValueType.error_BC = BC_error1 + BC_error2 * 0.01;

        int AC_error1 = hexToint(recv->error_AC[0]);
        int AC_error2 = hexToint(recv->error_AC[1]);
        three_ValueType.error_AC = AC_error1 + AC_error2 * 0.01;

        if (recv->sign_AB == 0x01) {
            sprintf(three_ValueType.sign_AB, "%s", "+");
        } else if (recv->sign_AB == 0x00) {
            sprintf(three_ValueType.sign_AB, "%s", "-");
        }

        if (recv->sign_AC == 0x01) {
            sprintf(three_ValueType.sign_AC, "%s", "+");
        } else if (recv->sign_AC == 0x00) {
            sprintf(three_ValueType.sign_AC, "%s", "-");
        }

        if (recv->sign_BC == 0x01) {
            sprintf(three_ValueType.sign_BC, "%s", "+");
        } else if (recv->sign_BC == 0x00) {
            sprintf(three_ValueType.sign_BC, "%s", "-");
        }

    }
}

char *CVT2301Send(void)
{
    char *str;
    cJSON *cjson_data = NULL;
    cJSON *cjson_array = NULL;

    /* 添加一个嵌套的JSON数据（添加一个链表节点） */
    cjson_data = cJSON_CreateObject();
    cjson_array = cJSON_CreateArray();

    cJSON_AddStringToObject(cjson_data, "device", "CVT2301");

    if (recv_cnt == 2) {
        PUBLIC_JsonArrayLoading(cjson_array, 1, "rated_variable_ratio", "double", "", single_ValueType.rated_variable_ratio, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 3, "result", "double", "", single_ValueType.result, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 4, "test_error", "double", "%", single_ValueType.test_error, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "polarity", "string", "null", 0, single_ValueType.polarity);
        PUBLIC_JsonArrayLoading(cjson_array, 1, "sign", "string", "null", 0, single_ValueType.sign);
    } else if (recv_cnt == 3) {
        PUBLIC_JsonArrayLoading(cjson_array, 1, "rated_variable_ratio", "double", "", three_ValueType.rated_variable_ratio, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "link_way", "string", "null", 0, three_ValueType.link_way);
        PUBLIC_JsonArrayLoading(cjson_array, 1, "group", "double", "", three_ValueType.group, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "tap_mid", "double", "", three_ValueType.tap_mid, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "tap_sum", "double", "", three_ValueType.tap_sum, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "tap_position", "double", "", three_ValueType.tap_position, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "Pressure_adjustment_at_each_stage", "double", "%", three_ValueType.Pressure_adjustment_at_each_stage, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "change_AB", "double", "", three_ValueType.change_AB, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "change_BC", "double", "", three_ValueType.change_BC, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "change_AC", "double", "", three_ValueType.change_AC, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "error_AB", "double", "", three_ValueType.error_AB, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "error_BC", "double", "", three_ValueType.error_BC, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "error_AC", "double", "", three_ValueType.error_AC, "null");
        PUBLIC_JsonArrayLoading(cjson_array, 1, "sign_AB", "string", "null", 0, three_ValueType.sign_AB);
        PUBLIC_JsonArrayLoading(cjson_array, 1, "sign_BC", "string", "null", 0, three_ValueType.sign_BC);
        PUBLIC_JsonArrayLoading(cjson_array, 1, "sign_AC", "string", "null", 0, three_ValueType.sign_AC);
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