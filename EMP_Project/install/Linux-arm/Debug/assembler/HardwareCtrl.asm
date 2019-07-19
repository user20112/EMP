#ifndef _HARDWARE_CTRL_ASM_INCLUDED_
#define _HARDWARE_CTRL_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "HardwareCtrlDefines.asm"
#include "GpioAccess.asm"

HARDWARE_CTRL_INIT:
	QBBC HARDWARE_CTRL_END, var_used_resources, BIT_RESOURCE_HARDWARE_CTRL

// ==========================================================================================
//	load data base pointer
// ==========================================================================================
	MOV pt_hw_ctrl_data, PT_HW_CTRL_DATA

// ==========================================================================================
//	initialize gpio output 1,17 ==> hardware enable
// ==========================================================================================
	gpio_as_output		pt_gpio_bank_1,	17
	clr_gpio			pt_gpio_bank_1,	17

// ==========================================================================================
//	initialize gpio multiplexed inputs
// ==========================================================================================
//     this will be also done in mdoule "digitalInputs.asm". Keep this in both files in case one isn't called
	gpio_as_input		pt_gpio_bank_2,	5		// in0
	gpio_as_input		pt_gpio_bank_2,	4		// in1
	gpio_as_input		pt_gpio_bank_1,	13		// in2
	gpio_as_input		pt_gpio_bank_1,	12		// in3
	gpio_as_input		pt_gpio_bank_0,	23		// in4
	gpio_as_input		pt_gpio_bank_0,	26		// in5
	gpio_as_input		pt_gpio_bank_1,	15		// in6
	gpio_as_input		pt_gpio_bank_1,	14		// in7

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
	SET var_temp_0, var_temp_0, BIT_RESOURCE_HARDWARE_CTRL
	SBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

	JMP HARDWARE_CTRL_END

HARDWARE_CTRL_LOGIC:
	QBBC HARDWARE_CTRL_END, var_used_resources, BIT_RESOURCE_HARDWARE_CTRL

// ==========================================================================================
//	toggle hardware alive bit
// ==========================================================================================
	LBBO var_temp_0, pt_hw_ctrl_data, OFFSET_HW_CTRL_TRIGGER_BIT, 2

	// toogle hardware alive bit
	QBBS HARDWARE_CTRL_SET_BIT, var_alive_counter, var_temp_0

	clr_gpio			pt_gpio_bank_1,	17
	CLR     var_firmware_status, BIT_SYSTEM_FW_STATUS_HW_ALIVE_BIT
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

	JMP HARDWARE_CTRL_UART_CTRL

HARDWARE_CTRL_SET_BIT:
	set_gpio			pt_gpio_bank_1,	17
	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_HW_ALIVE_BIT
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

// ==========================================================================================
//	change hardware control bits
// ==========================================================================================
HARDWARE_CTRL_UART_CTRL:
	// disable input channel
	set_gpio			pt_gpio_bank_2,	1

	// change direction of multiplexed gpio's
	gpio_as_output		pt_gpio_bank_2,	5		// in0
	clr_gpio			pt_gpio_bank_2,	5
	gpio_as_output		pt_gpio_bank_2,	4		// in1
	clr_gpio			pt_gpio_bank_2,	4
	gpio_as_output		pt_gpio_bank_1,	13		// in2
	clr_gpio			pt_gpio_bank_1,	13
	gpio_as_output		pt_gpio_bank_1,	12		// in3
	clr_gpio			pt_gpio_bank_1,	12
	gpio_as_output		pt_gpio_bank_0,	23		// in4
	clr_gpio			pt_gpio_bank_0,	23
	gpio_as_output		pt_gpio_bank_0,	26		// in5
	clr_gpio			pt_gpio_bank_0,	26
	gpio_as_output		pt_gpio_bank_1,	15		// in6
	clr_gpio			pt_gpio_bank_1,	15
	gpio_as_output		pt_gpio_bank_1,	14		// in7
	clr_gpio			pt_gpio_bank_1,	14

	// load required settings and current state
	LBBO var_temp_0, pt_hw_ctrl_data, OFFSET_HW_CTRL_REQ_STATE_LED_GR, 5	// load all 5 required register to temporary register
	LBBO var_temp_2, pt_hw_ctrl_data, OFFSET_HW_CTRL_CUR_STATE_LED_GR, 5	// load all 5 current register to temporary register

	// togge between register D6 and D14 (one each logic cycle)
	QBBS HARDWARE_CTRL_D14, var_alive_counter, 0

	// first register
HARDWARE_CTRL_D6:

	CLR var_temp_2.b2, 0
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_0, var_temp_0.b2, 0
		set_gpio			pt_gpio_bank_2,	5
		SET var_temp_2.b2, 0
	HARDWARE_CTRL_D6_SKIP_BIT_0:

	CLR var_temp_2.b3, 0
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_1, var_temp_0.b3, 0
		set_gpio			pt_gpio_bank_2,	4
		SET var_temp_2.b3, 0
	HARDWARE_CTRL_D6_SKIP_BIT_1:

	CLR var_temp_2.b2, 1
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_2, var_temp_0.b2, 1
		set_gpio			pt_gpio_bank_1,	13
		SET var_temp_2.b2, 1
	HARDWARE_CTRL_D6_SKIP_BIT_2:

	CLR var_temp_2.b3, 1
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_3, var_temp_0.b3, 1
		set_gpio			pt_gpio_bank_1,	12
		SET var_temp_2.b2, 1
	HARDWARE_CTRL_D6_SKIP_BIT_3:

	CLR var_temp_2.b2, 2
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_4, var_temp_0.b2, 2
		set_gpio			pt_gpio_bank_0,	23
		SET var_temp_2.b2, 2
	HARDWARE_CTRL_D6_SKIP_BIT_4:

	CLR var_temp_2.b3, 2
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_5, var_temp_0.b3, 2
		set_gpio			pt_gpio_bank_0,	26
		SET var_temp_2.b3, 2
	HARDWARE_CTRL_D6_SKIP_BIT_5:

	CLR var_temp_2.b1, 0
	QBBS HARDWARE_CTRL_D6_SKIP_BIT_6, var_temp_0.b1, 0
		set_gpio			pt_gpio_bank_1,	15
		SET var_temp_2.b1, 0
	HARDWARE_CTRL_D6_SKIP_BIT_6:

	CLR var_temp_2.b0, 0
	QBBC HARDWARE_CTRL_D6_SKIP_BIT_7, var_temp_0.b0, 0
		set_gpio			pt_gpio_bank_1,	14
		SET var_temp_2.b0, 0
	HARDWARE_CTRL_D6_SKIP_BIT_7:

	set_gpio			pt_gpio_bank_0,	27
	JMP HARDWARE_CTRL_LOGIC_END

	// second register
HARDWARE_CTRL_D14:
	CLR var_temp_2.b2, 3
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_0, var_temp_0.b2, 3
		set_gpio			pt_gpio_bank_2,	5
		SET var_temp_2.b2, 3
	HARDWARE_CTRL_D14_SKIP_BIT_0:

	CLR var_temp_2.b2, 4
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_1, var_temp_0.b2, 4
		set_gpio			pt_gpio_bank_2,	4
		SET var_temp_2.b2, 4
	HARDWARE_CTRL_D14_SKIP_BIT_1:

	CLR var_temp_2.b2, 5
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_2, var_temp_0.b2, 5
		set_gpio			pt_gpio_bank_1,	13
		SET var_temp_2.b2, 5
	HARDWARE_CTRL_D14_SKIP_BIT_2:

	CLR var_temp_2.b3, 3
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_3, var_temp_0.b3, 3
		set_gpio			pt_gpio_bank_1,	12
		SET var_temp_2.b3, 3
	HARDWARE_CTRL_D14_SKIP_BIT_3:

	CLR var_temp_2.b3, 4
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_4, var_temp_0.b3, 4
		set_gpio			pt_gpio_bank_0,	23
		SET var_temp_2.b3, 4
	HARDWARE_CTRL_D14_SKIP_BIT_4:

	CLR var_temp_2.b3, 5
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_5, var_temp_0.b3, 5
		set_gpio			pt_gpio_bank_0,	26
		SET var_temp_2.b3, 5
	HARDWARE_CTRL_D14_SKIP_BIT_5:

	SET var_temp_3.b0, 0
	QBBC HARDWARE_CTRL_D14_SKIP_BIT_7, var_temp_1.b0, 0
		set_gpio			pt_gpio_bank_1,	14
		SET var_temp_3.b0, 0
	HARDWARE_CTRL_D14_SKIP_BIT_7:

	set_gpio			pt_gpio_bank_2,	3
	JMP HARDWARE_CTRL_LOGIC_END

HARDWARE_CTRL_LOGIC_END:
// ==========================================================================================
//	finalize logic call
// ==========================================================================================
	// disable chip select
	clr_gpio			pt_gpio_bank_0,	27
	clr_gpio			pt_gpio_bank_2,	3

	// update all 5 current register
	SBBO var_temp_2, pt_hw_ctrl_data, OFFSET_HW_CTRL_CUR_STATE_LED_GR, 5

	// change direction of multiplexed gpio's
	clr_gpio			pt_gpio_bank_2,	5
	gpio_as_input		pt_gpio_bank_2,	5		// in0
	clr_gpio			pt_gpio_bank_2,	4
	gpio_as_input		pt_gpio_bank_2,	4		// in1
	clr_gpio			pt_gpio_bank_1,	15
	gpio_as_input		pt_gpio_bank_1,	13		// in2
	clr_gpio			pt_gpio_bank_1,	12
	gpio_as_input		pt_gpio_bank_1,	12		// in3
	clr_gpio			pt_gpio_bank_0,	23
	gpio_as_input		pt_gpio_bank_0,	23		// in4
	clr_gpio			pt_gpio_bank_0,	26
	gpio_as_input		pt_gpio_bank_0,	26		// in5
	clr_gpio			pt_gpio_bank_1,	15
	gpio_as_input		pt_gpio_bank_1,	15		// in6
	clr_gpio			pt_gpio_bank_1,	14
	gpio_as_input		pt_gpio_bank_1,	14		// in7

	// enable input channel
	clr_gpio			pt_gpio_bank_2,	1		// disable input channel

HARDWARE_CTRL_END:
	RET

#endif //  _HARDWARE_CTRL_ASM_INCLUDED_
