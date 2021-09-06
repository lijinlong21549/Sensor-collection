#ifndef __BMX160_Register_H__
#define __BMX160_Register_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
//返回值
#define BMX160_OK 0
#define BMX160_Error 1
//寄存器地址
#define R_CHIP_ID 0X00       //芯片识别码
#define R_ERR_REG 0X02       //错误标志
#define R_PMU_STATUS 0X03    //当前功率模式
#define R_DATA_0 0X04        //磁力计X轴LSB
#define R_DATA_1 0X05        //磁力计X轴MSB
#define R_DATA_2 0X06        //磁力计Y轴LSB
#define R_DATA_3 0X07        //磁力计Y轴MSB
#define R_DATA_4 0X08        //磁力计Z轴LSB
#define R_DATA_5 0X09        //磁力计Z轴MSB
#define R_DATA_6 0X0A        //RHALL_LSB
#define R_DATA_7 0X0B        //RHALL_MSB
#define R_DATA_8 0X0C        //陀螺仪X轴LSB
#define R_DATA_9 0X0D        //陀螺仪X轴MSB
#define R_DATA_10 0X0E       //陀螺仪Y轴LSB
#define R_DATA_11 0X0F       //陀螺仪Y轴MSB
#define R_DATA_12 0X10       //陀螺仪Z轴LSB
#define R_DATA_13 0X11       //陀螺仪Z轴MSB
#define R_DATA_14 0X12       //加速度X轴LSB
#define R_DATA_15 0X13       //加速度X轴MSB
#define R_DATA_16 0X14       //加速度Y轴LSB
#define R_DATA_17 0X15       //加速度Y轴MSB
#define R_DATA_18 0X16       //加速度Z轴LSB
#define R_DATA_19 0X17       //加速度Z轴MSB
#define R_SENSORTIME_0 0X18  //传感器时间0：7
#define R_SENSORTIME_1 0X19  //传感器时间8-15
#define R_SENSORTIME_2 0X1A  //传感器时间16-23
#define R_STATUS 0X1B        //状态标志
#define R_INT_STATUS_0 0X1C  //中断状态标志
#define R_INT_STATUS_1 0X1D  //中断状态标志
#define R_INT_STATUS_2 0X1E  //中断状态标志
#define R_INT_STATUS_3 0X1F  //中断状态标志
#define R_TEMPERATURE_0 0X20 //传感器温度
#define R_TEMPERATURE_1 0X21 //传感器温度
#define R_FIFO_LENGTH_0 0X22 //FIFO数据读出状态
#define R_FIFO_LENGTH_1 0X23 //FIFO数据读出状态
#define R_FIFO_DATA 0X24     //FIFO 数据读出寄存器
#define R_ACC_CONF 0X40      //加速度数据速率、带宽和加速度传感器的读取模式
#define R_ACC_RANGE 0X41     //加速度g范围
#define R_GYR_CONF 0X42      //陀螺仪数据速率、带宽和加速度传感器的读取模式
#define R_GYR_RANGE 0X43     //角速度范围
#define R_MAG_CONF 0X44      //磁力计数据速率、带宽和加速度传感器的读取模式
#define R_FIFO_DOWNS 0X45    //FIFO 的加速度和陀螺仪数据的下采样率
#define R_FIFO_CONFIG_0 0X46 //读取或设置当前FIFO水印级别、设置 FIFO的不同操作模式
#define R_FIFO_CONFIG_1 0X47 //读取或设置当前FIFO水印级别、设置 FIFO的不同操作模式
#define R_MAG_IF_0 0X4C      //磁力计寻址的寄存器
#define R_MAG_IF_1 0X4D      //磁力计寻址的寄存器
#define R_MAG_IF_2 0X4E      //磁力计寻址的寄存器
#define R_MAG_IF_3 0X4F      //磁力计寻址的寄存器
#define R_INT_EN_0 0X50      //控制中断引擎的开启
#define R_INT_EN_1 0X51      //控制中断引擎的开启
#define R_INT_EN_2 0X52      //控制中断引擎的开启
#define R_INT_OUT_CTRL 0X53  //中断引脚的电气定义
#define R_INT_LATCH 0X54     //中断复位位和中断模式选择
#define R_INT_MAP_0 0X55     //控制将哪些中断信号映射到INT1和INT2引脚
#define R_INT_MAP_1 0X56     //控制将哪些中断信号映射到INT1和INT2引脚
#define R_INT_MAP_2 0X57     //控制将哪些中断信号映射到INT1和INT2引脚
#define R_INT_DATA_0 0X58    //中断组的数据源定义
#define R_INT_DATA_1 0X59    //中断组的数据源定义
#define R_INT_LOWHIGH_0 0X5A //低G中断的延迟时间定义
#define R_INT_LOWHIGH_1 0X5B //包含low-g中断的阈值定义
#define R_INT_LOWHIGH_2 0X5C //低G中断模式的选择，低G中断迟滞的设置，以及高G中断迟滞的设置。
#define R_INT_LOWHIGH_3 0X5D //高g中断的延迟时间定义
#define R_INT_LOWHIGH_4 0X5E //高g中断的阈值定义
#define R_INTMOTION_0 0X5F   //对任意运动中断和慢速/无运动中断触发延迟所要评估的样本数的定义。
#define R_INTMOTION_1 0X60   //任意运动中断的阈值定义
#define R_INTMOTION_2 0X61   //慢速/无动作中断的阈值定义
#define R_INTMOTION_3 0X62   //慢动作/无动作配置
#define R_INT_TAP_0 0X63     //单击和双击中断的定时定义
#define R_INT_TAP_1 0X64     //单击和双击中断的阈值定义
#define R_INT_ORIENT_0 0X65  //方向中断的迟滞、阻塞和模式的定义
#define R_INT_ORIENT_1 0X66  //轴方向的定义，上/下屏蔽，以及方向中断的theta阻断角。
#define R_INT_FLAT_0 0X67    //平面中断的平坦阈值角度的定义
#define R_INT_FLAT_1 0X68    //平面中断保持时间和平面中断迟滞的定义
#define R_FOC_CONF 0X69      //加速度计和陀螺仪快速偏移补偿的配置设置
#define R_CONF 0X6A          //NVM编程配置
#define R_IF_CONF 0X6B       //三线SPI或四线SPI设置
#define R_PMU_TRIGGER 0X6C   //设置触发条件以改变陀螺仪电源模式
#define R_SELF_TEST 0X6D     //传感器自检配置和触发器的设置
#define R_NV_CONF 0X70       //数字接口的NVM设置
#define R_OFFSET_0 0X71      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_1 0X72      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_2 0X73      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_3 0X74      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_4 0X75      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_5 0X76      //加速度计和陀螺仪的偏移补偿值
#define R_OFFSET_6 0X77      //加速度计和陀螺仪的偏移补偿值
#define R_STEP_CNT_0 0X78    //步数
#define R_STEP_CNT_1 0X79    //步数
#define R_STEP_CONF_0 0X7A   //步数检测器的配置
#define R_STEP_CONF_1 0X7B   //步数检测器的配置
#define R_CMD 0X7E           //命令寄存器触发操作，如软复位、NVM编程等

#ifdef __cplusplus
}
#endif

#endif /* __BMX160_Register_H__ */
