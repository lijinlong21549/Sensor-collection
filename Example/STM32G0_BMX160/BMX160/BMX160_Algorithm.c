#include "BMX160_Algorithm.h"
#include "BMX160_use.h"
#include "BMX160_Control.h"
#include <math.h>
#include "usart.h"
/*****************位操作*****************/
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