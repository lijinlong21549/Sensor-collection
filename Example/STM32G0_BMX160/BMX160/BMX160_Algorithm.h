#ifndef __BMX160_Algorithm_H__
#define __BMX160_Algorithm_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//·µ»ØÖµ
#define BMX160_OK 0
#define BMX160_Error 1


int Extract_text(uint16_t *DATA, int NUM);
int Binary_To_Decimal(uint16_t *DATA, int NUM_Start, int NUM_Stop);
uint16_t Bit_Modification(uint16_t Reg, int Bit_Start, int Bit_Stop, uint16_t Value);

#ifdef __cplusplus
}
#endif

#endif /* __BMX160_Algorithm_H__ */
