/*
 * GPIO.h
 *
 *  Created on: 21.01.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_GPIO_H_
#define CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_GPIO_H_

#include <stdint.h>
#include <string>

namespace BBBResources {

    class GPIO
    {
        public:
            static const std::string DEV_NAME; // = "/dev/mem"

            enum class DIRCETION
            {
                INPUT,
                OUTPUT
            };

            GPIO(DIRCETION _direction, uint32_t _group, uint32_t _pin);
            virtual ~GPIO();

            inline void
            set (void);

            inline void
            clear (void);

            inline void
            write (bool val);

            inline bool
            read (void);

            void
            setDirection (DIRCETION dir);

        private:
            DIRCETION direction;
            uint32_t group;
            uint32_t pin;

            int fp;
            void* baseAddr;

            // bank address information
            static const uint32_t GPIO0_START_ADDR = 0x44E07000;
            static const uint32_t GPIO0_END_ADDR = 0x44E08FFF;
            static const uint32_t GPIO0_SIZE = (GPIO0_END_ADDR - GPIO0_START_ADDR);
            static const uint32_t GPIO1_START_ADDR = 0x4804C000;
            static const uint32_t GPIO1_END_ADDR = 0x4804DFFF;
            static const uint32_t GPIO1_SIZE = (GPIO1_END_ADDR - GPIO1_START_ADDR);
            static const uint32_t GPIO2_START_ADDR = 0x481AC000;
            static const uint32_t GPIO2_END_ADDR = 0x481ADFFF;
            static const uint32_t GPIO2_SIZE = (GPIO2_END_ADDR - GPIO2_START_ADDR);
            static const uint32_t GPIO3_START_ADDR = 0x481AE000;
            static const uint32_t GPIO3_END_ADDR = 0x481AFFFF;
            static const uint32_t GPIO3_SIZE = (GPIO3_END_ADDR - GPIO3_START_ADDR);

            // command offsets
            static const uint32_t GPIO_REVISION = 0x0;
            static const uint32_t GPIO_SYSCONFIG = 0x10;
            static const uint32_t GPIO_EOI = 0x20;
            static const uint32_t GPIO_IRQSTATUS_RAW_0 = 0x24;
            static const uint32_t GPIO_IRQSTATUS_RAW_1 = 0x28;
            static const uint32_t GPIO_IRQSTATUS_0 = 0x2C;
            static const uint32_t GPIO_IRQSTATUS_1 = 0x30;
            static const uint32_t GPIO_IRQSTATUS_SET_0 = 0x34;
            static const uint32_t GPIO_IRQSTATUS_SET_1 = 0x38;
            static const uint32_t GPIO_IRQSTATUS_CLR_0 = 0x3C;
            static const uint32_t GPIO_IRQSTATUS_CLR_1 = 0x40;
            static const uint32_t GPIO_IRQWAKEN_0 = 0x44;
            static const uint32_t GPIO_IRQWAKEN_1 = 0x48;
            static const uint32_t GPIO_SYSSTATUS = 0x114;
            static const uint32_t GPIO_CTRL = 0x130;
            static const uint32_t GPIO_OE = 0x134;
            static const uint32_t GPIO_DATAIN = 0x138;
            static const uint32_t GPIO_DATAOUT = 0x13C;
            static const uint32_t GPIO_LEVELDETECT0 = 0x140;
            static const uint32_t GPIO_LEVELDETECT1 = 0x144;
            static const uint32_t GPIO_RISINGDETECT = 0x148;
            static const uint32_t GPIO_FALLINGDETECT = 0x14C;
            static const uint32_t GPIO_DEBOUNCENABLE = 0x150;
            static const uint32_t GPIO_DEBOUNCINGTIME = 0x154;
            static const uint32_t GPIO_CLEARDATAOUT = 0x190;
            static const uint32_t GPIO_SETDATAOUT = 0x194;
    };

    void
    GPIO::set(void)
    {
        uint32_t *addr;
        addr = (uint32_t *) ((char *) baseAddr + GPIO_SETDATAOUT);
        *addr = 1 << pin;
    }

    void
    GPIO::clear(void)
    {
        uint32_t *addr;
        addr = (uint32_t *) ((char *) baseAddr + GPIO_CLEARDATAOUT);
        *addr = 1 << pin;
    }

    void
    GPIO::write(bool val)
    {
        uint32_t *addr;
        addr = (uint32_t *) ((char *) baseAddr + GPIO_DATAOUT);
        *addr = val << pin;
    }

    bool
    GPIO::read(void)
    {
        uint32_t *addr;
        bool val;
        addr = (uint32_t *) ((char *) baseAddr + GPIO_DATAIN);
        val = *(addr) & (1 << pin);
        return (val);
    }

} /* namespace BBBResources */

#endif /* CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_GPIO_H_ */
