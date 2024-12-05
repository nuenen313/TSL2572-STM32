#include "TSL2572.h"

HAL_StatusTypeDef TSL2572_Init(TSL2572 *tsl, I2C_HandleTypeDef *userHandle,
		uint8_t sensorAddress) {
	tsl->i2cHandle = userHandle;
	tsl->address = sensorAddress;

	//enable sensor
	HAL_StatusTypeDef status = TSL2572_WriteByte(tsl,
			TSL2572_COMMAND_BIT | TSL2572_REG_ENABLE, TSL2572_POWER_ON);
	if (status != HAL_OK)
		return status;

	//set integration time
	status =  TSL2572_WriteByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_ATIME, 0xDB); //101 ms integration time, figure 24 from the datasheet
	if (status != HAL_OK) return status;
	
	/*AGAIN - set in the  Control Register
	 * Field Value    |     ALS GAIN VALUE
	 *      00        |           1x gain
	 *      01        |           2x gain
	 *      10		    |           8x gain
	 *      11		    |           120x gain
	 */
	return TSL2572_WriteByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_CONTROL, 0x00); // 1x gain
}

HAL_StatusTypeDef TSL2572_GetLux(TSL2572 *tsl, float *luxValue) {
	uint16_t data0, data1;
	HAL_StatusTypeDef status = TSL2572_ReadData(tsl, &data0, &data1);
	if (status != HAL_OK)
		return status;

    float cpl = 1.67; //int time*gain/60
    float lux;

    //lux calc
    if (cpl == 0) {
        *luxValue = 0;
    }

    //from the datasheet
    float Lux1 = (1.0 * data0 - 1.87 * data1) / cpl;
    float Lux2 = (0.63 * data0 - 1.0 * data1) / cpl;

    *luxValue = fmaxf(fmaxf(Lux1, Lux2), 0);

	return HAL_OK;
}

HAL_StatusTypeDef TSL2572_ReadData(TSL2572 *tsl, uint16_t *data0Val,
		uint16_t *data1Val) {
	uint8_t data0Low, data0High, data1Low, data1High;

	TSL2572_ReadByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_DATA0LOW,
			&data0Low);
	TSL2572_ReadByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_DATA0HIGH,
			&data0High);
	TSL2572_ReadByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_DATA1LOW,
			&data1Low);
	TSL2572_ReadByte(tsl, TSL2572_COMMAND_BIT | TSL2572_REG_DATA1HIGH,
			&data1High);

	*data0Val = (data0High << 8) | data0Low; //figure 17 in the datasheet
	*data1Val = (data1High << 8) | data1Low; //data high before data low

	return HAL_OK;
}

HAL_StatusTypeDef TSL2572_WriteByte(TSL2572 *tsl, uint8_t reg, uint8_t value) {
	return HAL_I2C_Mem_Write(tsl->i2cHandle, tsl->address, reg, 1, &value, 1,
			TSL2572_MAX_DELAY);
}

HAL_StatusTypeDef TSL2572_ReadByte(TSL2572 *tsl, uint8_t reg, uint8_t *value) {
	return HAL_I2C_Mem_Read(tsl->i2cHandle, tsl->address, reg, 1, value, 1,
			TSL2572_MAX_DELAY);
}
