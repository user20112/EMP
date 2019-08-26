/**
 * @file PruInterface.cpp
 * @short contain definition of class \c PruInterface
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */

#include <istream>

#include "boost/format.hpp"

#include "exceptions/ExceptionsMacros.h"
#include "log/logger.h"

#include "prussdrv.h"

#include "pru/PruDriver.h"
#include "pru/PruInterface.h"

namespace BeagleBoneResources {

    PruInterface::PruInterface(uint32_t _pruNumber)
    {
        int retVal = 0;
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_pruNumber, 0, PruDriver::PRU_COUNT - 1);

        mLoggerName = "PRU_";
        mLoggerName += std::to_string(_pruNumber + 1);

        el::Loggers::getLogger(mLoggerName);
        mPruActive = false;

        PruDriver::getInstance().usePru(_pruNumber);
        pruNumber = _pruNumber;
        CLOG(INFO, mLoggerName.c_str())<< "using PRU " << pruNumber;

        CLOG(TRACE, mLoggerName.c_str())<< "call prussdrv_map_prumem for local memory";
        switch (_pruNumber) {
        case 0:
            retVal = prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, (void**) (&ptDataMemory));
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, (void**)(&ptDataMemory))\" failed (retVal: " << retVal << ").";
            }
            break;
            case 1:
            retVal = prussdrv_map_prumem (PRUSS0_PRU1_DATARAM, (void**)(&ptDataMemory));
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_map_prumem(PRUSS0_PRU1_DATARAM, (void**)(&ptDataMemory))\" failed (retVal: " << retVal << ").";
            }
            break;

            default:
            THROW_LOGIC_FAULT() << "unable to map local memory for PRU " << _pruNumber;
            break;
        }    // switch (_pruNumber)
        CLOG(TRACE, "PruDriver")<< "address for local memory: " << boost::format("0x%08x") % (uint32_t)ptDataMemory;
    }

    PruInterface::~PruInterface()
    {
        if (mPruActive) {
            CLOG(INFO, mLoggerName.c_str())<< "reset pru";
            /*
             * ATTENTION:
             * the following call causes a system crash. An alternative code will be fine!
             *
             * int retVal = 0;
             * retVal = prussdrv_pru_reset(pruNumber);
             * if (retVal != 0) {
             *   CLOG(ERROR, mLoggerName.c_str())<< "reset pru failed: (retVal:" << retVal << ")";
             * }
             *
             */
        }

        CLOG(INFO, mLoggerName.c_str())<< "release pru";
        PruDriver::getInstance().setPruState(pruNumber, PruDriver::PRU_STATE::UNUSED);
    }

    void
    PruInterface::loadProgram(std::vector<uint32_t>& _code)
    {
        int retVal = 0;
        CLOG(INFO, mLoggerName.c_str())<< "download PRU program (" << _code.size() << " Commands) ...";
        retVal = prussdrv_exec_code(pruNumber, _code.data(), (int) (_code.size() * 4));
        if (retVal != 0) {
            THROW_LOGIC_FAULT()<< "call \"prussdrv_exec_code(_pruNumber, _code.data, _code.size * 4)\" failed (retVal: " << retVal << "): bytes should be written: ." << _code.size() * 4;
        }

        CLOG(INFO, mLoggerName.c_str())<< "download PRU program (" << _code.size() << " Commands) ... done!";
        PruDriver::getInstance().setPruState(pruNumber, PruDriver::PRU_STATE::OPERATING);
        mPruActive = true;
    }

    void
    PruInterface::loadProgram(std::string _filePath)
    {
        std::vector<uint32_t> code;
        uint32_t hexdump;
        uint32_t cmdCount = 0;
        CLOG(INFO, mLoggerName.c_str())<< "read pru program " << _filePath;

        std::ifstream pruProg(_filePath.c_str());
        while (pruProg) {
            hexdump = 0xffffffff;
            pruProg >> std::hex >> hexdump;
            if (hexdump == 0xffffffff)
                break;
            cmdCount++;
            code.push_back(hexdump);
        }
        CLOG(DEBUG, mLoggerName.c_str())<< "get " << cmdCount << " commands";
        std::cout << "read " << std::dec << cmdCount << " commands from file " << _filePath << "." << std::endl;

        loadProgram(code);
    }

    int32_t
    PruInterface::compileProgram(std::string _path,
                                 std::string _fileBase)
    {
        int retVal = 0;
        std::string pasmCmd = "pasm -V3m ../assembler/BaseTecDriver.asm ../assembler/BaseTecDriver";
        CLOG(INFO, mLoggerName.c_str())<< "create PRU code with pasm ...";

        CLOG(TRACE, mLoggerName.c_str())<< "  call: " << pasmCmd;
        retVal = system(pasmCmd.c_str());
        CLOG(DEBUG, mLoggerName.c_str())<< "PRU compiler result: " << retVal;

        return (retVal);
    }

    volatile uint8_t*
    PruInterface::getLocalMemory()
    {
        return (ptDataMemory);
    }

    volatile uint8_t*
    PruInterface::getSharedMemory()
    {
        return (PruDriver::getInstance().getSharedMemory());
    }

} /* namespace BeagleBoneResources */
