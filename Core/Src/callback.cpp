//
// Created by kentl on 24-11-2.
//
#include "main.h"
#include "spi.h"
#include "gpio.h"
extern uint8_t tx_data[1];
extern uint8_t rx_data[6];
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_RESET);
        tx_data[0]=0x3B+0x80;
        HAL_SPI_Transmit(&hspi5, tx_data, 1, 1000);
//        while(HAL_SPI_GetState(&hspi5) != HAL_SPI_STATE_READY){};
        HAL_SPI_Receive(&hspi5, rx_data, 6, 1000);
//        while(HAL_SPI_GetState(&hspi5) != HAL_SPI_STATE_READY){};
        HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_SET);
    }
}