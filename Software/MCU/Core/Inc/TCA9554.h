/*
 * TCA9554.h
 *
 *  Created on: May 1, 2026
 *      Author: sp6gk
 */

#ifndef INC_TCA9554_H_
#define INC_TCA9554_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define TCA9554_ADDRESS (0x27 << 1)	//Configurable based on HW pins, see Table 2 on page 19 of datasheet

#define TCA9554_IN_REG   0x0
#define TCA9554_OUT_REG  0x1
#define TCA9554_POL_REG  0x2
#define TCA9554_CONF_REG 0x3

typedef struct{
	I2C_HandleTypeDef *hi2c;
	uint8_t address;
	uint8_t io_states;
	uint8_t io_configuration;
	uint8_t pol_inversion;
}TCA9554_HandleTypeDef;


void TCA9554_init(TCA9554_HandleTypeDef *dev);
uint8_t TCA9554_set_pin(TCA9554_HandleTypeDef *dev, uint8_t pin, bool state);
bool TCA9554_read_pin(TCA9554_HandleTypeDef *dev, uint8_t pin);

uint8_t TCA9554_write(TCA9554_HandleTypeDef *dev, uint8_t reg, uint8_t data);
uint8_t TCA9554_read(TCA9554_HandleTypeDef *dev, uint8_t reg);


#endif /* INC_TCA9554_H_ */
