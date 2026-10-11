# TCA9554 STM32 GPIO Expander

## Software
STM32 HAL driver for the **TCA9554 8-bit I/O expander**. This is a useful IC that I find more capable and easier to use than the common PPCF8574.

The project includes:
- HAL based driver
- Demo project in CubeIDE targeting the STM32F411
- KiCad project with eval PCB


### Usage
Copy the .c and .h from demo project to your project:
- TCA9554.c is in /Software/MCU/Src
- TCA9554.h is in /Software/MCU/Inc

Configure the I2C peripheral in STM32CubeMX and initialize the driver:

```c
#include "TCA9554.h"

TCA9554_HandleTypeDef GPIO_expander1 =
{
    .hi2c = &hi2c1,              // CubeMX I2C configuration
    .address = TCA9554_ADDRESS,  // Defined in header file
    .io_configuration = 0x00,    // 0 = Output, 1 = Input
    .io_states = 0x00,           // 0 = Low, 1 = High
    .pol_inversion = 0x00        // No polarity inversion
};

TCA9554_init(&GPIO_expander1);

```

By default, all pins are configured as inputs. Set `io_configuration` to configure individual pins: for example, `0b01010101` configures P0, P2, P4, and P6 as outputs, and P1, P3, P5, and P7 as inputs.

```c
uint8_t read_status = 0;
bool pin_status[8] = {0};

//Write to specific pin
for(int i = 0; i < 8; i++){
		  TCA9554_set_pin(&GPIO_expander1, i, true);
		  HAL_Delay(100);
	  }


//Write state of all pins at once
for(uint8_t counter = 0; counter < UINT8_MAX; counter++){
  TCA9554_write(&GPIO_expander1, TCA9554_OUT_REG, counter);

  read_status = TCA9554_read(&GPIO_expander1, TCA9554_IN_REG);	//Read status of every pin
  for(uint8_t i = 0; i < 8; i++){
  pin_status[i] = TCA9554_read_pin(&GPIO_expander1, i); //Read status of single pin
}

```


## Hardware

KiCad evaluation board design for the **TCA9554 I/O expander**.

The hardware project includes the schematic and PCB design files, organized under the `ECAD/` directory.
`Documents/` includes interactive BOM and .pdf schematic.
