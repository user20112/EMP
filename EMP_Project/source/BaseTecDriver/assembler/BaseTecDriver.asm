.origin 0
.entrypoint BEGIN
	JMP 	BEGIN	// goto programm entry point

// ==========================================================================================
//	include basic header
// ==========================================================================================
#include "PruRegisterList.asm"
#include "BaseTecDriverDefines.asm"
#include "GpioRegister.asm"

// ==========================================================================================
//	include functional modules
// ==========================================================================================
#include "HardwareCtrl.asm"
#include "DigitalInputs.asm"
#include "DigitalOutputs.asm"
#include "AnalogInputs.asm"
#include "TemperatureInputs.asm"

// ==========================================================================================
//	programm information
// ==========================================================================================
#define FIRMWARE_VERSION      0x01001001	// current Version: 01.01.001


// ==========================================================================================
// ==========================================================================================
//    Program Entry
// ==========================================================================================
// ==========================================================================================
BEGIN:

// ==========================================================================================
//    Memory initialization
// ==========================================================================================
  	// enable OCP master port (clear SYSCFG[STANDBY_INIT])
  	// needed to use global memory map
	LBCO   var_temp_0, C4, 4, 4  				// get current configuraion register
  	CLR    var_temp_0, var_temp_0, 4			// clear bit 4
  	SBCO   var_temp_0, C4, 4, 4					// write configuraion register

// ==========================================================================================
//    prepare initialization
// ==========================================================================================
	MOV     var_firmware_status, 0									// clear firmware status
	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_INIT_STARTED	// info: configuration started

	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_LOAD_MEMORY_MAP

// ==========================================================================================
//    init system data memory
// ==========================================================================================
	// load system momory pointer for config and data
  	MOV    pt_system_data, PT_SYSTEM_DATA

  	// copy firmware version to memory
 	MOV    var_temp_0, FIRMWARE_VERSION
  	SBBO   var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_FW_VERSION, 4

	// store firmware status
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

  	// reset alive counter
  	MOV     var_alive_counter, 0
  	SBBO    var_alive_counter, pt_system_data, OFFSET_SYSTEM_DATA_PRU_ALIVE_CNT, 4

  	// reset program loop counter and sleep counter
  	MOV     var_temp_0, 0
  	SBBO    var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PRU_SLEEP_CNT, 4
  	SBBO    var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PROGRAM_LOOP_CNT, 4

// ==========================================================================================
//    gpio bank pointer
// ==========================================================================================
	MOV		pt_gpio_bank_0, PT_GPIO_BANK_0
	MOV		pt_gpio_bank_1, PT_GPIO_BANK_1
	MOV		pt_gpio_bank_2, PT_GPIO_BANK_2
	MOV		pt_gpio_bank_3, PT_GPIO_BANK_3

// ==========================================================================================
//    get system configuration
// ==========================================================================================
	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_LAOD_SYSTEM_CFG
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

	LBBO   var_used_resources, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2
  	// clear resources list ==> will be updated during initialization
 	MOV    var_temp_0, 0
  	SBBO   var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

// ==========================================================================================
//    start module initialization
// ==========================================================================================
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_RUN_MODULE_INIT
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

	CALL HARDWARE_CTRL_INIT
	CALL DIGITAL_INPUTS_INIT
	CALL DIGITAL_OUTPUTS_INIT
	CALL ANALOG_INPUTS_INIT
	CALL TEMPERATURE_INPUTS_INIT

	// update active resources list
	LBBO   var_used_resources, pt_system_data, OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES, 2

// ==========================================================================================
//    initialization done
// ==========================================================================================
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_INIT_DONE
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4


// ==========================================================================================
// ==========================================================================================
//    Logic Loop
// ==========================================================================================
// ==========================================================================================
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_LOGIC_STARTED
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4
LOGIC_LOOP:

// ==========================================================================================
//    check alive counter
// ==========================================================================================
	// get firmware status
	MOV var_temp_0, 0
	LBBO    var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_STOP_CMD, 1
  	QBNE END, var_temp_0, 0

	// increment alive counter
  	LBBO    var_alive_counter, pt_system_data, OFFSET_SYSTEM_DATA_PRU_ALIVE_CNT, 4
	ADD     var_alive_counter, var_alive_counter, 1
  	SBBO    var_alive_counter, pt_system_data, OFFSET_SYSTEM_DATA_PRU_ALIVE_CNT, 4

	// check hostAliveCounter
	LBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_HOST_ALIVE_CNT, 4	// get current value from memory
	QBEQ    LOGIC_SLEEP, var_temp_0, 0											// jump to "LOGIC_SLEEP" when counter is zero
	SUB     var_temp_0, var_temp_0, 1											// decrement counter value
	SBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_HOST_ALIVE_CNT, 4	// write new value to memory

	// logic loop active
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_LOGIC_ACTIVE
  	CLR     var_firmware_status, BIT_SYSTEM_FW_STATUS_SLEEP_ACTIVE
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

	// increment loop counter
	LBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PROGRAM_LOOP_CNT, 4	// get current value from memory
	ADD     var_temp_0, var_temp_0, 1											// increment counter value
	SBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PROGRAM_LOOP_CNT, 4	// write new value to memory

// ==========================================================================================
//    call module logic
// ==========================================================================================

	CALL HARDWARE_CTRL_LOGIC
	CALL DIGITAL_INPUTS_LOGIC
	CALL DIGITAL_OUTPUTS_LOGIC
	CALL ANALOG_INPUTS_LOGIC
	CALL TEMPERATURE_INPUTS_LOGIC

// ==========================================================================================
//    loop done
// ==========================================================================================
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_FIRST_LOGIC_DONE
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

  	JMP		LOGIC_LOOP

LOGIC_SLEEP:
	// logic loop not active
  	CLR     var_firmware_status, BIT_SYSTEM_FW_STATUS_LOGIC_ACTIVE
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_SLEEP_ACTIVE
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

	// increment sleep counter
	LBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PRU_SLEEP_CNT, 4		// get current value from memory
	ADD     var_temp_0, var_temp_0, 1											// increment counter value
	SBBO	var_temp_0, pt_system_data, OFFSET_SYSTEM_DATA_PRU_SLEEP_CNT, 4		// write new value to memory

  	JMP		LOGIC_LOOP

// ==========================================================================================
// ==========================================================================================
//    clean up
// ==========================================================================================
// ==========================================================================================
END:
	// update status bit
  	CLR     var_firmware_status, BIT_SYSTEM_FW_STATUS_LOGIC_ACTIVE
  	CLR     var_firmware_status, BIT_SYSTEM_FW_STATUS_SLEEP_ACTIVE
  	SET     var_firmware_status, BIT_SYSTEM_FW_STATUS_PROGRAM_STOPPED
  	SBBO	var_firmware_status, pt_system_data, OFFSET_SYSTEM_DATA_FW_STATUS, 4

  	HALT
