#include "BMX160_Control.h"
#include "BMX160_Register.h"
#include "BMX160_Algorithm.h"
#include "i2c.h"
/*****************结构体*****************/
Sensor_BMX160 BMX160_1;
int BMX160_Pretreatment(void)
{
    BMX160_1.COM_Mode = BMX160_COM_Mode;
#if BMX160_COM_Mode == BMX160_IIC
    BMX160_1.IIC_Aisle = hi2c1;
    BMX160_1.IIC_ADDR = 0x69;
#else
    BMX160_1.SPI_Aisle;
#endif
    /**********加速度策略**********/
    BMX160_1.ACC_CONF_RANGE.ACC_RANGE = BMX160_ACC_RANGE_2g;
    /**********陀螺仪策略**********/
    BMX160_1.GYR_CONF_RANGE.GYR_RANGE = BMX160_GYR_RANGE_125;
    /**********磁力计策略**********/
    BMX160_1.MAG_CONF_RANGE.MAG_XY_Mode = BMX160_MAG_Mode_HighPrecision;
    BMX160_1.MAG_CONF_RANGE.MAG_Z_Mode = BMX160_MAG_Mode_HighPrecision;
    BMX160_1.MAG_CONF_RANGE.MAG_odr = BMX160_MAG_RANGE_12_5;
    /**********校准策略**********/
    BMX160_1.ACC_GYR_FOC_off.FOC_GYR_EN = BMX160_FOC_GYR_ON;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_X = BMX160_FOC_ACC_Recoup_0g;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_Y = BMX160_FOC_ACC_Recoup_0g;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_Z = BMX160_FOC_ACC_Recoup_P_1g;
    BMX160_1.ACC_GYR_FOC_off.Off_ACC_EN = BMX160_off_ACC_ON;
    BMX160_1.ACC_GYR_FOC_off.Off_GYR_EN = BMX160_off_GYR_ON;
    /**********中断策略**********/
    return BMX160_OK;
}
/*****************底层控制函数*****************/
//读写控制函数设计逻辑：
//分别写出IIC和SPI通讯的读写函数，通过总的读写函数判断设备走的通讯方式，分配其通讯的方式
/**
  * @brief IIC写
  * @param BMX160：写目标设备
  * @param DATA：写入的数据
  * @param DATA_NUM：写入数据的数量
  * @retval 写操作反馈
  */
int BMX160_IIC_Write(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t DATA)
{
    uint8_t DATA_OUT[2] = {0};
    DATA_OUT[0] = ADDR;
    DATA_OUT[1] = DATA;
    if (HAL_I2C_Master_Transmit(&(BMX160->IIC_Aisle), (BMX160->IIC_ADDR) << 1, DATA_OUT, 2, 1000) != HAL_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief IIC读
  * @param BMX160：读目标设备
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BMX160_IIC_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
    if (HAL_I2C_Master_Transmit(&(BMX160->IIC_Aisle), (BMX160->IIC_ADDR) << 1, &ADDR, 1, 1000) != HAL_OK)
    {
        return BMX160_Error;
    }
    if (HAL_I2C_Master_Receive(&(BMX160->IIC_Aisle), (BMX160->IIC_ADDR) << 1, DATA, DATA_NUM, 1000) != HAL_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief SPI写
  * @param BMX160：写目标设备
  * @param DATA：写入的数据
  * @param DATA_NUM：写入数据的数量
  * @retval 写操作反馈
  */
int BMX160_SPI_Write(Sensor_BMX160 *BMX160, uint8_t DATA, int DATA_NUM)
{
}
/**
  * @brief SPI读
  * @param BMX160：读目标设备
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BMX160_SPI_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
}
/**
  * @brief 设备写
  * @param BMX160：写目标设备
  * @param ADDR：写入地址
  * @param DATA：写入数据
  * @retval 写操作反馈
  */
int BMX160_Write(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t DATA)
{
    if (BMX160_COM_Mode == BMX160_IIC)
    {
        if (BMX160_IIC_Write(&*BMX160, ADDR, DATA) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (BMX160_COM_Mode == BMX160_SPI)
    {
        if (BMX160_SPI_Write(&*BMX160, ADDR, DATA) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
}
/**
  * @brief 设备读
  * @param BMX160：读目标设备
  * @param ADDR：读取的开始地址
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BMX160_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
    if (BMX160_COM_Mode == BMX160_IIC)
    {
        if (BMX160_IIC_Read(&*BMX160, ADDR, &*DATA, DATA_NUM) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (BMX160_COM_Mode == BMX160_SPI)
    {
        if (BMX160_SPI_Read(&*BMX160, ADDR, &*DATA, DATA_NUM) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
}
