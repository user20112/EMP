/*
 * HardwareCtrl.cpp
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#include "GaAppBaseLib.h"

#include "HardwareCtrl.h"

namespace BaseTecDriver {

    HardwareCtrl::HardwareCtrl(volatile void* ptMemoryBase,
                               std::string _dataBaseNode,
                               std::string _loggerName)
            : dataBaseNode(_dataBaseNode),
              HardwareTriggerBit(        (_dataBaseNode + ".Config.HardwareTriggerBit").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              RequestedLedStatusGr(      (_dataBaseNode + ".Config.reqStateLEDgr").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              RequestedLedStatusRt(      (_dataBaseNode + ".Config.reqStateLEDrt").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              RequestedCtrlUart1(        (_dataBaseNode + ".Config.reqCtrlUart_00").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              RequestedCtrlUart2(        (_dataBaseNode + ".Config.reqCtrlUart_01").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              RequestedCtrlTemperature(  (_dataBaseNode + ".Config.reqStateTempCtrl").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              CurrentLedStatusGr(        (_dataBaseNode + ".Data.actStateLEDgr").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              CurrentLedStatusRt(        (_dataBaseNode + ".Data.actStateLEDrt").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              CurrentCtrlUart1(          (_dataBaseNode + ".Data.actCtrlUart_00").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              CurrentCtrlUart2(          (_dataBaseNode + ".Data.actCtrlUart_01").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING),
              CurrentCtrlTemperature(    (_dataBaseNode + ".Data.actStateTempCtrl").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING)
    {
        mLoggerName = _loggerName;
        el::Loggers::getLogger(mLoggerName);

        ptRawData = (tDataChannel*) ptMemoryBase;
        memset((void*) ptRawData, 0, sizeof(tDataChannel));

        RequestedLedStatusGr = 1;
        RequestedLedStatusRt = 0;

        ptRawData->hwTriggerBitMask = HardwareTriggerBit;
    }

    HardwareCtrl::~HardwareCtrl()
    {
    }

    int32_t
    HardwareCtrl::taskRun(gs_Task taskHandle,
                          const uint32_t* frameNumber) noexcept
    {
        try {
            ptRawData->hwTriggerBitMask = HardwareTriggerBit;

            ptRawData->reqStateLEDgr = RequestedLedStatusGr;
            ptRawData->reqStateLEDrt = RequestedLedStatusRt;
            ptRawData->reqStateUARTCtrl[0].word = RequestedCtrlUart1;
            ptRawData->reqStateUARTCtrl[1].word = RequestedCtrlUart2;
            ptRawData->reqStateTempCtrl.word = RequestedCtrlTemperature;
/*
            CurrentLedStatusGr = (uint8_t)ptRawData->activeStateLEDgr;
            CurrentLedStatusRt = (uint8_t)ptRawData->activeStateLEDrt;
            CurrentCtrlUart1 = (uint8_t)ptRawData->activeStateUARTCtrl[0].word;
            CurrentCtrlUart2 = (uint8_t)ptRawData->activeStateUARTCtrl[1].word;
            CurrentCtrlTemperature = (uint8_t)ptRawData->activeStateTempCtrl.word;
*/
        }
        catch (std::exception &e) {
            CLOG(ERROR, mLoggerName.c_str()) << "error in logic task:\n" << e.what();
        }

        return (0);
    }

} /* namespace BaseTecDriver */
