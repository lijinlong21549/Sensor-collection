
#ifndef __OPT3001_H
#define __OPT3001_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
//����ֵ
#define OPT3001_OK 0
#define OPT3001_Error 1
//�Ĵ�����ַ
#define R_Result 0x00 //����Ĵ���
#define R_Configuration 0x01  //���üĴ���
#define R_Low_Limit 0x02 //����ֵ�Ĵ���
#define R_High_Limit 0x03//����ֵ�Ĵ���
#define R_Manufacturer_ID 0x7e//���쳧��ID
#define R_Device_ID 0x7f//�豸����ID
//ת��ʱ��
#define Fast_Conversion 0x00       //����ת��
#define completely_Conversion 0x01 //��ȫ����ת��
//ת��ģʽ
#define default 0x00    //�ػ�
#define single 0x01     //����ת��
#define continuous 0x2 //����ת��
//�ж�ģʽ
#define transparent_Hysteresis_style 0x00 //͸���ͺ�ʽ
#define latched_Window_style 0x01         //����ʽ
//�ж����ż���ģʽ
#define Low_efficient 0x00  //�͵�ƽ��Ч
#define High_efficient 0x01 //�ߵ�ƽ��Ч
//�Ƿ���ʾָ���ֶ�
#define Exponent_show 0x00   //��ʾָ���ֶ�
#define Exponent_shield 0x01 //����ָ���ֶ�
//���ϱ�������
#define Fault_One 0x00   //һ������
#define Fault_Two 0x01   //��������
#define Fault_Four 0x2  //�ĸ�����
#define Fault_Eight 0x3 //�˸�����
//����ѡ��
#define Range_40_95 0x00//���̣�40.95
#define Range_81_90 0x01//���̣�81.90
#define Range_163_80 0x02//���̣�163.80
#define Range_327_60 0x03//���̣�327.60
#define Range_655_20 0x04//���̣�655.20
#define Range_1310_40 0x05//���̣�1310.40
#define Range_2620_80 0x06//���̣�2620.80
#define Range_5241_60 0x07//���̣�5241.60
#define Range_10483_20 0x08//���̣�10483.20
#define Range_20966_40 0x09//���̣�20966.40
#define Range_41932_80 0x0a//���̣�41932.80
#define Range_83865_60 0x0b//���̣�83865.60
#define Range_AUTO 0x0c//���̣��Զ�����
    //���üĴ����ṹ��
    struct RS_Configuration
    {
        uint16_t All;
        int Range;                      //��ǰ����
        int Conversion_Time;            //ת��ʱ��
        uint16_t Conversion_Mode;       //ת��ģʽ
        int overflow_Bit;               //���ָʾ
        int Conversion_Finish_Bit;      //ת����ɱ�־λ
        int High_Limit_Bit;             //�߱�־λ
        int Low_Limit_Bit;              //�ͱ�־λ
        int Latch_field_Bit;            //�ж�ģʽ
        int Polarity_Field_Bit;         //INT����
        int Mask_Exponent_Field_Bit;    //����ָ���ֶ�
        uint16_t Fault_Count_Field_Bit; //���ϼ����ֶ�
    };

    typedef struct __OPT3001
    {
        //�ж�����
        uint16_t INT_Pin;
        GPIO_TypeDef *INT_Prot;
        //��ʹ�õ�IIC
        I2C_HandleTypeDef IIC_Aisle;
        //IIC��ַ
        uint8_t IIC_ADDR;
        //������ֵ
        float Current_Figure;
        //����ֵ
        int Low_Limit;
        //����ֵ
        int High_Limit;
        /*���üĴ�����ֵ*/
        struct RS_Configuration Configuration;
        //������ID
        uint16_t Manufacturer_ID;
        //�豸ID
        uint16_t Device_ID;

    } OPT3001;


int OPT3001_Init(void);
int OPT3001_INT(OPT3001 *OPT3001);
int OPT3001_Read_Device_ID(OPT3001 *OPT3001);
int OPT3001_Read_Manufacturer_ID(OPT3001 *OPT3001);
int OPT3001_Write_Configuration(OPT3001 *OPT3001);
int OPT3001_Read_Brightness(OPT3001 *OPT3001, float *DATA_OUT);
int OPT3001_Write_High_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Write_Low_Limit(OPT3001 *OPT3001, int DATA);
int OPT3001_Reset(OPT3001 *OPT3001);
extern OPT3001 Eye_1;
#ifdef __cplusplus
}
#endif

#endif /* __OPT3001_H */
