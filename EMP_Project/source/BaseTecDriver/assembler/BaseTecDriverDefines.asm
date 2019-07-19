#ifndef _BASE_TEC_DRIVER_DEFINES_ASM_INCLUDED_
#define _BASE_TEC_DRIVER_DEFINES_ASM_INCLUDED_

// ==========================================================================================
// ==========================================================================================
//    data memory offsets
// ==========================================================================================
// ==========================================================================================
#define OFFSET_SYSTEM_DATA_FW_VERSION			0x00		// length: 4 bytes
#define OFFSET_SYSTEM_DATA_ACTIVE_RESOURCES		0x04		// length: 2 bytes
#define OFFSET_SYSTEM_DATA_RESERVED_01			0x06		// length: 2 bytes
#define OFFSET_SYSTEM_DATA_FW_STATUS			0x08		// length: 4 bytes
#define OFFSET_SYSTEM_DATA_RESERVED_02			0x0c		// length: 3 bytes
#define OFFSET_SYSTEM_DATA_STOP_CMD				0x0f		// length: 1 byte

#define OFFSET_SYSTEM_DATA_PRU_ALIVE_CNT		0x10		// length: 4 bytes
#define OFFSET_SYSTEM_DATA_HOST_ALIVE_CNT		0x14		// length: 4 bytes
#define OFFSET_SYSTEM_DATA_PROGRAM_LOOP_CNT		0x18		// length: 4 bytes
#define OFFSET_SYSTEM_DATA_PRU_SLEEP_CNT		0x1c		// length: 4 bytes


// ==========================================================================================
// ==========================================================================================
//    bit information: firmware status
// ==========================================================================================
// ==========================================================================================
#define BIT_SYSTEM_FW_STATUS_INIT_STARTED		0
#define BIT_SYSTEM_FW_STATUS_LOAD_MEMORY_MAP	1
#define BIT_SYSTEM_FW_STATUS_LAOD_SYSTEM_CFG	2
#define BIT_SYSTEM_FW_STATUS_RUN_MODULE_INIT	3
#define BIT_SYSTEM_FW_STATUS_04					4
#define BIT_SYSTEM_FW_STATUS_05					5
#define BIT_SYSTEM_FW_STATUS_06					6
#define BIT_SYSTEM_FW_STATUS_INIT_DONE			7
#define BIT_SYSTEM_FW_STATUS_LOGIC_STARTED		8
#define BIT_SYSTEM_FW_STATUS_FIRST_LOGIC_DONE	9
#define BIT_SYSTEM_FW_STATUS_10					10
#define BIT_SYSTEM_FW_STATUS_11					11
#define BIT_SYSTEM_FW_STATUS_12					12
#define BIT_SYSTEM_FW_STATUS_13					13
#define BIT_SYSTEM_FW_STATUS_14					14
#define BIT_SYSTEM_FW_STATUS_15					15
#define BIT_SYSTEM_FW_STATUS_LOGIC_ACTIVE		16
#define BIT_SYSTEM_FW_STATUS_SLEEP_ACTIVE		17
#define BIT_SYSTEM_FW_STATUS_HW_ALIVE_BIT		18
#define BIT_SYSTEM_FW_STATUS_19					19
#define BIT_SYSTEM_FW_STATUS_20					20
#define BIT_SYSTEM_FW_STATUS_21					21
#define BIT_SYSTEM_FW_STATUS_22					22
#define BIT_SYSTEM_FW_STATUS_23					23
#define BIT_SYSTEM_FW_STATUS_24					24
#define BIT_SYSTEM_FW_STATUS_25					25
#define BIT_SYSTEM_FW_STATUS_26					26
#define BIT_SYSTEM_FW_STATUS_27					27
#define BIT_SYSTEM_FW_STATUS_28					28
#define BIT_SYSTEM_FW_STATUS_29					29
#define BIT_SYSTEM_FW_STATUS_STOPPING_PROG		30
#define BIT_SYSTEM_FW_STATUS_PROGRAM_STOPPED	31

// ==========================================================================================
// ==========================================================================================
//    bit information: resource list
// ==========================================================================================
// ==========================================================================================
#define BIT_RESOURCE_HARDWARE_CTRL				0
#define BIT_RESOURCE_DIGITAL_INPUTS				1
#define BIT_RESOURCE_DIGITAL_OUPUTS				2
#define BIT_RESOURCE_ANALOG_INPUTS			    3
#define BIT_RESOURCE_TEMPERATURE_INPUTS		    4
#define BIT_RESOURCE__05					    5
#define BIT_RESOURCE__06					    6
#define BIT_RESOURCE__07					    7
#define BIT_RESOURCE__08					    8
#define BIT_RESOURCE__09					    9
#define BIT_RESOURCE__10					    10
#define BIT_RESOURCE__11					    11
#define BIT_RESOURCE__12					    12
#define BIT_RESOURCE__13					    13
#define BIT_RESOURCE__14					    14
#define BIT_RESOURCE__15					    15



// #define BIT_SYSTEM_FW_STATUS_00					0
// #define BIT_SYSTEM_FW_STATUS_01					1
// #define BIT_SYSTEM_FW_STATUS_02					2
// #define BIT_SYSTEM_FW_STATUS_03					3
// #define BIT_SYSTEM_FW_STATUS_04					4
// #define BIT_SYSTEM_FW_STATUS_05					5
// #define BIT_SYSTEM_FW_STATUS_06					6
// #define BIT_SYSTEM_FW_STATUS_07					7
// #define BIT_SYSTEM_FW_STATUS_08					8
// #define BIT_SYSTEM_FW_STATUS_09					9
// #define BIT_SYSTEM_FW_STATUS_10					10
// #define BIT_SYSTEM_FW_STATUS_11					11
// #define BIT_SYSTEM_FW_STATUS_12					12
// #define BIT_SYSTEM_FW_STATUS_13					13
// #define BIT_SYSTEM_FW_STATUS_14					14
// #define BIT_SYSTEM_FW_STATUS_15					15
// #define BIT_SYSTEM_FW_STATUS_16					16
// #define BIT_SYSTEM_FW_STATUS_17					17
// #define BIT_SYSTEM_FW_STATUS_18					18
// #define BIT_SYSTEM_FW_STATUS_19					19
// #define BIT_SYSTEM_FW_STATUS_20					20
// #define BIT_SYSTEM_FW_STATUS_21					21
// #define BIT_SYSTEM_FW_STATUS_22					22
// #define BIT_SYSTEM_FW_STATUS_23					23
// #define BIT_SYSTEM_FW_STATUS_24					24
// #define BIT_SYSTEM_FW_STATUS_25					25
// #define BIT_SYSTEM_FW_STATUS_26					26
// #define BIT_SYSTEM_FW_STATUS_27					27
// #define BIT_SYSTEM_FW_STATUS_28					28
// #define BIT_SYSTEM_FW_STATUS_29					29
// #define BIT_SYSTEM_FW_STATUS_30					30
// #define BIT_SYSTEM_FW_STATUS_31					31

#endif //  _BASE_TEC_DRIVER_DEFINES_ASM_INCLUDED_
