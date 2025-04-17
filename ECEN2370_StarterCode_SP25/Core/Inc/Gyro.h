#ifndef GYRO_H
#define GYRO_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"


#define GYRO_WHO_AM_I_REG         0x0F
#define GYRO_CTRL_REG1            0x20
#define GYRO_CTRL_REG5            0x24
#define GYRO_OUT_TEMP             0x26
#define GYRO_STATUS_REG           0x27
#define GYRO_OUT_X_L              0x28
#define GYRO_OUT_X_H              0x29
#define GYRO_OUT_Y_L              0x2A
#define GYRO_OUT_Y_H              0x2B
#define GYRO_OUT_Z_L              0x2C
#define GYRO_OUT_Z_H              0x2D


#define GYRO_CS_PORT              GPIOC
#define GYRO_CS_PIN               GPIO_PIN_1
#define GYRO_SPI_INSTANCE         SPI5


#define GYRO_NORMAL_MODE          0x0F
#define GYRO_BANDWIDTH_01         0x10
#define GYRO_REBOOT_MEMORY        0x80


void GyroInit(SPI_HandleTypeDef *hspi);
void GyroGetDeviceID(SPI_HandleTypeDef *hspi);
void GyroPowerOn(SPI_HandleTypeDef *hspi);
void GyroPowerOff(SPI_HandleTypeDef *hspi);
void GyroGetTemperature(SPI_HandleTypeDef *hspi);
void GyroConfigureRegisters(SPI_HandleTypeDef *hspi);
uint8_t GyroReadRegister(SPI_HandleTypeDef *hspi, uint8_t reg);
void GyroWriteRegister(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t value);
bool GyroVerifyHALStatus(void);
void GyroEnableSlaveCommunication(void);
void printGyro();

#endif // GYRO_H
