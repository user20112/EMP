/*
 * TemperatureInputs.cpp
 *
 *  Created on: 06.03.2015
 *      Author: s.hegemann
 */

#include <iomanip>

#include "TemperatureInputs.h"

namespace BaseTecDriver {

    TemperatureInputs::TemperatureInputs(volatile void* ptMemoryBase,
                                         std::string _dataBaseNode)
            : dataBaseNode(_dataBaseNode)
    {
        ptRawData = (tPruData*) ptMemoryBase;
        memset((void*) ptRawData, 0, sizeof(tPruData));

    }

    TemperatureInputs::~TemperatureInputs()
    {
        // TODO Auto-generated destructor stub
    }

    int32_t
    TemperatureInputs::taskRun(gs_Task taskHandle,
                               const uint32_t* frameNumber) noexcept
    {

        switch (ptRawData->commandState) {
        case 0:
            // TODO: prepare next command
            ptRawData->commandState = 1;
            break;

        case 1: // wait for sending command
        case 2: // command will be send
            break;

        case 3:
            // std::cout << "temperature inputs: command done" << std::endl;
            ptRawData->commandState = 4;
            break;

        case 4:
            ptRawData->commandState = 0;
            // TODO: read command result
            break;


        default:
            std::cerr << "temperature inputs: invalid command state " << (uint16_t)ptRawData->commandState << std::endl;
            ptRawData->commandState = 0;
            break;

        } // switch (ptRawData->commandState)

        return (0);
    }


    void
    TemperatureInputs::printInfo()
    {
        std::cout << "\n Temperature Input Register:"
                  << "\n=============================="
                  << "\n"
                  << "\n   PRU code status:        0x" << std::hex << std::setw(2) << std::setfill('0') << (uint16_t)ptRawData->hwInfo.word
                  << "\n   PRU diag counter:       " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->commandState
                  << "\n   PRU Bytes to Write:     " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->writeByteCnt
                  << "\n   PRU read Bytes:         " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->readByteCnt
                  << "\n"
                  << "\n" << std::endl;
    }

} /* namespace BaseTecDriver */
