/**
 * @file BaseTecDriver
 * @short contain declaration of class \c BaseTecDriver methods
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
// System header
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

// external library header
#include <native/task.h>
#include <native/timer.h>

#include "pugixml.hpp"

// local library header
#include "BaseTecDriver.h"
#include "BaseTecDriverVersionInfo.h"

/**
 * @fn createModule
 * @short create a new module instance
 * @param _instanceName name of module instance
 * @param _configNode pointer to XML configuration information
 * @return pointer to new module instance
 *
 * @fn deleteModule
 * @short destroy module instance
 * @param _module pointer to instance
 */
EXPORT_FUNCTIONS(BaseTecDriver, BaseTecDriver)

namespace BaseTecDriver {

    /**
     * @short global wrapper for thread function
     * @param _arg pointer to class BaseTecDriver
     */
    void globalRealtimeThread(void* _arg)
    {
        BaseTecDriver* ptDriver = (BaseTecDriver*) _arg;
        VALIDATE_ARGUMENT_NOT_EQUAL(ptDriver, nullptr);

        ptDriver->realtimeThread();
    }

    // **************************************************************************************************
    // ** BaseTecDriver
    // **************************************************************************************************
    BaseTecDriver::BaseTecDriver(const char* _instanceName,
                                 pugi::xml_node* _configInfo)
            : GaAppBaseLib::ModuleInterface(_instanceName, _configInfo),
              pru(0)
    {

        pruCycleTime = 0.02172;    // ms per PRU cycle

        bufferIndex = 0;
        maxCycleTime = 0;
        minCycleTime = 0xffffffff;
        meanCycleTime = 0;

        mStopRealtimeThread = false;
        mRealtimeThreadActive = false;

        mCycleTime = 100 * 1000 * 1000;    // default cycle time: 100 ms
        mPriority = 99;

        pugi::xml_attribute attr;
        pugi::xml_node rtSetup = getConfigNode().child("RealtimeSetup");
        if (!rtSetup.empty()) {
            attr = rtSetup.attribute("cycleTime");
            if (!attr.empty()) {
                mCycleTime = attr.as_int() * 1000;
            }

            attr = rtSetup.attribute("priority");
            if (!attr.empty()) {
                mPriority = attr.as_int();
            }
        }

        CLOG(INFO, mLoggerName.c_str())<< "realtime task: cycle time: " << mCycleTime << " ns; << priority: " << mPriority;

        mGammaPathBase = "HardwareResources.BaseTecDriver";
        mGammaSlot == ":BaseTecDriver.IOSync";

        pugi::xml_node gaSetup = getConfigNode().child("GammaConnection");
        if (!gaSetup.empty()) {
            attr = gaSetup.attribute("PVNode");
            if (!attr.empty()) {
                mGammaPathBase = attr.value();
            }

            attr = gaSetup.attribute("SchedulerSlot");
            if (!attr.empty()) {
                mGammaSlot = attr.value();
            }
        }

        CLOG(INFO, mLoggerName.c_str())<< "gamma connection: PV base address: " << mGammaPathBase << "; Scheduler Slot: " << mGammaSlot;

        // get gamma connection
        connect(mGammaSlot);

        HostAliveTimer.connectToPv((mGammaPathBase + ".BaseSystem.Config.HostAliveTimer").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        RequestedResources.connectToPv((mGammaPathBase + ".BaseSystem.Config.RequestedResources").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        ActiveResources.connectToPv((mGammaPathBase + ".BaseSystem.Data.ActiveResources").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        FirmwareStatus.connectToPv((mGammaPathBase + ".BaseSystem.Data.FirmwareStatus").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        FirmwareVersion.connectToPv((mGammaPathBase + ".BaseSystem.Data.FirmwareVersion").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        MinHostAliveTimer.connectToPv((mGammaPathBase + ".BaseSystem.Debug.MinHostAliveTimer").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        ProgramLoopCounter.connectToPv((mGammaPathBase + ".BaseSystem.Debug.ProgramLoopCounter").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        PruAliveTimer.connectToPv((mGammaPathBase + ".BaseSystem.Debug.PruAliveTimer").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        SleepCounter.connectToPv((mGammaPathBase + ".BaseSystem.Debug.SleepCounter").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        BaseMeanCycleTime.connectToPv((mGammaPathBase + ".BaseSystem.Debug.CycleTimeInfo[0]").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        BaseMaxCycleTime.connectToPv((mGammaPathBase + ".BaseSystem.Debug.CycleTimeInfo[1]").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
        BaseMinCycleTime.connectToPv((mGammaPathBase + ".BaseSystem.Debug.CycleTimeInfo[2]").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);

        MinHostAliveTimer = 9999.999;
        if (HostAliveTimer == 0) {
            HostAliveTimer = 100000;
        }

        if (RequestedResources == 0) {
            RequestedResources = 0x001f;
        }

        // global firmware data area
        ptRawData = (tPruData*) (pru.getSharedMemory() + 0x000);
        memset((void*) ptRawData, 0, sizeof(tPruData));

        ptRawData->activeResources.word = RequestedResources;
        ptRawData->hostAliveCounter = HostAliveTimer * 10;

        try {
            CLOG(DEBUG, mLoggerName.c_str())<< "load submodules";
            hwCtrl = new HardwareCtrl(pru.getSharedMemory() + 0x0020, mGammaPathBase + ".HardwareCtrl", mLoggerName + ".HWControl");
            digIn = new DigitalInputs(pru.getSharedMemory() + 0x0040, mGammaPathBase + ".DigitalInputs", mLoggerName + ".DigitalInputs");
            digOut = new DigitalOutputs(pru.getSharedMemory() + 0x00a0, mGammaPathBase + ".DigitalOutputs", mLoggerName + ".DigitalOutputs");
            anaIn = new AnalogInputs(pru.getSharedMemory() + 0x00f0, mGammaPathBase + ".AnalogInputs", mLoggerName + ".AnalogInputs");
            // temperatureIn = new TemperatureInputs(pru.getSharedMemory() + 0x2fb0, mGammaPathBase + ".TemperatureInputs", mLoggerName + ".TemperatureInputs");
        }
        catch (std::exception &e) {
            CLOG(ERROR, mLoggerName.c_str()) << "unable to create sub modules:\n" << e.what();
            throw;
        }
    }

    // **************************************************************************************************
    // ** ~BaseTecDriver
    // **************************************************************************************************
    BaseTecDriver::~BaseTecDriver()
    {
        delete hwCtrl;
        delete digIn;
        delete digOut;
        delete anaIn;
        // delete temperatureIn;
    }

    // **************************************************************************************************
    // ** prepareStart
    // **************************************************************************************************
    void
    BaseTecDriver::prepareStart()
    {
        int retVal;

        mStopRealtimeThread = false;

        // mRealtimeTask
        retVal = rt_task_create(&mRealtimeTask, (getName() + ".realtime").c_str(), 0, 99, 0);
        if (retVal != 0) {
            THROW_LOGIC_FAULT()<< "unable to create realtime class (retVal = " << retVal << ")";
        }

        retVal = rt_task_set_periodic(&mRealtimeTask, TM_NOW, mCycleTime);
        if (retVal != 0) {
            THROW_LOGIC_FAULT()<< "unable to set cycle time (retVal = " << retVal << ")";
        }

        retVal = rt_task_start(&mRealtimeTask, &globalRealtimeThread, (void*) this);
        if (retVal != 0) {
            THROW_LOGIC_FAULT()<< "unable to start realtime thread (retVal = " << retVal << ")";
        }

        if (pru.compileProgram("../assembler/", "BaseTecDriver")) {
            THROW_LOGIC_FAULT()<< "unable to create PRU program. See terminal output for further details";
        }
        pru.loadProgram("../assembler/BaseTecDriver.img");

        do {
            CLOG(DEBUG, mLoggerName.c_str())<< "wait until PRU program is running. (Status: 0x" << std::hex << std::setw(8) << std::setfill('0') << ptRawData->firmwareStatus.word << "; active resources: 0x" << std::setw(4) << ptRawData->activeResources.word << ")" << std::endl;
            usleep(1000 * 1000);
        }while (!ptRawData->firmwareStatus.bit._bit08);

        if (ptRawData->activeResources.word != RequestedResources) {
            std::cerr << "\n\n\tnot all requested modules are loaded !!" << std::endl;
            char buf[512];
            sprintf(buf, "unable to load all pru resources (req: 0x%4.4x; act: 0x%4.4x)", (uint16_t) RequestedResources, ptRawData->activeResources.word);
            std::string msg = buf;
            THROW_LOGIC_FAULT()<< msg;
        }
        CLOG(INFO, mLoggerName.c_str())<< "PRU program successful started (active modules: 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->activeResources.word << ")" << std::endl;
    }

    // **************************************************************************************************
    // ** cleanUp
    // **************************************************************************************************
    void
    BaseTecDriver::cleanUp()
    {
        int retVal;
        int waitCounter = 0;

        if (mRealtimeThreadActive) {
            mStopRealtimeThread = true;
            while (mRealtimeThreadActive) {
                usleep(mCycleTime / 1000);
                waitCounter++;
                if (waitCounter > 10) {
                    CLOG(WARNING, mLoggerName.c_str())<< "unable to stop realtime Task. Force deleting thread";
                    retVal = rt_task_delete(&mRealtimeTask);
                    if (retVal != 0) {
                        THROW_LOGIC_FAULT() << "unable to delete realtime class (retVal = " << retVal << ")";
                    }
                    break;
                }
            }
        }

        ptRawData->shutdownPRU = 0xff;

        do {
            std::cout << "wait until PRU program is stopped. (Status: 0x" << std::hex << std::setw(8) << std::setfill('0') << ptRawData->firmwareStatus.word << ")" << std::endl;
            usleep(1000 * 1000);
        } while (!ptRawData->firmwareStatus.bit._bit31);
    }

    // **************************************************************************************************
    // ** execCommand
    // **************************************************************************************************
    void
    BaseTecDriver::execCommand(std::string& _cmdLine)
    {
        // extract given command
        std::string cmd = _cmdLine.substr(0, _cmdLine.find(' '));

        // extract module name
        size_t delimitPos = cmd.find(':');

        // -------------------------------------------------------------------------------------------------------
        // command: "info"  => print version information
        // -------------------------------------------------------------------------------------------------------
        if (cmd == "info") {
            std::cout << "  " << getName() << " (Type:" << ModuleVersionInfo::getInstance().getName() << ")" << std::endl;
            ModuleVersionInfo::getInstance().printInfo(4);
        }
        // -------------------------------------------------------------------------------------------------------
        // command: "test"  => a testing command. not really useful
        // -------------------------------------------------------------------------------------------------------
        else if (cmd == "myCommand") {
            /*
             * TODO: add your stuff here:
             *  - run your command interface
             */
        }
        // -------------------------------------------------------------------------------------------------------
        // submodule command
        // -------------------------------------------------------------------------------------------------------
        else if (delimitPos != std::string::npos) {
            std::string moduleName = cmd.substr(0, delimitPos);
            std::string moduleCmd = _cmdLine.substr(delimitPos + 1, std::string::npos);

            // TODO: call submodule command interface
            std::cout << "  " << getName() << ": command for submodule \"" << moduleName << "\": \"" << moduleCmd << "\"" << std::endl;
        }
        // -------------------------------------------------------------------------------------------------------
        // unknown command
        // -------------------------------------------------------------------------------------------------------
        else if (_cmdLine.length() > 0) {
            std::cerr << "  " << getName() << ": unknown command \"" << cmd << "\"" << std::endl;
        }
    }

    // **************************************************************************************************
    // ** execCommand
    // **************************************************************************************************
    void
    BaseTecDriver::realtimeThread()
    {
        CLOG(INFO, mLoggerName.c_str())<<"start realtime Thread";
        mRealtimeThreadActive = true;

        while (!mStopRealtimeThread) {
            rt_task_wait_period(nullptr);
            anaIn->taskRun();
        }

        CLOG(INFO, mLoggerName.c_str()) << "stop realtime Thread";
        mRealtimeThreadActive = false;
    }

    // **************************************************************************************************
    // ** taskInit
    // **************************************************************************************************
    int32_t
    BaseTecDriver::taskInit() noexcept
    {

        return (0);
    }

    // **************************************************************************************************
    // ** taskDeinit
    // **************************************************************************************************
    int32_t
    BaseTecDriver::taskDeinit() noexcept
    {

        return (0);
    }

    // **************************************************************************************************
    // ** taskRun
    // **************************************************************************************************
    int32_t
    BaseTecDriver::taskRun(gs_Task taskHandle,
                           const uint32_t* frameNumber) noexcept
    {
        try {
            ActiveResources = (uint16_t) ptRawData->activeResources.word;
            FirmwareStatus = (uint32_t) ptRawData->firmwareStatus.word;
            FirmwareVersion = (uint32_t) ptRawData->firmwareVersion;
            ProgramLoopCounter = (uint32_t) ptRawData->programLoopCounter;
            PruAliveTimer = (uint32_t) ptRawData->pruAliveCounter;
            SleepCounter = (uint32_t) ptRawData->sleepCounter;

            MinHostAliveTimer = (uint32_t) ptRawData->hostAliveCounter;
            ptRawData->hostAliveCounter = HostAliveTimer;

            bufferIndex++;
            if (bufferIndex >= 1024)
                bufferIndex = 0;
            meanCycleTime -= timerBuffer[bufferIndex] / 1024;
            timerBuffer[bufferIndex] = (HostAliveTimer - MinHostAliveTimer) * pruCycleTime;
            meanCycleTime += timerBuffer[bufferIndex] / 1024;

            if (timerBuffer[bufferIndex] > maxCycleTime) {
                maxCycleTime = timerBuffer[bufferIndex];
            }

            if (timerBuffer[bufferIndex] < minCycleTime) {
                minCycleTime = timerBuffer[bufferIndex];
            }

            BaseMeanCycleTime = meanCycleTime;
            BaseMaxCycleTime = maxCycleTime;
            BaseMinCycleTime = minCycleTime;

            hwCtrl->taskRun(taskHandle, frameNumber);
            digIn->taskRun(taskHandle, frameNumber);
            digOut->taskRun(taskHandle, frameNumber);
        }
        catch (std::exception &e) {
            CLOG(ERROR, mLoggerName.c_str())<<"error in logic task:\n" << e.what();
    }

    return (0);
}

}
/* namespace BaseTecDriver */
