#ifndef _GPIO_REGISTER_ASM_INCLUDED_
#define _GPIO_REGISTER_ASM_INCLUDED_

// ==========================================================================================
// ==========================================================================================
//    gpio memory address
// ==========================================================================================
// ==========================================================================================
//
//  IMPORTANT NOTE:
//  ===============
// the base address is given with an offset of 0x100
// this must be done to reduce the GPIO-Offsets
// so it is possible to use the command LBBO and SBBO
#define PT_GPIO_BANK_0		      0x44E07000 + 0x100
#define PT_GPIO_BANK_1            0x4804C000 + 0x100
#define PT_GPIO_BANK_2            0x481AC000 + 0x100
#define PT_GPIO_BANK_3            0x481AE000 + 0x100

// ==========================================================================================
// ==========================================================================================
//    configuration register
// ==========================================================================================
// ==========================================================================================
//  this register are not used are unavilable by base adress PT_GPIO_BANK_X macros !
#define GPIO_REVISION             0x00
#define GPIO_SYSCONFIG            0x10
#define GPIO_EOI                  0x20
#define GPIO_IRQSTATUS_RAW_0      0x24
#define GPIO_IRQSTATUS_RAW_1      0x28
#define GPIO_IRQSTATUS_0          0x2C
#define GPIO_IRQSTATUS_1          0x30
#define GPIO_IRQSTATUS_SET_0      0x34
#define GPIO_IRQSTATUS_SET_1      0x38
#define GPIO_IRQSTATUS_CLR_0      0x3C
#define GPIO_IRQSTATUS_CLR_1      0x40
#define GPIO_IRQWAKEN_0           0x44
#define GPIO_IRQWAKEN_1           0x48

// ==========================================================================================
//    important node: to use following offset, the register base address has to increase by 0x100 !!!
//    this is already done in the base definition
// ==========================================================================================
#define GPIO_SYSSTATUS            0x14
#define GPIO_CTRL                 0x30
#define GPIO_OE                   0x34
#define GPIO_DATAIN               0x38
#define GPIO_DATAOUT              0x3C
#define GPIO_LEVELDETECT0         0x40
#define GPIO_LEVELDETECT1         0x44
#define GPIO_RISINGDETECT         0x48
#define GPIO_FALLINGDETECT        0x4C
#define GPIO_DEBOUNCENABLE        0x50
#define GPIO_DEBOUNCINGTIME       0x54
#define GPIO_CLEARDATAOUT         0x90
#define GPIO_SETDATAOUT           0x94

#endif // _GPIO_REGISTER_ASM_INCLUDED_
