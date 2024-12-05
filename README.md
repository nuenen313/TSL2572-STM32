# TSL2572-STM32
STM32 library for the TSL2572 light sensor. Returns a value in lux. Usage:

```
#include "TSL2572.h"
static const uint8_t TSL2572_ADDR = 0x72;

TSL2572 tsl2572_sensor;

int main(void){
  if (TSL2572_Init(&tsl2572_sensor, &hi2c1, TSL2572_ADDR) == HAL_OK) {
  		printf("TSL2572 initialized successfully!\n");
  	} else {
  		printf("TSL2572 initialization failed!\n");
  	}

  while (1) {
    buff[0] = REG_ADDR;
		  if (TSL2572_GetLux(&tsl2572_sensor, &lux) == HAL_OK)
		  {
		        sprintf(displayBuffer, "Light: %0.2f lux\r\n", lux);
		        HAL_UART_Transmit(&huart2, (uint8_t*)displayBuffer, strlen(displayBuffer), HAL_MAX_DELAY);
		  }
		HAL_Delay(1000);
  }
}
```
Tested using NUCLEO-L152RE.
