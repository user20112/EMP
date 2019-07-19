/*
 * GaTask.cpp
 *
 *  Created on: 09.12.2014
 *      Author: s.hegemann
 */
#include "GaAppBaseLib.h"

#include "common/GaService.h"
#include "exceptions/GammaFaultException.h"
#include "scheduler/GaTask.h"

namespace GaGCppAPI {

    int32_t ga_task_init(void* userData)
    {
        GaTask* ptTask = (GaTask*) userData;
        return (ptTask->taskInit());
    }

    int32_t ga_task_deinit(void* userData)
    {
        GaTask* ptTask = (GaTask*) userData;
        return (ptTask->taskDeinit());
    }

    int32_t ga_task_run(void* userData,
                        gs_Task taskHandle,
                        const uint32_t* frameNumber)
    {
        GaTask* ptTask = (GaTask*) userData;
        return (ptTask->taskRun(taskHandle, frameNumber));
    }

    GaTask::GaTask()
    {
        mConnected = false;
        mName = "";
        mTaskHandler = nullptr;
    }

    GaTask::GaTask(std::string& _name)
    {
        mConnected = false;
        mName = "";
        mTaskHandler = nullptr;

        connect(_name);
    }

    GaTask::~GaTask()
    {
        if (mConnected) {
            gc_ErrorID result;
            result =  gs_task_stop  (&mTaskHandler, &mStatistics);
            if (result != gc_ERROR_SUCCESS.errorID) {
                // TODO: hier braucht es noch was schlaues! Aber keine Exception bitte!!!
            }
        }
    }

    void
    GaTask::connect(std::string& _name)
    {
        VALIDATE_ARGUMENT_EQUAL(mConnected, false);
        mName = _name;

        gc_ErrorID result;
        result =  gs_task_register (&mTaskHandler, mName.c_str(), (void* const)this, ga_task_init, ga_task_run, ga_task_deinit);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "unable to register to task " << mName;
        }

        GaService& service = GaService::getInstance();

        service.addScheduler(_name.substr(0, _name.find('.')));

        mConnected = true;
    }

    void
    GaTask::updateStatistics()
    {
        VALIDATE_ARGUMENT_EQUAL(mConnected, true);

        gc_ErrorID result;
        result =  gs_task_getStatistics  (mTaskHandler, &mStatistics);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "unable to update task " << mName << " statistics";
        }
    }

    void
    GaTask::waitNextFrame(const uint32_t  _framesToWait)
    {
        VALIDATE_ARGUMENT_EQUAL(mConnected, true);

        gc_ErrorID result;
        result =  gs_task_waitNextFrame  (mTaskHandler, _framesToWait);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "error while waiting for " << _framesToWait << " Frames. (Task " << mName << ")";
        }
    }

} /* namespace GaGCppAPI */
