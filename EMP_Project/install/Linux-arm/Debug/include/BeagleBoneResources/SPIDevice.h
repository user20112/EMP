/*
 * SPIDevice.h
 *
 *  Created on: 23.01.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIDEVICE_H_
#define CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIDEVICE_H_

#include "SPIBus.h"
#include "GPIO.h"

namespace BBBResources {

    class SPIDevice
    {
        public:
            enum class CHIP_SELECT_MODE
                            : int {
                    HI_ACTIVE,
                LOW_ACTIVE
            };
            SPIDevice(SPIBus& _bus,
                      GPIO& _chipSelect,
                      CHIP_SELECT_MODE _mode);
            virtual ~SPIDevice();

            inline size_t
            readData(std::vector<uint8_t>& _buffer,
                     size_t _bytesToRead,
                     bool lastBlock = true);

            inline size_t
            writeData(std::vector<uint8_t>& _buffer,
                      bool lastBlock = true);

        protected:
            inline void
            enableDevice();

            inline void
            disableDevice();

        private:
            SPIBus& spiBus;
            GPIO& chipSelectSignal;
            CHIP_SELECT_MODE chipSelectMode;
    };

    inline size_t
    SPIDevice::readData(std::vector<uint8_t>& _buffer,
                        size_t _bytesToRead,
                        bool lastBlock /* = true */)
    {
        size_t readBytes = 0;
        enableDevice();
        readBytes = spiBus.readData(_buffer, _bytesToRead);
        if (lastBlock) {
            disableDevice();
        }
        return (readBytes);
    }

    inline size_t
    SPIDevice::writeData(std::vector<uint8_t>& _buffer,
                         bool lastBlock /* = true */)
    {
        size_t writtenBytes = 0;
        enableDevice();
        writtenBytes = spiBus.writeData(_buffer);
        if (lastBlock) {
            disableDevice();
        }
        return (writtenBytes);
    }

    void
    SPIDevice::enableDevice()
    {
        if (chipSelectMode == CHIP_SELECT_MODE::HI_ACTIVE) {
            chipSelectSignal.set();
        }
        else {
            chipSelectSignal.clear();
        }
    }

    void
    SPIDevice::disableDevice()
    {
        if (chipSelectMode == CHIP_SELECT_MODE::HI_ACTIVE) {
            chipSelectSignal.clear();
        }
        else {
            chipSelectSignal.set();
        }
    }

} /* namespace BBBResources */

#endif /* CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIDEVICE_H_ */
