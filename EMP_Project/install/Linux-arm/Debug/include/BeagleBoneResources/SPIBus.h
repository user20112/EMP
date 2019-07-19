/*
 * SPIBus.h
 *
 *  Created on: 21.01.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIBUS_H_
#define CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIBUS_H_

#include <string>
#include <vector>

#include <stdlib.h>
#include <unistd.h>

#include "exceptions/ArgumentFaultException.h"
#include "exceptions/SystemCallException.h"
#include "exceptions/LogicFaultException.h"

#include "./exceptions/ExceptionsMacros.h"

namespace BBBResources {

    class SPIBus
    {
        public:
            static const uint8_t SPI0 = 0;
            static const uint8_t SPI1 = 1;
            static const std::string SPI0_DRV;    // = "/dev/spidev1.0"
            static const std::string SPI1_DRV;    // = "/dev/spidev2.0"

            enum class CLOCK_MODE
                : int {
                LOW = 0,
                HI = 2
            };

            enum class SAMPLE_MODE
                : int {
                RISINGEDGE = 0,
                FALLINGEDGE = 1
            };

            enum class JUSTIFICATION
                : int {
                LSB_FIRST = 0,
                MSB_FIRST = 1
            };

            SPIBus(uint8_t busNumber);
            SPIBus(uint8_t busNumber,
                   int clkSpeed,
                   CLOCK_MODE clkMode,
                   SAMPLE_MODE sampleMode,
                   JUSTIFICATION justification,
                   int length);
            virtual ~SPIBus();

            void setBusSettings(int clkSpeed,
                                CLOCK_MODE clkMode,
                                SAMPLE_MODE sampleMode,
                                JUSTIFICATION justification,
                                int length);

            inline size_t
            readData(std::vector<uint8_t>& _buffer, size_t _bytesToRead);

            inline size_t
            writeData(std::vector<uint8_t>& _buffer);

        private:
            void init(uint8_t busNumber);

            int fp;
            int currentClock;
            int currentMode;
            JUSTIFICATION currentJustification;
            int currentLength;

    };


    inline size_t
    SPIBus::readData(std::vector<uint8_t>& _buffer, size_t _bytesToRead)
    {
        size_t readBytes = 0;

        if (_buffer.size() < _bytesToRead) {
            _buffer.reserve(_bytesToRead);
        }

        readBytes = read(fp, _buffer.data(), _bytesToRead);
        if (readBytes < 0) {
            THROW_SYSTEM_FAULT() << "unable to read " << _bytesToRead << " from device " << fp << ".";
        }
        else if (readBytes != _bytesToRead) {
            // TODO: braucht es diese Überwachung? Oder Bestandteil des User-Codes.
            THROW_LOGIC_FAULT() << "unable to read complete information (bytes to read: " << _bytesToRead << "; read bytes: " << readBytes << ").";
        }

        return (readBytes);
    }

    inline size_t
    SPIBus::writeData(std::vector<uint8_t>& _buffer)
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(_buffer.size(), 0);

        size_t bytesToWrite = _buffer.size();
        size_t writtenBytes = 0;

        writtenBytes = write(fp, _buffer.data(), bytesToWrite);
        if (writtenBytes < 0) {
            THROW_SYSTEM_FAULT() << "unable to write " << bytesToWrite << " to device " << fp << ".";
        }
        else if (writtenBytes != bytesToWrite) {
            // TODO: braucht es diese Überwachung? Oder Bestandteil des User-Codes.
            THROW_LOGIC_FAULT() << "unable to write complete information (bytes to write: " << bytesToWrite << "; written bytes: " << writtenBytes << ").";
        }

        return (writtenBytes);
    }

} /* namespace BBBResources */


// disable exception macros for following code
#define UNLOAD_MACROS
#include "./exceptions/ExceptionsMacros.h"

#endif /* CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_SPIBUS_H_ */
