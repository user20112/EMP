#ifndef _GPIO_MACROS_ASM_INCLUDED_
#define _GPIO_MACROS_ASM_INCLUDED_

#include "GpioRegister.asm"

// set_gpio (PT_TO_BANK, BIT)
.macro set_gpio
.mparam pt_gpio_bank, bit
.mparam temp_register = var_temp_1
	MOV  temp_register, 1 << bit
	SBBO temp_register, pt_gpio_bank, GPIO_SETDATAOUT, 4
.endm

// clr_gpio (PT_TO_BANK, BIT)
.macro clr_gpio
.mparam pt_gpio_bank, bit
.mparam temp_register = var_temp_1
	MOV  temp_register, 1 << bit
	SBBO temp_register, pt_gpio_bank, GPIO_CLEARDATAOUT, 4
.endm

// gpio_as_input (PT_TO_BANK, BIT)
.macro gpio_as_input
.mparam pt_gpio_bank, bit
.mparam temp_register = var_temp_1
	LBBO temp_register, pt_gpio_bank, GPIO_OE, 4
	SET  temp_register, bit
	SBBO temp_register, pt_gpio_bank, GPIO_OE, 4
.endm

// gpio_as_output (PT_TO_BANK, BIT)
.macro gpio_as_output
.mparam pt_gpio_bank, bit
.mparam temp_register = var_temp_1
	LBBO temp_register, pt_gpio_bank, GPIO_OE, 4
	CLR  temp_register, bit
	SBBO temp_register, pt_gpio_bank, GPIO_OE, 4
.endm

.macro copy_bit
.mparam desWord, desBit
.mparam srcWord, srcBit
	QBBS COPY_BIT_SET srcWord, srcBit
	CLR desWord, desBit
	JMP COPY_BIT_CLR

	COPY_BIT_SET:
	SET desWord, desBit

	COPY_BIT_CLR:
.endm

#endif // _GPIO_MACROS_ASM_INCLUDED_
