#include "BMX160_use.h"
#include "BMX160_Control.h"
#include "BMX160_Register.h"
#include "BMX160_Algorithm.h"
#include "usart.h"

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
/**
  * @brief BMX160��ʼ��
  * @retval ��ʼ�����
  */
int BMX160_Init(void)
{
    if (BMX160_Pretreatment() != BMX160_OK) //��ʼ���ṹ��
    {
        return BMX160_Error;
    }
    //��ȡ�豸ID
    uint8_t DATA = {0};
    BMX160_Get_ChipID(&BMX160_1, &DATA);
    printf("%X\n", DATA);
    //�����豸
    BMX160_CMD(&BMX160_1, BMX160_CMD_Softreset);
    HAL_Delay(100);
    //����������������Ϊ��ͨģʽ
    BMX160_CMD(&BMX160_1, BMX160_CMD_PMU_ACC_Normal);
    HAL_Delay(10);
    BMX160_CMD(&BMX160_1, BMX160_CMD_PMU_GYR_Normal);
    HAL_Delay(80);
    BMX160_CMD(&BMX160_1, BMX160_CMD_PMU_MAG_Normal);
    HAL_Delay(10);
    //��ȡ����ģʽ
    int Mode[3];
    BMX160_Get_PMU_STATUS(&BMX160_1, &Mode[0], &Mode[1], &Mode[2], Report_Y);
    float DATA1 = 0;
    BMX160_Get_Temperature(&BMX160_1, &DATA1);
    printf("%f\n", DATA1);
    //���ü��ٶȼƲ�������
    BMX160_ACC_Sampling_Mode(&BMX160_1, BMX160_ACC_Normal_Oversampling, BMX160_ACC_ODR_100);
    BMX160_ACC_RANGE(&BMX160_1, BMX160_1.ACC_CONF_RANGE.ACC_RANGE);
    //���������ǲ�������
    BMX160_GYR_Sampling_Mode(&BMX160_1, BMX160_GYR_Normal_Oversampling, BMX160_GYR_ODR_100);
    BMX160_GYR_RANGE(&BMX160_1, BMX160_1.GYR_CONF_RANGE.GYR_RANGE);
    //���ô����Ʋ�������
    BMX160_MAG_Sampling_Mode(&BMX160_1, BMX160_1.MAG_CONF_RANGE.MAG_XY_Mode, BMX160_1.MAG_CONF_RANGE.MAG_Z_Mode, BMX160_1.MAG_CONF_RANGE.MAG_odr);
    //У׼
    BMX160_Auto_Calibration(&BMX160_1);

    //��ȡ����
    float ACC_DATA[3] = {0};
    float GYR_DATA[3] = {0};
    float MAG_DATA[3] = {0};
    while (1)
    {
        BMX160_Get_ACC(&BMX160_1, &ACC_DATA[0], &ACC_DATA[1], &ACC_DATA[2]);
        BMX160_Get_GYR(&BMX160_1, &GYR_DATA[0], &GYR_DATA[1], &GYR_DATA[2]);
        BMX160_Get_MAG(&BMX160_1, &MAG_DATA[0], &MAG_DATA[1], &MAG_DATA[2]);
        printf("���ٶȣ�");
        printf("X:%.2f", ACC_DATA[0]);
        printf(",");
        printf("Y:%.2f", ACC_DATA[1]);
        printf(",");
        printf("Z:%.2f", ACC_DATA[2]);
        printf("\r\n");
        printf("�����ǣ�");
        printf("X:%.2f", GYR_DATA[0]);
        printf(",");
        printf("Y:%.2f", GYR_DATA[1]);
        printf(",");
        printf("Z:%.2f", GYR_DATA[2]);
        printf("\r\n");
        printf("�����ƣ�");
        printf("X:%.2f", MAG_DATA[0]);
        printf(",");
        printf("Y:%.2f", MAG_DATA[1]);
        printf(",");
        printf("Z:%.2f", MAG_DATA[2]);
        printf("\r\n\r\n\r\n");

        HAL_Delay(500);
    }
}
/**
  * @brief ֱ�ӻ�ȡ�����Ƶ��������
  * @param BMX160��Ŀ���豸
  * @param DATA_X��X�����
  * @param DATA_Y��Y�����
  * @param DATA_Z��Z�����
  * @retval ��ʼ�����
  */
int BMX160_Get_MAG(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z)
{
    uint8_t DATA_IN[6] = {0};
    if (BMX160_Read(&*BMX160, R_DATA_0, DATA_IN, 6) != BMX160_OK)
    {
        return BMX160_Error;
    }
    uint16_t DATA[3] = {0};
    DATA[0] = (DATA_IN[1] << 8) + (DATA_IN[0]);
    DATA[1] = (DATA_IN[3] << 8) + (DATA_IN[2]);
    DATA[2] = (DATA_IN[5] << 8) + (DATA_IN[4]);
    *DATA_X = DATA[0] / 16.0;
    *DATA_Y = DATA[1] / 16.0;
    *DATA_Z = DATA[2] / 16.0;

    if (*DATA_X > 2048)
    {
        *DATA_X = *DATA_X - 4096;
    }
    if (*DATA_Y > 2048)
    {
        *DATA_Y = *DATA_Y - 4096;
    }
    if (*DATA_Z > 2048)
    {
        *DATA_Z = *DATA_Z - 4096;
    }
}
/**
  * @brief ֱ�ӻ�ȡ���ٶȼƵ��������
  * @param BMX160��Ŀ���豸
  * @param DATA_X��X�����
  * @param DATA_Y��Y�����
  * @param DATA_Z��Z�����
  * @retval ��ʼ�����
  */
int BMX160_Get_ACC(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z)
{
    uint8_t DATA_IN[6] = {0};
    if (BMX160_Read(&*BMX160, R_DATA_14, DATA_IN, 6) != BMX160_OK)
    {
        return BMX160_Error;
    }
    uint16_t DATA[3] = {0};
    DATA[0] = (DATA_IN[1] << 8) + (DATA_IN[0]);
    DATA[1] = (DATA_IN[3] << 8) + (DATA_IN[2]);
    DATA[2] = (DATA_IN[5] << 8) + (DATA_IN[4]);
    if (BMX160->ACC_CONF_RANGE.ACC_RANGE == BMX160_ACC_RANGE_2g)
    {
        *DATA_X = DATA[0] / 16384.0;
        *DATA_Y = DATA[1] / 16384.0;
        *DATA_Z = DATA[2] / 16384.0;

        if (*DATA_X > 2)
        {
            *DATA_X = *DATA_X - 4;
        }
        if (*DATA_Y > 2)
        {
            *DATA_Y = *DATA_Y - 4;
        }
        if (*DATA_Z > 2)
        {
            *DATA_Z = *DATA_Z - 4;
        }
    }
    else if (BMX160->ACC_CONF_RANGE.ACC_RANGE == BMX160_ACC_RANGE_4g)
    {
        *DATA_X = DATA[0] / 8192.0;
        *DATA_Y = DATA[1] / 8192.0;
        *DATA_Z = DATA[2] / 8192.0;
        if (*DATA_X > 4)
        {
            *DATA_X = *DATA_X - 8;
        }
        if (*DATA_Y > 4)
        {
            *DATA_Y = *DATA_Y - 8;
        }
        if (*DATA_Z > 4)
        {
            *DATA_Z = *DATA_Z - 8;
        }
    }
    else if (BMX160->ACC_CONF_RANGE.ACC_RANGE == BMX160_ACC_RANGE_8g)
    {
        *DATA_X = DATA[0] / 4096.0;
        *DATA_Y = DATA[1] / 4096.0;
        *DATA_Z = DATA[2] / 4096.0;
        if (*DATA_X > 8)
        {
            *DATA_X = *DATA_X - 16;
        }
        if (*DATA_Y > 8)
        {
            *DATA_Y = *DATA_Y - 16;
        }
        if (*DATA_Z > 8)
        {
            *DATA_Z = *DATA_Z - 16;
        }
    }
    else if (BMX160->ACC_CONF_RANGE.ACC_RANGE == BMX160_ACC_RANGE_16g)
    {
        *DATA_X = DATA[0] / 2048.0;
        *DATA_Y = DATA[1] / 2048.0;
        *DATA_Z = DATA[2] / 2048.0;
        if (*DATA_X > 16)
        {
            *DATA_X = *DATA_X - 32;
        }
        if (*DATA_Y > 16)
        {
            *DATA_Y = *DATA_Y - 32;
        }
        if (*DATA_Z > 16)
        {
            *DATA_Z = *DATA_Z - 32;
        }
    }
    else
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ֱ�ӻ�ȡ�����ǵ��������
  * @param BMX160��Ŀ���豸
  * @param DATA_X��X�����
  * @param DATA_Y��Y�����
  * @param DATA_Z��Z�����
  * @retval ��ʼ�����
  */
int BMX160_Get_GYR(Sensor_BMX160 *BMX160, float *DATA_X, float *DATA_Y, float *DATA_Z)
{
    uint8_t DATA_IN[6] = {0};
    if (BMX160_Read(&*BMX160, R_DATA_8, DATA_IN, 6) != BMX160_OK)
    {
        return BMX160_Error;
    }
    uint16_t DATA[3] = {0};
    DATA[0] = (DATA_IN[1] << 8) + (DATA_IN[0]);
    DATA[1] = (DATA_IN[3] << 8) + (DATA_IN[2]);
    DATA[2] = (DATA_IN[5] << 8) + (DATA_IN[4]);

    if (BMX160->GYR_CONF_RANGE.GYR_RANGE == BMX160_GYR_RANGE_2000)
    {
        *DATA_X = (DATA[0] / 16.3);
        *DATA_Y = (DATA[1] / 16.3);
        *DATA_Z = (DATA[2] / 16.3);
        if (*DATA_X > 2000)
        {
            *DATA_X = *DATA_X - 4000;
        }
        if (*DATA_Y > 2000)
        {
            *DATA_Y = *DATA_Y - 4000;
        }
        if (*DATA_Z > 2000)
        {
            *DATA_Z = *DATA_Z - 4000;
        }
    }
    else if (BMX160->GYR_CONF_RANGE.GYR_RANGE == BMX160_GYR_RANGE_1000)
    {
        *DATA_X = (DATA[0] / 32.8);
        *DATA_Y = (DATA[1] / 32.8);
        *DATA_Z = (DATA[2] / 32.8);
        if (*DATA_X > 1000)
        {
            *DATA_X = *DATA_X - 2000;
        }
        if (*DATA_Y > 1000)
        {
            *DATA_Y = *DATA_Y - 2000;
        }
        if (*DATA_Z > 1000)
        {
            *DATA_Z = *DATA_Z - 2000;
        }
    }
    else if (BMX160->GYR_CONF_RANGE.GYR_RANGE == BMX160_GYR_RANGE_500)
    {
        *DATA_X = (DATA[0] / 65.6);
        *DATA_Y = (DATA[1] / 65.6);
        *DATA_Z = (DATA[2] / 65.6);
        if (*DATA_X > 500)
        {
            *DATA_X = *DATA_X - 1000;
        }
        if (*DATA_Y > 500)
        {
            *DATA_Y = *DATA_Y - 1000;
        }
        if (*DATA_Z > 500)
        {
            *DATA_Z = *DATA_Z - 1000;
        }
    }
    else if (BMX160->GYR_CONF_RANGE.GYR_RANGE == BMX160_GYR_RANGE_250)
    {
        *DATA_X = (DATA[0] / 131.2);
        *DATA_Y = (DATA[1] / 131.2);
        *DATA_Z = (DATA[2] / 131.2);
        if (*DATA_X > 250)
        {
            *DATA_X = *DATA_X - 500;
        }
        if (*DATA_Y > 250)
        {
            *DATA_Y = *DATA_Y - 500;
        }
        if (*DATA_Z > 250)
        {
            *DATA_Z = *DATA_Z - 500;
        }
    }
    else if (BMX160->GYR_CONF_RANGE.GYR_RANGE == BMX160_GYR_RANGE_125)
    {
        *DATA_X = (DATA[0] / 262.4);
        *DATA_Y = (DATA[1] / 262.4);
        *DATA_Z = (DATA[2] / 262.4);

        if (*DATA_X > 125)
        {
            *DATA_X = *DATA_X - 250;
        }
        if (*DATA_Y > 125)
        {
            *DATA_Y = *DATA_Y - 250;
        }
        if (*DATA_Z > 125)
        {
            *DATA_Z = *DATA_Z - 250;
        }
    }
    return BMX160_OK;
}

/**
  * @brief ��ȡ�豸ID
  * @param BMX160��Ŀ���豸
  * @param Chip_ID���豸ID
  * @retval ��ʼ�����
  */
int BMX160_Get_ChipID(Sensor_BMX160 *BMX160, uint8_t *Chip_ID)
{
    if (BMX160_Read(&*BMX160, R_CHIP_ID, Chip_ID, 1) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ���ü��ٶȼƲ�������
  * @param BMX160��Ŀ���豸
  * @param Sampling_Mode����������
  * @param ACC_ODR���������
  * @retval ���ý��
  */
int BMX160_ACC_Sampling_Mode(Sensor_BMX160 *BMX160, int Sampling_Mode, int ACC_ODR)
{
    //������ģʽ�£�������ʲ��ܵ���12.5/HZ
    if ((Sampling_Mode == BMX160_ACC_Normal_Oversampling || Sampling_Mode == BMX160_ACC_OSR2_Oversampling || Sampling_Mode == BMX160_ACC_OSR4_Oversampling) && (ACC_ODR == BMX160_ACC_ODR_0_78125 || ACC_ODR == BMX160_ACC_ODR_1_5625 || ACC_ODR == BMX160_ACC_ODR_3_125 || ACC_ODR == BMX160_ACC_ODR_6_25))
    {
        return BMX160_Error;
    }
    if (Sampling_Mode == BMX160_ACC_Normal_Oversampling) //�����˲���
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x0;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x2;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_OSR2_Oversampling) //2��������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x0;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_OSR4_Oversampling) //4��������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x0;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x0;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //1ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x0;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //2ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //4ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x2;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //8ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x3;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //16ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x4;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //32ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x5;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //64ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x6;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else if (Sampling_Mode == BMX160_ACC_1_Undersampling) //128ƽ������
    {
        BMX160->ACC_CONF_RANGE.ACC_us = 0x1;
        BMX160->ACC_CONF_RANGE.ACC_bwp = 0x7;
        BMX160->ACC_CONF_RANGE.ACC_odr = ACC_ODR;
    }
    else
    {
        return BMX160_Error;
    }
    uint8_t DATA_OUT = {0};
    DATA_OUT = Bit_Modification(DATA_OUT, 7, 7, BMX160->ACC_CONF_RANGE.ACC_us);
    DATA_OUT = Bit_Modification(DATA_OUT, 4, 6, BMX160->ACC_CONF_RANGE.ACC_bwp);
    DATA_OUT = Bit_Modification(DATA_OUT, 0, 3, BMX160->ACC_CONF_RANGE.ACC_odr);
    if (BMX160_Write(&*BMX160, R_ACC_CONF, DATA_OUT) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ���ü��ٶȼ�g��Χ
  * @param BMX160��Ŀ���豸
  * @param ACC_RANGE��g��Χ
  * @retval ���ý��
  */
int BMX160_ACC_RANGE(Sensor_BMX160 *BMX160, int ACC_RANGE)
{
    if (ACC_RANGE == BMX160_ACC_RANGE_2g || ACC_RANGE == BMX160_ACC_RANGE_4g || ACC_RANGE == BMX160_ACC_RANGE_8g || ACC_RANGE == BMX160_ACC_RANGE_16g)
    {
        BMX160->ACC_CONF_RANGE.ACC_RANGE = ACC_RANGE;
    }
    else
    {
        return BMX160_Error;
    }
    //д���豸
    uint8_t DATA_OUT = {0};
    DATA_OUT = Bit_Modification(DATA_OUT, 0, 3, BMX160->ACC_CONF_RANGE.ACC_RANGE);
    if (BMX160_Write(&*BMX160, R_ACC_RANGE, DATA_OUT) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //��ȡ���ٶ����ݣ�ˢ������
    float DATA[3] = {0};
    if (BMX160_Get_ACC(&*BMX160, &DATA[0], &DATA[1], &DATA[2]) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ���������ǲ�������
  * @param BMX160��Ŀ���豸
  * @param Sampling_Mode����������
  * @param GYR_ODR���������
  * @retval ���ý��
  */
int BMX160_GYR_Sampling_Mode(Sensor_BMX160 *BMX160, int Sampling_Mode, int GYR_ODR)
{
    if (Sampling_Mode == BMX160_GYR_Normal_Oversampling)
    {
        BMX160->GYR_CONF_RANGE.GYR_bwp = 0x2;
    }
    else if (Sampling_Mode == BMX160_GYR_OSR2_Oversampling)
    {
        BMX160->GYR_CONF_RANGE.GYR_bwp = 0x1;
    }
    else if (Sampling_Mode == BMX160_GYR_OSR4_Oversampling)
    {
        BMX160->GYR_CONF_RANGE.GYR_bwp = 0x0;
    }
    else
    {
        return BMX160_Error;
    }
    BMX160->GYR_CONF_RANGE.GYR_odr = GYR_ODR;
    uint8_t DATA_OUT = {0};
    DATA_OUT = Bit_Modification(DATA_OUT, 4, 6, BMX160->GYR_CONF_RANGE.GYR_bwp);
    DATA_OUT = Bit_Modification(DATA_OUT, 0, 3, BMX160->GYR_CONF_RANGE.GYR_odr);
    if (BMX160_Write(&*BMX160, R_GYR_CONF, DATA_OUT) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}

/**
  * @brief ���������ǽ��ٶȷ�Χ
  * @param BMX160��Ŀ���豸
  * @param GYR_RANGE�����ٶȷ�Χ
  * @retval ���ý��
  */
int BMX160_GYR_RANGE(Sensor_BMX160 *BMX160, int GYR_RANGE)
{
    if (GYR_RANGE == BMX160_GYR_RANGE_2000 || GYR_RANGE == BMX160_GYR_RANGE_1000 || GYR_RANGE == BMX160_GYR_RANGE_500 || GYR_RANGE == BMX160_GYR_RANGE_250 || GYR_RANGE == BMX160_GYR_RANGE_125)
    {
        BMX160->GYR_CONF_RANGE.GYR_RANGE = GYR_RANGE;
    }
    else
    {
        return BMX160_Error;
    }
    //д���豸
    uint8_t DATA_OUT = {0};
    DATA_OUT = Bit_Modification(DATA_OUT, 0, 3, BMX160->GYR_CONF_RANGE.GYR_RANGE);
    if (BMX160_Write(&*BMX160, R_GYR_RANGE, DATA_OUT) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //��ȡ���ٶ����ݣ�ˢ������
    float DATA[3] = {0};
    if (BMX160_Get_GYR(&*BMX160, &DATA[0], &DATA[1], &DATA[2]) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ���ô����Ʋ�������
  * @param BMX160��Ŀ���豸
  * @param MAG_XY_Mode��XY�����
  * @param MAG_Z_Mode��Z�����
  * @param MAG_ODR���������
  * @retval ���ý��
  */
int BMX160_MAG_Sampling_Mode(Sensor_BMX160 *BMX160, int MAG_XY_Mode, int MAG_Z_Mode, int MAG_ODR)
{
    if (MAG_XY_Mode == BMX160_MAG_Mode_LowPower || MAG_XY_Mode == BMX160_MAG_Mode_Normal || MAG_XY_Mode == BMX160_MAG_Mode_Strengthen || MAG_XY_Mode == BMX160_MAG_Mode_HighPrecision)
    {
        BMX160->MAG_CONF_RANGE.MAG_XY_Mode = MAG_XY_Mode;
    }
    if (MAG_Z_Mode == BMX160_MAG_Mode_LowPower || MAG_Z_Mode == BMX160_MAG_Mode_Normal || MAG_Z_Mode == BMX160_MAG_Mode_Strengthen || MAG_Z_Mode == BMX160_MAG_Mode_HighPrecision)
    {
        BMX160->MAG_CONF_RANGE.MAG_Z_Mode = MAG_Z_Mode;
    }
    if (MAG_ODR == BMX160_MAG_RANGE_0_78125 || MAG_ODR == BMX160_MAG_RANGE_1_5625 || MAG_ODR == BMX160_MAG_RANGE_3_125 || MAG_ODR == BMX160_MAG_RANGE_6_25 || MAG_ODR == BMX160_MAG_RANGE_12_5 || MAG_ODR == BMX160_MAG_RANGE_25 || MAG_ODR == BMX160_MAG_RANGE_50 || MAG_ODR == BMX160_MAG_RANGE_100 || MAG_ODR == BMX160_MAG_RANGE_200 || MAG_ODR == BMX160_MAG_RANGE_400 || MAG_ODR == BMX160_MAG_RANGE_800)
    {
        BMX160->MAG_CONF_RANGE.MAG_odr = MAG_ODR;
    }

    //CMD����0x19����
    if (BMX160_CMD(&*BMX160, BMX160_CMD_PMU_MAG_Normal) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //д��IF[0]��0x80
    if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x01) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //���д��0x4B,MAG����˯��
    if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x4B) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //��������ģʽ��д��Ԥ��
    if (MAG_XY_Mode == BMX160_MAG_Mode_LowPower)
    {
        //���д��PEPXY
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x01) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x51) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_XY_Mode == BMX160_MAG_Mode_Normal)
    {
        //���д��PEPXY
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x04) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x51) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_XY_Mode == BMX160_MAG_Mode_Strengthen)
    {
        //���д��PEPXY
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x07) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x51) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_XY_Mode == BMX160_MAG_Mode_HighPrecision)
    {
        //���д��PEPXY
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x17) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x51) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }

    if (MAG_Z_Mode == BMX160_MAG_Mode_LowPower)
    {
        //���д��PEPZ
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x02) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x52) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_Z_Mode == BMX160_MAG_Mode_Normal)
    {
        //���д��PEPZ
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x0E) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x52) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_Z_Mode == BMX160_MAG_Mode_Strengthen)
    {
        //���д��PEPZ
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x1A) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x52) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else if (MAG_Z_Mode == BMX160_MAG_Mode_HighPrecision)
    {
        //���д��PEPZ
        if (BMX160_Write(&*BMX160, R_MAG_IF_3, 0x52) != BMX160_OK)
        {
            return BMX160_Error;
        }
        if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x52) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    else
    {
        return BMX160_Error;
    }

    if (BMX160_Write(&*BMX160, R_MAG_IF_2, 0x4C) != BMX160_OK)
    {
        return BMX160_Error;
    }
    if (BMX160_Write(&*BMX160, R_MAG_IF_1, 0x42) != BMX160_OK)
    {
        return BMX160_Error;
    }
    uint8_t DATA_ODR = {0};
    if (MAG_ODR == BMX160_MAG_RANGE_0_78125 || MAG_ODR == BMX160_MAG_RANGE_1_5625 || MAG_ODR == BMX160_MAG_RANGE_3_125 || MAG_ODR == BMX160_MAG_RANGE_6_25 || MAG_ODR == BMX160_MAG_RANGE_12_5 || MAG_ODR == BMX160_MAG_RANGE_25 || MAG_ODR == BMX160_MAG_RANGE_50 || MAG_ODR == BMX160_MAG_RANGE_100 || MAG_ODR == BMX160_MAG_RANGE_200 || MAG_ODR == BMX160_MAG_RANGE_400 || MAG_ODR == BMX160_MAG_RANGE_800)
    {
        DATA_ODR = Bit_Modification(DATA_ODR, 0, 3, MAG_ODR);
        if (BMX160_Write(&*BMX160, R_MAG_CONF, DATA_ODR) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
    if (BMX160_Write(&*BMX160, R_MAG_IF_0, 0x00) != BMX160_OK)
    {
        return BMX160_Error;
    }
    if (MAG_XY_Mode == BMX160_MAG_Mode_LowPower && MAG_Z_Mode == BMX160_MAG_Mode_LowPower)
    {
        if (BMX160_CMD(&*BMX160, BMX160_CMD_PMU_MAG_LowPower) != BMX160_OK)
        {
            return BMX160_Error;
        }
    }
}
/**
  * @brief ��ȡ�������¶�
  * @param BMX160��Ŀ���豸
  * @param DATA���¶�ֵ
  * @retval ��ȡ�Ƿ�ɹ�
  */
int BMX160_Get_Temperature(Sensor_BMX160 *BMX160, float *DATA)
{
    uint8_t DATA_IN[2];
    if (BMX160_Read(&*BMX160, R_TEMPERATURE_0, DATA_IN, 2) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //Tem�ĵ�15λָʾ����������ָʾ��ֵ
    uint16_t Tem = (DATA_IN[1] << 8) + (DATA_IN[0]);
    //����0λ����14λת��Ϊʮ���ƣ��ͷֱ�����ˣ�����0x0000ʱ��23��
    *DATA = (Binary_To_Decimal(&Tem, 0, 14) * 0.001953125) + 23;
    //�ж�����
    if (Extract_text(&Tem, 15) == 1)
    {
        *DATA = -*DATA;
    }
    return BMX160_OK;
}
/**
  * @brief ��ȡ��ǰ����ģʽ
  * @param BMX160��Ŀ���豸
  * @param ACC_Mode�����ٶȼƹ���ģʽ
  * @param GYR_Mode�������ǹ���ģʽ
  * @param MAG_Mode�������Ƽƹ���ģʽ
  * @param report���Ƿ��ϱ�
  * @retval ��ȡ�Ƿ�ɹ�
  */
int BMX160_Get_PMU_STATUS(Sensor_BMX160 *BMX160, int *ACC_Mode, int *GYR_Mode, int *MAG_Mode, int Report)
{
    uint8_t DATA_IN = {0};
    //��ȡ��ǰ���ʼĴ���
    if (BMX160_Read(&*BMX160, R_PMU_STATUS, &DATA_IN, 1) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //���ٶȼ�
    uint16_t DATA = DATA_IN;
    if (Binary_To_Decimal(&DATA, 4, 5) == 0)
    {
        *ACC_Mode = BMX160_POW_MODE_Suspend;
    }
    else if (Binary_To_Decimal(&DATA, 4, 5) == 1)
    {
        *ACC_Mode = BMX160_POW_MODE_Normal;
    }
    else if (Binary_To_Decimal(&DATA, 4, 5) == 2)
    {
        *ACC_Mode = BMX160_POW_MODE_LowPower;
    }
    //������
    if (Binary_To_Decimal(&DATA, 2, 3) == 0)
    {
        *GYR_Mode = BMX160_POW_MODE_Suspend;
    }
    else if (Binary_To_Decimal(&DATA, 2, 3) == 1)
    {
        *GYR_Mode = BMX160_POW_MODE_Normal;
    }
    else if (Binary_To_Decimal(&DATA, 2, 3) == 3)
    {
        *GYR_Mode = BMX160_POW_MODE_FastStartUp;
    }
    //������
    if (Binary_To_Decimal(&DATA, 0, 1) == 0)
    {
        *MAG_Mode = BMX160_POW_MODE_Suspend;
    }
    else if (Binary_To_Decimal(&DATA, 0, 1) == 1)
    {
        *MAG_Mode = BMX160_POW_MODE_Normal;
    }
    else if (Binary_To_Decimal(&DATA, 0, 1) == 2)
    {
        *MAG_Mode = BMX160_POW_MODE_LowPower;
    }
    if (Report == Report_Y)
    {
        printf("BMX160���ʱ���\r\n");
        printf("    ���ٶȣ�");
        if (*ACC_Mode == BMX160_POW_MODE_Suspend)
        {
            printf("��ͣģʽ\r\n");
        }
        else if (*ACC_Mode == BMX160_POW_MODE_Normal)
        {
            printf("��ͨģʽ\r\n");
        }
        else if (*ACC_Mode == BMX160_POW_MODE_LowPower)
        {
            printf("�͹���ģʽ\r\n");
        }
        printf("    �����ǣ�");
        if (*GYR_Mode == BMX160_POW_MODE_Suspend)
        {
            printf("��ͣģʽ\r\n");
        }
        else if (*GYR_Mode == BMX160_POW_MODE_Normal)
        {
            printf("��ͨģʽ\r\n");
        }
        else if (*GYR_Mode == BMX160_POW_MODE_FastStartUp)
        {
            printf("��������ģʽ\r\n");
        }
        printf("    �����ƣ�");
        if (*MAG_Mode == BMX160_POW_MODE_Suspend)
        {
            printf("��ͣģʽ\r\n");
        }
        else if (*MAG_Mode == BMX160_POW_MODE_Normal)
        {
            printf("��ͨģʽ\r\n");
        }
        else if (*MAG_Mode == BMX160_POW_MODE_LowPower)
        {
            printf("�͹���ģʽ\r\n");
        }
    }
    return BMX160_OK;
}
/**
  * @brief CMD����
  * @param BMX160��Ŀ���豸
  * @param CMD��CMD����
  * @retval ���ͽ��
  */
int BMX160_CMD(Sensor_BMX160 *BMX160, uint8_t CMD)
{
    if (BMX160_Write(&*BMX160, R_CMD, CMD) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}
/**
  * @brief ����У׼�����Զ�У׼�豸
  * @param BMX160��Ŀ���豸
  * @retval У׼�Ƿ�ɹ�
  */
int BMX160_Auto_Calibration(Sensor_BMX160 *BMX160)
{
    //��Ҫ��ǰ����У׼����
    //����FOC_CONF�Ĵ���
    uint8_t DATA_FOC_CONF = {0};
    //�����ǿ���ƫ�Ʋ���
    if (BMX160->ACC_GYR_FOC_off.FOC_GYR_EN == BMX160_FOC_GYR_ON || BMX160->ACC_GYR_FOC_off.FOC_GYR_EN == BMX160_FOC_GYR_OFF)
    {
        DATA_FOC_CONF = Bit_Modification(DATA_FOC_CONF, 6, 6, BMX160->ACC_GYR_FOC_off.FOC_GYR_EN);
    }
    else
    {
        return BMX160_Error;
    }
    //���ٶȼ�X�Ჹ��Ŀ��ֵ
    if (BMX160->ACC_GYR_FOC_off.FOC_ACC_X == BMX160_FOC_ACC_Recoup_Ban || BMX160->ACC_GYR_FOC_off.FOC_ACC_X == BMX160_FOC_ACC_Recoup_P_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_X == BMX160_FOC_ACC_Recoup_N_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_X == BMX160_FOC_ACC_Recoup_0g)
    {
        DATA_FOC_CONF = Bit_Modification(DATA_FOC_CONF, 4, 5, BMX160->ACC_GYR_FOC_off.FOC_ACC_X);
    }
    else
    {
        return BMX160_Error;
    }
    //���ٶȼ�Y�Ჹ��Ŀ��ֵ
    if (BMX160->ACC_GYR_FOC_off.FOC_ACC_Y == BMX160_FOC_ACC_Recoup_Ban || BMX160->ACC_GYR_FOC_off.FOC_ACC_Y == BMX160_FOC_ACC_Recoup_P_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_Y == BMX160_FOC_ACC_Recoup_N_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_Y == BMX160_FOC_ACC_Recoup_0g)
    {
        DATA_FOC_CONF = Bit_Modification(DATA_FOC_CONF, 2, 3, BMX160->ACC_GYR_FOC_off.FOC_ACC_Y);
    }
    else
    {
        return BMX160_Error;
    }
    //���ٶȼ�Z�Ჹ��Ŀ��ֵ
    if (BMX160->ACC_GYR_FOC_off.FOC_ACC_Z == BMX160_FOC_ACC_Recoup_Ban || BMX160->ACC_GYR_FOC_off.FOC_ACC_Z == BMX160_FOC_ACC_Recoup_P_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_Z == BMX160_FOC_ACC_Recoup_N_1g || BMX160->ACC_GYR_FOC_off.FOC_ACC_Z == BMX160_FOC_ACC_Recoup_0g)
    {
        DATA_FOC_CONF = Bit_Modification(DATA_FOC_CONF, 0, 1, BMX160->ACC_GYR_FOC_off.FOC_ACC_Z);
    }
    else
    {
        return BMX160_Error;
    }
    if (BMX160_Write(&*BMX160, R_FOC_CONF, DATA_FOC_CONF) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //����У׼
    uint8_t DATA_OFFSET = {0};
    if (BMX160->ACC_GYR_FOC_off.Off_ACC_EN == BMX160_off_ACC_ON || BMX160->ACC_GYR_FOC_off.Off_ACC_EN == BMX160_off_ACC_OFF)
    {
        DATA_OFFSET = Bit_Modification(DATA_OFFSET, 6, 6, BMX160->ACC_GYR_FOC_off.Off_ACC_EN);
    }
    else
    {
        return BMX160_Error;
    }
    if (BMX160->ACC_GYR_FOC_off.Off_GYR_EN == BMX160_off_GYR_ON || BMX160->ACC_GYR_FOC_off.Off_GYR_EN == BMX160_off_GYR_OFF)
    {
        DATA_OFFSET = Bit_Modification(DATA_OFFSET, 7, 7, BMX160->ACC_GYR_FOC_off.Off_GYR_EN);
    }
    else
    {
        return BMX160_Error;
    }
    if (BMX160_Write(&*BMX160, R_OFFSET_6, DATA_OFFSET) != BMX160_OK)
    {
        return BMX160_Error;
    }
    //����У׼����
    if (BMX160_CMD(&*BMX160, BMX160_CMD_StartFoc) != BMX160_OK)
    {
        return BMX160_Error;
    }

    HAL_Delay(100);
    uint8_t DATA_OFF[7] = {0};
    if (BMX160_Read(&*BMX160, R_OFFSET_0, DATA_OFF, 7) != BMX160_OK)
    {
        return BMX160_Error;
    }
    return BMX160_OK;
}