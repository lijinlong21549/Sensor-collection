#include "OPT3001.h"
#include "i2c.h"
#include "usart.h"
#include <math.h>
/**
* @brief  ��ʼ��������һ��OPT3001���豸
* @retval ��ֵ
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
  /********�û�����********/
  //INT��λ
  Eye_1.INT_Pin = OPT3001_INT_Pin;
  Eye_1.INT_Prot = OPT3001_INT_GPIO_Port;
  //ʹ�õ�IIC
  Eye_1.IIC_Aisle = hi2c1;
  Eye_1.IIC_ADDR = 0x45;
  //����ֵ
  Eye_1.Low_Limit = 200;
  //����ֵ
  Eye_1.High_Limit = 60000;
  //��ǰ����
  Eye_1.Configuration.Range = Range_AUTO;
  //ת��ʱ��
  Eye_1.Configuration.Conversion_Time = completely_Conversion;
  //ת��ģʽ
  Eye_1.Configuration.Conversion_Mode = continuous;
  //INT����
  Eye_1.Configuration.Polarity_Field_Bit = Low_efficient;
  //���ϼ����ֶ�
  Eye_1.Configuration.Fault_Count_Field_Bit = Fault_One;
  //����ָ���ֶ�
  Eye_1.Configuration.Mask_Exponent_Field_Bit = Exponent_show;
  //�ж�ģʽ
  Eye_1.Configuration.Latch_field_Bit = latched_Window_style;

  /********���ݲ���********/
  //��ȡ����ID
  Eye_1.Manufacturer_ID = 0;
  Eye_1.Device_ID = 0;
  /********��ʼ������********/
  //��λOPT3001
  OPT3001_Reset(&Eye_1);
  //��ȡ��������ID���豸ID
  OPT3001_Read_Manufacturer_ID(&Eye_1);
  OPT3001_Read_Device_ID(&Eye_1);
  HAL_Delay(1);
  if ((Eye_1.Manufacturer_ID == 0x5449) & (Eye_1.Device_ID == 0x3001))
  {
    printf("��ʶ��");
		printf("OPT3001\r\n");
  }
  else
  {
    printf("δʶ��");
		printf("OPT3001\r\n");
    return OPT3001_Error;
  }
  //���������ò����ϴ������üĴ�����������ֵ�Ĵ���
  OPT3001_Write_Configuration(&Eye_1);
  OPT3001_Write_High_Limit(&Eye_1, Eye_1.High_Limit);
  OPT3001_Write_Low_Limit(&Eye_1, Eye_1.Low_Limit);
}
/************************�û�����************************/
/**
  * @brief ��ȡ��ǰ����
  * @param OPT3001����Ŀ���豸
  * @param DATA����ȡ����
  * @retval ����������
  */
int OPT3001_Read_Brightness(OPT3001 *OPT3001, float *DATA_OUT)
{
  uint16_t DATA;

  //ȷ�ϵ�ǰ�����ȿɶ�
  if (OPT3001->Configuration.Conversion_Mode == continuous)
  {
    if (OPT3001_IIC_Read(&*OPT3001, R_Result, &DATA) != OPT3001_OK)
    {
      return OPT3001_Error;
    }
    //���ݴ���
    *DATA_OUT = 0.01 * (pow(2, (Binary_To_Decimal(&DATA, 12, 15)))) * Binary_To_Decimal(&DATA, 0, 11);
    return OPT3001_OK;
  }
  else
  {
    return OPT3001_Error;
  }
}
/**
  * @brief ���ø���ֵ
  * @param OPT3001������Ŀ���豸
  * @param DATA����ֵ
  * @retval д��������
  */
int OPT3001_Write_High_Limit(OPT3001 *OPT3001, int DATA)
{
  uint16_t DATA_OUT = (0xb000) | ((DATA * 100) / 2048);
  OPT3001_IIC_Write(&*OPT3001, R_High_Limit, DATA_OUT);
}

/**
  * @brief ���õ���ֵ
  * @param OPT3001������Ŀ���豸
  * @param DATA����ֵ
  * @retval д��������
  */
int OPT3001_Write_Low_Limit(OPT3001 *OPT3001, int DATA)
{
  uint16_t DATA_OUT = (0xb000) | ((DATA * 100) / 2048);
  OPT3001_IIC_Write(&*OPT3001, R_Low_Limit, DATA_OUT);
}

/**
  * @brief ��ȡ��������ID
  * @param OPT3001����Ŀ���豸
  * @retval д��������
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
  * @brief ��ȡ�豸ID
  * @param OPT3001����Ŀ���豸
  * @retval д��������
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
  * @brief �ϴ����üĴ���
  * @param OPT3001������Ŀ���豸
  * @retval д��������
  */
int OPT3001_Write_Configuration(OPT3001 *OPT3001)
{
  OPT3001->Configuration.All = 0x0000;
  //��ǰ����
  if ((OPT3001->Configuration.Range == 0x00) || (OPT3001->Configuration.Range == 0x01) || (OPT3001->Configuration.Range == 0x02) || (OPT3001->Configuration.Range == 0x03) || (OPT3001->Configuration.Range == 0x04) || (OPT3001->Configuration.Range == 0x05) || (OPT3001->Configuration.Range == 0x06) || (OPT3001->Configuration.Range == 0x07) || (OPT3001->Configuration.Range == 0x08) || (OPT3001->Configuration.Range == 0x09) || (OPT3001->Configuration.Range == 0x0a) || (OPT3001->Configuration.Range == 0x0b) || (OPT3001->Configuration.Range == 0x0c))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 12, 15, OPT3001->Configuration.Range);
  }
  else
  {
    return OPT3001_Error;
  }
  //ת��ʱ��
  if ((OPT3001->Configuration.Conversion_Time == Fast_Conversion) || (OPT3001->Configuration.Conversion_Time == completely_Conversion))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 11, 11, OPT3001->Configuration.Conversion_Time);
  }
  else
  {
    return OPT3001_Error;
  }
  //ת��ģʽ
  if ((OPT3001->Configuration.Conversion_Mode == default) || (OPT3001->Configuration.Conversion_Mode == single) || (OPT3001->Configuration.Conversion_Mode == continuous))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 9, 10, OPT3001->Configuration.Conversion_Mode);
  }
  else
  {
    return OPT3001_Error;
  }
  //�ж�ģʽ
  if ((OPT3001->Configuration.Latch_field_Bit == transparent_Hysteresis_style) || (OPT3001->Configuration.Latch_field_Bit == latched_Window_style))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 4, 4, OPT3001->Configuration.Latch_field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //INT����
  if ((OPT3001->Configuration.Polarity_Field_Bit == Low_efficient) || (OPT3001->Configuration.Polarity_Field_Bit == High_efficient))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 3, 3, OPT3001->Configuration.Polarity_Field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //����ָ���ֶ�
  if ((OPT3001->Configuration.Mask_Exponent_Field_Bit == Exponent_show) || (OPT3001->Configuration.Mask_Exponent_Field_Bit == Exponent_shield))
  {
    OPT3001->Configuration.All = Bit_Modification(OPT3001->Configuration.All, 2, 2, OPT3001->Configuration.Mask_Exponent_Field_Bit);
  }
  else
  {
    return OPT3001_Error;
  }
  //���ϼ����ֶ�
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
  * @brief ��ȡ���üĴ���
  * @param OPT3001����Ŀ���豸
  * @retval д��������
  */
int OPT3001_Read_Configuration(OPT3001 *OPT3001)
{
  //��ȡ���üĴ�������ֵ������DATA��
  uint16_t DATA;
  if (OPT3001_IIC_Read(OPT3001, R_Configuration, &DATA) != OPT3001_OK)
  {
    return OPT3001_Error;
  }
  else
  {
    OPT3001->Configuration.All = DATA;
  }
  //�߱�־λ
  if (Extract_text(&DATA, 6) != 3)
  {
    OPT3001->Configuration.High_Limit_Bit = Extract_text(&DATA, 6);
  }
  else
  {
    return OPT3001_Error;
  }
  //�ͱ�־λ
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
/************************�жϺ���************************/
int OPT3001_INT(OPT3001 *OPT3001)
{
  //�жϱ�־
  OPT3001_Read_Configuration(&*OPT3001);
  //�жϸߵͱ�־λ
  if (OPT3001->Configuration.Low_Limit_Bit == 1)
  {
    OPT3001->Configuration.Low_Limit_Bit = 0;
    printf("���ж� \r\n");
  }
  if (OPT3001->Configuration.High_Limit_Bit == 1)
  {
    OPT3001->Configuration.High_Limit_Bit = 0;
    printf("���ж� \r\n");
  }
}
/************************�ڲ�����************************/
/**
  * @brief IIC��ȡ
  * @param OPT3001����Ŀ���豸
  * @param DATA������
  * @retval д��������
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
  * @brief IICд
  * @param OPT3001��дĿ���豸
  * @param DATA������
  * @retval д��������
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
* @brief  ��ȡ16λ������������һλ�����ظ�λ��0��1
* @param	DATA:ԭʼ����
* @param	NUM������λ��
* @retval ����ֵ
*/
int Extract_text(uint16_t *DATA, int NUM)
{
  int RE_NUM = 3;
  if (NUM < 0 || NUM > 15)
  {
    printf("��ȡ��������");
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
* @brief  ��ȡʮ��λ�������е�һ�Σ�ת��Ϊʮ����
* @param	DATA:ԭʼ����
* @param	NUM_Start������λ�ÿ�ʼ
* @param	NUM_Stop������λ��ֹͣ
* @retval ����ֵ
*/
int Binary_To_Decimal(uint16_t *DATA, int NUM_Start, int NUM_Stop)
{
  //����������������ʼ��ֹͣλ����Ҫ����0С��15������ֹͣλ�ô��ڿ�ʼλ��
  if ((NUM_Start < 0 || NUM_Start > 15) || (NUM_Stop < 0 && NUM_Stop > 15) || (NUM_Start > NUM_Stop))
  {
    printf("ת�����ʹ���\r\n");
    return (-1);
  }
  //��ȡ������λ
  int NUM_B[16] = {0};
  for (int i = 0; i < ((NUM_Stop - NUM_Start) + 1); i++)
  {
    NUM_B[i] = Extract_text(DATA, NUM_Start + i);
  }
  //ת��Ϊʮ����
  int NUM_D = 0;
  for (int i = 0; i < ((NUM_Stop - NUM_Start) + 1); i++)
  {
    NUM_D = NUM_D + (NUM_B[i] * pow(2, i));
  }
  return NUM_D;
}

/**
  * @brief λ����
  * @param Reg:���޸ĵ�ֵ
  * @param Bit_Start:��ʼ�޸ĵ�λ��
  * @param Bit_Stop:�����޸ĵ�λ��
  * @param Value:��Ҫ�޸ĳɵ�ֵ(�����Ʊ�ʾ)
  * @retval �����޸���ɺ�ı���
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