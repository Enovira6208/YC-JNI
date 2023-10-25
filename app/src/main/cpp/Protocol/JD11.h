/*
 * JD11.h
 * @Author       : zhengshuo
 * @Date         : 2023年10月17日
 * @Copyright    : Copyright (c) 2023  福建省亿鑫海信息科技有限公司
 * @Descripttion :
 * @version      : 1.0
 * @Modify record:
 */

#ifndef APPLICATION_MIDDLEDRIVERS_JD11_H_
#define APPLICATION_MIDDLEDRIVERS_JD11_H_

#include "../public/public.h"

typedef struct
{
    uint8_t str[9];
} JD11StrType;



typedef struct
{
    uint8_t time[5];                          /* 时间 */
    uint8_t temp_polarity[1];                           /* 温度极性 */
    uint8_t temp[2];                              /* 温度 */
    uint8_t contact_type[1];                           /* 接点类型 */
    uint8_t other[2];                                   /* 不明 */
    
    uint8_t contact2_1_up_pt[2];                                 /*接点2第1次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_1_up_p20[2];                                 /*接点2第1次上升值P20(前低后高，有符号双字节）*/
    
    uint8_t contact2_2_up_pt[2];                                 /*接点2第2次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_2_up_p20[2];                                 /*接点2第2次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact2_3_up_pt[2];                                 /*接点2第3次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_3_up_p20[2];                                 /*接点2第3次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact2_up_avg_pt[2];                                 /*接点2上升平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_up_avg_p20[2];                                 /*接点2上升平均值P20(前低后高，有符号双字节）*/

    uint8_t contact2_1_down_pt[2];                                 /*接点2第1次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_1_down_p20[2];                                 /*接点2第1次下降值P20(前低后高，有符号双字节）*/
    
    uint8_t contact2_2_down_pt[2];                                 /*接点2第2次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_2_down_p20[2];                                 /*接点2第2次下降值P20(前低后高，有符号双字节）*/

    uint8_t contact2_3_down_pt[2];                                 /*接点2第3次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_3_down_p20[2];                                 /*接点2第3次下降值P20(前低后高，有符号双字节）*/    

    uint8_t contact2_down_avg_pt[2];                                 /*接点2下降平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact2_down_avg_p20[2];                                 /*接点2下降平均值P20(前低后高，有符号双字节）*/




    uint8_t contact3_1_up_pt[2];                                 /*接点3第1次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_1_up_p20[2];                                 /*接点3第1次上升值P20(前低后高，有符号双字节）*/
    
    uint8_t contact3_2_up_pt[2];                                 /*接点3第2次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_2_up_p20[2];                                 /*接点3第2次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact3_3_up_pt[2];                                 /*接点3第3次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_3_up_p20[2];                                 /*接点3第3次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact3_up_avg_pt[2];                                 /*接点3上升平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_up_avg_p20[2];                                 /*接点3上升平均值P20(前低后高，有符号双字节）*/

    uint8_t contact3_1_down_pt[2];                                 /*接点3第1次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_1_down_p20[2];                                 /*接点3第1次下降值P20(前低后高，有符号双字节）*/
    
    uint8_t contact3_2_down_pt[2];                                 /*接点3第2次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_2_down_p20[2];                                 /*接点3第2次下降值P20(前低后高，有符号双字节）*/

    uint8_t contact3_3_down_pt[2];                                 /*接点3第3次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_3_down_p20[2];                                 /*接点3第3次下降值P20(前低后高，有符号双字节）*/    

    uint8_t contact3_down_avg_pt[2];                                 /*接点3下降平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact3_down_avg_p20[2];                                 /*接点3下降平均值P20(前低后高，有符号双字节）*/




    uint8_t contact1_1_up_pt[2];                                 /*接点1第1次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_1_up_p20[2];                                 /*接点1第1次上升值P20(前低后高，有符号双字节）*/
    
    uint8_t contact1_2_up_pt[2];                                 /*接点1第2次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_2_up_p20[2];                                 /*接点1第2次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact1_3_up_pt[2];                                 /*接点1第3次上升值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_3_up_p20[2];                                 /*接点1第3次上升值P20(前低后高，有符号双字节）*/

    uint8_t contact1_up_avg_pt[2];                                 /*接点1上升平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_up_avg_p20[2];                                 /*接点1上升平均值P20(前低后高，有符号双字节）*/

    uint8_t contact1_1_down_pt[2];                                 /*接点1第1次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_1_down_p20[2];                                 /*接点1第1次下降值P20(前低后高，有符号双字节）*/
    
    uint8_t contact1_2_down_pt[2];                                 /*接点1第2次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_2_down_p20[2];                                 /*接点1第2次下降值P20(前低后高，有符号双字节）*/

    uint8_t contact1_3_down_pt[2];                                 /*接点1第3次下降值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_3_down_p20[2];                                 /*接点1第3次下降值P20(前低后高，有符号双字节）*/    

    uint8_t contact1_down_avg_pt[2];                                 /*接点1下降平均值Pt(前低后高，有符号双字节）*/
    uint8_t contact1_down_avg_p20[2];                                 /*接点1下降平均值P20(前低后高，有符号双字节）*/

} JD11_MessageDataType;

typedef struct
{
    uint8_t time[16];                          /* 时间 */
    double temp;                              /* 温度 */
    double contact_type;                           /* 接点类型 */
    
    double contact2_1_up_pt;                                 /*接点2第1次上升值Pt(前低后高，有符号双字节）*/
    double contact2_1_up_p20;                                 /*接点2第1次上升值P20(前低后高，有符号双字节）*/
    
    double contact2_2_up_pt;                                 /*接点2第2次上升值Pt(前低后高，有符号双字节）*/
    double contact2_2_up_p20;                                 /*接点2第2次上升值P20(前低后高，有符号双字节）*/

    double contact2_3_up_pt;                                 /*接点2第3次上升值Pt(前低后高，有符号双字节）*/
    double contact2_3_up_p20;                                 /*接点2第3次上升值P20(前低后高，有符号双字节）*/

    double contact2_up_avg_pt;                                 /*接点2上升平均值Pt(前低后高，有符号双字节）*/
    double contact2_up_avg_p20;                                 /*接点2上升平均值P20(前低后高，有符号双字节）*/

    double contact2_1_down_pt;                                 /*接点2第1次下降值Pt(前低后高，有符号双字节）*/
    double contact2_1_down_p20;                                 /*接点2第1次下降值P20(前低后高，有符号双字节）*/
    
    double contact2_2_down_pt;                                 /*接点2第2次下降值Pt(前低后高，有符号双字节）*/
    double contact2_2_down_p20;                                 /*接点2第2次下降值P20(前低后高，有符号双字节）*/

    double contact2_3_down_pt;                                 /*接点2第3次下降值Pt(前低后高，有符号双字节）*/
    double contact2_3_down_p20;                                 /*接点2第3次下降值P20(前低后高，有符号双字节）*/    

    double contact2_down_avg_pt;                                 /*接点2下降平均值Pt(前低后高，有符号双字节）*/
    double contact2_down_avg_p20;                                 /*接点2下降平均值P20(前低后高，有符号双字节）*/




    double contact3_1_up_pt;                                 /*接点3第1次上升值Pt(前低后高，有符号双字节）*/
    double contact3_1_up_p20;                                 /*接点3第1次上升值P20(前低后高，有符号双字节）*/
    
    double contact3_2_up_pt;                                 /*接点3第2次上升值Pt(前低后高，有符号双字节）*/
    double contact3_2_up_p20;                                 /*接点3第2次上升值P20(前低后高，有符号双字节）*/

    double contact3_3_up_pt;                                 /*接点3第3次上升值Pt(前低后高，有符号双字节）*/
    double contact3_3_up_p20;                                 /*接点3第3次上升值P20(前低后高，有符号双字节）*/

    double contact3_up_avg_pt;                                 /*接点3上升平均值Pt(前低后高，有符号双字节）*/
    double contact3_up_avg_p20;                                 /*接点3上升平均值P20(前低后高，有符号双字节）*/

    double contact3_1_down_pt;                                 /*接点3第1次下降值Pt(前低后高，有符号双字节）*/
    double contact3_1_down_p20;                                 /*接点3第1次下降值P20(前低后高，有符号双字节）*/
    
    double contact3_2_down_pt;                                 /*接点3第2次下降值Pt(前低后高，有符号双字节）*/
    double contact3_2_down_p20;                                 /*接点3第2次下降值P20(前低后高，有符号双字节）*/

    double contact3_3_down_pt;                                 /*接点3第3次下降值Pt(前低后高，有符号双字节）*/
    double contact3_3_down_p20;                                 /*接点3第3次下降值P20(前低后高，有符号双字节）*/    

    double contact3_down_avg_pt;                                 /*接点3下降平均值Pt(前低后高，有符号双字节）*/
    double contact3_down_avg_p20;                                 /*接点3下降平均值P20(前低后高，有符号双字节）*/




    double contact1_1_up_pt;                                 /*接点1第1次上升值Pt(前低后高，有符号双字节）*/
    double contact1_1_up_p20;                                 /*接点1第1次上升值P20(前低后高，有符号双字节）*/
    
    double contact1_2_up_pt;                                 /*接点1第2次上升值Pt(前低后高，有符号双字节）*/
    double contact1_2_up_p20;                                 /*接点1第2次上升值P20(前低后高，有符号双字节）*/

    double contact1_3_up_pt;                                 /*接点1第3次上升值Pt(前低后高，有符号双字节）*/
    double contact1_3_up_p20;                                 /*接点1第3次上升值P20(前低后高，有符号双字节）*/

    double contact1_up_avg_pt;                                 /*接点1上升平均值Pt(前低后高，有符号双字节）*/
    double contact1_up_avg_p20;                                 /*接点1上升平均值P20(前低后高，有符号双字节）*/

    double contact1_1_down_pt;                                 /*接点1第1次下降值Pt(前低后高，有符号双字节）*/
    double contact1_1_down_p20;                                 /*接点1第1次下降值P20(前低后高，有符号双字节）*/
    
    double contact1_2_down_pt;                                 /*接点1第2次下降值Pt(前低后高，有符号双字节）*/
    double contact1_2_down_p20;                                 /*接点1第2次下降值P20(前低后高，有符号双字节）*/

    double contact1_3_down_pt;                                 /*接点1第3次下降值Pt(前低后高，有符号双字节）*/
    double contact1_3_down_p20;                                 /*接点1第3次下降值P20(前低后高，有符号双字节）*/    

    double contact1_down_avg_pt;                                 /*接点1下降平均值Pt(前低后高，有符号双字节）*/
    double contact1_down_avg_p20;                                 /*接点1下降平均值P20(前低后高，有符号双字节）*/
} JD11_ValueType;
/***************************************************************************************/
typedef struct
{
    uint8_t Head;
    uint8_t Data[150];
} JD11_MessageType;

uint16_t JD11ReadData(uint8_t *buff, uint8_t cnt);
char *JD11RecvMessage(uint8_t *buff, uint16_t size);

#endif /* APPLICATION_MIDDLEDRIVERS_JD11_H_ */
