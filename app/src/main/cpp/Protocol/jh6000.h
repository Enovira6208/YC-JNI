/*
 * jh6000.h
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_JH6000_H_
#define APPLICATION_MIDDLEDRIVERS_JH6000_H_

#include "../public/public.h"


#define JH6000_MSG_HEAD					(0x65)
#define JH6000_MSG_TAIL					(0x56)
#define JH6000_DATA_SIZE				(150)

typedef enum
{
	JH6000_DETECTION_GASES = 0x01,						/* 气体检测 */
}JH6000_DetectionEnum;

typedef enum
{
	JH6000_CONTROL_GET_DEVICE_MES = 0x01,				/* 获取设备信息 */
//	JH6000_CONTROL_SEND_UUID,							/* 发送UUID */
//	JH6000_CONTROL_GET_REAL_TIME_DATA,					/* 获取实时数据 */
//	JH6000_CONTROL_GET_PAST_DATA,						/* 获取历史数据 */
	JH6000_CONTROL_GET_PAST_DATA_CNT,					/* 获取历史数据条数 */
	JH6000_CONTROL_GET_DETECTION_DATA,					/* 获取检测数据 */
	JH6000_CONTROL_END_DETECTION,						/* 结束检测 */
}JH6000_ControlEnum;


typedef union {

    float f;
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} JH6000_myfloatType;

typedef struct
{
	uint8_t UUID[48];									/* UUID */
	uint8_t TestEncoding[8];							/* 测试编码 */
	uint8_t JobNumber[8];								/* 工单号 */
	uint8_t Breaker;									/* 断路器 */
	uint8_t OtherDevive;								/* 其他设备 */
	uint8_t Prerun;										/* 预试 */
	uint8_t Connect;									/* 交接 */
	uint8_t GasesChoose;								/* 气体选择 */
	uint8_t Decomposer;									/* 分解物 */
	uint8_t Purity;										/* 纯度 */
	uint8_t Moisture;									/* 水分 */
}JH6000_MsgUUIDType;

typedef struct
{
	uint8_t SerialNumber[2];								/* 编号 */
	uint8_t DateTime[6];								/* 时间 */
	uint8_t Status;										/* 状态 */
	uint8_t DeviceNumber[6];							/* 设备编码 */
	uint8_t ExpertNumber[2];								/* 专家编号 */
	uint8_t SO2[4];
	uint8_t H2S[4];
	uint8_t CO[4];
	uint8_t HF[4];
	uint8_t H2[4];
	uint8_t CF4[4];
	uint8_t NO[4];
	uint8_t O2[4];
	uint8_t DewPoint[4];										/* 露点 */
	uint8_t Humi[4];
	uint8_t Humi20[4];
	uint8_t SF6_V[4];
	uint8_t SF6_W[4];
	uint8_t CF4_V[4];
	uint8_t CF4_W[4];
	uint8_t Temp[4];
	uint8_t MPA[4];
	uint8_t N2_V[4];
	uint8_t N2_W[4];
	uint8_t AIR_V[4];
	uint8_t AIR_W[4];
	uint8_t SF6_CF4_V[4];
	uint8_t SF6_CF4_W[4];
	uint8_t SF6_N2_V[4];
	uint8_t SF6_N2_W[4];
}JH6000_DataAnalysisType;

typedef struct
{
	uint16_t SerialNumber;								/* 编号 */
	uint8_t DateTime[6];								/* 时间 */
	uint8_t Status;										/* 状态 */
	uint8_t DeviceNumber[6];							/* 设备编码 */
	uint16_t ExpertNumber;								/* 专家编号 */
	double SO2;
	double H2S;
	double CO;
	double HF;
	double H2;
	double CF4;
	double NO;
	double O2;
	double DewPoint;										/* 露点 */
	double Humi;
	double Humi20;
	double SF6_V;
	double SF6_W;
	double CF4_V;
	double CF4_W;
	double Temp;
	double MPA;
	double N2_V;
	double N2_W;
	double AIR_V;
	double AIR_W;
	double SF6_CF4_V;
	double SF6_CF4_W;
	double SF6_N2_V;
	double SF6_N2_W;
}JH6000_DataValueType;

typedef struct
{
	uint8_t Head;										/* 头 	*/
	uint8_t DetectionType;								/* 检测类型 	*/
	uint8_t ControlType;								/* 控制类型 	*/
	uint8_t Length[2];									/* 数据域长度 */
	uint8_t Data[JH6000_DATA_SIZE];						/* 数据	*/
	uint8_t Verify[2];									/* 校验	*/
	uint8_t Tail;										/* 尾 */
} JH6000_MessageType;

extern JH6000_DataValueType JH6000_Value;


uint16_t JH6000_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char* JH6000_RecvMessage(uint8_t* buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_JH6000_H_ */
