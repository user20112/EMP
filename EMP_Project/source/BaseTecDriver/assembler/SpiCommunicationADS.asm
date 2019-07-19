#ifndef _SPI_COMMUNICATION_ADS_ASM_INCLUDED_
#define _SPI_COMMUNICATION_ADS_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"

.macro spi_communication_sleep_ads
.mparam delay_count
.mparam temp_register = var_temp_0
	LDI	temp_register, delay_count
	DIGITAL_OUTPUTS_SLEEP_LOOP2:
		SUB temp_register, temp_register, 1
		QBNE DIGITAL_OUTPUTS_SLEEP_LOOP2, temp_register, 0
.endm




.macro spi_communication_run_ads
.mparam input_data = var_spi_input_data
.mparam loop_count = var_spi_loop_count
.mparam output_data = var_spi_output_data

	MOV		input_data, 0

	SPI_COMMUNICATION_CLOCK_LOOP:

			SUB				loop_count, loop_count, 1

			// set mosi bit
			QBBC SPI_COMMUNICATION_CLEAR_MOSI, output_data, loop_count
				set_gpio		pt_gpio_bank_0,	4
				JMP SPI_COMMUNICATION_MOSI_DONE
			SPI_COMMUNICATION_CLEAR_MOSI:
				clr_gpio		pt_gpio_bank_0,	4
			SPI_COMMUNICATION_MOSI_DONE:

			// set spi clock bit and wait
			set_gpio		pt_gpio_bank_0,	2
			spi_communication_sleep 255

			// load status of gpio bank 0
			LBBO var_temp_3, pt_gpio_bank_0, GPIO_DATAIN, 4

			QBBC	SPI_COMMUNICATION_MISO_CLEARED, var_temp_3, 3
				SET		input_data, 0
			SPI_COMMUNICATION_MISO_CLEARED:

			LSL		input_data, input_data, 1

			// clear spi clock bit and wait
			clr_gpio		pt_gpio_bank_0,	2
			spi_communication_sleep 255

			// decrement loop counter and close loop
			QBNE			SPI_COMMUNICATION_CLOCK_LOOP, loop_count, 0

	LSR			input_data, input_data, 1
/*
.mparam input_data = var_spi_input_data
//.mparam loop_count = var_spi_loop_count
.mparam loop_count = var_temp_2
.mparam output_data = var_spi_output_data
.mparam clks_to_send = var_spi_loop_count

	MOV 	loop_count, 0
	MOV		input_data, 0

	SPI_COMMUNICATION_CLOCK_LOOP2:

//			SUB				loop_count, loop_count, 1
			// set mosi bit
			QBBC SPI_COMMUNICATION_CLEAR_MOSI2, output_data, loop_count
				set_gpio		pt_gpio_bank_0,	4
				JMP SPI_COMMUNICATION_MOSI_DONE2
			SPI_COMMUNICATION_CLEAR_MOSI2:
				clr_gpio		pt_gpio_bank_0,	4
			SPI_COMMUNICATION_MOSI_DONE2:
			// set spi clock bit and wait
			set_gpio		pt_gpio_bank_0,	2
			spi_communication_sleep 30

			// load status of gpio bank 0
			LBBO var_temp_3, pt_gpio_bank_0, GPIO_DATAIN, 4

			QBBC	SPI_COMMUNICATION_MISO_CLEARED2, var_temp_3, 3
				SET		input_data, 0
			SPI_COMMUNICATION_MISO_CLEARED2:
			LSL		input_data, input_data, 1

			// clear spi clock bit and wait
			clr_gpio		pt_gpio_bank_0,	2
			spi_communication_sleep 30

			ADD				loop_count, loop_count, 1
			// check loop condition, jump until loop_count equals var_spi_loop_count
			QBNE			SPI_COMMUNICATION_CLOCK_LOOP2, clks_to_send, loop_count
	//		QBLT			SPI_COMMUNICATION_CLOCK_LOOP2, clks_to_send, loop_count

LSR			input_data, input_data, 1
*/
.endm

#endif //  _SPI_COMMUNICATION_ASM_INCLUDED_
