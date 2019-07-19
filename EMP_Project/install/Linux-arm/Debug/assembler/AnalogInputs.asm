#ifndef _ANALOG_INPUTS_ASM_INCLUDED_
#define _ANALOG_INPUTS_ASM_INCLUDED_

// ==========================================================================================
//	include required header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "AnalogInputsDefines.asm"


// ==========================================================================================
// ==========================================================================================
//    module initialization
// ==========================================================================================
// ==========================================================================================
ANALOG_INPUTS_INIT:
	QBBC ANALOG_INPUTS_END, var_used_resources, BIT_RESOURCE_ANALOG_INPUTS

	// get memory address
	MOV  pt_analogInputConfigData, PT_ANA_IN_DATA
    MOV  pt_analogInput_register, PT_ADC_REGISTER_BASE_ADDR
    MOV  pt_analogInput_data, PT_ADC_FIFO_DATA_1

// ==========================================================================================
//	wakeup ADC
// ==========================================================================================
	MOV var_analogInputStartInfo, 0
	SET var_analogInputStartInfo, 0
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

    LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_REVISION, 4	// check ADC revision, if 0 wakeup
    QBNE ANALOG_INPUTS_IS_AWAKE, var_temp_0, 0

	SET var_analogInputStartInfo, 1
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

    MOV  var_temp_1, PT_ADC_REGISTER_WAKEUP_ADDR                             // wakeup ADC
    MOV  var_temp_2, 0x02
    SBBO var_temp_2.b0, var_temp_1, 0, 1

	// wait ADC ok 16 cycles
    MOV var_temp_2, 16

ANALOG_INPUTS_WAKEUP_LOOP:
    LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_REVISION, 4
    QBNE ANALOG_INPUTS_IS_AWAKE, var_temp_0, 0
    SUB  var_temp_2, var_temp_2, 1
    QBNE ANALOG_INPUTS_WAKEUP_LOOP, var_temp_2, 0

	// unable to get adc wake up. stop this functional module ==> stop initialization.
	// AnalogInput module don't become active !!!
    JMP ANALOG_INPUTS_END

ANALOG_INPUTS_IS_AWAKE:

	SET var_analogInputStartInfo, 2
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_0, 0

// ==========================================================================================
//	 enable ADC Configuration
// ==========================================================================================
	SET var_analogInputStartInfo, 3
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_1, 0x00000006
	SBBO var_temp_1, pt_analogInput_register, OFFSET_ADC_REGISTER_CTRL, 4

// ==========================================================================================
//	 set idle mode and wait until it's acknowledged
// ==========================================================================================
	SET var_analogInputStartInfo, 4
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_1, 0
	SBBO var_temp_1, pt_analogInput_register, OFFSET_ADC_REGISTER_SYSCONFIG, 4

ANALOG_INPUTS_IS_BUSY:
    LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_ADCSTAT, 4   // get ADC status
    QBBS ANALOG_INPUTS_IS_BUSY, var_temp_0, 5                                  // ADC busy, wait

// ==========================================================================================
//	 set IRQ-Register to zero
// ==========================================================================================
	SET var_analogInputStartInfo, 5
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_0, 0
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IRQSTATUS_RAW, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IRQSTATUS, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IRQENABLE_SET, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IRQENABLE_CLR, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IRQWAKEUP, 4

// ==========================================================================================
//	 set DMA-Register to zero
// ==========================================================================================
	SET var_analogInputStartInfo, 6
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_0, 0
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_DMAENABLE_SET, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_DMAENABLE_CLR, 4

// ==========================================================================================
//	 set general ADC settings
// ==========================================================================================
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_ADC_CLKDIV, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_ADC_MISC, 4

// ==========================================================================================
//	 config scheduler
// ==========================================================================================
	SET var_analogInputStartInfo, 7
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	// IDLE-Step
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_IDLECONFIG, 4

	// Charge-Step
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_TS_CHARGE_STEPCONFIG, 4
	SBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_TS_CHARGE_DELAY, 4

	// converting steps

	// Get Step requested settings from host
	LBBO var_temp_0, pt_analogInputConfigData, OFFSET_ADC_DATA_SAMPLE_AVERAGE, 2
	LSL var_temp_0, var_temp_0, 2		// move data to needed register position
	ADD var_temp_0, var_temp_0, 0b01	// set: SW enabled, single shot

	LBBO var_temp_1, pt_analogInputConfigData, OFFSET_ADC_DATA_SAMPLE_DELAY, 2
	LSL var_temp_1, var_temp_1, 24

	LBBO var_temp_2, pt_analogInputConfigData, OFFSET_ADC_DATA_OPEN_DELAY, 2
	ADD var_temp_1, var_temp_1, var_temp_2

	SET var_analogInputStartInfo, 8
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	MOV var_temp_2, 0				// step counter

ANALOG_INPUTS_STEP_CONFIG_LOOP:
	// create config information
	LSL var_temp_4, var_temp_2, 19		    // current step = channel id
	ADD var_temp_4, var_temp_4, var_temp_0  // add basic configuration

	// calcuate register offset
	LSL var_temp_3, var_temp_2, 3		// multiply current step by 8 (= offset between config register)
	ADD var_temp_3, var_temp_3, OFFSET_ADC_REGISTER_STEPCONFIG1	// add base offset

	// store register information
	SBBO var_temp_4, pt_analogInput_register, var_temp_3, 4

	// calcuate register offset
	ADD var_temp_3, var_temp_3, 4		// address of sample register

	// store register information
	SBBO var_temp_1, pt_analogInput_register, var_temp_3, 4

	ADD var_temp_2, var_temp_2, 1

	QBGT ANALOG_INPUTS_STEP_CONFIG_LOOP, var_temp_2, 7

// ==========================================================================================
//	 clear fifo values
// ==========================================================================================
	SET var_analogInputStartInfo, 9
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

ANALOG_INPUTS_CLEAR_FIFO_0:
	LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_FIFO0COUNT, 4
	QBEQ ANALOG_INPUTS_FIFO_0_CLEARED, var_temp_0, 0
	LBBO var_temp_1, pt_analogInput_data, 0, 4
	JMP ANALOG_INPUTS_CLEAR_FIFO_0

ANALOG_INPUTS_FIFO_0_CLEARED:

	MOV pt_analogInput_data, PT_ADC_FIFO_DATA_2
ANALOG_INPUTS_CLEAR_FIFO_1:
	LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_FIFO1COUNT, 4
	QBEQ ANALOG_INPUTS_FIFO_1_CLEARED, var_temp_0, 0
	LBBO var_temp_1, pt_analogInput_data, 0, 4
	JMP ANALOG_INPUTS_CLEAR_FIFO_1

ANALOG_INPUTS_FIFO_1_CLEARED:

// ==========================================================================================
//	 finalize ADC Configuration
// ==========================================================================================
	SET var_analogInputStartInfo, 10
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	// enable scheduler steps
	MOV var_temp_2, 0x000000fe
	SBBO var_temp_2, pt_analogInput_register, OFFSET_ADC_REGISTER_STEPENABLE, 4

	// activate write protection for ADC register and start scheduler
	MOV var_temp_1, 0x00000003
	SBBO var_temp_1, pt_analogInput_register, OFFSET_ADC_REGISTER_CTRL, 4

	MOV pt_analogInput_data, PT_ADC_FIFO_DATA_1	// default data fifo: channel 1

// ==========================================================================================
//	finalize initialisation and set active resource information
// ==========================================================================================
	SET var_analogInputStartInfo, 11
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	LBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2
	SET var_temp_0, var_temp_0, BIT_RESOURCE_ANALOG_INPUTS
	SBBO var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

	JMP ANALOG_INPUTS_END

// ==========================================================================================
// ==========================================================================================
//    cyclic program
// ==========================================================================================
// ==========================================================================================
ANALOG_INPUTS_LOGIC:
	QBBC ANALOG_INPUTS_END, var_used_resources, BIT_RESOURCE_ANALOG_INPUTS

	// debug info: logic called
	SET var_analogInputStartInfo, 12
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	// get count of values in fifo 0
	LBBO var_temp_0, pt_analogInput_register, OFFSET_ADC_REGISTER_FIFO0COUNT, 4

	// debug: add count of values to memory
	// =================== DEBUG: OFF ======================================
	LBBO var_temp_1, pt_analogInputConfigData, OFFSET_ADC_DATA_READ_VAL_CNT, 2
	ADD var_temp_1, var_temp_1, var_temp_0
	SBBO var_temp_1, pt_analogInputConfigData, OFFSET_ADC_DATA_READ_VAL_CNT, 2
	// =================== DEBUG: OFF ======================================


ANALOG_INPUTS_READ_FIFO_0:
	// quit loop, when no values are left
	QBEQ ANALOG_INPUTS_READ_FIFO_0_DONE, var_temp_0, 0

	// debug info: read fifo 0 active
	SET var_analogInputStartInfo, 13
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	// get next value from ADC-fifo
	LBBO var_temp_1, pt_analogInput_data, 0, 4

	// extract channel ID from input value and move to bit 12 - 14
	MOV var_temp_4, 0x00070000
	AND var_temp_2, var_temp_1, var_temp_4
	LSR var_temp_2, var_temp_1, 4

	// copy channel ID to measurement value
	OR var_temp_1, var_temp_1, var_temp_2
	// set MSB (16 bit) => value is valid
	SET var_temp_1, var_temp_1, 15

	// get write position from memory
	MOV var_temp_2, 0
	LBBO var_temp_2, pt_analogInputConfigData, OFFSET_ADC_DATA_WRITE_POS, 2

	// check for limitation
	MOV var_temp_4, ADC_DATA_BUFFER_SIZE
	LSL var_temp_4, var_temp_4, 1
	QBGT ANALOG_INPUTS_STORE_VALUE, var_temp_2, var_temp_4
		MOV var_temp_2, 0

ANALOG_INPUTS_STORE_VALUE:
	// calculate memory address for next value
	MOV var_temp_3, pt_analogInputConfigData
	ADD var_temp_3, var_temp_3, OFFSET_ADC_DATA_DATA_BUFFER
	ADD var_temp_3, var_temp_3, var_temp_2

	// store current value
	SBBO var_temp_1, var_temp_3, 0, 2

	// store next write offset
	ADD var_temp_2, var_temp_2, 2
	SBBO var_temp_2, pt_analogInputConfigData, OFFSET_ADC_DATA_WRITE_POS, 2

ANALOG_INPUTS_READ_FIFO_0_SKIP_VAL:

	// decremnt value counter and return to reading loop
	SUB var_temp_0, var_temp_0, 1
	JMP ANALOG_INPUTS_READ_FIFO_0

ANALOG_INPUTS_READ_FIFO_0_DONE:
	// debug info: read fifo 0 finished
	SET var_analogInputStartInfo, 14
	SBBO var_analogInputStartInfo, pt_analogInputConfigData, OFFSET_ADC_DATA_STATE, 4

	JMP ANALOG_INPUTS_END

// ==========================================================================================
// ==========================================================================================
//    end subprogram
// ==========================================================================================
// ==========================================================================================
ANALOG_INPUTS_END:
	RET

#endif //  _ANALOG_INPUTS_ASM_INCLUDED_
