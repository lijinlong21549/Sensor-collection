/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BME280_H__
#define __BME280_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#define BME280_OK 0
#define BME280_Error 1
//寄存器地址
#define R_ID 0xD0
#define R_Reset 0xE0
#define R_Ctrl_Hum 0xF2
#define R_Status 0xF3
#define R_Ctrl_Meas 0xF4
#define R_Config 0xF5
#define R_Press_MSB 0xF7
#define R_Press_LSB 0xF8
#define R_Press_XLSB 0xF9
#define R_Temp_MSB 0xFA
#define R_Temp_LSB 0xFB
#define R_Temp_XLSB 0xFC
#define R_Hum_MSB 0xFD
#define R_Hum_LSB 0xFE
//补偿参数寄存器
#define R_DIG_T1_MSB 0x88
#define R_DIG_T1_LSB 0x89
#define R_DIG_T2_MSB 0x8A
#define R_DIG_T2_LSB 0x8B
#define R_DIG_T3_MSB 0x8C
#define R_DIG_T3_LSB 0x8D

#define R_DIG_P1_MSB 0x8E
#define R_DIG_P1_LSB 0x8F
#define R_DIG_P2_MSB 0x90
#define R_DIG_P2_LSB 0x91
#define R_DIG_P3_MSB 0x92
#define R_DIG_P3_LSB 0x93
#define R_DIG_P4_MSB 0x94
#define R_DIG_P4_LSB 0x95
#define R_DIG_P5_MSB 0x96
#define R_DIG_P5_LSB 0x97
#define R_DIG_P6_MSB 0x98
#define R_DIG_P6_LSB 0x99
#define R_DIG_P7_MSB 0x9a
#define R_DIG_P7_LSB 0x9b
#define R_DIG_P8_MSB 0x9c
#define R_DIG_P8_LSB 0x9d
#define R_DIG_P9_MSB 0x9e
#define R_DIG_P9_LSB 0x9f

#define R_DIG_H1 0xA1
#define R_DIG_H2_LSB 0xE1
#define R_DIG_H2_MSB 0xE2
#define R_DIG_H3 0xE3
#define R_DIG_H4_MSB 0xE4
#define R_DIG_H4_LSB 0xE5
#define R_DIG_H5_MSB 0xE5
#define R_DIG_H5_LSB 0xE6
#define R_DIG_H6 0xE7
/*****************结构体*****************/
//采样状态
#define BME280_Sensor_ON 1  //开启采样
#define BME280_Sensor_OFF 0 //关闭采样
//过采样
#define BME280_Over_1 0x1
#define BME280_Over_2 0x2
#define BME280_Over_4 0x3
#define BME280_Over_8 0x4
#define BME280_Over_16 0x5
//设备模式
#define BME280_Mode_Sleep 0x0  //睡眠模式
#define BME280_Mode_Forced 0x1 //强制模式
#define BME280_Mode_Normal 0x3 //正常模式
//正常模式下非活动持续时间(ms)
#define BME280_Tstandby_0_5 0x0
#define BME280_Tstandby_62_5 0x1
#define BME280_Tstandby_125 0x2
#define BME280_Tstandby_250 0x3
#define BME280_Tstandby_500 0x4
#define BME280_Tstandby_1000 0x5
#define BME280_Tstandby_10 0x6
#define BME280_Tstandby_20 0x7
//IIR滤波器的时间常数
#define BME280_Filter_OFF 0x0 //关闭
#define BME280_Filter_2 0x1
#define BME280_Filter_4 0x2
#define BME280_Filter_8 0x3
#define BME280_Filter_16 0x4

  /*****************湿度结构体*****************/
  struct Str_BME280_HUM
  {
    int HUM_EN;    //是否跳过采样
    int HUM_Ove;   //过采样参数
    float HUM_Num; //当前湿度
  };
  /*****************温度结构体*****************/
  struct Str_BME280_TEMP
  {
    int TEMP_EN;    //是否跳过采样
    int TEMP_Ove;   //过采样参数
    float TEMP_Num; //当前湿度
  };
  /*****************压力结构体*****************/
  struct Str_BME280_PRESS
  {
    int PRESS_EN;    //是否跳过采样
    int PRESS_Ove;   //过采样参数
    float PRESS_Num; //当前湿度
  };
  /*****************补偿结构体*****************/
  struct Str_BME280_Compensation
  {
    uint32_t DIG_T1;
    uint32_t DIG_T2;
    uint32_t DIG_T3;
    uint32_t DIG_P1;
    uint32_t DIG_P2;
    uint32_t DIG_P3;
    uint32_t DIG_P4;
    uint32_t DIG_P5;
    uint32_t DIG_P6;
    uint32_t DIG_P7;
    uint32_t DIG_P8;
    uint32_t DIG_P9;
    uint32_t DIG_H1;
    uint32_t DIG_H2;
    uint32_t DIG_H3;
    uint32_t DIG_H4;
    uint32_t DIG_H5;
    uint32_t DIG_H6;
  };
  /*****************总结构体*****************/
//通讯方式
#define BME280_IIC 0 //BME280通过IIC通讯
#define BME280_SPI 1 //BME280通过SPI通讯
//用户修改
#define BME280_COM_Mode BME280_IIC //BME280的通讯方式

  //结构体
  typedef struct __BME280
  {
    int COM_Mode;
#if BME280_COM_Mode == BME280_IIC
    I2C_HandleTypeDef IIC_Aisle;
    uint8_t IIC_ADDR;
#else
  SPI_HandleTypeDef SPI_Aisle;
#endif
    uint8_t BME280_ID;   //设备ID
    int BME280_Mode;     //设备模式
    int BME280_Tstandby; //正常模式下非活动持续时间(ms)
    int BME280_IIR_Time; //IIR滤波器的时间常数
    uint32_t t_fine;     //全局温度值
    struct Str_BME280_HUM HUM;
    struct Str_BME280_TEMP TEMP;
    struct Str_BME280_PRESS PRESS;
    struct Str_BME280_Compensation DIG;
  } Sensor_BME280;
  /*****************函数*****************/
  int BME280_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* __BME280_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
