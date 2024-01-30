// /*
//  * @Description:
//  * @Author:  chuhouzhong
//  * @Copyright: 福建省亿鑫海信息科技有限公司
//  * @Date: 2023-05-30 10:48:56
//  * @LastEditTime: 2023-05-30 17:19:46
//  * @LastEditors:
//  */
// #ifndef _DB_8001_
// #define _DB_8001_

// #include "../public/public.h"

// typedef struct {
//     uint8_t test[7];
//     uint8_t type;                /*断路器断口类型*/
//     uint8_t switch_way[4];       /*开关行程*/
//     uint8_t test_type;
//     uint8_t dataMid;
//     uint8_t dataLow;
//     uint8_t cmd;
//     uint8_t high_switch_status;  /*高压开关状态*/
//     uint8_t device_status;       /*仪器状态*/
//     uint8_t data[100];
//     uint8_t xorCheck;
//     uint8_t tail;
// } JYCMessageType;


// typedef struct {
//     char name[4];
//     char unitName[3];
//     char sign[2];
//     double dataValue;
// } DataValue;

// typedef struct {
//     uint8_t dataLength[3];
//     uint8_t high_switch_status;  /*高压开关状态*/
//     uint8_t device_status;       /*仪器状态*/
//     int count;
//     DataValue v[20];
// } JYCValueType;

// uint16_t DB_8001_ReadData(uint8_t *ascllBuff, uint8_t cnt);
// char *DB_8001_RecvMessage(uint8_t *buff, uint16_t size);

// #endif