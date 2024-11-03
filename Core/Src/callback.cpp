//
// Created by kentl on 24-11-2.
//
#include "mpu.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        MPU6500_Read();
    }
}