#ifndef __BMX160_Register_H__
#define __BMX160_Register_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
//����ֵ
#define BMX160_OK 0
#define BMX160_Error 1
//�Ĵ�����ַ
#define R_CHIP_ID 0X00       //оƬʶ����
#define R_ERR_REG 0X02       //�����־
#define R_PMU_STATUS 0X03    //��ǰ����ģʽ
#define R_DATA_0 0X04        //������X��LSB
#define R_DATA_1 0X05        //������X��MSB
#define R_DATA_2 0X06        //������Y��LSB
#define R_DATA_3 0X07        //������Y��MSB
#define R_DATA_4 0X08        //������Z��LSB
#define R_DATA_5 0X09        //������Z��MSB
#define R_DATA_6 0X0A        //RHALL_LSB
#define R_DATA_7 0X0B        //RHALL_MSB
#define R_DATA_8 0X0C        //������X��LSB
#define R_DATA_9 0X0D        //������X��MSB
#define R_DATA_10 0X0E       //������Y��LSB
#define R_DATA_11 0X0F       //������Y��MSB
#define R_DATA_12 0X10       //������Z��LSB
#define R_DATA_13 0X11       //������Z��MSB
#define R_DATA_14 0X12       //���ٶ�X��LSB
#define R_DATA_15 0X13       //���ٶ�X��MSB
#define R_DATA_16 0X14       //���ٶ�Y��LSB
#define R_DATA_17 0X15       //���ٶ�Y��MSB
#define R_DATA_18 0X16       //���ٶ�Z��LSB
#define R_DATA_19 0X17       //���ٶ�Z��MSB
#define R_SENSORTIME_0 0X18  //������ʱ��0��7
#define R_SENSORTIME_1 0X19  //������ʱ��8-15
#define R_SENSORTIME_2 0X1A  //������ʱ��16-23
#define R_STATUS 0X1B        //״̬��־
#define R_INT_STATUS_0 0X1C  //�ж�״̬��־
#define R_INT_STATUS_1 0X1D  //�ж�״̬��־
#define R_INT_STATUS_2 0X1E  //�ж�״̬��־
#define R_INT_STATUS_3 0X1F  //�ж�״̬��־
#define R_TEMPERATURE_0 0X20 //�������¶�
#define R_TEMPERATURE_1 0X21 //�������¶�
#define R_FIFO_LENGTH_0 0X22 //FIFO���ݶ���״̬
#define R_FIFO_LENGTH_1 0X23 //FIFO���ݶ���״̬
#define R_FIFO_DATA 0X24     //FIFO ���ݶ����Ĵ���
#define R_ACC_CONF 0X40      //���ٶ��������ʡ�����ͼ��ٶȴ������Ķ�ȡģʽ
#define R_ACC_RANGE 0X41     //���ٶ�g��Χ
#define R_GYR_CONF 0X42      //�������������ʡ�����ͼ��ٶȴ������Ķ�ȡģʽ
#define R_GYR_RANGE 0X43     //���ٶȷ�Χ
#define R_MAG_CONF 0X44      //�������������ʡ�����ͼ��ٶȴ������Ķ�ȡģʽ
#define R_FIFO_DOWNS 0X45    //FIFO �ļ��ٶȺ����������ݵ��²�����
#define R_FIFO_CONFIG_0 0X46 //��ȡ�����õ�ǰFIFOˮӡ�������� FIFO�Ĳ�ͬ����ģʽ
#define R_FIFO_CONFIG_1 0X47 //��ȡ�����õ�ǰFIFOˮӡ�������� FIFO�Ĳ�ͬ����ģʽ
#define R_MAG_IF_0 0X4C      //������Ѱַ�ļĴ���
#define R_MAG_IF_1 0X4D      //������Ѱַ�ļĴ���
#define R_MAG_IF_2 0X4E      //������Ѱַ�ļĴ���
#define R_MAG_IF_3 0X4F      //������Ѱַ�ļĴ���
#define R_INT_EN_0 0X50      //�����ж�����Ŀ���
#define R_INT_EN_1 0X51      //�����ж�����Ŀ���
#define R_INT_EN_2 0X52      //�����ж�����Ŀ���
#define R_INT_OUT_CTRL 0X53  //�ж����ŵĵ�������
#define R_INT_LATCH 0X54     //�жϸ�λλ���ж�ģʽѡ��
#define R_INT_MAP_0 0X55     //���ƽ���Щ�ж��ź�ӳ�䵽INT1��INT2����
#define R_INT_MAP_1 0X56     //���ƽ���Щ�ж��ź�ӳ�䵽INT1��INT2����
#define R_INT_MAP_2 0X57     //���ƽ���Щ�ж��ź�ӳ�䵽INT1��INT2����
#define R_INT_DATA_0 0X58    //�ж��������Դ����
#define R_INT_DATA_1 0X59    //�ж��������Դ����
#define R_INT_LOWHIGH_0 0X5A //��G�жϵ��ӳ�ʱ�䶨��
#define R_INT_LOWHIGH_1 0X5B //����low-g�жϵ���ֵ����
#define R_INT_LOWHIGH_2 0X5C //��G�ж�ģʽ��ѡ�񣬵�G�жϳ��͵����ã��Լ���G�жϳ��͵����á�
#define R_INT_LOWHIGH_3 0X5D //��g�жϵ��ӳ�ʱ�䶨��
#define R_INT_LOWHIGH_4 0X5E //��g�жϵ���ֵ����
#define R_INTMOTION_0 0X5F   //�������˶��жϺ�����/���˶��жϴ����ӳ���Ҫ�������������Ķ��塣
#define R_INTMOTION_1 0X60   //�����˶��жϵ���ֵ����
#define R_INTMOTION_2 0X61   //����/�޶����жϵ���ֵ����
#define R_INTMOTION_3 0X62   //������/�޶�������
#define R_INT_TAP_0 0X63     //������˫���жϵĶ�ʱ����
#define R_INT_TAP_1 0X64     //������˫���жϵ���ֵ����
#define R_INT_ORIENT_0 0X65  //�����жϵĳ��͡�������ģʽ�Ķ���
#define R_INT_ORIENT_1 0X66  //�᷽��Ķ��壬��/�����Σ��Լ������жϵ�theta��Ͻǡ�
#define R_INT_FLAT_0 0X67    //ƽ���жϵ�ƽ̹��ֵ�ǶȵĶ���
#define R_INT_FLAT_1 0X68    //ƽ���жϱ���ʱ���ƽ���жϳ��͵Ķ���
#define R_FOC_CONF 0X69      //���ٶȼƺ������ǿ���ƫ�Ʋ�������������
#define R_CONF 0X6A          //NVM�������
#define R_IF_CONF 0X6B       //����SPI������SPI����
#define R_PMU_TRIGGER 0X6C   //���ô��������Ըı������ǵ�Դģʽ
#define R_SELF_TEST 0X6D     //�������Լ����úʹ�����������
#define R_NV_CONF 0X70       //���ֽӿڵ�NVM����
#define R_OFFSET_0 0X71      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_1 0X72      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_2 0X73      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_3 0X74      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_4 0X75      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_5 0X76      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_OFFSET_6 0X77      //���ٶȼƺ������ǵ�ƫ�Ʋ���ֵ
#define R_STEP_CNT_0 0X78    //����
#define R_STEP_CNT_1 0X79    //����
#define R_STEP_CONF_0 0X7A   //���������������
#define R_STEP_CONF_1 0X7B   //���������������
#define R_CMD 0X7E           //����Ĵ�����������������λ��NVM��̵�

#ifdef __cplusplus
}
#endif

#endif /* __BMX160_Register_H__ */
