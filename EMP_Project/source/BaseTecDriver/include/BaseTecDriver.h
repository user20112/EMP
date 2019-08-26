/**
 * @file BaseTecDriver
 * @short contain definition of class \c BaseTecDriver::BaseTecDriver
 *
 * @remark
 * this file is a template file and could be used to create new GaApp - Modules. Do do so replace all "BaseTecDriver" by your module name and add your code to all TODO comments
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_BASETECDRIVER_BASETECDRIVER_H_
#define SOURCE_BASETECDRIVER_BASETECDRIVER_H_

// System header
#include <string>

// external library header
#include "GaAppBaseLib.h"
#include "GaGCppAPI.h"
#include "BeagleBoneResources.h"

// library header
#include "HardwareCtrl.h"
#include "DigitalInputs.h"
#include "DigitalOutputs.h"
#include "AnalogInputs.h"

namespace BaseTecDriver {

    /**
     * @short TODO: add your module description here
     */
    class BaseTecDriver: public GaAppBaseLib::ModuleInterface,
            public GaGCppAPI::GaTask
    {
        public:
            union tHWResources
            {
                    uint16_t word;
                    struct
                    {
                            uint8_t hardwareCtrl :1;
                            uint8_t digitalInputs :1;
                            uint8_t digitalOutputs :1;
                            uint8_t analogInputs :1;
                            uint8_t temperatureInputs :1;
                            uint8_t _bit05 :1;
                            uint8_t _bit06 :1;
                            uint8_t _bit07 :1;
                            uint8_t _bit08 :1;
                            uint8_t _bit09 :1;
                            uint8_t _bit10 :1;
                            uint8_t _bit11 :1;
                            uint8_t _bit12 :1;
                            uint8_t _bit13 :1;
                            uint8_t _bit14 :1;
                            uint8_t _bit15 :1;
                    } bit;
            };

            union tFirmwareStatus
            {
                    uint32_t word;
                    struct
                    {
                            uint8_t _bit00 :1;
                            uint8_t _bit01 :1;
                            uint8_t _bit02 :1;
                            uint8_t _bit03 :1;
                            uint8_t _bit04 :1;
                            uint8_t _bit05 :1;
                            uint8_t _bit06 :1;
                            uint8_t _bit07 :1;
                            uint8_t _bit08 :1;
                            uint8_t _bit09 :1;
                            uint8_t _bit10 :1;
                            uint8_t _bit11 :1;
                            uint8_t _bit12 :1;
                            uint8_t _bit13 :1;
                            uint8_t _bit14 :1;
                            uint8_t _bit15 :1;
                            uint8_t _bit16 :1;
                            uint8_t _bit17 :1;
                            uint8_t _bit18 :1;
                            uint8_t _bit19 :1;
                            uint8_t _bit20 :1;
                            uint8_t _bit21 :1;
                            uint8_t _bit22 :1;
                            uint8_t _bit23 :1;
                            uint8_t _bit24 :1;
                            uint8_t _bit25 :1;
                            uint8_t _bit26 :1;
                            uint8_t _bit27 :1;
                            uint8_t _bit28 :1;
                            uint8_t _bit29 :1;
                            uint8_t _bit30 :1;
                            uint8_t _bit31 :1;
                    } bit;
            };

            struct tPruData
            {
                    uint32_t firmwareVersion;
                    tHWResources activeResources;
                    uint8_t _reserved_01[2];
                    tFirmwareStatus firmwareStatus;
                    uint8_t _reserved_02[3];
                    uint8_t shutdownPRU;

                    uint32_t pruAliveCounter;
                    uint32_t hostAliveCounter;
                    uint32_t programLoopCounter;
                    uint32_t sleepCounter;
            };

        public:
            /**
             * @short constructor
             *
             * @remark
             * don't add more input parameter, because the calling function wouldn't know them!
             *
             * __actual situation__
             *
             * the constructor is called during all modules will be loaded. There is no guarantee witch modules are active now.
             * During the construction the module is only for its own and should not try to connect to other modules.
             *
             * __jobs to do here__
             *  - parse xml configuration and setup this instance
             *  - create and connect to own gamma variables and scheduler slots
             *
             * @param _instanceName name of this instance
             * @param _configInfo pointer to xml configuration node
             */
            BaseTecDriver(const char* _instanceName,
                          pugi::xml_node* _configInfo);

            /**
             * @short destructor
             *
             * __actual situation__
             *
             * the application is shutting down and unload all modules.
             *
             * __jobs to do here__
             *  - Clean up your stuff
             */
            virtual ~BaseTecDriver();

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
            virtual void
            prepareStart();

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
            virtual void
            cleanUp();

            /**
             * @short general command interface
             *
             * the application has a user terminal. Commands can be forwarded to a module by using the syntax [moduleName]:[command] [args...]
             * This function will be called, when a command for this module is given to the terminal.
             *
             * @param _cmdLine command as string including all arguments
             */
            virtual void
            execCommand(std::string& _cmdLine);

            /**
             * @short method for realtime thread
             *
             * @remark
             * this method will be run as realtime thread. Take care, what you will do here.
             */
            void
            realtimeThread();

        protected:
            /**
             *
             * @return
             */
            virtual int32_t
            taskInit() noexcept;

            /**
             *
             * @return
             */
            virtual int32_t
            taskDeinit() noexcept;

            /**
             *
             * @param taskHandle
             * @param frameNumber
             * @return
             */
            virtual int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

        private:
            BeagleBoneResources::PruInterface pru;      ///< @short PRU driver

            bool mStopRealtimeThread;                   ///< @short when set, the realtime task will stop.
            bool mRealtimeThreadActive;                 ///< @short is set, when realtime task is active
            RT_TASK mRealtimeTask;                      ///< @short handler for realtime task

            int mCycleTime;                             ///< @short realtime cycle time in ns
            int mPriority;                              ///< @short realtime task priority

            std::string mGammaPathBase;                 ///< @short path base to gamma PV's
            std::string mGammaSlot;                     ///< @short name of gamma scheduler slot

            HardwareCtrl* hwCtrl;
            DigitalInputs* digIn;
            DigitalOutputs* digOut;
            AnalogInputs* anaIn;
            /*
             TemperatureInputs temperatureIn;
             */

            volatile tPruData* ptRawData;

            float pruCycleTime;

            float timerBuffer[1024];
            uint16_t bufferIndex;
            float maxCycleTime;
            float minCycleTime;
            float meanCycleTime;

            // section Config
            GaGCppAPI::TypedPV<uint32_t> HostAliveTimer;
            GaGCppAPI::TypedPV<uint16_t> RequestedResources;

            // section Data
            GaGCppAPI::TypedPV<uint16_t> ActiveResources;
            GaGCppAPI::TypedPV<uint32_t> FirmwareStatus;
            GaGCppAPI::TypedPV<uint32_t> FirmwareVersion;

            // section Debug
            GaGCppAPI::TypedPV<uint32_t> MinHostAliveTimer;
            GaGCppAPI::TypedPV<uint32_t> ProgramLoopCounter;
            GaGCppAPI::TypedPV<uint32_t> PruAliveTimer;
            GaGCppAPI::TypedPV<uint32_t> SleepCounter;
            GaGCppAPI::TypedPV<float> BaseMeanCycleTime;
            GaGCppAPI::TypedPV<float> BaseMaxCycleTime;
            GaGCppAPI::TypedPV<float> BaseMinCycleTime;
    };

} /* namespace BaseTecDriver */

#endif /* SOURCE_BASETECDRIVER_BASETECDRIVER_H_ */
