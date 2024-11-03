//
// Created by kentl on 24-11-3.
//

#ifndef MPU_H
#define MPU_H
#include "main.h"
#include "spi.h"

extern float x_accel,y_accel,z_accel;
extern float x_gyro,y_gyro,z_gyro;
static uint8_t tx_data[3],rx_data[14];
static int16_t accel_ratio[4]={2,4,8,16}, gyro_ratio[4]={250,500,1000,2000};
static int16_t x_temp,y_temp,z_temp;

const static uint8_t accel_sel=3,gyro_sel=3;

void MPU6500_Init()
{
    tx_data[0]=0x1B;//no 0x80 means read
    tx_data[1]=8*accel_sel;
    tx_data[2]=8*gyro_sel;
    HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi5, tx_data, 3, 1000);
    HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_SET);

}

void MPU6500_Read()
{
    tx_data[0]=0x3B+0x80;//0x80 means write
    HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi5, tx_data, 1, 1000);
    HAL_SPI_Receive(&hspi5, rx_data, 14, 1000);
    HAL_GPIO_WritePin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin, GPIO_PIN_SET);//read

    x_temp=rx_data[0]*256+rx_data[1];
    y_temp=rx_data[2]*256+rx_data[3];
    z_temp=rx_data[4]*256+rx_data[5];
    x_accel=(float)accel_ratio[accel_sel]*x_temp/32768;
    y_accel=(float)accel_ratio[accel_sel]*y_temp/32768;
    z_accel=(float)accel_ratio[accel_sel]*z_temp/32768;

    x_temp=rx_data[8]*256+rx_data[9];
    y_temp=rx_data[10]*256+rx_data[11];
    z_temp=rx_data[12]*256+rx_data[13];
    x_gyro=(float)gyro_ratio[gyro_sel]*x_temp/32768;
    y_gyro=(float)gyro_ratio[gyro_sel]*y_temp/32768;
    z_gyro=(float)gyro_ratio[gyro_sel]*z_temp/32768;
}
#endif //MPU_H
