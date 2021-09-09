#include "BMX160_Control.h"
#include "BMX160_Register.h"
#include "BMX160_Algorithm.h"
#include "i2c.h"
/*****************�ṹ��*****************/
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
    /**********���ٶȲ���**********/
    BMX160_1.ACC_CONF_RANGE.ACC_RANGE = BMX160_ACC_RANGE_2g;
    /**********�����ǲ���**********/
    BMX160_1.GYR_CONF_RANGE.GYR_RANGE = BMX160_GYR_RANGE_125;
    /**********�����Ʋ���**********/
    BMX160_1.MAG_CONF_RANGE.MAG_XY_Mode = BMX160_MAG_Mode_HighPrecision;
    BMX160_1.MAG_CONF_RANGE.MAG_Z_Mode = BMX160_MAG_Mode_HighPrecision;
    BMX160_1.MAG_CONF_RANGE.MAG_odr = BMX160_MAG_RANGE_12_5;
    /**********У׼����**********/
    BMX160_1.ACC_GYR_FOC_off.FOC_GYR_EN = BMX160_FOC_GYR_ON;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_X = BMX160_FOC_ACC_Recoup_0g;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_Y = BMX160_FOC_ACC_Recoup_0g;
    BMX160_1.ACC_GYR_FOC_off.FOC_ACC_Z = BMX160_FOC_ACC_Recoup_P_1g;
    BMX160_1.ACC_GYR_FOC_off.Off_ACC_EN = BMX160_off_ACC_ON;
    BMX160_1.ACC_GYR_FOC_off.Off_GYR_EN = BMX160_off_GYR_ON;
    /**********�жϲ���**********/
    return BMX160_OK;
}
/*****************�ײ���ƺ���*****************/
//��д���ƺ�������߼���
//�ֱ�д��IIC��SPIͨѶ�Ķ�д������ͨ���ܵĶ�д�����ж��豸�ߵ�ͨѶ��ʽ��������ͨѶ�ķ�ʽ
/**
  * @brief IICд
  * @param BMX160��дĿ���豸
  * @param DATA��д�������
  * @param DATA_NUM��д�����ݵ�����
  * @retval д��������
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
  * @brief IIC��
  * @param BMX160����Ŀ���豸
  * @param DATA�����������
  * @param DATA_NUM���������ݵ�����
  * @retval ����������
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
  * @brief SPIд
  * @param BMX160��дĿ���豸
  * @param DATA��д�������
  * @param DATA_NUM��д�����ݵ�����
  * @retval д��������
  */
int BMX160_SPI_Write(Sensor_BMX160 *BMX160, uint8_t DATA, int DATA_NUM)
{
}
/**
  * @brief SPI��
  * @param BMX160����Ŀ���豸
  * @param DATA�����������
  * @param DATA_NUM���������ݵ�����
  * @retval ����������
  */
int BMX160_SPI_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
}
/**
  * @brief �豸д
  * @param BMX160��дĿ���豸
  * @param ADDR��д���ַ
  * @param DATA��д������
  * @retval д��������
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
  * @brief �豸��
  * @param BMX160����Ŀ���豸
  * @param ADDR����ȡ�Ŀ�ʼ��ַ
  * @param DATA�����������
  * @param DATA_NUM���������ݵ�����
  * @retval ����������
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
