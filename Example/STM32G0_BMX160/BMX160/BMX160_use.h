#ifndef __BMX160_use_H__
#define __BMX160_use_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "BMX160_Control.h"
#include "BMX160_Register.h"
#include "BMX160_Algorithm.h"

//返回值
#define BMX160_OK 0
#define BMX160_Error 1
//是否串口上报
#define Report_Y 1 //上报
#define Report_N 0 //不上报
//功率模式
#define BMX160_POW_MODE_Suspend 0x0     //暂停模式
#define BMX160_POW_MODE_Normal 0x1      //普通模式
#define BMX160_POW_MODE_LowPower 0x2    //低功耗模式
#define BMX160_POW_MODE_FastStartUp 0x3 //快速启动模式
//CMD命令
#define BMX106_CMD_PMU_ACC_Suspend 0x10     //加速度计暂停模式
#define BMX106_CMD_PMU_ACC_Normal 0x11      //加速度计普通模式
#define BMX106_CMD_PMU_ACC_LowPower 0x12    //加速度计低功耗模式
#define BMX106_CMD_PMU_GYR_Suspend 0x14     //陀螺仪计暂停模式
#define BMX106_CMD_PMU_GYR_Normal 0x15      //陀螺仪计普通模式
#define BMX106_CMD_PMU_GYR_FastStartUp 0x17 //陀螺仪计快速启动模式
#define BMX106_CMD_PMU_MAG_Suspend 0x18     //磁力计计暂停模式
#define BMX106_CMD_PMU_MAG_Normal 0x19      //磁力计计普通模式
#define BMX106_CMD_PMU_MAG_LowPower 0x1a    //磁力计计低功耗模式
#define BMX106_CMD_StartFoc 0x03            //加速度和陀螺仪的快速偏移校准
#define BMX106_CMD_ProgNvm 0xa0             //写入NVM
#define BMX106_CMD_FifoFlush 0xb0           //清除Fifo中所有数据
#define BMX106_CMD_IntReset 0xb1            //重置中断引擎
#define BMX106_CMD_Softreset 0xb6           //重启
#define BMX106_CMD_StepCntClr 0xb2          //步数计数器重置

    /*****************功能函数*****************/

    int BMX160_Init(void);
    int BMX160_ACC_RANGE(Sensor_BMX160 *BMX160, int GYR_RANGE);
    int BMX160_ACC_Sampling_Mode(Sensor_BMX160 *BMX160, int Sampling_Mode, int GYR_ODR);
    int BMX160_Get_ChipID(Sensor_BMX160 *BMX160, uint8_t *Chip_ID);
    int BMX160_Get_Temperature(Sensor_BMX160 *BMX160, float *DATA);
    int BMX160_Get_PMU_STATUS(Sensor_BMX160 *BMX160, int *ACC_Mode, int *GYR_Mode, int *MAG_Mode, int Report);
    int BMX160_Get_ACC(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z);
    int BMX160_CMD(Sensor_BMX160 *BMX160, uint8_t CMD);
    int BMX160_Auto_Calibration(Sensor_BMX160 *BMX160);
    int BMX160_Get_GYR(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z);
    int BMX160_GYR_Sampling_Mode(Sensor_BMX160 *BMX160, int Sampling_Mode, int GYR_ODR);
    int BMX160_GYR_RANGE(Sensor_BMX160 *BMX160, int GYR_RANGE);
    int BMX160_Get_MAG(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z);
    int BMX160_MAG_Sampling_Mode(Sensor_BMX160 *BMX160, int MAG_XY_Mode, int MAG_Z_Mode, int MAG_ODR);
		
#ifdef __cplusplus
}
#endif

#endif /* __BMX160_use_H__ */