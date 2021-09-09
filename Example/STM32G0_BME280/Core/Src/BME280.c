#include "BME280.h"
#include "usart.h"
#include "i2c.h"

uint16_t Bit_Modification(uint16_t Reg, int Bit_Start, int Bit_Stop, uint16_t Value);
int Binary_To_Decimal(uint16_t *DATA, int NUM_Start, int NUM_Stop);
int Extract_text(uint16_t *DATA, int NUM);
int BME280_ID(Sensor_BME280 *BME280, uint8_t *ID);
int BME280_Read(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t *DATA, int DATA_NUM);
int BME280_Write(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t DATA);
int BME280_Configuration(Sensor_BME280 *BME280);
int BME280_Reset(Sensor_BME280 *BME280);
int BME280_Get_OLL(Sensor_BME280 *BME280, float *Temp, float *Hum, float *Press);
int BME280_Get_DIG(Sensor_BME280 *BME280);
int BME280_Get_Temp(Sensor_BME280 *BME280, float *DATA);
int BME280_Get_Press(Sensor_BME280 *BME280, float *DATA);
int BME280_Get_HUM(Sensor_BME280 *BME280, float *DATA);
int BME280_Sleep(Sensor_BME280 *BME280);
int BME280_UP(Sensor_BME280 *BME280);
/*****************初始化函数*****************/
Sensor_BME280 BME280_1;
int BME280_Init(void)
{
    /****结构体初始化****/
    //设备参数
    BME280_1.IIC_Aisle = hi2c1;
    BME280_1.IIC_ADDR = 0x77;
    BME280_1.BME280_Mode = BME280_Mode_Normal;
    BME280_1.BME280_IIR_Time = BME280_Filter_16;
    BME280_1.BME280_Tstandby = BME280_Tstandby_0_5;
    //温度参数
    BME280_1.TEMP.TEMP_EN = BME280_Sensor_ON;
    BME280_1.TEMP.TEMP_Ove = BME280_Over_16;
    //湿度参数
    BME280_1.HUM.HUM_EN = BME280_Sensor_ON;
    BME280_1.HUM.HUM_Ove = BME280_Over_16;
    //压力参数
    BME280_1.PRESS.PRESS_EN = BME280_Sensor_ON;
    BME280_1.PRESS.PRESS_Ove = BME280_Over_16;
    /****初始化程序****/
    //复位设备
    if (BME280_Reset(&BME280_1) != BME280_OK)
    {
        return BME280_Error;
    }
    //读取ID
    uint8_t ID = {0};
    BME280_ID(&BME280_1, &ID);
    if (ID == 0x60)
    {
        printf("识别到BME280\r\n");
    }
    else
    {
        printf("未别到BME280\r\n");
    }
    //读取补偿值
    BME280_Get_DIG(&BME280_1);
    //上传配置
    if (BME280_Configuration(&BME280_1) != BME280_OK)
    {
        return BME280_Error;
    }
    HAL_Delay(100);
    float DATA1[3] = 0;
    while (1)
    {
        BME280_UP(&BME280_1);
        //读取温度、湿度、压力
        if (BME280_Get_OLL(&BME280_1, &DATA1[0], &DATA1[1], &DATA1[2]) != BME280_OK)
        {
            return BME280_Error;
        }
        printf("Temp=");
        printf("%0.3f,", DATA1[0]);
        printf("Hum=");
        printf("%0.3f,", DATA1[1]);
        printf("Press=");
        printf("%0.3f\r\n", DATA1[2]);
        BME280_Sleep(&BME280_1);
        HAL_Delay(50);
    }
}
/*****************功能函数*****************/
/**
  * @brief 获取当前温度、湿度、压力
  * @param BME280：目标设备
  * @param Temp：温度
  * @param Hum：湿度
  * @param Press：压力
  * @retval 操作反馈
  */
int BME280_Get_OLL(Sensor_BME280 *BME280, float *Temp, float *Hum, float *Press)
{
    uint8_t DATA_IN[8] = {0};
    if (BME280_Read(&*BME280, R_Press_MSB, DATA_IN, 8) != BME280_OK)
    {
        return BME280_Error;
    }
    uint32_t DAC_T = {0};
    uint32_t DAC_H = {0};
    uint32_t DAC_P = {0};

    DAC_P = (DATA_IN[0] << 12) + (DATA_IN[1] << 4) + (DATA_IN[2] >> 4);
    DAC_T = (DATA_IN[3] << 12) + (DATA_IN[4] << 4) + (DATA_IN[5] >> 4);
    DAC_H = (DATA_IN[6] << 8) + (DATA_IN[7]);

    uint32_t Dig_T1 = BME280->DIG.DIG_T1;
    uint32_t Dig_T2 = BME280->DIG.DIG_T2;
    uint32_t Dig_T3 = BME280->DIG.DIG_T3;
    uint32_t Dig_H1 = BME280->DIG.DIG_H1;
    uint32_t Dig_H2 = BME280->DIG.DIG_H2;
    uint32_t Dig_H3 = BME280->DIG.DIG_H3;
    uint32_t Dig_H4 = BME280->DIG.DIG_H4;
    uint32_t Dig_H5 = BME280->DIG.DIG_H5;
    uint32_t Dig_H6 = BME280->DIG.DIG_H6;
    uint32_t Dig_P1 = BME280->DIG.DIG_P1;
    uint32_t Dig_P2 = BME280->DIG.DIG_P2;
    uint32_t Dig_P3 = BME280->DIG.DIG_P3;
    uint32_t Dig_P4 = BME280->DIG.DIG_P4;
    uint32_t Dig_P5 = BME280->DIG.DIG_P5;
    uint32_t Dig_P6 = BME280->DIG.DIG_P6;
    uint32_t Dig_P7 = BME280->DIG.DIG_P7;
    uint32_t Dig_P8 = BME280->DIG.DIG_P8;
    uint32_t Dig_P9 = BME280->DIG.DIG_P9;
    //温度计算
    double T_var1, T_var2, T = 0;
    T_var1 = (((double)DAC_T) / 16384.0 - ((double)Dig_T1) / 1024.0) * ((double)Dig_T2);
    T_var2 = ((((double)DAC_T) / 131072.0 - ((double)Dig_T1) / 8192.0) * (((double)DAC_T) / 131072.0 - ((double)Dig_T1) / 8192.0)) * ((double)Dig_T3);
    BME280->t_fine = (double)(T_var1 + T_var2);
    T = (T_var1 + T_var2) / 5120.0;
    *Temp = T;
    //湿度计算
    double Var_H;
    Var_H = (((double)BME280->t_fine) - 76800.0);
    Var_H = (DAC_H - (((double)Dig_H4) * 64.0 + ((double)Dig_H5) / 16384.0 * Var_H)) * (((double)Dig_H2) / 65536.0 * (1.0 + ((double)Dig_H6) / 67108864.0 * Var_H * (1.0 + ((double)Dig_H3) / 67108864.0 * Var_H)));
    Var_H = Var_H * (1.0 - ((double)Dig_H1) * Var_H / 524288.0);

    if (Var_H > 100.0)
    {
        Var_H = 100.0;
    }
    else if (Var_H < 0.0)
    {
        Var_H = 0.0;
    }
    *Hum = Var_H;
    //压力计算
    double P_var1 = {0};
    double P_var2 = {0};
    double p = {0};

    P_var1 = ((double)BME280->t_fine / 2.0) - 64000.0;
    P_var2 = P_var1 * P_var1 * ((double)Dig_P6) / 32768.0;
    P_var2 = P_var2 + P_var1 * ((double)Dig_P5) * 2.0;
    P_var2 = (P_var2 / 4.0) + (((double)Dig_P4) * 65536.0);
    P_var1 = (((double)Dig_P3) * P_var1 * P_var1 / 524288.0 + ((double)Dig_P2) * P_var1) / 524288.0;
    P_var1 = (1.0 + P_var1 / 32768.0) * ((double)Dig_P1);
    if (P_var1 == 0.0)
    {
        return BME280_Error;
    }
    p = 1048576.0 - (double)DAC_P;
    p = (p - (P_var2 / 4096.0)) * 6250.0 / P_var1;
    P_var1 = ((double)Dig_P9) * p * p / 2147483648.0;
    P_var2 = p * ((double)Dig_P8) / 32768.0;
    p = (p + (P_var1 + P_var2 + ((double)Dig_P7)) / 16.0) / 100.0;
    *Press = p;
    return BME280_OK;
}
/**
  * @brief 获取当前温度
  * @param BME280：目标设备
  * @param DATA：获得的数据
  * @retval 操作反馈
  */
int BME280_Get_Temp(Sensor_BME280 *BME280, float *DATA)
{

    //读取温度值
    uint8_t DATA_IN[3] = {0};
    if (BME280_Read(&*BME280, R_Temp_MSB, DATA_IN, 3) != BME280_OK)
    {
        return BME280_Error;
    }
    //整合数值
    uint32_t DAC_T = {0};
    DAC_T = (DATA_IN[0] << 12) + (DATA_IN[1] << 4) + (DATA_IN[2] >> 4);

    uint32_t Dig_T1 = BME280->DIG.DIG_T1;
    uint32_t Dig_T2 = BME280->DIG.DIG_T2;
    uint32_t Dig_T3 = BME280->DIG.DIG_T3;

    //补偿公式参考官方文档
    double var1, var2, T = 0;
    var1 = (((double)DAC_T) / 16384.0 - ((double)Dig_T1) / 1024.0) * ((double)Dig_T2);
    var2 = ((((double)DAC_T) / 131072.0 - ((double)Dig_T1) / 8192.0) * (((double)DAC_T) / 131072.0 - ((double)Dig_T1) / 8192.0)) * ((double)Dig_T3);
    BME280->t_fine = (double)(var1 + var2);
    T = (var1 + var2) / 5120.0;
    *DATA = T;
    //printf("%f\r\n", *DATA);
    return BME280_OK;
}
/**
  * @brief 获取当前湿度
  * @param BME280：目标设备
  * @param DATA：获得的数据
  * @retval 操作反馈
  */
int BME280_Get_HUM(Sensor_BME280 *BME280, float *DATA)
{
    //读取湿度值
    uint8_t DATA_IN[2] = {0};
    if (BME280_Read(&*BME280, R_Hum_MSB, DATA_IN, 2) != BME280_OK)
    {
        return BME280_Error;
    }
    //整合数值
    uint32_t DAC_H = {0};
    DAC_H = (DATA_IN[0] << 8) + (DATA_IN[1]);

    uint32_t v_x1 = {0};
    uint32_t Dig_H1 = BME280->DIG.DIG_H1;
    uint32_t Dig_H2 = BME280->DIG.DIG_H2;
    uint32_t Dig_H3 = BME280->DIG.DIG_H3;
    uint32_t Dig_H4 = BME280->DIG.DIG_H4;
    uint32_t Dig_H5 = BME280->DIG.DIG_H5;
    uint32_t Dig_H6 = BME280->DIG.DIG_H6;
    //补偿公式参考官方文档

    double Var_H;
    Var_H = (((double)BME280->t_fine) - 76800.0);
    Var_H = (DAC_H - (((double)Dig_H4) * 64.0 + ((double)Dig_H5) / 16384.0 * Var_H)) * (((double)Dig_H2) / 65536.0 * (1.0 + ((double)Dig_H6) / 67108864.0 * Var_H * (1.0 + ((double)Dig_H3) / 67108864.0 * Var_H)));
    Var_H = Var_H * (1.0 - ((double)Dig_H1) * Var_H / 524288.0);

    if (Var_H > 100.0)
    {
        Var_H = 100.0;
    }
    else if (Var_H < 0.0)
    {
        Var_H = 0.0;
    }
    *DATA = Var_H;
    //printf("%f\r\n", *DATA);
    return BME280_OK;
}

/**
  * @brief 获取当前压力
  * @param BME280：目标设备
  * @param DATA：获得的数据
  * @retval 操作反馈
  */
int BME280_Get_Press(Sensor_BME280 *BME280, float *DATA)
{
    //读取压力值
    uint8_t DATA_IN[3] = {0};
    if (BME280_Read(&*BME280, R_Press_MSB, DATA_IN, 3) != BME280_OK)
    {
        return BME280_Error;
    }
    //整合数值
    uint32_t DAC_P = {0};
    DAC_P = (DATA_IN[0] << 12) + (DATA_IN[1] << 4) + (DATA_IN[2] >> 4);

    uint32_t Dig_P1 = BME280->DIG.DIG_P1;
    uint32_t Dig_P2 = BME280->DIG.DIG_P2;
    uint32_t Dig_P3 = BME280->DIG.DIG_P3;
    uint32_t Dig_P4 = BME280->DIG.DIG_P4;
    uint32_t Dig_P5 = BME280->DIG.DIG_P5;
    uint32_t Dig_P6 = BME280->DIG.DIG_P6;
    uint32_t Dig_P7 = BME280->DIG.DIG_P7;
    uint32_t Dig_P8 = BME280->DIG.DIG_P8;
    uint32_t Dig_P9 = BME280->DIG.DIG_P9;

    double var1 = {0};
    double var2 = {0};
    double p = {0};
    //补偿公式参考官方文档
    var1 = ((double)BME280->t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)Dig_P6) / 32768.0;
    var2 = var2 + var1 * ((double)Dig_P5) * 2.0;
    var2 = (var2 / 4.0) + (((double)Dig_P4) * 65536.0);
    var1 = (((double)Dig_P3) * var1 * var1 / 524288.0 + ((double)Dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)Dig_P1);
    if (var1 == 0.0)
    {
        return BME280_Error;
    }
    p = 1048576.0 - (double)DAC_P;
    p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)Dig_P9) * p * p / 2147483648.0;
    var2 = p * ((double)Dig_P8) / 32768.0;
    p = (p + (var1 + var2 + ((double)Dig_P7)) / 16.0) / 100.0;
    *DATA = p;
    //printf("%f\r\n", *DATA);
    return BME280_OK;
}
/**
  * @brief 读取补偿值
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Get_DIG(Sensor_BME280 *BME280)
{
    //温度
    uint8_t DATA_T[6] = {0};
    if (BME280_Read(&*BME280, R_DIG_T1_MSB, DATA_T, 6) != BME280_OK)
    {
        return BME280_Error;
    }
    BME280->DIG.DIG_T1 = (DATA_T[1] << 8) + (DATA_T[0]);
    BME280->DIG.DIG_T2 = (DATA_T[3] << 8) + (DATA_T[2]);
    BME280->DIG.DIG_T3 = (DATA_T[5] << 8) + (DATA_T[4]);
    //压力
    uint8_t DATA_P[18] = {0};
    if (BME280_Read(&*BME280, R_DIG_P1_MSB, DATA_P, 18) != BME280_OK)
    {
        return BME280_Error;
    }
    BME280->DIG.DIG_P1 = (DATA_P[1] << 8) + (DATA_P[0]);
    BME280->DIG.DIG_P2 = (DATA_P[3] << 8) + (DATA_P[2]);
    BME280->DIG.DIG_P3 = (DATA_P[5] << 8) + (DATA_P[4]);
    BME280->DIG.DIG_P4 = (DATA_P[7] << 8) + (DATA_P[6]);
    BME280->DIG.DIG_P5 = (DATA_P[9] << 8) + (DATA_P[8]);
    BME280->DIG.DIG_P6 = (DATA_P[11] << 8) + (DATA_P[10]);
    BME280->DIG.DIG_P7 = (DATA_P[13] << 8) + (DATA_P[12]);
    BME280->DIG.DIG_P8 = (DATA_P[15] << 8) + (DATA_P[14]);
    BME280->DIG.DIG_P9 = (DATA_P[17] << 8) + (DATA_P[16]);
    //湿度
    uint8_t DATA_H_A1 = {0};
    uint8_t DATA_H[7] = {0};
    if (BME280_Read(&*BME280, R_DIG_H1, &DATA_H_A1, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Read(&*BME280, R_DIG_H2_LSB, DATA_H, 7) != BME280_OK)
    {
        return BME280_Error;
    }
    BME280->DIG.DIG_H1 = DATA_H_A1;
    BME280->DIG.DIG_H2 = (DATA_H[1] << 8) + (DATA_H[0]);
    BME280->DIG.DIG_H3 = DATA_H[2];
    BME280->DIG.DIG_H4 = (DATA_H[3] << 4) + ((uint8_t)((DATA_H[4] << 4)) >> 4);
    BME280->DIG.DIG_H5 = (DATA_H[4] >> 4) + ((DATA_H[5]) << 4);
    BME280->DIG.DIG_H6 = DATA_H[6];
}
/**
  * @brief 通过结构体参数配置传感器
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Configuration(Sensor_BME280 *BME280)
{
    uint8_t DATA_Config = {0};
    uint8_t DATA_Ctrl_Hum = {0};
    uint8_t DATA_Ctrl_Meas = {0};
    //三个配置寄存器写入顺序：Config、Ctrl_Hum、Ctrl_Meas
    //Config
    //Tstandby位
    if (BME280->BME280_Tstandby == BME280_Tstandby_0_5 || BME280->BME280_Tstandby == BME280_Tstandby_62_5 || BME280->BME280_Tstandby == BME280_Tstandby_125 || BME280->BME280_Tstandby == BME280_Tstandby_250 || BME280->BME280_Tstandby == BME280_Tstandby_500 || BME280->BME280_Tstandby == BME280_Tstandby_1000 || BME280->BME280_Tstandby == BME280_Tstandby_10 || BME280->BME280_Tstandby == BME280_Tstandby_20)
    {
        DATA_Config = Bit_Modification(DATA_Config, 5, 7, BME280->BME280_Tstandby);
    }
    else
    {
        return BME280_Error;
    }
    //Filter位
    if (BME280->BME280_IIR_Time == BME280_Filter_OFF || BME280->BME280_IIR_Time == BME280_Filter_2 || BME280->BME280_IIR_Time == BME280_Filter_4 || BME280->BME280_IIR_Time == BME280_Filter_8 || BME280->BME280_IIR_Time == BME280_Filter_16)
    {
        DATA_Config = Bit_Modification(DATA_Config, 2, 4, BME280->BME280_IIR_Time);
    }
    //Ctrl_Hum
    if (BME280->HUM.HUM_EN == BME280_Sensor_ON)
    {
        if (BME280->HUM.HUM_Ove == BME280_Over_1 || BME280->HUM.HUM_Ove == BME280_Over_2 || BME280->HUM.HUM_Ove == BME280_Over_4 || BME280->HUM.HUM_Ove == BME280_Over_8 || BME280->HUM.HUM_Ove == BME280_Over_16)
        {
            DATA_Ctrl_Hum = Bit_Modification(DATA_Ctrl_Hum, 0, 2, BME280->HUM.HUM_Ove);
        }
        else
        {
            return BME280_Error;
        }
    }
    else if (BME280->HUM.HUM_EN == BME280_Sensor_OFF)
    {
        DATA_Ctrl_Hum = Bit_Modification(DATA_Ctrl_Hum, 0, 2, BME280->HUM.HUM_EN);
    }
    else
    {
        return BME280_Error;
    }
    //Ctrl_Meas
    //温度过采样
    if (BME280->TEMP.TEMP_EN == BME280_Sensor_ON)
    {
        if (BME280->TEMP.TEMP_Ove == BME280_Over_1 || BME280->TEMP.TEMP_Ove == BME280_Over_2 || BME280->TEMP.TEMP_Ove == BME280_Over_4 || BME280->TEMP.TEMP_Ove == BME280_Over_8 || BME280->TEMP.TEMP_Ove == BME280_Over_16)
        {
            DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 5, 7, BME280->TEMP.TEMP_Ove);
        }
        else
        {
            return BME280_Error;
        }
    }
    else if (BME280->TEMP.TEMP_EN == BME280_Sensor_OFF)
    {
        DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 5, 7, BME280->TEMP.TEMP_Ove);
    }
    else
    {
        return BME280_Error;
    }
    //压力过采样
    if (BME280->PRESS.PRESS_EN == BME280_Sensor_ON)
    {
        if (BME280->PRESS.PRESS_Ove == BME280_Over_1 || BME280->PRESS.PRESS_Ove == BME280_Over_2 || BME280->PRESS.PRESS_Ove == BME280_Over_4 || BME280->PRESS.PRESS_Ove == BME280_Over_8 || BME280->PRESS.PRESS_Ove == BME280_Over_16)
        {
            DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 2, 4, BME280->PRESS.PRESS_Ove);
        }
        else
        {
            return BME280_Error;
        }
    }
    else if (BME280->PRESS.PRESS_EN == BME280_Sensor_OFF)
    {
        DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 2, 4, BME280->PRESS.PRESS_Ove);
    }
    else
    {
        return BME280_Error;
    }
    //设备模式
    if (BME280->BME280_Mode == BME280_Mode_Sleep || BME280->BME280_Mode == BME280_Mode_Forced || BME280->BME280_Mode == BME280_Mode_Normal)
    {
        DATA_Ctrl_Meas = Bit_Modification(DATA_Ctrl_Meas, 0, 1, BME280->BME280_Mode);
    }
    else
    {
        return BME280_Error;
    }
    //依次写入设备
    if (BME280_Write(&*BME280, R_Config, DATA_Config) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Write(&*BME280, R_Ctrl_Hum, DATA_Ctrl_Hum) != BME280_OK)
    {
        return BME280_Error;
    }
    if (BME280_Write(&*BME280, R_Ctrl_Meas, DATA_Ctrl_Meas) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
/**
  * @brief 复位设备
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Reset(Sensor_BME280 *BME280)
{
    if (BME280_Write(&*BME280, R_Reset, 0xB6) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
/**
  * @brief 使设备睡眠
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_Sleep(Sensor_BME280 *BME280)
{
    BME280->BME280_Mode = BME280_Mode_Sleep;
    if (BME280_Configuration(&BME280_1) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
/**
  * @brief 使设备开机（正常模式）
  * @param BME280：目标设备
  * @retval 操作反馈
  */
int BME280_UP(Sensor_BME280 *BME280)
{
    BME280->BME280_Mode = BME280_Mode_Normal;
    if (BME280_Configuration(&BME280_1) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}

/**
  * @brief 读取设备ID
  * @param BME280：目标设备
  * @param ID：读取的ID
  * @retval 操作反馈
  */
int BME280_ID(Sensor_BME280 *BME280, uint8_t *ID)
{
    if (BME280_Read(&*BME280, R_ID, &*ID, 1) != BME280_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}

/*****************底层控制函数*****************/
//读写控制函数设计逻辑：
//分别写出IIC和SPI通讯的读写函数，通过总的读写函数判断设备走的通讯方式，分配其通讯的方式
/**
  * @brief IIC写
  * @param BME280：写目标设备
  * @param DATA：写入的数据
  * @param DATA_NUM：写入数据的数量
  * @retval 写操作反馈
  */
int BME280_IIC_Write(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t DATA)
{
    uint8_t DATA_OUT[2] = {0};
    DATA_OUT[0] = ADDR;
    DATA_OUT[1] = DATA;
    if (HAL_I2C_Master_Transmit(&(BME280->IIC_Aisle), (BME280->IIC_ADDR) << 1, DATA_OUT, 2, 1000) != HAL_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
/**
  * @brief IIC读
  * @param BME280：读目标设备
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BME280_IIC_Read(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
    if (HAL_I2C_Master_Transmit(&(BME280->IIC_Aisle), (BME280->IIC_ADDR) << 1, &ADDR, 1, 1000) != HAL_OK)
    {
        return BME280_Error;
    }
    if (HAL_I2C_Master_Receive(&(BME280->IIC_Aisle), (BME280->IIC_ADDR) << 1, DATA, DATA_NUM, 1000) != HAL_OK)
    {
        return BME280_Error;
    }
    return BME280_OK;
}
/**
  * @brief SPI写
  * @param BME280：写目标设备
  * @param DATA：写入的数据
  * @param DATA_NUM：写入数据的数量
  * @retval 写操作反馈
  */
int BME280_SPI_Write(Sensor_BME280 *BME280, uint8_t DATA, int DATA_NUM)
{
}
/**
  * @brief SPI读
  * @param BME280：读目标设备
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BME280_SPI_Read(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
}
/**
  * @brief 设备写
  * @param BME280：写目标设备
  * @param ADDR：写入地址
  * @param DATA：写入数据
  * @retval 写操作反馈
  */
int BME280_Write(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t DATA)
{
    if (BME280_COM_Mode == BME280_IIC)
    {
        if (BME280_IIC_Write(&*BME280, ADDR, DATA) != BME280_OK)
        {
            return BME280_Error;
        }
    }
    else if (BME280_COM_Mode == BME280_SPI)
    {
        if (BME280_SPI_Write(&*BME280, ADDR, DATA) != BME280_OK)
        {
            return BME280_Error;
        }
    }
}
/**
  * @brief 设备读
  * @param BME280：读目标设备
  * @param ADDR：读取的开始地址
  * @param DATA：读入的数据
  * @param DATA_NUM：读入数据的数量
  * @retval 读操作反馈
  */
int BME280_Read(Sensor_BME280 *BME280, uint8_t ADDR, uint8_t *DATA, int DATA_NUM)
{
    if (BME280_COM_Mode == BME280_IIC)
    {
        if (BME280_IIC_Read(&*BME280, ADDR, &*DATA, DATA_NUM) != BME280_OK)
        {
            return BME280_Error;
        }
    }
    else if (BME280_COM_Mode == BME280_SPI)
    {
        if (BME280_SPI_Read(&*BME280, ADDR, &*DATA, DATA_NUM) != BME280_OK)
        {
            return BME280_Error;
        }
    }
}
/*****************位操作函数*****************/
/**
* @brief  提取16位二进制数据中一位，返回该位是0或1
* @param	DATA:原始数据
* @param	NUM：数据位置
* @retval 数据值
*/
int Extract_text(uint16_t *DATA, int NUM)
{
    int RE_NUM = 3;
    if (NUM < 0 || NUM > 15)
    {
        printf("提取发生错误");
        while (1)
            ;
        return RE_NUM;
    }

    if (*DATA & (1 << NUM))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
* @brief  提取十六位二进制中的一段，转换为十进制
* @param	DATA:原始数据
* @param	NUM_Start：数据位置开始
* @param	NUM_Stop：数据位置停止
* @retval 数据值
*/
int Binary_To_Decimal(uint16_t *DATA, int NUM_Start, int NUM_Stop)
{
    //函数开启条件：开始和停止位置需要大于0小于15，并且停止位置大于开始位置
    if ((NUM_Start < 0 || NUM_Start > 15) || (NUM_Stop < 0 && NUM_Stop > 15) || (NUM_Start > NUM_Stop))
    {
        printf("转换发送错误\r\n");
        return (-1);
    }
    //读取二进制位
    int NUM_B[16] = {0};
    for (int i = 0; i < ((NUM_Stop - NUM_Start) + 1); i++)
    {
        NUM_B[i] = Extract_text(DATA, NUM_Start + i);
    }
    //转换为十进制
    int NUM_D = 0;
    for (int i = 0; i < ((NUM_Stop - NUM_Start) + 1); i++)
    {
        NUM_D = NUM_D + (NUM_B[i] * pow(2, i));
    }
    return NUM_D;
}

/**
  * @brief 位操作
  * @param Reg:被修改的值
  * @param Bit_Start:开始修改的位置
  * @param Bit_Stop:结束修改的位置
  * @param Value:需要修改成的值(二进制表示)
  * @retval 返回修改完成后的变量
  */
uint16_t Bit_Modification(uint16_t Reg, int Bit_Start, int Bit_Stop, uint16_t Value)
{
    uint16_t X = 0xFFFF;
    for (int i = Bit_Start; i < Bit_Stop + 1; i++)
    {
        X &= ~(1 << i);
    }
    Reg &= X;
    Reg |= Value << Bit_Start;
    return Reg;
}