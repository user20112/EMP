/*
 * HardwareCtrl.h
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_HARDWARECTRL_H_
#define CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_HARDWARECTRL_H_

#include <stdint.h>
#include <string>

#include "GaGCppAPI.h"

namespace BaseTecDriver {

  class HardwareCtrl
  {
    public:
      union tUARTCtrl
      {
        uint8_t word;
        struct
        {
            uint8_t term_rx_en :1;
            uint8_t term_tx_en :1;
            uint8_t rx_rs4xx_en :1;
            uint8_t h_not_f :1;
            uint8_t srl :1;
            uint8_t txp :1;
            uint8_t _bit06 :1;
            uint8_t _bit07 :1;
        } bit;
      };

      union tTempInCtrl
      {
          uint8_t word;
          struct
          {
              uint8_t not_reset :1;
              uint8_t _bit01 :1;
              uint8_t _bit02 :1;
              uint8_t _bit03 :1;
              uint8_t _bit04 :1;
              uint8_t _bit05 :1;
              uint8_t _bit06 :1;
              uint8_t _bit07 :1;
          } bit;
      };

      struct tDataChannel
      {
          // basic hardware setup
          uint16_t hwTriggerBitMask;

          // hardware control requests
          uint8_t reqStateLEDgr;
          uint8_t reqStateLEDrt;
          tUARTCtrl reqStateUARTCtrl[2];
          tTempInCtrl reqStateTempCtrl;
          uint8_t _reserved01[1];

          // current hardware control state
          uint8_t _reserved02[2];
          uint8_t activeStateLEDgr;
          uint8_t activeStateLEDrt;
          tUARTCtrl activeStateUARTCtrl[2];
          tTempInCtrl activeStateTempCtrl;
          uint8_t _reserved03[1];
      };

    public:
      HardwareCtrl(volatile void* ptMemoryBase,
          std::string _dataBaseNode,
          std::string _loggerName);

      virtual
      ~HardwareCtrl();

      int32_t
      taskRun(gs_Task taskHandle,
          const uint32_t* frameNumber) noexcept;

      void setTemperatureReset(bool state);
      //void setUartConfig(int intf, bool useRS4xx, )

    private:
      std::string dataBaseNode;
      volatile tDataChannel* ptRawData;
      std::string mLoggerName;

      // section Config
      GaGCppAPI::TypedPV<uint16_t> HardwareTriggerBit;
      GaGCppAPI::TypedPV<uint8_t> RequestedLedStatusGr;
      GaGCppAPI::TypedPV<uint8_t> RequestedLedStatusRt;
      GaGCppAPI::TypedPV<uint8_t> RequestedCtrlUart1;
      GaGCppAPI::TypedPV<uint8_t> RequestedCtrlUart2;
      //           GaGCppAPI::TypedPV<uint8_t> RequestedCtrlTemperature;
      bool RequestedCtrlTemperature;

      // section Data
      GaGCppAPI::TypedPV<uint8_t> CurrentLedStatusGr;
      GaGCppAPI::TypedPV<uint8_t> CurrentLedStatusRt;
      GaGCppAPI::TypedPV<uint8_t> CurrentCtrlUart1;
      GaGCppAPI::TypedPV<uint8_t> CurrentCtrlUart2;
      GaGCppAPI::TypedPV<uint8_t> CurrentCtrlTemperature;
  };

} /* namespace BaseTecDriver */

#endif /* CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_HARDWARECTRL_H_ */
