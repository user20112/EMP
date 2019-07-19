#ifndef _DIGITAL_OUTPUTS_ASM_INCLUDED_
#define _DIGITAL_OUTPUTS_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "DigitalOutputsDefines.asm"
#include "SpiCommunication.asm"


#define OFFSET_DITITAL_OUT_CTRL			0		// length: 4 bytes
#define OFFSET_DITITAL_OUT_INPUT		4		// length: 2 bytes
#define OFFSET_DITITAL_OUT_OUTPUT		6		// length: 2 bytes

#define OFFSET_DITITAL_OUT_DIAG_CNT_1	8		// length: 4 bytes
#define OFFSET_DITITAL_OUT_DIAG_CNT_2	12		// length: 4 bytes
#define OFFSET_DITITAL_OUT_DIAG_CNT_3	16		// length: 4 bytes
#define OFFSET_DITITAL_OUT_DIAG_CNT_4	20		// length: 4 bytes


// ==========================================================================================
//      digital output control
// ==========================================================================================
#define BIT_DIGITAL_OUPUT_TRANSMISSION_ACTIVE		0
#define BIT_DIGITAL_OUPUT_SEND_DATA					1


.macro digital_outputs_sleep
.mparam delay_count
.mparam temp_register = var_temp_0
	LDI	temp_register, delay_count
	DIGITAL_OUTPUTS_SLEEP_LOOP:
		SUB temp_register, temp_register, 1
		QBNE DIGITAL_OUTPUTS_SLEEP_LOOP, temp_register, 0
.endm

DIGITAL_OUTPUTS_INIT:
	QBBC DIGITAL_OUTPUTS_END, var_used_resources, BIT_RESOURCE_DIGITAL_OUPUTS

// ==========================================================================================
//	load data base pointer
// ==========================================================================================
	MOV pt_digitalOutput_data, PT_DIG_OUT_DATA

	MOV var_next_result_address_offset, OFFSET_DIG_OUT_STD_DIAG

// ==========================================================================================
//	initialize spi bus
// ==========================================================================================
	gpio_as_output		pt_gpio_bank_0,	2		// spi clk
	gpio_as_input		pt_gpio_bank_0,	3		// spi miso (master out slave in)
	gpio_as_output		pt_gpio_bank_0,	4		// spi mosi (master out slave in)
	gpio_as_output		pt_gpio_bank_0,	5		// spi cs (chip select)

	clr_gpio		 pt_gpio_bank_0,	2		// clear spi bus
	clr_gpio		 pt_gpio_bank_0,	4
	set_gpio		 pt_gpio_bank_0,	5		// disable chip select (low active)

// ==========================================================================================
//	initialize result address
// ==========================================================================================
	MOV   var_next_result_address_offset, OFFSET_DIG_OUT_STD_DIAG

// ==========================================================================================
//	finalize initialisation and set active resource information
// ==========================================================================================
	LBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2
	SET var_temp_0, var_temp_0, BIT_RESOURCE_DIGITAL_OUPUTS
	SBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

	JMP DIGITAL_OUTPUTS_END

DIGITAL_OUTPUTS_LOGIC:
	QBBC DIGITAL_OUTPUTS_END, var_used_resources, BIT_RESOURCE_DIGITAL_OUPUTS

	// start SPI transmission
	clr_gpio		 pt_gpio_bank_0,	2
	clr_gpio		 pt_gpio_bank_0,	4
	clr_gpio		 pt_gpio_bank_0,	5

	// wait until chip select becomes active
	digital_outputs_sleep 30

	// clear input data
	MOV var_spi_input_data, 0
	// set bit count
	MOV var_spi_loop_count, 16

	// check for command in command buffer
	MOV var_temp_4, 0
	LBBO var_temp_4, pt_digitalOutput_data, OFFSET_DIG_OUT_READ_OFFSET, 2
	MOV var_temp_2, 0
	LBBO var_temp_2, pt_digitalOutput_data, OFFSET_DIG_OUT_WRITE_OFFSET, 2

	QBNE DIGITAL_OUTPUTS_SEND_COMMAND, var_temp_4, var_temp_2

	// get output data from memory
	LBBO var_spi_output_data, pt_digitalOutput_data, OFFSET_DIG_OUT_REQ_STATE, 2
	SBBO var_spi_output_data, pt_digitalOutput_data, OFFSET_DIG_OUT_ACT_STATE, 2

    // send command to chip
	spi_communication_run

	// save result
	SBBO  var_spi_input_data, pt_digitalOutput_data, var_next_result_address_offset, 2
	MOV   var_next_result_address_offset, OFFSET_DIG_OUT_STD_DIAG

	JMP DIGITAL_OUTPUTS_CLOSE_SPI

DIGITAL_OUTPUTS_SEND_COMMAND:
	// calculate command buffer offset
	MOV var_temp_2, var_temp_4
	LSL var_temp_2, var_temp_2, 2
	ADD var_temp_2, var_temp_2, OFFSET_DIG_OUT_CMD_QUEUE_DATA

	// get command value
	SBBO var_temp_2, pt_digitalOutput_data, OFFSET_DIG_OUT_BUFFER_READ_OFFSET, 2
	LBBO var_spi_output_data, pt_digitalOutput_data, var_temp_2, 2

	SBBO var_temp_4, pt_digitalOutput_data , OFFSET_DIG_OUT_DEBUG_1, 4

    // send command to chip
	spi_communication_run

	SBBO var_temp_4, pt_digitalOutput_data , OFFSET_DIG_OUT_DEBUG_2, 4

	// save result
	SBBO 		var_spi_input_data, pt_digitalOutput_data, var_next_result_address_offset, 2
	ADD var_temp_2, var_temp_2, 2
	MOV var_next_result_address_offset, var_temp_2

	ADD var_temp_4, var_temp_4, 1
	QBGT DIGITAL_OUTPUTS_SAVE_NEXT_BUFFER_INDEX, var_temp_4, 8
		MOV var_temp_4, 0

DIGITAL_OUTPUTS_SAVE_NEXT_BUFFER_INDEX:
	SBBO var_temp_4, pt_digitalOutput_data, OFFSET_DIG_OUT_READ_OFFSET, 2

DIGITAL_OUTPUTS_CLOSE_SPI:
	// clear spi bus bits
	clr_gpio		 pt_gpio_bank_0,	2
	clr_gpio		 pt_gpio_bank_0,	4
	set_gpio		 pt_gpio_bank_0,	5

	digital_outputs_sleep 30

	SBBO var_next_result_address_offset, pt_digitalOutput_data, OFFSET_DIG_OUT_NEXT_RESULT_OFFSET, 2

DIGITAL_OUTPUTS_END:
	RET

#endif //  _DIGITAL_OUTPUTS_ASM_INCLUDED_
