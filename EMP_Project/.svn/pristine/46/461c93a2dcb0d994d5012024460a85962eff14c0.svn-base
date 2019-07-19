/**
 * @file PruDriver.cpp
 * @short contain definition of class \c PruDriver
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */

#include "boost/format.hpp"

#include "prussdrv.h"
#include "pruss_intc_mapping.h"

#include "pru/PruDriver.h"
#include "exceptions/ExceptionsMacros.h"
#include "log/logger.h"

namespace BeagleBoneResources {

    const tpruss_intc_initdata prus_int_SPI = PRUSS_INTC_INITDATA;

    // **************************************************************************************************
    // ** PruDriver()
    // **************************************************************************************************
    PruDriver::PruDriver()
    {
        int retVal;
        el::Loggers::getLogger("PruDriver");

        try {
            lock.lock();

            CLOG(INFO, "PruDriver")<< "activate system PRU modules";
            // HardWareDriver::activateModule("BB-BONE-PRU-01");
            // HardWareDriver::activateModule("BB-BONE-PRU-02");

            CLOG(DEBUG, "PruDriver")<< "open PRU driver";
            CLOG(TRACE, "PruDriver")<< "call prussdrv_init";
            retVal = prussdrv_init();
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_init()\" failed (retVal: " << retVal << ").";
            }

            CLOG(DEBUG, "PruDriver")<< "start initialization for PRU units";
            CLOG(TRACE, "PruDriver")<< "call prussdrv_open";
            retVal = prussdrv_open(PRU_EVTOUT_0);
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_open(PRU_EVTOUT_0)\" failed (retVal: " << retVal << ").";
            }

            CLOG(TRACE, "PruDriver")<< "call prussdrv_pruintc_init";
            retVal = prussdrv_pruintc_init(&prus_int_SPI);
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_pruintc_init(&prus_int_SPI)\" failed (retVal: " << retVal << ").";
            }

            CLOG(TRACE, "PruDriver")<< "set PRU state";
            for (uint8_t i = 0; i < PRU_COUNT; i++) {
                pruState[i] = PRU_STATE::UNUSED;
            }

            CLOG(TRACE, "PruDriver")<< "call prussdrv_map_prumem for sharedMemory";
            ptSharedMemory = nullptr;
            retVal = prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void**) (&ptSharedMemory));
            if (retVal != 0) {
                THROW_LOGIC_FAULT()<< "call \"prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, (void**)(&ptSharedMemory))\" failed (retVal: " << retVal << ").";
            }
            CLOG(TRACE, "PruDriver")<< "address for shared memory: " << boost::format("0x%08x") % (uint32_t)ptSharedMemory;
            CLOG(TRACE, "PruDriver")<< "initialization done successfully.";
            lock.unlock();
        }
        catch (...) {
            lock.unlock();
            throw;
        }
    }

    // **************************************************************************************************
    // ** ~PruDriver()
    // **************************************************************************************************
    PruDriver::~PruDriver()
    {
        int retVal;

        CLOG(DEBUG, "PruDriver")<< "close PRU driver";
        CLOG(TRACE, "PruDriver")<< "call prussdrv_exit";
        retVal = prussdrv_exit();
        if (retVal != 0) {
            THROW_LOGIC_FAULT()<< "call \"prussdrv_exit()\" failed (retVal: " << retVal << ").";
        }
    }

    // **************************************************************************************************
    // ** usePru
    // **************************************************************************************************
    void
    PruDriver::usePru(uint8_t _pruNumber)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_pruNumber, 0, PRU_COUNT - 1);

        lock.lock();
        if (pruState[_pruNumber] != PRU_STATE::UNUSED) {
            lock.unlock();
            THROW_LOGIC_FAULT()<< "pru " << _pruNumber << " is already in used. Permission denied.";
        }
        pruState[_pruNumber] = PRU_STATE::INITIALIZING;
        CLOG(DEBUG, "PruDriver")<< "PRU " << _pruNumber << " now in state INITIALIZING";
        lock.unlock();
    }

    // **************************************************************************************************
    // ** setPruState
    // **************************************************************************************************
    void
    PruDriver::setPruState(uint8_t _pruNumber, PRU_STATE _state)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_pruNumber, 0, PRU_COUNT - 1);
        lock.lock();
        if (pruState[_pruNumber] == PRU_STATE::UNUSED) {
            lock.unlock();
            THROW_LOGIC_FAULT()<< "pru " << _pruNumber << " is not used. Unable to change state to " << (uint32_t)_state;
        }
        pruState[_pruNumber] = _state;
        switch (_state) {
        case PRU_STATE::INITIALIZING:
            CLOG(DEBUG, "PruDriver")<< "PRU " << _pruNumber << " now in state INITIALIZING";
            break;
        case PRU_STATE::OPERATING:
            CLOG(DEBUG, "PruDriver")<< "PRU " << _pruNumber << " now in state OPERATING";
            break;
        case PRU_STATE::UNUSED:
            CLOG(DEBUG, "PruDriver")<< "PRU " << _pruNumber << " now in state UNUSED";
            break;
        }
        lock.unlock();
    }

    // **************************************************************************************************
    // ** releasePru
    // **************************************************************************************************
    void
    PruDriver::releasePru(uint8_t _pruNumber)
    {
        setPruState(_pruNumber, PRU_STATE::UNUSED);
    }

    // **************************************************************************************************
    // ** GetInstance
    // **************************************************************************************************
    PruDriver&
    PruDriver::getInstance()
    {
        static PruDriver instance;
        return (instance);
    }

    volatile uint8_t*
    PruDriver::getSharedMemory()
    {
        return (ptSharedMemory);
    }

} /* namespace BeagleBoneResources */
