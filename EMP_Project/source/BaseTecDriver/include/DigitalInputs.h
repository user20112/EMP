/*
 * DigitalInputs.h
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_DIGITALINPUTS_H_
#define CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_DIGITALINPUTS_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "GaGCppAPI.h"

namespace BaseTecDriver {

    class DigitalInputs
    {
        public:
            enum class eCountMode
                : uint8_t {
                    DISABLED,
                ON_EDGE_HIGH,
                ON_EDGE_LOW,
                ON_BOTH_EDGES
            };

            struct tDataChannel
            {
                    uint8_t activeState[9];
                    uint8_t _reserved01[7];
                    eCountMode countMode[9];
                    uint8_t _reserved02[7];

                    uint32_t edgeCounter[9];
                    uint8_t _reserved03[12];
            };

        public:
            DigitalInputs(volatile void* ptMemoryBase,
                          std::string _dataBaseNode,
                          std::string _loggerName);

            virtual ~DigitalInputs();

            int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

        private:
            std::string dataBaseNode;
            volatile tDataChannel* ptRawData;
            std::string mLoggerName;

            // section Config
            std::vector<GaGCppAPI::TypedPV<uint8_t>*> countMode;

            // section Data
            std::vector<GaGCppAPI::TypedPV<uint8_t>*> actState;
            std::vector<GaGCppAPI::TypedPV<uint32_t>*> rawCounter;
            std::vector<GaGCppAPI::TypedPV<float>*> edgeCounter;
            std::vector<float> counterScaleFactor;
    };

} /* namespace BaseTecDriver */

#endif /* CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_DIGITALINPUTS_H_ */
