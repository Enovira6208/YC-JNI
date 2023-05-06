/*
 * HCYZ_iv.h
 * @Author       : chuhouzhong
 * @Date         : 2021年9月23日
 * @Copyright    : Copyright (c) 2021  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_PROTOCOL_HCYZ_IV_H_
#define APPLICATION_PROTOCOL_HCYZ_IV_H_

#include "../public/public.h"

typedef struct 
{
	uint8_t Addr[2];					/* 地址 */
	uint8_t seat;						/* 位置码 */
	uint8_t Type;						/* 值类型 */
	uint8_t Value[4];					/* 值 */
	uint8_t OrderMagnitude;				/* 数量级 */

} HCYZ_ivMessageDataAPDU_ObjType;

typedef struct 
{
	uint8_t Head;						/* 头 */
	uint8_t Len;						/* 长度 */
	uint8_t GatherAddr[4];				/* 采集地址 */
	uint8_t Type;						/* 类型标识 */
	uint8_t Determiner;					/* 限定词 */
	uint8_t Reason;						/* 传送原因 */
	uint8_t PublicAddr[2];				/* 公共地址 */

	HCYZ_ivMessageDataAPDU_ObjType Obj[4];
	uint8_t Time[7];

} HCYZ_ivMessageDataAPDUType;

typedef struct
{
	uint8_t Head;						/* 头 */
	uint8_t APDU_Len[2];				/* APDU长度 */
	HCYZ_ivMessageDataAPDUType APDU[3];
	uint8_t Verify;
	uint8_t Tail;
} HCYZ_ivMessageDataType;


typedef struct
{
	uint8_t PhasePosition;					/* 相位 */
	uint8_t Type;							/* 类型 */
	double Resistance;						/* 阻值 */
	double SwitchingTime;					/* 切换时间 */
} HCYZ_ivMessageValueType;


typedef struct
{
	uint8_t Data[500];
} HCYZ_ivMessageType;


typedef struct
{
	cJSON* Param;
} HCYZ_ivCjsonParamType;

typedef struct
{
	HCYZ_ivCjsonParamType Array[3];
} HCYZ_ivCjsonType;


char* HCYZ_ivRecvMessage(uint8_t* buff, uint16_t size);

#endif /* APPLICATION_PROTOCOL_HCYZ_IV_H_ */
