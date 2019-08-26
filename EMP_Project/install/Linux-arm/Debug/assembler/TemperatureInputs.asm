#ifndef _TEMPERATURE_INPUTS_ASM_INCLUDED_
#define _TEMPERATURE_INPUTS_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "TemperatureInputsDefines.asm"


.macro temp_inputs_sleep
.mparam delay_count
.mparam temp_register = var_temp_0
	LDI	temp_register, delay_count
	DIGITAL_OUTPUTS_SLEEP_LOOP:
		SUB temp_register, temp_register, 1
		QBNE DIGITAL_OUTPUTS_SLEEP_LOOP, temp_register, 0
.endm


TEMPERATURE_INPUTS_INIT:
	QBBC TEMPERATURE_INPUTS_END, var_used_resources, BIT_RESOURCE_TEMPERATURE_INPUTS

// ==========================================================================================
//	load data base pointer
// ==========================================================================================
	MOV pt_temperatireInputConfigData, PT_TEMP_IN_DATA

// ==========================================================================================
//	initialize spi bus
// ==========================================================================================
	gpio_as_output		pt_gpio_bank_0,	2		// spi clk
	gpio_as_input		pt_gpio_bank_0,	3		// spi miso (master out slave in)
	gpio_as_output		pt_gpio_bank_0,	4		// spi mosi (master out slave in)
	gpio_as_output		pt_gpio_bank_0,	12    	// spi cs (chip select)

	clr_gpio		 pt_gpio_bank_0,	2		// clear spi bus
	clr_gpio		 pt_gpio_bank_0,	4
	set_gpio		 pt_gpio_bank_0,	12		// disable chip select (low active)

	// finalize initialisation and set active resource information
	LBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2
	SET var_temp_0, var_temp_0, BIT_RESOURCE_TEMPERATURE_INPUTS
	SBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

	JMP TEMPERATURE_INPUTS_END

TEMPERATURE_INPUTS_LOGIC:
	QBBC TEMPERATURE_INPUTS_END, var_used_resources, BIT_RESOURCE_TEMPERATURE_INPUTS

	LBBO var_temp_0, pt_temperatireInputConfigData, TEMPERATURE_INPUTS_OFFSET_COMMAND_STATE, 1
	QBNE TEMPERATURE_INPUTS_END, var_temp_0, 1

	MOV var_temp_0, 2
	SBBO var_temp_0, pt_temperatireInputConfigData, TEMPERATURE_INPUTS_OFFSET_COMMAND_STATE, 1

	LBBO var_temp_0, pt_temperatireInputConfigData, TEMPERATURE_INPUTS_OFFSET_BYTES_TO_WRITE, 1


	// start SPI transmission
	clr_gpio		 pt_gpio_bank_0,	2
	clr_gpio		 pt_gpio_bank_0,	4
	clr_gpio		 pt_gpio_bank_0,	12

	// wait until chip select becomes active
	temp_inputs_sleep 30

	// clear input data
	MOV var_spi_input_data, 0
	// set bit count
	MOV var_spi_loop_count, 32


	// clear spi bus bits
	clr_gpio		 pt_gpio_bank_0,	2
	clr_gpio		 pt_gpio_bank_0,	4
	set_gpio		 pt_gpio_bank_0,	12

	temp_inputs_sleep 30



	MOV var_temp_0, 3
	SBBO var_temp_0, pt_temperatireInputConfigData, TEMPERATURE_INPUTS_OFFSET_COMMAND_STATE, 1

	JMP TEMPERATURE_INPUTS_END

TEMPERATURE_INPUTS_END:
	RET

#endif //  _TEMPERATURE_INPUTS_ASM_INCLUDED_
