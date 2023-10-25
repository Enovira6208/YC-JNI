// /*
//  * CMD2100D.h
//  * @Author       : zhengshuo
//  * @Date         : 2023年10月13日
//  * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
//  * @Descripttion :
//  * @version      : 1.0
//  * @Modify record:
//  */

// #ifndef APPLICATION_MIDDLEDRIVERS_CMD2100_H_
// #define APPLICATION_MIDDLEDRIVERS_CMD2100_H_

// #include "../public/public.h"

// //*****************************************************************************************************
// typedef struct
// {
//     uint8_t voltage[4];                           /* 电压 */
//     uint8_t current[4];                           /* 电流 */
//     uint8_t capacitance[4];                         /*电容*/ 
// } CM2100D_C_MessageDataType;

// typedef struct
// {
//     double voltage;                         /*电压*/
//     double current;                                   /* 电流 */
//     double capacitance;                                   /* 电容 */
// } CM2100D_C_ValueType;
// //*****************************************************************************************************
// typedef struct
// {
//     uint8_t other[4];                           /* 其他 */
//     uint8_t current[4];                           /* 电流 */
// } CM2100D_I_MessageDataType;

// typedef struct
// {
//     double other;                         /*其他*/
//     double current;                                   /* 电流 */
// } CM2100D_I_ValueType;
// //*****************************************************************************************************
// typedef struct
// {
//     uint8_t voltage[4];                           /* 电压 */
//     uint8_t current[4];                           /* 电流 */
//     uint8_t other[4];                           /* 其他 */
//     uint8_t inductance[4];                           /* 电感 */
//     uint8_t reactance[4];                         /*电抗*/ 
// } CM2100D_H_MessageDataType;

// typedef struct
// {
//     double voltage;                           /* 电压 */
//     double current;                           /* 电流 */
//     double other;                           /* 其他 */
//     double inductance;                           /* 电感 */
//     double reactance;                         /*电抗*/ 
// } CM2100D_H_ValueType;
// //*****************************************************************************************************
// typedef struct
// {
//     uint8_t voltage[4];                           /* 电压 */
//     uint8_t current[4];                           /* 电流 */
//     uint8_t other[8];                           /* 其他 */
//     uint8_t resistance[4];                         /*电抗*/ 
// } CM2100D_R_MessageDataType;

// typedef struct
// {
//     double voltage;                           /* 电压 */
//     double current;                           /* 电流 */
//     double other;                           /* 其他 */
//     double resistance;                         /*电抗*/ 
// } CM2100D_R_ValueType;
// //*****************************************************************************************************
// typedef struct
// {
//     uint8_t Data[253];
// } CM2100DMessageType;

// uint16_t CM2100DReadData(uint8_t *buff, uint8_t cnt);
// char *CM2100DRecvMessage(uint8_t *buff, uint16_t size);

// #endif /* APPLICATION_MIDDLEDRIVERS_CM2100D_H_ */
