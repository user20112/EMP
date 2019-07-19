/*
 * DigitalOutputs.cpp
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#include <iomanip>
#include <unistd.h>

#include "DigitalOutputs.h"
#include "GaAppBaseLib.h"

namespace BaseTecDriver {

  DigitalOutputs::DigitalOutputs(volatile void* ptMemoryBase,
      std::string _dataBaseNode,
      std::string _loggerName)
  : dataBaseNode(_dataBaseNode),
    standardDiag((dataBaseNode + ".Debug.StandartDiagnostic").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING)
  {
    mLoggerName = _loggerName;
    el::Loggers::getLogger(mLoggerName);

    ptRawData = (tDataChannel*) ptMemoryBase;
    memset((void*) ptRawData, 0, sizeof(tDataChannel));

    firstRunDone = false;
    requestCommandIndex = 99;

    for (int i = 0; i < 8; i++) {
      std::string index = std::to_string(i);

      GaGCppAPI::TypedPV<uint8_t>* reqChannelState = new GaGCppAPI::TypedPV<uint8_t>((dataBaseNode + ".Output_0" + index + ".reqState").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      reqState.push_back(reqChannelState);

      GaGCppAPI::TypedPV<uint8_t>* curChannelState = new GaGCppAPI::TypedPV<uint8_t>((dataBaseNode + ".Output_0" + index + ".curState").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      curState.push_back(curChannelState);
    }

  }

  DigitalOutputs::~DigitalOutputs()
  {
    for (auto elm = reqState.begin(); elm != reqState.end(); elm++) {
      delete (*elm);
    }
    reqState.clear();
  }

  int32_t
  DigitalOutputs::taskRun(gs_Task taskHandle,
      const uint32_t* frameNumber) noexcept
      {
    uint16_t stateInfo = 0;
    if (!firstRunDone) {
      resetHardware();
      firstRunDone = true;
    }
    else {
      if (requestCommandIndex < 8) {
        if (!isCommandDone(requestCommandIndex)) {
          CLOG(WARNING, mLoggerName.c_str()) << "digital outputs: no current output state available";
        }
        else {
          stateInfo = getCommandResult(requestCommandIndex);
        }
      }
      requestCommandIndex = sendCommand(0x0000);
    }


    // clear all outputs
    uint16_t diagInfo = ptRawData->standardDiagnosticInfo;
    uint16_t reqOutputState = 0x8080;

    // ---------------------------------------
    // STATUS DRIVER 1

    // check output state
    for (int i = 0; i < 4; i++)
    {
      if (reqState.at(i)->get() == 1)
        reqOutputState |= (1 << i);

      if (~diagInfo & 0x0010)                               // check if bts54220 is in standby (STB bit set)
        curState.at(i)->put((stateInfo & (1 << i))?1:0);    // copy state from output register
      else
        curState.at(i)->put(0);                             // in standby mode, output is off
    }

    // check if driver is in limp home mode (happens when monoflop is not triggered any more)
    if(diagInfo & DRIVER1_DIAG_LIMPHOME)
    {
      driverInStandBy[0] = false;           // limp home includes standby! but don't initiate reset yet here.

      if(driverInLimpHome[0] == false)
      {
        driverInLimpHome[0] = true;
        CLOG(WARNING, mLoggerName.c_str()) << "output driver #1 now in limp home mode";
      }
    }
    // check if driver is in standby mode (will happen after limp home mode)
    else if(diagInfo & DRIVER1_DIAG_STANDBY)
    {
      driverInLimpHome[0] = false;

      if(driverInStandBy[0] == false)
      {
        driverInStandBy[0] = true;
        CLOG(WARNING, mLoggerName.c_str()) << "output driver #1 now in standby mode";
      }
    }
    else
    {
      driverInLimpHome[0] = false;
      driverInStandBy[0] = false;
    }

    // ---------------------------------------
    // STATUS DRIVER 2

    // check state
    for (int i = 4; i < 8; i++)
    {
      if (reqState.at(i)->get() == 1)
        reqOutputState |= (1 << (i + 4));

      if (~diagInfo & 0x1000)                               // check if bts54220 is in standby (STB bit set)
        curState.at(i)->put((stateInfo & (1 << (i + 4)))?1:0);      // copy state from output register
      else
        curState.at(i)->put(0);                             // in standby mode, output is off
    }

    // check if driver is in limp home mode (happens when monoflop is not triggered any more)
    if(diagInfo & DRIVER2_DIAG_LIMPHOME)
    {
      driverInStandBy[1] = false;           // limp home includes standby! but don't initiate reset yet here.

      if(driverInLimpHome[1] == false)
      {
        driverInLimpHome[1] = true;
        CLOG(WARNING, mLoggerName.c_str()) << "output driver #2 now in limp home mode";
      }
    }
    // check if driver is in standby mode (will happen after limp home mode)
    else if(diagInfo & DRIVER2_DIAG_STANDBY)
    {
      driverInLimpHome[1] = false;

      if(driverInStandBy[1] == false)
      {
        driverInStandBy[1] = true;
        CLOG(WARNING, mLoggerName.c_str()) << "output driver #2 now in standby mode";
      }
    }
    else
    {
      driverInLimpHome[1] = false;
      driverInStandBy[1] = false;
    }

    // ---------------------------------------
    // DRIVER RESET LOGIC

    // check if either driver is in standby
    if((driverInStandBy[0] == true) || (driverInStandBy[1] == true))
    {
      if(standbyDelayCnt < DRIVER_RESET_DELAY)          // delay counter
      {
        standbyDelayCnt++;

        if(standbyDelayCnt == DRIVER_RESET_DELAY)       // issue reset when counter reaches threshold
        {
          CLOG(INFO, mLoggerName.c_str()) << "initiate output driver reset";
          resetHardware();

          standbyDelayCnt = 0;                          // reset counter for possible further reset
        }
      }
    }
    else
    {
      standbyDelayCnt = 0;
    }

    standardDiag = (uint16_t)ptRawData->standardDiagnosticInfo;
    ptRawData->reqState = reqOutputState;

    return (0);
  }


  void
  DigitalOutputs::getStatus ()
  {
    std::cout << "\n Digital Output Register:"
        << "\n=============================="
        << "\n"
        << "\n   current state:          0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->curState
        << "\n   requested state:        0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->reqState
        << "\n   default diagnostic:     0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->standardDiagnosticInfo
        << "\n   next result offset:     0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->nextResultOffset
        << "\n   last buffer read offset:0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->lastBufferRead
        << "\n"
        << "\n   cmd buffer write:       0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->writeOffset
        << "\n   cmd buffer read:        0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->readOffset
        << "\n   debug 1:                0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->debug[0]
        << "\n   debug 2:                0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->debug[1]
        << "\n"
        << "\n   buffer [0]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[0].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[0].response
        << "\n   buffer [1]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[1].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[1].response
        << "\n   buffer [2]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[2].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[2].response
        << "\n   buffer [3]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[3].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[3].response
        << "\n   buffer [4]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[4].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[4].response
        << "\n   buffer [5]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[5].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[5].response
        << "\n   buffer [6]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[6].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[6].response
        << "\n   buffer [7]  command: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[7].cmd << "  => response: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->cmdFifo[7].response
        << "\n" << std::endl;
  }


  uint16_t
  DigitalOutputs::sendCommand (uint16_t cmdvalue)
  {
    uint16_t index = ptRawData->writeOffset;
    ptRawData->cmdFifo[index].cmd = cmdvalue;
    ptRawData->cmdFifo[index].response = 0xffff;
    ptRawData->writeOffset ++;
    if (ptRawData->writeOffset > 7)
      ptRawData->writeOffset = 0;

    return (index);
  }

  bool
  DigitalOutputs::isCommandDone (uint16_t index)
  {
    if (index > 7)
      return (false);

    if (ptRawData->cmdFifo[index].response != 0xffff) {
      return (true);
    }
    return (false);
  }

  uint16_t
  DigitalOutputs::getCommandResult (uint16_t index)
  {
    if (index > 7)
      return (0xffff);

    return (ptRawData->cmdFifo[index].response);
  }

  void
  DigitalOutputs::resetHardware()
  {
    sendCommand(0xe0e0);        // activate device from standby (was 0xe2e2; standby was implicitly left by setting DMUX)
    sendCommand(0xf3f3);        // use current sense of channel 4 for IS pin
    sendCommand(0x8080);
  }


} /* namespace BaseTecDriver */
