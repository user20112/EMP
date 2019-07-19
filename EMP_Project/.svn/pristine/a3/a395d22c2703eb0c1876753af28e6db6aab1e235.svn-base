#ifndef _PRU_REGISTER_LIST_ASM_INCLUDED_
#define _PRU_REGISTER_LIST_ASM_INCLUDED_


// ==========================================================================================
// ==========================================================================================
//    memory mapping
// ==========================================================================================
// ==========================================================================================

// ==========================================================================================
//      local memory
// ==========================================================================================
#define PT_LOCAL_MEMORY				0x00000000

// ==========================================================================================
//      shared memory
// ==========================================================================================
#define PT_SHARED_MEMORY			0x00010000

#define PT_SYSTEM_DATA				PT_SHARED_MEMORY + 0x0000
#define PT_HW_CTRL_DATA				PT_SHARED_MEMORY + 0x0020
#define PT_DIG_IN_DATA				PT_SHARED_MEMORY + 0x0040
#define PT_DIG_OUT_DATA				PT_SHARED_MEMORY + 0x00a0
#define PT_ANA_IN_DATA				PT_SHARED_MEMORY + 0x00f0
#define PT_TEMP_IN_DATA				PT_SHARED_MEMORY + 0x2fb0


// ==========================================================================================
// ==========================================================================================
//    cpu register usage
// ==========================================================================================
// ==========================================================================================

// ==========================================================================================
//      global scope
// ==========================================================================================
#define var_temp_0					r0 		// temporary usage
#define var_temp_1					r1 		// temporary usage
#define var_temp_2					r2 		// temporary usage
#define var_temp_3					r3 		// temporary usage
#define var_temp_4					r4 		// temporary usage

// base struct access
#define pt_systen_config			r5 		// pointer to system configuaration
#define pt_system_data				r6		// pointer to system data
#define var_used_resources			r7		// shadow copy of used hardware resources
#define var_firmware_status			r8		// shadow copy of firmware status
#define var_alive_counter			r9		// current logic cycle number (alive counter)

// gpio pointer
#define pt_gpio_bank_0				r10		// start address for GPIO Bank 1
#define pt_gpio_bank_1				r11		// start address for GPIO Bank 2
#define pt_gpio_bank_2				r12		// start address for GPIO Bank 3
#define pt_gpio_bank_3				r13		// start address for GPIO Bank 4

// calling subrouting
#define var_return_address			r30		// register used by system !!!
#define var_return_value			r31

// ==========================================================================================
//      HardwareCtrl
// ==========================================================================================
#define pt_hw_ctrl_data				r14

// ==========================================================================================
//      Digital Inputs
// ==========================================================================================
#define pt_digitalInput_data		r15
#define var_ditital_input_status	r16

// ==========================================================================================
//      SPI communication
// ==========================================================================================
#define var_spi_loop_count			r19
#define var_spi_input_data			r20
#define var_spi_output_data			r21

// ==========================================================================================
//      Digital Outputs
// ==========================================================================================
#define pt_digitalOutput_data		r17
#define var_next_result_address_offset	r18

// ==========================================================================================
//      Analog Inputs
// ==========================================================================================
#define pt_analogInput_register		r22
#define pt_analogInput_data			r23
#define pt_analogInputConfigData	r24
#define var_analogInputStartInfo	r20

#define var_analogInputOffsetWrite	r25
#define var_analogInputOffsetRead	r26
#define var_analogInputValOverflow	r27
#define var_analogInputValCounter	r28

// ==========================================================================================
//      Temperature Inputs
// ==========================================================================================
#define pt_temperatireInputConfigData	r29

// ==========================================================================================
//      unuedes register
// ==========================================================================================


#endif //  _PRU_REGISTER_LIST_ASM_INCLUDED_
