
#ifndef __OPT3001_H
#define __OPT3001_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
//返回值
#define OPT3001_OK 0
#define OPT3001_Error 1
//寄存器地址
#define R_Result 0x00 //结果寄存器
#define R_Configuration 0x01  //配置寄存器
#define R_Low_Limit 0x02 //低阈值寄存器
#define R_High_Limit 0x03//高阈值寄存器
#define R_Manufacturer_ID 0x7e//制造厂商ID
#define R_Device_ID 0x7f//设备厂商ID
//转换时间
#define Fast_Conversion 0x00       //快速转换
#define completely_Conversion 0x01 //完全精度转换
//转换模式
#define default 0x00    //关机
#define single 0x01     //单次转换
#define continuous 0x2 //连续转换
//中断模式
#define transparent_Hysteresis_style 0x00 //透明滞后式
#define latched_Window_style 0x01         //锁窗式
//中断引脚极性模式
#define Low_efficient 0x00  //低电平有效
#define High_efficient 0x01 //高电平有效
//是否显示指数字段
#define Exponent_show 0x00   //显示指数字段
#define Exponent_shield 0x01 //屏蔽指数字段
//故障报警数量
#define Fault_One 0x00   //一个故障
#define Fault_Two 0x01   //两个故障
#define Fault_Four 0x2  //四个故障
#define Fault_Eight 0x3 //八个故障
//量程选择
#define Range_40_95 0x00//量程：40.95
#define Range_81_90 0x01//量程：81.90
#define Range_163_80 0x02//量程：163.80
#define Range_327_60 0x03//量程：327.60
#define Range_655_20 0x04//量程：655.20
#define Range_1310_40 0x05//量程：1310.40
#define Range_2620_80 0x06//量程：2620.80
#define Range_5241_60 0x07//量程：5241.60
#define Range_10483_20 0x08//量程：10483.20
#define Range_20966_40 0x09//量程：20966.40
#define Range_41932_80 0x0a//量程：41932.80
#define Range_83865_60 0x0b//量程：83865.60
#define Range_AUTO 0x0c//量程：自动量程
    //配置寄存器结构体
    struct RS_Configuration
    {
        uint16_t All;
        int Range;                      //当前量程
        int Conversion_Time;            //转换时间
        uint16_t Conversion_Mode;       //转换模式
        int overflow_Bit;               //溢出指示
        int Conversion_Finish_Bit;      //转换完成标志位
        int High_Limit_Bit;             //高标志位
        int Low_Limit_Bit;              //低标志位
        int Latch_field_Bit;            //中断模式
        int Polarity_Field_Bit;         //INT极性
        int Mask_Exponent_Field_Bit;    //屏蔽指数字段
        uint16_t Fault_Count_Field_Bit; //故障计数字段
    };

    typedef struct __OPT3001
    {
        //中断引脚
        uint16_t INT_Pin;
        GPIO_TypeDef *INT_Prot;
        //所使用的IIC
        I2C_HandleTypeDef IIC_Aisle;
        //IIC地址
        uint8_t IIC_ADDR;
        //最新数值
        float Current_Figure;
        //低阈值
        int Low_Limit;
        //高阈值
        int High_Limit;
        /*配置寄存器数值*/
        struct RS_Configuration Configuration;
        //制造商ID
        uint16_t Manufacturer_ID;
        //设备ID
        uint16_t Device_ID;

    } OPT3001;


int OPT3001_Init(void);
int OPT3001_INT(OPT3001 *OPT3001);
int OPT3001_Read_Device_ID(OPT3001 *OPT3001);
int OPT3001_Read_Manufacturer_ID(OPT3001 *OPT3001);
int OPT3001_Write_Configuration(OPT3001 *OPT3001);
int OPT3001_Read_Brightness(OPT3001 *OPT3001, float *DATA_OUT);
int OPT3001_Write_High_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Write_Low_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Reset(OPT3001 *OPT3001);
extern OPT3001 Eye_1;
#ifdef __cplusplus
}
#endif

#endif /* __OPT3001_H */
