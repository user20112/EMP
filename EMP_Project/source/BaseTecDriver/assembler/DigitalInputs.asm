#ifndef _DIGITAL_INPUTS_ASM_INCLUDED_
#define _DIGITAL_INPUTS_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "DigitalInputsDefines.asm"
#include "GpioAccess.asm"

DIGITAL_INPUTS_INIT:
	QBBC DIGITAL_INPUTS_END, var_used_resources, BIT_RESOURCE_DIGITAL_INPUTS

// ==========================================================================================
//	load data base pointer
// ==========================================================================================
	MOV pt_digitalInput_data, PT_DIG_IN_DATA

// ==========================================================================================
//	initialize gpio multiplexed inputs
// ==========================================================================================
//     this will be also done in mdoule "HardwareCtrl.asm". Keep this in both files in case one isn't called
	gpio_as_input		pt_gpio_bank_2,	5		// in0
	gpio_as_input		pt_gpio_bank_2,	4		// in1
	gpio_as_input		pt_gpio_bank_1,	13		// in2
	gpio_as_input		pt_gpio_bank_1,	12		// in3
	gpio_as_input		pt_gpio_bank_0,	23		// in4
	gpio_as_input		pt_gpio_bank_0,	26		// in5
	gpio_as_input		pt_gpio_bank_1,	15		// in6
	gpio_as_input		pt_gpio_bank_1,	14		// in7
	gpio_as_input		pt_gpio_bank_3,	14		// in8

// ==========================================================================================
//	setup chip select bits
// ==========================================================================================
	// initialize gpio  !EN_INPUT
	gpio_as_output		pt_gpio_bank_2,	1
	clr_gpio			pt_gpio_bank_2,	1		// input are enabled by default

	// initialize gpio  CKL_D6-A
	gpio_as_output		pt_gpio_bank_0,	27
	clr_gpio			pt_gpio_bank_0,	27

	// initialize gpio  CKL_D14-A
	gpio_as_output		pt_gpio_bank_2,	3
	clr_gpio			pt_gpio_bank_2,	3

// ==========================================================================================
//	finalize initialisation and set active resource information
// ==========================================================================================
	LBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2
	SET var_temp_0, var_temp_0, BIT_RESOURCE_DIGITAL_INPUTS
	SBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

	JMP DIGITAL_INPUTS_END

DIGITAL_INPUTS_LOGIC:
	QBBC DIGITAL_INPUTS_END, var_used_resources, BIT_RESOURCE_DIGITAL_INPUTS

	clr_gpio			pt_gpio_bank_2,	1		// enable reading inputs

	MOV var_temp_3, 0
	MOV var_temp_4, 1

	// get gpio state register 0
	LBBO var_temp_0, pt_gpio_bank_0, GPIO_DATAIN, 4

	// in4
DIGITAL_INPUTS_BIT_4:
	QBBS DIGITAL_INPUTS_BIT_4_SET, var_temp_0, 23

	DIGITAL_INPUTS_BIT_4_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_4, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_4, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_4_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_4, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_4_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_4, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_4, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_4_END

	DIGITAL_INPUTS_BIT_4_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_4, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_4, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_4_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_4, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_4_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_4, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_4, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_4_END

DIGITAL_INPUTS_BIT_4_END:

	// in5
DIGITAL_INPUTS_BIT_5:
	QBBS DIGITAL_INPUTS_BIT_5_SET, var_temp_0, 26

	DIGITAL_INPUTS_BIT_5_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_5, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_5, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_5_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_5, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_5_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_5, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_5, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_5_END

	DIGITAL_INPUTS_BIT_5_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_5, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_5, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_5_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_5, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_5_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_5, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_5, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_5_END

DIGITAL_INPUTS_BIT_5_END:

	// get gpio state register 1
	LBBO var_temp_0, pt_gpio_bank_1, GPIO_DATAIN, 4

	// in2
DIGITAL_INPUTS_BIT_2:
	QBBS DIGITAL_INPUTS_BIT_2_SET, var_temp_0, 13

	DIGITAL_INPUTS_BIT_2_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_2, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_2, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_2_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_2, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_2_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_2, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_2, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_2_END

	DIGITAL_INPUTS_BIT_2_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_2, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_2, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_2_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_2, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_2_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_2, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_2, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_2_END

DIGITAL_INPUTS_BIT_2_END:

	// in3
DIGITAL_INPUTS_BIT_3:
	QBBS DIGITAL_INPUTS_BIT_3_SET, var_temp_0, 12

	DIGITAL_INPUTS_BIT_3_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_3, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_3, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_3_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_3, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_3_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_3, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_3, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_3_END

	DIGITAL_INPUTS_BIT_3_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_3, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_3, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_3_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_3, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_3_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_3, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_3, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_3_END

DIGITAL_INPUTS_BIT_3_END:

	// in6
DIGITAL_INPUTS_BIT_6:
	QBBS DIGITAL_INPUTS_BIT_6_SET, var_temp_0, 15

	DIGITAL_INPUTS_BIT_6_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_6, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_6, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_6_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_6, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_6_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_6, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_6, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_6_END

	DIGITAL_INPUTS_BIT_6_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_6, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_6, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_6_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_6, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_6_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_6, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_6, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_6_END

DIGITAL_INPUTS_BIT_6_END:

	// in7
DIGITAL_INPUTS_BIT_7:
	QBBS DIGITAL_INPUTS_BIT_7_SET, var_temp_0, 14

	DIGITAL_INPUTS_BIT_7_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_7, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_7, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_7_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_7, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_7_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_7, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_7, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_7_END

	DIGITAL_INPUTS_BIT_7_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_7, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_7, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_7_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_7, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_7_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_7, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_7, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_7_END

DIGITAL_INPUTS_BIT_7_END:

	// get gpio state register 2
	LBBO var_temp_0, pt_gpio_bank_2, GPIO_DATAIN, 4

	// in0
DIGITAL_INPUTS_BIT_0:
	QBBS DIGITAL_INPUTS_BIT_0_SET, var_temp_0, 5

	DIGITAL_INPUTS_BIT_0_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_0, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_0, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_0_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_0, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_0_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_0, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_0, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_0_END

	DIGITAL_INPUTS_BIT_0_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_0, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_0, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_0_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_0, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_0_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_0, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_0, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_0_END

DIGITAL_INPUTS_BIT_0_END:

	// in1
DIGITAL_INPUTS_BIT_1:
	QBBS DIGITAL_INPUTS_BIT_1_SET, var_temp_0, 4

	DIGITAL_INPUTS_BIT_1_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_1, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_1, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_1_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_1, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_1_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_1, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_1, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_1_END

	DIGITAL_INPUTS_BIT_1_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_1, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_1, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_1_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_1, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_1_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_1, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_1, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_1_END

DIGITAL_INPUTS_BIT_1_END:

	// get gpio state register 3
	LBBO var_temp_0, pt_gpio_bank_3, GPIO_DATAIN, 14

	// in8
DIGITAL_INPUTS_BIT_8:
	QBBS DIGITAL_INPUTS_BIT_8_SET, var_temp_0, 5

	DIGITAL_INPUTS_BIT_8_CLR:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_8, 1	// get last input state
		SBBO var_temp_3, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_8, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_8_END, var_temp_1, 0	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_8, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_8_END, var_temp_2, 1	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_8, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_8, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_8_END

	DIGITAL_INPUTS_BIT_8_SET:
		LBBO var_temp_1, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_8, 1	// get last input state
		SBBO var_temp_4, pt_digitalInput_data, OFFSET_DIG_IN_CUR_STATE_BIT_8, 1	// set new input state

		// check for need to increment counter
		QBEQ DIGITAL_INPUTS_BIT_8_END, var_temp_1, 1	// last value not set ==> no edge
		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNT_MODE_BIT_8, 1	// get count mode
		QBBC DIGITAL_INPUTS_BIT_8_END, var_temp_2, 0	// don't count faling edges

		LBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_8, 1	// get last counter value
		ADD var_temp_2, var_temp_2, 1											// increment counter
		SBBO var_temp_2, pt_digitalInput_data, OFFSET_DIG_IN_COUNTER_BIT_8, 1	// get last counter value
		JMP DIGITAL_INPUTS_BIT_8_END

DIGITAL_INPUTS_BIT_8_END:

	set_gpio			pt_gpio_bank_2,	1		// enable reading inputs
	JMP DIGITAL_INPUTS_END

DIGITAL_INPUTS_END:
	RET

#endif //  _DIGITAL_INPUTS_ASM_INCLUDED_
