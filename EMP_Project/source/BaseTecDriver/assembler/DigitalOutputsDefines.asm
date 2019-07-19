#ifndef _DIGITAL_OUTPUTS_DEFINES_ASM_INCLUDED_
#define _DIGITAL_OUTPUTS_DEFINES_ASM_INCLUDED_

// ==========================================================================================
// ==========================================================================================
//    memory offsets
// ==========================================================================================
// ==========================================================================================
#define OFFSET_DIG_OUT_REQ_STATE						0x00	// length: 2 bytes
#define OFFSET_DIG_OUT_ACT_STATE						0x02	// length: 2 bytes
#define OFFSET_DIG_OUT_STD_DIAG							0x04	// length: 2 bytes
#define OFFSET_DIG_OUT_NEXT_RESULT_OFFSET				0x06	// length: 2 bytes
#define OFFSET_DIG_OUT_BUFFER_READ_OFFSET				0x08	// length: 2 bytes
#define OFFSET_DIG_OUT_UNUSED_01						0x0a	// length: 6 bytes
#define OFFSET_DIG_OUT_READ_OFFSET						0x10	// length: 2 bytes
#define OFFSET_DIG_OUT_WRITE_OFFSET						0x12	// length: 2 bytes
#define OFFSET_DIG_OUT_DIAG_BUF_OVERFLOW				0x14	// length: 2 bytes
#define OFFSET_DIG_OUT_UNUSED_02						0x16	// length: 2 bytes
#define OFFSET_DIG_OUT_DEBUG_1							0x18	// length: 4 bytes
#define OFFSET_DIG_OUT_DEBUG_2							0x1c	// length: 4 bytes
#define OFFSET_DIG_OUT_CMD_QUEUE_DATA					0x20	// length: 2*8*2 bytes



#endif //  _DIGITAL_OUTPUTS_DEFINES_ASM_INCLUDED_
