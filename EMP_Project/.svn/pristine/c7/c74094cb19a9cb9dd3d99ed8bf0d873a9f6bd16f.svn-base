#ifndef _ANALOG_INPUTS_DEFINES_ASM_INCLUDED_
#define _ANALOG_INPUTS_DEFINES_ASM_INCLUDED_

// ==========================================================================================
// ==========================================================================================
//    memory offsets
// ==========================================================================================
// ==========================================================================================
#define OFFSET_ADC_DATA_STATE							0x00	// length: 4 bytes
#define OFFSET_ADC_DATA_SAMPLE_AVERAGE					0x04	// length: 2 bytes
#define OFFSET_ADC_DATA_OPEN_DELAY						0x06	// length: 2 bytes
#define OFFSET_ADC_DATA_SAMPLE_DELAY					0x08	// length: 2 bytes
#define OFFSET_ADC_DATA_READ_VAL_CNT					0x0a	// length: 2 bytes
#define OFFSET_ADC_DATA_WRITE_POS						0x0c	// length: 2 bytes
#define OFFSET_ADC_DATA_READ_POS						0x0e	// length: 2 bytes
#define OFFSET_ADC_DATA_DATA_BUFFER						0x10	// length: 5888*2 bytes

#define ADC_DATA_BUFFER_SIZE							5888

// ==========================================================================================
//      Register Base address
// ==========================================================================================
#define PT_ADC_REGISTER_BASE_ADDR						0x44E0D000
#define PT_ADC_FIFO_DATA_1								0x44E0D100
#define PT_ADC_FIFO_DATA_2								0x44E0D200

// ==========================================================================================
//      Register Offsets
// ==========================================================================================
#define OFFSET_ADC_REGISTER_REVISION                    0x0
#define OFFSET_ADC_REGISTER_SYSCONFIG                   0x10
#define OFFSET_ADC_REGISTER_IRQSTATUS_RAW               0x24
#define OFFSET_ADC_REGISTER_IRQSTATUS                   0x28
#define OFFSET_ADC_REGISTER_IRQENABLE_SET               0x2C
#define OFFSET_ADC_REGISTER_IRQENABLE_CLR               0x30
#define OFFSET_ADC_REGISTER_IRQWAKEUP                   0x34
#define OFFSET_ADC_REGISTER_DMAENABLE_SET               0x38
#define OFFSET_ADC_REGISTER_DMAENABLE_CLR               0x3C
#define OFFSET_ADC_REGISTER_CTRL                        0x40
#define OFFSET_ADC_REGISTER_ADCSTAT                     0x44
#define OFFSET_ADC_REGISTER_ADCRANGE                    0x48
#define OFFSET_ADC_REGISTER_ADC_CLKDIV                  0x4C
#define OFFSET_ADC_REGISTER_ADC_MISC                    0x50
#define OFFSET_ADC_REGISTER_STEPENABLE                  0x54
#define OFFSET_ADC_REGISTER_IDLECONFIG                  0x58
#define OFFSET_ADC_REGISTER_TS_CHARGE_STEPCONFIG        0x5C
#define OFFSET_ADC_REGISTER_TS_CHARGE_DELAY             0x60
#define OFFSET_ADC_REGISTER_STEPCONFIG1                 0x64
#define OFFSET_ADC_REGISTER_STEPDELAY1                  0x68
#define OFFSET_ADC_REGISTER_STEPCONFIG2                 0x6C
#define OFFSET_ADC_REGISTER_STEPDELAY2                  0x70
#define OFFSET_ADC_REGISTER_STEPCONFIG3                 0x74
#define OFFSET_ADC_REGISTER_STEPDELAY3                  0x78
#define OFFSET_ADC_REGISTER_STEPCONFIG4                 0x7C
#define OFFSET_ADC_REGISTER_STEPDELAY4                  0x80
#define OFFSET_ADC_REGISTER_STEPCONFIG5                 0x84
#define OFFSET_ADC_REGISTER_STEPDELAY5                  0x88
#define OFFSET_ADC_REGISTER_STEPCONFIG6                 0x8C
#define OFFSET_ADC_REGISTER_STEPDELAY6                  0x90
#define OFFSET_ADC_REGISTER_STEPCONFIG7                 0x94
#define OFFSET_ADC_REGISTER_STEPDELAY7                  0x98
#define OFFSET_ADC_REGISTER_STEPCONFIG8                 0x9C
#define OFFSET_ADC_REGISTER_STEPDELAY8                  0xA0
#define OFFSET_ADC_REGISTER_STEPCONFIG9                 0xA4
#define OFFSET_ADC_REGISTER_STEPDELAY9                  0xA8
#define OFFSET_ADC_REGISTER_STEPCONFIG10                0xAC
#define OFFSET_ADC_REGISTER_STEPDELAY10                 0xB0
#define OFFSET_ADC_REGISTER_STEPCONFIG11                0xB4
#define OFFSET_ADC_REGISTER_STEPDELAY11                 0xB8
#define OFFSET_ADC_REGISTER_STEPCONFIG12                0xBC
#define OFFSET_ADC_REGISTER_STEPDELAY12                 0xC0
#define OFFSET_ADC_REGISTER_STEPCONFIG13                0xC4
#define OFFSET_ADC_REGISTER_STEPDELAY13                 0xC8
#define OFFSET_ADC_REGISTER_STEPCONFIG14                0xCC
#define OFFSET_ADC_REGISTER_STEPDELAY14                 0xD0
#define OFFSET_ADC_REGISTER_STEPCONFIG15                0xD4
#define OFFSET_ADC_REGISTER_STEPDELAY15                 0xD8
#define OFFSET_ADC_REGISTER_STEPCONFIG16                0xDC
#define OFFSET_ADC_REGISTER_STEPDELAY16                 0xE0
#define OFFSET_ADC_REGISTER_FIFO0COUNT                  0xE4
#define OFFSET_ADC_REGISTER_FIFO0THRESHOLD              0xE8
#define OFFSET_ADC_REGISTER_DMA0REQ                     0xEC
#define OFFSET_ADC_REGISTER_FIFO1COUNT                  0xF0
#define OFFSET_ADC_REGISTER_FIFO1THRESHOLD              0xF4
#define OFFSET_ADC_REGISTER_DMA1REQ                     0xF8
#define OFFSET_ADC_REGISTER_FIFO0DATA                   0x100		// cannot be used by commands SBBO or LBBO as Offset. Use base address PT_ADC_FIFO_DATA_1
#define OFFSET_ADC_REGISTER_FIFO1DATA                   0x200		// cannot be used by commands SBBO or LBBO as Offset. Use base address PT_ADC_FIFO_DATA_2


// ==========================================================================================
//      required config register
// ==========================================================================================
#define PT_ADC_REGISTER_WAKEUP_ADDR   					0x44E004BC

#endif //  _ANALOG_INPUTS_DEFINES_ASM_INCLUDED_
