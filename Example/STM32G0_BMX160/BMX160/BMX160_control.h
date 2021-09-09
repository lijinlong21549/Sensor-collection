#ifndef __BMX160_Control_H__
#define __BMX160_Control_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
//ͨѶ��ʽ
#define BMX160_IIC 0 //BMX160ͨ��IICͨѶ
#define BMX160_SPI 1 //BMX160ͨ��SPIͨѶ
//оƬʶ����
#define CHIPID 0xD8
    /**************************BMX160���ٶȼƵ����ò����ͷ�Χ**************************/
    /**
  * @brief BMX160���ٶȼƵ����ò����ͷ�Χ
  * @param ACC_us��Ƿ��������
  * @param ACC_bwp���������
  * @param ACC_odr�������������
  * @param ACC_RANGE��//���ٶ�G��Χ
  */
//��Դģʽ
#define BMX160_ACC_Normal_mode 0 //����ģʽ
#define BMX160_ACC_LPower_mode 1 //�͹���ģʽ
//����ģʽ��
#define BMX160_ACC_Normal_Oversampling 0 //�����˲���
#define BMX160_ACC_OSR2_Oversampling -1  //2��������
#define BMX160_ACC_OSR4_Oversampling -2  //4��������
//�͹���ģʽ
#define BMX160_ACC_1_Undersampling 1     //1ƽ������
#define BMX160_ACC_2_Undersampling 2     //2ƽ������
#define BMX160_ACC_4_Undersampling 4     //4ƽ������
#define BMX160_ACC_8_Undersampling 8     //8ƽ������
#define BMX160_ACC_16_Undersampling 16   //16ƽ������
#define BMX160_ACC_32_Undersampling 32   //32ƽ������
#define BMX160_ACC_64_Undersampling 64   //64ƽ������
#define BMX160_ACC_128_Undersampling 128 //128ƽ������
//�������
#define BMX160_ACC_ODR_0_78125 0x1 //�������0.78125/HZ
#define BMX160_ACC_ODR_1_5625 0x2  //�������1.5625/HZ
#define BMX160_ACC_ODR_3_125 0x3   //�������3.125/HZ
#define BMX160_ACC_ODR_6_25 0x4    //�������6.25/HZ
#define BMX160_ACC_ODR_12_5 0x5    //�������12.5/HZ
#define BMX160_ACC_ODR_25 0x6      //�������25/HZ
#define BMX160_ACC_ODR_50 0x7      //�������50/HZ
#define BMX160_ACC_ODR_100 0x8     //�������100/HZ
#define BMX160_ACC_ODR_200 0x9     //�������200/HZ
#define BMX160_ACC_ODR_400 0xa     //�������400/HZ
#define BMX160_ACC_ODR_800 0xb     //�������800/HZ
#define BMX160_ACC_ODR_1600 0xc    //�������1600/HZ
//���ٶ�G��Χ
#define BMX160_ACC_RANGE_2g 0x03  //��2g
#define BMX160_ACC_RANGE_4g 0x05  //��4g
#define BMX160_ACC_RANGE_8g 0x08  //��8g
#define BMX160_ACC_RANGE_16g 0x0c //��16g
    struct Str_BMX160_ACC_CONF_RANGE
    {
        int ACC_us;      //�͹���
        int ACC_bwp;     //�˲���
        uint8_t ACC_odr; //�������
        int ACC_RANGE;   //���ٶ�G��Χ
    };
    /**************************BMX160�����ǵ����ò����ͷ�Χ**************************/
    /**
  * @brief BMX160�����ǵ����ò����ͷ�Χ
  * @param GYR_bwp���������
  * @param GYR_odr�������������
  * @param GYR_RANGE��//���ٶȷ�Χ
  */
//����ģʽ��
#define BMX160_GYR_Normal_Oversampling 0 //�����˲���
#define BMX160_GYR_OSR2_Oversampling -1  //2��������
#define BMX160_GYR_OSR4_Oversampling -2  //4��������
//�������
#define BMX160_GYR_ODR_25 0x6   //�������25/HZ
#define BMX160_GYR_ODR_50 0x7   //�������50/HZ
#define BMX160_GYR_ODR_100 0x8  //�������100/HZ
#define BMX160_GYR_ODR_200 0x9  //�������200/HZ
#define BMX160_GYR_ODR_400 0xa  //�������400/HZ
#define BMX160_GYR_ODR_800 0xb  //�������800/HZ
#define BMX160_GYR_ODR_1600 0xc //�������1600/HZ
#define BMX160_GYR_ODR_3200 0xd //�������3200/HZ
//���ٶȷ�Χ
#define BMX160_GYR_RANGE_2000 0x00 //2000/s
#define BMX160_GYR_RANGE_1000 0x01 //1000/s
#define BMX160_GYR_RANGE_500 0x02  //500/s
#define BMX160_GYR_RANGE_250 0x03  //250/s
#define BMX160_GYR_RANGE_125 0x04  //125/s

    struct Str_BMX160_GYR_CONF_RANGE
    {
        int GYR_bwp;     //�˲���
        uint8_t GYR_odr; //�������
        int GYR_RANGE;   //���ٶȷ�Χ
    };

/**************************BMX160�����Ƶ����ò����ͷ�Χ**************************/
//������ģʽ
#define BMX160_MAG_Mode_LowPower 0      //�͹���ģʽ
#define BMX160_MAG_Mode_Normal 1        //��ͨģʽ
#define BMX160_MAG_Mode_Strengthen 2    //��ǿģʽ
#define BMX160_MAG_Mode_HighPrecision 3 //�߾���ģʽ
//�������
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
        int MAG_XY_Mode; //������XY��ģʽ
        int MAG_Z_Mode;  //������XY��ģʽ
        uint8_t MAG_odr; //�������
    };
/**************************BMX160����ƫ�Ʋ��������ò���**************************/
#define BMX160_FOC_GYR_ON 0x1           //�����������������ƫ�Ʋ���
#define BMX160_FOC_GYR_OFF 0x0          //�ر��������������ƫ�Ʋ���
#define BMX160_FOC_ACC_Recoup_Ban 0x00  //���ٶȼƽ��ò���Ŀ��ֵ
#define BMX160_FOC_ACC_Recoup_P_1g 0x01 //���ٶȼƲ���Ŀ��ֵ1g
#define BMX160_FOC_ACC_Recoup_N_1g 0x02 //���ٶȼƲ���Ŀ��ֵ-1g
#define BMX160_FOC_ACC_Recoup_0g 0x03   //���ٶȼƲ���Ŀ��ֵ0g
#define BMX160_off_ACC_ON 0x1           //�������ٶȼƵ�ƫ�Ʋ���
#define BMX160_off_ACC_OFF 0x0          //�رռ��ٶȼƵ�ƫ�Ʋ���
#define BMX160_off_GYR_ON 0x1           //�����������ǵ�ƫ�Ʋ���
#define BMX160_off_GYR_OFF 0x0          //�رռ������ǵ�ƫ�Ʋ���
    struct Str_BMX160_ACC_GYR_FOC_off
    {
        int FOC_GYR_EN;         //�����ǿ���ƫ�Ʋ���
        uint8_t FOC_ACC_X;      //���ٶȼ�X�Ჹ��Ŀ��ֵ
        uint8_t FOC_ACC_Y;      //���ٶȼ�Y�Ჹ��Ŀ��ֵ
        uint8_t FOC_ACC_Z;      //���ٶȼ�Z�Ჹ��Ŀ��ֵ
        int Off_ACC_EN;         //���ٶȼ�ƫ�Ʋ���
        int Off_GYR_EN;         //������ƫ�Ʋ���
        uint8_t Off_ACC_NUM_X;  //���ٶȼ�X��ƫ��ֵ
        uint8_t Off_ACC_NUM_Y;  //���ٶȼ�Y��ƫ��ֵ
        uint8_t Off_ACC_NUM_Z;  //���ٶȼ�Z��ƫ��ֵ
        uint16_t Off_GYR_NUM_X; //������X��ƫ��ֵ
        uint16_t Off_GYR_NUM_Y; //������Y��ƫ��ֵ
        uint16_t Off_GYR_NUM_Z; //������Z��ƫ��ֵ
    };
//�û��޸�
#define BMX160_COM_Mode BMX160_IIC //BMX160��ͨѶ��ʽ
    /*****************�ṹ��*****************/

    typedef struct __BMX160
    {
        int COM_Mode;
#if BMX160_COM_Mode == BMX160_IIC
        I2C_HandleTypeDef IIC_Aisle;
        uint8_t IIC_ADDR;
#else
    SPI_HandleTypeDef SPI_Aisle;
#endif
        //�ж�1
        uint16_t INT1_Pin;
        GPIO_TypeDef *INT1_Prot;
        //�ж�2
        uint16_t INT2_Pin;
        GPIO_TypeDef *INT2_Prot;
        struct Str_BMX160_ACC_CONF_RANGE ACC_CONF_RANGE;   //BMX160���ٶȼƵ����ò����ͷ�Χ
        struct Str_BMX160_GYR_CONF_RANGE GYR_CONF_RANGE;   //BMX160�����ǵ����ò����ͷ�Χ
        struct Str_BMX160_MAG_CONF_RANGE MAG_CONF_RANGE;   //BMX160�����Ƶ����ò����ͷ�Χ
        struct Str_BMX160_ACC_GYR_FOC_off ACC_GYR_FOC_off; //BMX160����У׼����
    } Sensor_BMX160;
    /*****************��������*****************/
    int BMX160_Pretreatment(void);
    int BMX160_Read(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t *DATA, int DATA_NUM);
    int BMX160_Write(Sensor_BMX160 *BMX160, uint8_t ADDR, uint8_t DATA);
    extern Sensor_BMX160 BMX160_1;
#ifdef __cplusplus
}
#endif

#endif /* __BMX160_Control_H__ */
