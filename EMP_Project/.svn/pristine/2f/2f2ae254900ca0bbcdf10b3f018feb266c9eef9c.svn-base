/*
 * AnalogInputs.h
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_ANALOGINPUTS_H_
#define CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_ANALOGINPUTS_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "GaGCppAPI.h"

namespace BaseTecDriver {

    class AnalogInputs
    {
        public:
            static const uint32_t dataBufferSize = 5888;

            struct tAnalogData
            {
                    uint32_t inputState;
                    uint16_t sampleAverage;
                    uint16_t openDelay;
                    uint16_t sampleDelay;
                    uint16_t diagCnt;
                    uint16_t writePos;
                    uint16_t readPos;
                    uint16_t dataBuffer[dataBufferSize];
            };

            struct tChanelData
            {
                    float lastValue;
                    int32_t sampleCount;
                    float sumValues;
                    float sampleRate;
            };

        public:
            AnalogInputs(volatile void* ptMemoryBase,
                         std::string _dataBaseNode,
                         std::string _loggerName,
                         uint32_t _taskCycleTime);
            virtual ~AnalogInputs();

            int32_t
            taskRun() noexcept;

            void
            printRegisterInfo ();

        private:
            std::string dataBaseNode;
            volatile tAnalogData*  ptRawData;
            tChanelData chn[7];
            std::string mLoggerName;

            uint32_t taskCycleTime;

            uint16_t    lastReadPos;
            uint16_t    lastWritePos;
            uint32_t    lastChannelId;

            // section Data
            std::vector<GaGCppAPI::TypedPV<uint16_t>*> rawVal;
            std::vector<GaGCppAPI::TypedPV<float>*> normVal;
            std::vector<GaGCppAPI::TypedPV<float>*> Val;
    };

} /* namespace BaseTecDriver */

#endif /* CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_ANALOGINPUTS_H_ */
