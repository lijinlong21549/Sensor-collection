#ifndef __BMX160_Control_H__
#define __BMX160_Control_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
//通讯方式
#define BMX160_IIC 0 //BMX160通过IIC通讯
#define BMX160_SPI 1 //BMX160通过SPI通讯
//芯片识别码
#define CHIPID 0xD8
    /**************************BMX160加速度计的配置参数和范围**************************/
    /**
  * @brief BMX160加速度计的配置参数和范围
  * @param ACC_us：欠采样参数
  * @param ACC_bwp：带宽参数
  * @param ACC_odr：输出数据速率
  * @param ACC_RANGE：//加速度G范围
  */
//电源模式
#define BMX160_ACC_Normal_mode 0 //正常模式
#define BMX160_ACC_LPower_mode 1 //低功耗模式
//正常模式下
#define BMX160_ACC_Normal_Oversampling 0 //正常滤波器
#define BMX160_ACC_OSR2_Oversampling -1  //2倍过采样
#define BMX160_ACC_OSR4_Oversampling -2  //4倍过采样
//低功耗模式
#define BMX160_ACC_1_Undersampling 1     //1平均样本
#define BMX160_ACC_2_Undersampling 2     //2平均样本
#define BMX160_ACC_4_Undersampling 4     //4平均样本
#define BMX160_ACC_8_Undersampling 8     //8平均样本
#define BMX160_ACC_16_Undersampling 16   //16平均样本
#define BMX160_ACC_32_Undersampling 32   //32平均样本
#define BMX160_ACC_64_Undersampling 64   //64平均样本
#define BMX160_ACC_128_Undersampling 128 //128平均样本
//输出速率
#define BMX160_ACC_ODR_0_78125 0x1 //输出速率0.78125/HZ
#define BMX160_ACC_ODR_1_5625 0x2  //输出速率1.5625/HZ
#define BMX160_ACC_ODR_3_125 0x3   //输出速率3.125/HZ
#define BMX160_ACC_ODR_6_25 0x4    //输出速率6.25/HZ
#define BMX160_ACC_ODR_12_5 0x5    //输出速率12.5/HZ
#define BMX160_ACC_ODR_25 0x6      //输出速率25/HZ
#define BMX160_ACC_ODR_50 0x7      //输出速率50/HZ
#define BMX160_ACC_ODR_100 0x8     //输出速率100/HZ
#define BMX160_ACC_ODR_200 0x9     //输出速率200/HZ
#define BMX160_ACC_ODR_400 0xa     //输出速率400/HZ
#define BMX160_ACC_ODR_800 0xb     //输出速率800/HZ
#define BMX160_ACC_ODR_1600 0xc    //输出速率1600/HZ
//加速度G范围
#define BMX160_ACC_RANGE_2g 0x03  //±2g
#define BMX160_ACC_RANGE_4g 0x05  //±4g
#define BMX160_ACC_RANGE_8g 0x08  //±8g
#define BMX160_ACC_RANGE_16g 0x0c //±16g
    struct Str_BMX160_ACC_CONF_RANGE
    {
        int ACC_us;      //低功耗
        int ACC_bwp;     //滤波器
        uint8_t ACC_odr; //输出速率
        int ACC_RANGE;   //加速度G范围
    };
    /**************************BMX160陀螺仪的配置参数和范围**************************/
    /**
  * @brief BMX160陀螺仪的配置参数和范围
  * @param GYR_bwp：带宽参数
  * @param GYR_odr：输出数据速率
  * @param GYR_RANGE：//角速度范围
  */
//正常模式下
#define BMX160_GYR_Normal_Oversampling 0 //正常滤波器
#define BMX160_GYR_OSR2_Oversampling -1  //2倍过采样
#define BMX160_GYR_OSR4_Oversampling -2  //4倍过采样
//输出速率
#define BMX160_GYR_ODR_25 0x6   //输出速率25/HZ
#define BMX160_GYR_ODR_50 0x7   //输出速率50/HZ
#define BMX160_GYR_ODR_100 0x8  //输出速率100/HZ
#define BMX160_GYR_ODR_200 0x9  //输出速率200/HZ
#define BMX160_GYR_ODR_400 0xa  //输出速率400/HZ
#define BMX160_GYR_ODR_800 0xb  //输出速率800/HZ
#define BMX160_GYR_ODR_1600 0xc //输出速率1600/HZ
#define BMX160_GYR_ODR_3200 0xd //输出速率3200/HZ
//角速度范围
#define BMX160_GYR_RANGE_2000 0x00 //2000/s
#define BMX160_GYR_RANGE_1000 0x01 //1000/s
#define BMX160_GYR_RANGE_500 0x02  //500/s
#define BMX160_GYR_RANGE_250 0x03  //250/s
#define BMX160_GYR_RANGE_125 0x04  //125/s

    struct Str_BMX160_GYR_CONF_RANGE
    {
        int GYR_bwp;     //滤波器
        uint8_t GYR_odr; //输出速率
        int GYR_RANGE;   //角速度范围
    };

/**************************BMX160磁力计的配置参数和范围**************************/
//磁力计模式
#define BMX160_MAG_Mode_LowPower 0      //低功耗模式
#define BMX160_MAG_Mode_Normal 1        //普通模式
#define BMX160_MAG_Mode_Strengthen 2    //增强模式
#define BMX160_MAG_Mode_HighPrecision 3 //高精度模式
//输出速率
#define BMX160_MAG_RANGE_0_78125 0x1
#define BMX160_MAG_RANGE_1_5625 0x2
#define BMX160_MAG_RANGE_3_125 0x3
#define BMX160_MAG_RANGE_6_25 0x4
#define BMX160_MAG_RANGE_12_5 0x5
#define BMX160_MAG_RANGE_25 0x6
#define BMX160_MAG_RANGE_50 0x7
#define BMX160_MAG_RANGE_100 0x8
#define BMX160_MAG_RANGE_200 0x9
#define BMX160_MAG_RANGE_400 0xa
#define BMX160_MAG_RANGE_800 0xb
    struct Str_BMX160_MAG_CONF_RANGE
    {
        int MAG_XY_Mode; //磁力计XY轴模式
        int MAG_Z_Mode;  //磁力计XY轴模式
        uint8_t MAG_odr; //输出速率
    };
/**************************BMX160六轴偏移补偿的配置参数**************************/
#define BMX160_FOC_GYR_ON 0x1           //开启陀螺仪三轴快速偏移补偿
#define BMX160_FOC_GYR_OFF 0x0          //关闭陀螺仪三轴快速偏移补偿
#define BMX160_FOC_ACC_Recoup_Ban 0x00  //加速度计禁用补偿目标值
#define BMX160_FOC_ACC_Recoup_P_1g 0x01 //加速度计补偿目标值1g
#define BMX160_FOC_ACC_Recoup_N_1g 0x02 //加速度计补偿目标值-1g
#define BMX160_FOC_ACC_Recoup_0g 0x03   //加速度计补偿目标值0g
#define BMX160_off_ACC_ON 0x1           //开启加速度计的偏移补偿
#define BMX160_off_ACC_OFF 0x0          //关闭加速度计的偏移补偿
#define BMX160_off_GYR_ON 0x1           //开启加陀螺仪的偏移补偿
#define BMX160_off_GYR_OFF 0x0          //关闭加陀螺仪的偏移补偿
    struct Str_BMX160_ACC_GYR_FOC_off
    {
        int FOC_GYR_EN;         //陀螺仪快速偏移补偿
        uint8_t FOC_ACC_X;      //加速度计X轴补偿目标值
        uint8_t FOC_ACC_Y;      //加速度计Y轴补偿目标值
        uint8_t FOC_ACC_Z;      //加速度计Z轴补偿目标值
        int Off_ACC_EN;         //加速度计偏移补偿
        int Off_GYR_EN;         //陀螺仪偏移补偿
        uint8_t Off_ACC_NUM_X;  //加速度计X轴偏移值
        uint8_t Off_ACC_NUM_Y;  //加速度计Y轴偏移值
        uint8_t Off_ACC_NUM_Z;  //加速度计Z轴偏移值
        uint16_t Off_GYR_NUM_X; //陀螺仪X轴偏移值
        uint16_t Off_GYR_NUM_Y; //陀螺仪Y轴偏移值
        uint16_t Off_GYR_NUM_Z; //陀螺仪Z轴偏移值
    };
//用户修改
#define BMX160_COM_Mode BMX160_IIC //BMX160的通讯方式
    /*****************结构体*****************/

    typedef struct __BMX160
    {
        int COM_Mode;
#if BMX160_COM_Mode == BMX160_IIC
        I2C_HandleTypeDef IIC_Aisle;
        uint8_t IIC_ADDR;
#else
    SPI_HandleTypeDef SPI_Aisle;
#endif
        //中断1
        uint16_t INT1_Pin;
        GPIO_TypeDef *INT1_Prot;
        //中断2
        uint16_t INT2_Pin;
        GPIO_TypeDef *INT2_Prot;
        struct Str_BMX160_ACC_CONF_RANGE ACC_CONF_RANGE;   //BMX160加速度计的配置参数和范围
        struct Str_BMX160_GYR_CONF_RANGE GYR_CONF_RANGE;   //BMX160陀螺仪的配置参数和范围
        struct Str_BMX160_MAG_CONF_RANGE MAG_CONF_RANGE;   //BMX160磁力计的配置参数和范围
        struct Str_BMX160_ACC_GYR_FOC_off ACC_GYR_FOC_off; //BMX160六轴校准参数
    } Sensor_BMX160;
    /*****************函数声明*****************/
    int BMX160_Pretreatment(void);
    int BMX160_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM);
    int BMX160_Write(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t DATA);
    extern Sensor_BMX160 BMX160_1;
#ifdef __cplusplus
}
#endif

#endif /* __BMX160_Control_H__ */
