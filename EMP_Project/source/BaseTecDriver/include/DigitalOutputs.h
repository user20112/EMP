/*
 * DigitalOutputs.h
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#ifndef SOURCE_BASETECDRIVER_INCLUDE_DIGITALOUTPUTS_H_
#define SOURCE_BASETECDRIVER_INCLUDE_DIGITALOUTPUTS_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "GaGCppAPI.h"

namespace BaseTecDriver {

    class DigitalOutputs
    {
        public:

            struct tDataChannel {
                uint16_t reqState;
                uint16_t curState;
                uint16_t standardDiagnosticInfo;
                uint16_t nextResultOffset;
                uint16_t lastBufferRead;
                uint8_t _reserved01[6];

                uint16_t readOffset;
                uint16_t writeOffset;
                uint16_t diagOverflowCounter;
                uint8_t _reserved02[2];
                uint32_t debug[2];

                struct {
                        uint16_t cmd;
                        uint16_t response;
                } cmdFifo[8];

            };

        public:
            DigitalOutputs(volatile void* ptMemoryBase,
                           std::string _dataBaseNode,
                           std::string _loggerName);
            virtual ~DigitalOutputs();

            int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

            void
            getStatus ();

            uint16_t
            sendCommand (uint16_t cmdvalue);

            bool
            isCommandDone (uint16_t index);

            uint16_t
            getCommandResult (uint16_t index);

            void
            resetHardware();

        private:
            std::string dataBaseNode;
            volatile tDataChannel* ptRawData;
            std::string mLoggerName;

            std::vector<GaGCppAPI::TypedPV<uint8_t>*> reqState;
            std::vector<GaGCppAPI::TypedPV<uint8_t>*> curState;

            GaGCppAPI::TypedPV<uint16_t> standardDiag;

            bool firstRunDone;
            uint16_t requestCommandIndex;
    };

} /* namespace BaseTecDriver */

#endif /* SOURCE_BASETECDRIVER_INCLUDE_DIGITALOUTPUTS_H_ */
