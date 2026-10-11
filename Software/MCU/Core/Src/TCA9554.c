/*
 * TCA9554.c
 *
 *  Created on: May 1, 2026
 *      Author: sp6gk
 */

#include "TCA9554.h"
#include "i2c.h"
#include "stdbool.h"


void TCA9554_init(TCA9554_HandleTypeDef *dev){
	TCA9554_write(dev, TCA9554_CONF_REG, dev->io_configuration);
	TCA9554_write(dev, TCA9554_POL_REG, dev->pol_inversion);
	TCA9554_write(dev, TCA9554_OUT_REG, dev->io_states);
}

uint8_t TCA9554_set_pin(TCA9554_HandleTypeDef *dev, uint8_t pin, bool state) {
    HAL_StatusTypeDef status = HAL_OK;
    //Sanity check
    if (pin > 7) {
        return 1;
    }

    uint8_t mask = (1U << pin);

    if(state == 1){
        dev->io_states |= mask;
    }
    else{
        dev->io_states &= ~mask;
    }

    status = TCA9554_write(dev, TCA9554_OUT_REG, dev->io_states);

    return status;
}

bool TCA9554_read_pin(TCA9554_HandleTypeDef *dev, uint8_t pin) {
	//Sanity check
    if (pin > 7) {
        return false;
    }

    dev->io_states = TCA9554_read(dev, TCA9554_IN_REG);
    uint8_t mask = (1U << pin);
    return (dev->io_states & mask) != 0;
}


//General write and read, addresses all pins / their settings at once
uint8_t TCA9554_write(TCA9554_HandleTypeDef *dev, uint8_t reg, uint8_t data){
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(dev->hi2c, dev->address, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
	if(status != HAL_OK){
		//Handle exception here
	}

	return status;
}

uint8_t TCA9554_read(TCA9554_HandleTypeDef *dev, uint8_t reg){
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t data = 0;

	status = HAL_I2C_Mem_Read(dev->hi2c, dev->address, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
	if(status != HAL_OK){
		//Handle exception here
	}

	return data;
}

