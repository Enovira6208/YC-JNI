/*
 * @Description:
 * @Author:  chuhouzhong
 * @Copyright: 福建省亿鑫海信息科技有限公司
 * @Date: 2022-11-16 19:35:12
 * @LastEditTime: 2022-11-18 08:57:41
 * @LastEditors:
 */

#ifndef _JYW6400_IM_H_
#define _JYW6400_IM_H_

#include "../public/public.h"

#define POINTS "points"

typedef struct
{
    uint8_t Head[3];
    uint8_t Length[4];
    uint8_t Cmd[2];                                        /* 命令 */
    uint8_t DataLength[4];
    uint8_t Data[500];
    uint8_t verify[2];
} JYW6400_IMMessageType;

typedef struct
{
    double voltage;                     /* 电压    */
    double electricity;                 /* 电流    */
    double power;                       /* 功率    */
    double reactance;                   /* 电抗    */
    double impedance;                   /* 阻抗    */
    double phasePosition;               /* 相位    */
    double shortCircuitImpedance;       /* 短路阻抗百分比     */

} JYW6400_IMResistanceType;

typedef struct
{
    char testTime[10];                      /*  */
    double testMethod;                      /* 测试方法 */
    double testMode;                        /* 测试方式 */
    char highPressureWinding[2];             /* 加压绕组 */
    char shortJointedWinding[2];             /* 短接绕组 */
    double switchingGearPosition;           /* 开关档位 */
    double frequency;                       /* 频率 */
    double dissipationImpedance;            /* 三相短路损耗 */
    double impedanceVoltage;                /* 三相阻抗电压（%） */
    double shortCircuitImpedance_ABC;       /* 三相短路阻抗 */
    JYW6400_IMResistanceType value[3];
} JYW6400_IMValueType;

uint16_t JYW6400_IMReadData(uint8_t *ascllBuff);
char *JYW6400_IMRecvMessage(uint8_t *buff, uint16_t size);

#endif // _JYW6400_IM_H_

