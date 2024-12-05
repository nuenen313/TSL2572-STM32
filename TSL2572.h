#ifndef TSL2572_I2C_DRIVER_H_
#define TSL2572_I2C_DRIVER_H_

#include "main.h"
#include "math.h"

#define TSL2572_COMMAND_BIT                0xA0
#define TSL2572_POWER_ON                   0x03
#define TSL2572_MAX_DELAY                  HAL_MAX_DELAY

#define TSL2572_REG_ENABLE                 0x00
#define TSL2572_REG_ATIME                  0x01
#define TSL2572_REG_WTIME				           0x03
#define TSL2572_REG_CONTROL                0x0F
#define TSL2572_REG_ID                     0x12
#define TSL2572_REG_STATUS				         0x14
#define TSL2572_REG_DATA0LOW               0x14
#define TSL2572_REG_DATA0HIGH              0x15
#define TSL2572_REG_DATA1LOW               0x16
#define TSL2572_REG_DATA1HIGH              0x17

typedef struct
{
    I2C_HandleTypeDef* i2cHandle;
    uint8_t address;
} TSL2572;

HAL_StatusTypeDef TSL2572_Init(TSL2572* tsl, I2C_HandleTypeDef* userHandle, uint8_t sensorAddress);
HAL_StatusTypeDef TSL2572_GetLux(TSL2572* tsl, float* luxValue);

HAL_StatusTypeDef TSL2572_WriteByte(TSL2572* tsl, uint8_t reg, uint8_t value);
HAL_StatusTypeDef TSL2572_ReadByte(TSL2572* tsl, uint8_t reg, uint8_t* value);
HAL_StatusTypeDef TSL2572_ReadData(TSL2572* tsl, uint16_t* data0Val, uint16_t* data1Val);

#endif
