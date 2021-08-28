#include "OPT3001.h"
#include "i2c.h"
#include "usart.h"
#include <math.h>
/**
* @brief  初始化并创建一个OPT3001的设备
* @retval 空值
*/

int OPT3001_Read_Device_ID(OPT3001 *OPT3001);
int OPT3001_Read_Manufacturer_ID(OPT3001 *OPT3001);
int OPT3001_Write_Configuration(OPT3001 *OPT3001);
int OPT3001_Read_Brightness(OPT3001 *OPT3001, float *DATA_OUT);
int OPT3001_Write_High_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Write_Low_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Reset(OPT3001 *OPT3001);

int OPT3001_INT(OPT3001 *OPT3001);
int OPT3001_IIC_Read(OPT3001 *OPT3001, uint8_t ADDR, uint16_t *DATA);
int OPT3001_IIC_Write(OPT3001 *OPT3001, uint8_t ADDR, uint16_t DATA);
int Extract_text(uint16_t *DATA, int NUM);
int Binary_To_Decimal(uint16_t *DATA, int NUM_Start, int NUM_Stop);
uint16_t Bit_Modification(uint16_t Reg, int Bit_Start, int Bit_Stop, uint16_t Value);


OPT3001 Eye_1;
int OPT3001_Init(void)
{
  /********用户参数********/
  //INT脚位
  Eye_1.INT_Pin = OPT3001_INT_Pin;
  Eye_1.INT_Prot = OPT3001_INT_GPIO_Port;
  //使用的IIC
  Eye_1.IIC_Aisle = hi2c1;
  Eye_1.IIC_ADDR = 0x45;
  //低阈值
  Eye_1.Low_Limit = 200;
  //高阈值
  Eye_1.High_Limit = 60000;
  //当前量程
  Eye_1.Configuration.Range = Range_AUTO;
  //转换时间
  Eye_1.Configuration.Conversion_Time = completely_Conversion;
  //转换模式
  Eye_1.Configuration.Conversion_Mode = continuous;
  //INT极性
  Eye_1.Configuration.Polarity_Field_Bit = Low_efficient;
  //故障计数字段
  Eye_1.Configuration.Fault_Count_Field_Bit = Fault_One;
  //屏蔽指数字段
  Eye_1.Configuration.Mask_Exponent_Field_Bit = Exponent_show;
  //中断模式
  Eye_1.Configuration.Latch_field_Bit = latched_Window_style;

  /********传递参数********/
  //读取两个ID
  Eye_1.Manufacturer_ID = 0;
  Eye_1.Device_ID = 0;
  /********初始化程序********/
  //复位OPT3001
  OPT3001_Reset(&Eye_1);
  //读取生产厂商ID和设备ID
  OPT3001_Read_Manufacturer_ID(&Eye_1);
  OPT3001_Read_Device_ID(&Eye_1);
  HAL_Delay(1);
  if ((Eye_1.Manufacturer_ID == 0x5449) & (Eye_1.Device_ID == 0x3001))
  {
    printf("已识别到");
		printf("OPT3001\r\n");
  }
  else
  {
    printf("未识别到");
		printf("OPT3001\r\n");
    return OPT3001_Error;
  }
  //将上述配置参数上传到配置寄存器和上下阈值寄存器
  OPT3001_Write_Configuration(&Eye_1);
  OPT3001_Write_High_Limit(&Eye_1, Eye_1.High_Limit);
  OPT3001_Write_Low_Limit(&Eye_1, Eye_1.Low_Limit);
}
/************************用户函数************************/
/**
  * @brief 读取当前亮度
  * @param OPT3001：读目标设备
  * @param DATA：读取内容
  * @retval 读操作反馈
  */
int OPT3001_Read_Brightness(OPT3001 *OPT3001, float *DATA_OUT)
{
  uint16_t DATA;

  //确认当前的亮度可读
  if (OPT3001->Configuration.Conversion_Mode == continuous)
  {
    if (OPT3001_IIC_Read(&*OPT3001, R_Result, &DATA) != OPT3001_OK)
    {
      return OPT3001_Error;
    }
    //数据处理
    *DATA_OUT = 0.01 * (pow(2, (Binary_To_Decimal(&DATA, 12, 15)))) * Binary_To_Decimal(&DATA, 0, 11);
    return OPT3001_OK;
  }
  else
  {
    return OPT3001_Error;
  }
}
/**
  * @brief 设置高阈值
  * @param OPT3001：设置目标设备
  * @param DATA：阈值
  * @retval 写操作反馈
  */
int OPT3001_Write_High_Limit(OPT3001 *OPT3001, int DATA)
{
  uint16_t DATA_OUT = (0xb000) | ((DATA * 100) / 2048);
  OPT3001_IIC_Write(&*OPT3001, R_High_Limit, DATA_OUT);
}

/**
  * @brief 设置低阈值
  * @param OPT3001：设置目标设备
  * @param DATA：阈值
  * @retval 写操作反馈
  */
int OPT3001_Write_Low_Limit(OPT3001 *OPT3001, int DATA)
{
  uint16_t DATA_OUT = (0xb000) | ((DATA * 100) / 2048);
  OPT3001_IIC_Write(&*OPT3001, R_Low_Limit, DATA_OUT);
}

/**
  * @brief 读取生产厂商ID
  * @param OPT3001：读目标设备
  * @retval 写操作反馈
  */
int OPT3001_Read_Manufacturer_ID(OPT3001 *OPT3001)
{
  uint16_t DATA = {0};
  if (OPT3001_IIC_Read(&Eye_1, R_Manufacturer_ID, &DATA) != OPT3001_OK)
  {
    return OPT3001_Error;
  }
  OPT3001->Manufacturer_ID = DATA;
  return OPT3001_OK;
}
/**
  * @brief 读取设备ID
  * @param OPT3001：读目标设备
  * @retval 写操作反馈
  */
int OPT3001_Read_Device_ID(OPT3001 *OPT3001)
{
  uint16_t DATA = {0};
  if (OPT3001_IIC_Read(&Eye_1, R_Device_ID, &DATA) != OPT3001_OK)
  {
    return OPT3001_Error;
  }
  OPT3001->Device_ID = DATA;
  return OPT3001_OK;
}
/**
  * @brief 上传配置寄存器
  * @param OPT3001：设置目标设备
  * @retval 写操作反馈
  */
int OPT3001_Write_Configuration(OPT3001 *OPT3001)
{
  OPT3001->Configuration.All = 0x0000;
  //当前量程
  if ((OPT3001->Configuration.Range == 0x00) || (OPT3001->Configuration.Range == 0x01) || (OPT3001->Configuration.Range == 0x02) || (OPT3001->Configuration.Range == 0x03) || (OPT3001->Configuration.Range == 0x04) || (OPT3001->Configuration.Range == 0x05) || (OPT3001->Configuration.Range == 0x06) || (OPT3001->Configuration.Range == 0x07) || (OPT3001->Configuration.Range == 0x08) || (OPT3001->Configuration.Range == 0x09) || (OPT3001->Configuration.Range == 0x0a) || (OPT3001->Configuration.Range == 0x0b) || (OPT3001->Configuration.Range == 0x0c))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 12, 15, OPT3001->Configuration.Range);
  }
  else
  {
    return OPT3001_Error;
  }
  //转换时间
  if ((OPT3001->Configuration.Conversion_Time == Fast_Conversion) || (OPT3001->Configuration.Conversion_Time == completely_Conversion))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 11, 11, OPT3001->Configuration.Conversion_Time);
  }
  else
  {
    return OPT3001_Error;
  }
  //转换模式
  if ((OPT3001->Configuration.Conversion_Mode == default) || (OPT3001->Configuration.Conversion_Mode == single) || (OPT3001->Configuration.Conversion_Mode == continuous))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 9, 10, OPT3001->Configuration.Conversion_Mode);
  }
  else
  {
    return OPT3001_Error;
  }
  //中断模式
  if ((OPT3001->Configuration.Latch_field_Bit == transparent_Hysteresis_style) || (OPT3001->Configuration.Latch_field_Bit == latched_Window_style))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 4, 4, OPT3001->Configuration.Latch_field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //INT极性
  if ((OPT3001->Configuration.Polarity_Field_Bit == Low_efficient) || (OPT3001->Configuration.Polarity_Field_Bit == High_efficient))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 3, 3, OPT3001->Configuration.Polarity_Field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //屏蔽指数字段
  if ((OPT3001->Configuration.Mask_Exponent_Field_Bit == Exponent_show) || (OPT3001->Configuration.Mask_Exponent_Field_Bit == Exponent_shield))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 2, 2, OPT3001->Configuration.Mask_Exponent_Field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //故障计数字段
  if ((OPT3001->Configuration.Fault_Count_Field_Bit == Fault_One) || (OPT3001->Configuration.Fault_Count_Field_Bit == Fault_Two) || (OPT3001->Configuration.Fault_Count_Field_Bit == Fault_Four) || (OPT3001->Configuration.Fault_Count_Field_Bit == Fault_Eight))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 0, 1, OPT3001->Configuration.Fault_Count_Field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  if (OPT3001_IIC_Write(&*OPT3001, (uint8_t)R_Configuration, OPT3001->Configuration.All) != OPT3001_OK)
  {
    return OPT3001_Error;
  }
  else
  {
    return OPT3001_OK;
  }
}

/**
  * @brief 读取配置寄存器
  * @param OPT3001：读目标设备
  * @retval 写操作反馈
  */
int OPT3001_Read_Configuration(OPT3001 *OPT3001)
{
  //读取配置寄存器的数值，存于DATA中
  uint16_t DATA;
  if (OPT3001_IIC_Read(OPT3001, R_Configuration, &DATA) != OPT3001_OK)
  {
    return OPT3001_Error;
  }
  else
  {
    OPT3001->Configuration.All = DATA;
  }
  //高标志位
  if (Extract_text(&DATA, 6) != 3)
  {
    OPT3001->Configuration.High_Limit_Bit = Extract_text(&DATA, 6);
  }
  else
  {
    return OPT3001_Error;
  }
  //低标志位
  if (Extract_text(&DATA, 5) != 3)
  {
    OPT3001->Configuration.Low_Limit_Bit = Extract_text(&DATA, 5);
  }
  else
  {
    return OPT3001_Error;
  }
  return OPT3001_OK;
}
int OPT3001_Reset(OPT3001 *OPT3001)
{
  uint8_t DATA = 0x06;
  if (HAL_I2C_Master_Transmit(&(OPT3001->IIC_Aisle), 0x00 << 1, &DATA, 1, 1000) != HAL_OK)
  {
    return OPT3001_Error;
  }
}
/************************中断函数************************/
int OPT3001_INT(OPT3001 *OPT3001)
{
  //中断标志
  OPT3001_Read_Configuration(&*OPT3001);
  //判断高低标志位
  if (OPT3001->Configuration.Low_Limit_Bit == 1)
  {
    OPT3001->Configuration.Low_Limit_Bit = 0;
    printf("低中断 \r\n");
  }
  if (OPT3001->Configuration.High_Limit_Bit == 1)
  {
    OPT3001->Configuration.High_Limit_Bit = 0;
    printf("高中断 \r\n");
  }
}
/************************内部函数************************/
/**
  * @brief IIC读取
  * @param OPT3001：读目标设备
  * @param DATA：数据
  * @retval 写操作反馈
  */
int OPT3001_IIC_Read(OPT3001 *OPT3001, uint8_t ADDR, uint16_t *DATA)
{
  uint8_t DATA_OUT[2] = {0};
  if (HAL_I2C_Master_Transmit(&(OPT3001->IIC_Aisle), (OPT3001->IIC_ADDR) << 1, &ADDR, 1, 1000) != HAL_OK)
  {
    return OPT3001_Error;
  }
  if (HAL_I2C_Master_Receive(&(OPT3001->IIC_Aisle), (OPT3001->IIC_ADDR) << 1, DATA_OUT, 2, 1000) != HAL_OK)
  {
    return OPT3001_Error;
  }
  *DATA = ((uint16_t)DATA_OUT[0] << 8) | DATA_OUT[1];
  return OPT3001_OK;
}

/**
  * @brief IIC写
  * @param OPT3001：写目标设备
  * @param DATA：数据
  * @retval 写操作反馈
  */
int OPT3001_IIC_Write(OPT3001 *OPT3001, uint8_t ADDR, uint16_t DATA)
{
  uint8_t DATA_OUT[3] = {0};
  DATA_OUT[0] = ADDR;
  DATA_OUT[1] = DATA >> 8;
  DATA_OUT[2] = DATA;
  if (HAL_I2C_Master_Transmit(&(OPT3001->IIC_Aisle), (OPT3001->IIC_ADDR) << 1, DATA_OUT, 3, 1000) != HAL_OK)
  {
    return OPT3001_Error;
  }
  return OPT3001_OK;
}

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