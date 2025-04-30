#include "Gyro.h"

static HAL_StatusTypeDef gyroHALStatus = HAL_OK;

extern SPI_HandleTypeDef hspi5;


static void GyroCSEnable(void)
{
    HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_RESET);
}


static void GyroCSDisable(void)
{
    HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, GPIO_PIN_SET);
}


void GyroEnableSlaveCommunication(void)
{
    GyroCSEnable();
}


void GyroDisableSlaveCommunication(void)
{
    GyroCSDisable();
}


bool GyroVerifyHALStatus(void)
{
    APPLICATION_ASSERT(gyroHALStatus == HAL_OK);
    return (gyroHALStatus == HAL_OK);
}


uint8_t GyroReadRegister(SPI_HandleTypeDef *hspi, uint8_t reg)
{
    uint8_t txData = reg | 0x80;
    uint8_t rxData = 0;

    GyroCSEnable();
    gyroHALStatus = HAL_SPI_Transmit(hspi, &txData, 1, HAL_MAX_DELAY);
    GyroVerifyHALStatus();
    gyroHALStatus = HAL_SPI_Receive(hspi, &rxData, 1, HAL_MAX_DELAY);
    GyroVerifyHALStatus();
    GyroCSDisable();

    return rxData;
}


void GyroWriteRegister(SPI_HandleTypeDef *hspi, uint8_t reg, uint8_t value)
{
    uint8_t txData[2] = {reg & 0x7F, value};

    GyroCSEnable();
    gyroHALStatus = HAL_SPI_Transmit(hspi, txData, 2, HAL_MAX_DELAY);
    GyroVerifyHALStatus();
    GyroCSDisable();
}

void printGyro(){
		uint8_t deviceID = GyroReadRegister(&hspi5, 0x0F);
	    uint8_t rawTemp = GyroReadRegister(&hspi5, 0x26);
	    int8_t temp = (int8_t)rawTemp;

	    printf("Gyro Device ID: 0x%02X\r\nGyro Temp: %d°C\r\n\r\n", deviceID, temp);

}


void GyroInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GYRO_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GYRO_CS_PORT, &GPIO_InitStruct);

    GyroCSDisable();

    GyroConfigureRegisters(hspi);
}


void GyroConfigureRegisters(SPI_HandleTypeDef *hspi)
{
    GyroWriteRegister(hspi, GYRO_CTRL_REG1, GYRO_NORMAL_MODE | GYRO_BANDWIDTH_01);
    GyroWriteRegister(hspi, GYRO_CTRL_REG5, GYRO_REBOOT_MEMORY);
}


void GyroGetDeviceID(SPI_HandleTypeDef *hspi)
{
    uint8_t deviceID = GyroReadRegister(hspi, GYRO_WHO_AM_I_REG);
    printf("Gyro Device ID: 0x%X\n", deviceID);
}


void GyroPowerOn(SPI_HandleTypeDef *hspi)
{
    uint8_t ctrlReg1 = GyroReadRegister(hspi, GYRO_CTRL_REG1);
    ctrlReg1 |= (1 << 3);
    GyroWriteRegister(hspi, GYRO_CTRL_REG1, ctrlReg1);
}


void GyroPowerOff(SPI_HandleTypeDef *hspi)
{
    uint8_t ctrlReg1 = GyroReadRegister(hspi, GYRO_CTRL_REG1);
    ctrlReg1 &= ~(1 << 3);
    GyroWriteRegister(hspi, GYRO_CTRL_REG1, ctrlReg1);
}


void GyroGetTemperature(SPI_HandleTypeDef *hspi)
{
    uint8_t tempData = GyroReadRegister(hspi, GYRO_OUT_TEMP);
    printf("Gyro Temperature: %d°C\n", tempData);
}

