/*
 * UART.h
 *
 *  Created on: 14.09.2017
 *      Author: mario.richter
 */

#ifndef SOURCE_BEAGLEBONERESOURCES_INCLUDE_UART_H_
#define SOURCE_BEAGLEBONERESOURCES_INCLUDE_UART_H_

// Used for TimeOut operations
#include <sys/time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <termios.h>
#include <string.h>
#include <iostream>

// File control definitions
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "GaAppBaseLib.h"
// external library header
#include "GaGCppAPI.h"
#include "BeagleBoneResources.h"

#include "pugixml.hpp"

#include "log/logger.h"

#define CIRBUFLEN       1024

typedef struct
{
    unsigned int read;                            /* pts at next filled char    */
    unsigned int writ;                            /* pts at next free char      */
    unsigned char buf[CIRBUFLEN];                 /* circular buffer for input  */
} cir_buf;


namespace BeagleBoneResources
{
  class UartInterface : public GaAppBaseLib::ModuleInterface, public GaGCppAPI::GaTask
  {
    public:

      /**
       * @short Constructor
       */
      UartInterface(const char* _instanceName, pugi::xml_node* _configInfo);

      /**
       * @short Destructor
       */
      virtual ~UartInterface();

      /**
       * @short method will be called by application before cycle task will be started
       *
       * __actual situation__
       *
       * all modules are loaded and the gamma middleware contain all needed variables, but the values do not necessarily have to be valid!
       *
       * __jobs to do here__
       *  - browse gamma variables
       *  - connect to other modules
       *
       */
      virtual void prepareStart();

      /**
       * @short method will be called by application after cycle task is stopped
       *
       * __actual situation__
       *
       * all cyclic task and scheduler are stopped. This is the last chance to get values from gamma. During this call no values should be changed anymore.
       *
       * __jobs to do here__
       *  - make needed backups
       *  - disconnect from gamma
       */
      virtual void cleanUp();

      /**
       * @short general command interface
       *
       * the application has a user terminal. Commands can be forwarded to a module by using the syntax [moduleName]:[command] [args...]
       * This function will be called, when a command for this module is given to the terminal.
       *
       * @param _cmdLine command as string including all arguments
       */
      virtual void execCommand(std::string& _cmdLine);

    protected:
        /**
         *
         * @return
         */
        virtual int32_t taskInit() noexcept;

        /**
         *
         * @return
         */
        virtual int32_t taskDeinit() noexcept;

        /**
         *
         * @param taskHandle
         * @param frameNumber
         * @return
         */
        virtual int32_t taskRun(gs_Task taskHandle, const uint32_t* frameNumber) noexcept;

    private:

      /**
       * @short Open file to access the serial port.
       * @param _device Name (string) of the device to open, e.g. /dev/ttyO1
       * @param _baud Baud rate for serial communication
       * @return  0 if successfully opened
       * @return -1 if file could not be opened
       * @return -2 if baudrate is invalid
       */
      int UartOpen(const char* _device, const unsigned int _baud);

      /**
       * @short Close file to access the serial port.
       * @return none
       */
      void UartClose(void);

      int fHandle;            //!< file handle for UART file access
      cir_buf recv_buf;       //!< circular receive buffer
      cir_buf send_buf;       //!< circular send buffer

      std::string mGammaPathBase;                 ///< @short path base to gamma PV's
      std::string mGammaSlot;                     ///< @short name of gamma scheduler slot

      // gamma variables for UART interface configuration
      GaGCppAPI::TypedPV<uint8_t>   uartdeviceNo;
      GaGCppAPI::TypedPV<uint32_t>  uartBaudRate;
  };
}

#endif /* SOURCE_BEAGLEBONERESOURCES_INCLUDE_UART_H_ */
