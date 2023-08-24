/*
 * JHMD3_jh6000.h
 * @Author       : chuhouzhong
 * @Date         : 2021-01-26 10:21:31
 * @Copyright    : Copyright (c) 2020  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_JHMD3_jh6000_H_
#define APPLICATION_MIDDLEDRIVERS_JHMD3_jh6000_H_

#include "../public/public.h"


#define JHMD3_jh6000_MSG_HEAD                 (0x65)
#define JHMD3_jh6000_MSG_TAIL                 (0x56)
#define JHMD3_jh6000_DATA_SIZE                (2000)

typedef enum {
    JHMD3_jh6000_DETECTION_GASES = 0x01,                      /* 气体检测 */
} JHMD3_jh6000_DetectionEnum;

typedef enum {
    JHMD3_jh6000_CONTROL_GET_DEVICE_MES = 0x01,               /* 获取设备信息 */
    JHMD3_jh6000_CONTROL_SEND_UUID,                           /* 发送UUID */
    JHMD3_jh6000_CONTROL_GET_DETECTION_DATA,                   /* 获取实时数据 */
    JHMD3_jh6000_CONTROL_GET_PAST_DATA,                       /* 获取历史数据 */
    JHMD3_jh6000_CONTROL_GET_PAST_DATA_CNT,                   /* 获取历史数据条数 */
    JHMD3_jh6000_CONTROL_END_DETECTION,                       /* 结束检测 */
} JHMD3_jh6000_ControlEnum;


typedef union {

    float f;
    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } raw;
} JHMD3_jh6000_myfloatType;

typedef struct {
    uint8_t UUID[48];                                   /* UUID */
    uint8_t TestEncoding[8];                            /* 测试编码 */
    uint8_t JobNumber[8];                               /* 工单号 */
    uint8_t Breaker;                                    /* 断路器 */
    uint8_t OtherDevive;                                /* 其他设备 */
    uint8_t Prerun;                                     /* 预试 */
    uint8_t Connect;                                    /* 交接 */
    uint8_t GasesChoose;                                /* 气体选择 */
    uint8_t Decomposer;                                 /* 分解物 */
    uint8_t Purity;                                     /* 纯度 */
    uint8_t Moisture;                                   /* 水分 */
} JHMD3_jh6000_MsgUUIDType;

typedef struct {
    uint8_t SerialNumber[48];                           /* UUID编号 */
    uint8_t TestEncoding[8];                                /* 唯一测试编码 */
    uint8_t JobNumber[8];                               /* 工单号 */
    uint8_t SF6[4];
    uint8_t temperature[4];                             /* 温度 */
    uint8_t humidity;                                   /* 湿度 */
    uint8_t max[4];
    uint8_t min[4];
    uint8_t electric_quantity[4];                       /* 当前电量 */
    uint8_t status;                                     /* 当前检测状态 */
} JHMD3_jh6000_DataAnalysisType;

typedef struct {
    uint8_t SerialNumber[48];                           /* UUID编号 */
    uint8_t TestEncoding[8];                                /* 唯一测试编码 */
    uint8_t JobNumber[8];                               /* 工单号 */
    double SF6;
    double temperature;                             /* 温度 */
    uint8_t humidity;                                   /* 湿度 */
    double max;
    double min;
    double electric_quantity;                       /* 当前电量 */
    uint8_t status;                                     /* 当前检测状态 */
} JHMD3_jh6000_DataValueType;

typedef struct {
    uint8_t Head;                                       /* 头  */
    uint8_t DetectionType;                              /* 检测类型     */
    uint8_t ControlType;                                /* 控制类型     */
    uint8_t Length[2];                                  /* 数据域长度 */
    uint8_t Data[JHMD3_jh6000_DATA_SIZE];                     /* 数据   */
    uint8_t Verify[2];                                  /* 校验   */
    uint8_t Tail;                                       /* 尾 */
} JHMD3_jh6000_MessageType;

extern JHMD3_jh6000_DataValueType JHMD3_jh6000_Value;


uint16_t JHMD3_jh6000_ReadData(uint8_t *ascllBuff, uint8_t cnt);
char *JHMD3_jh6000_RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_JHMD3_jh6000_H_ */
