/*
 * TemperatureInputs.h
 *
 *  Created on: 06.03.2015
 *      Author: s.hegemann
 */

#ifndef SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_
#define SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "GaGCppAPI.h"

namespace BaseTecDriver {

    class TemperatureInputs
    {
        public:
            struct tPruData
            {
                union {
                        struct {
                                uint8_t rdy             : 1;
                                uint8_t __bit01         : 1;
                                uint8_t __bit02         : 1;
                                uint8_t __bit03         : 1;
                                uint8_t __bit04         : 1;
                                uint8_t __bit05         : 1;
                                uint8_t __bit06         : 1;
                                uint8_t __bit07         : 1;
                        } bit;
                        uint8_t word;
                } hwInfo;

                uint8_t commandState;
                uint8_t writeByteCnt;
                uint8_t readByteCnt;
                uint8_t _unused[12];
                uint8_t writeBuffer[32];
                uint8_t readBuffer[32];
            };

        public:
            TemperatureInputs(volatile void* ptMemoryBase,
                              std::string _dataBaseNode);

            virtual ~TemperatureInputs();

            int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

            void
            printInfo();

        private:
            std::string dataBaseNode;
            volatile tPruData*  ptRawData;

    };


} /* namespace BaseTecDriver */

#endif /* SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_ */
