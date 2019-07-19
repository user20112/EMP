/*
 * GaConnection.cpp
 *
 *  Created on: 04.12.2014
 *      Author: s.hegemann
 */

#include <time.h>
#include <sstream>

#include "gaapi/api.h"
#include "gasched/sched.h"

#include "log/Logger.h"
#include "exceptions/ExceptionsMacros.h"

#include "common/GaService.h"
#include "exceptions/GammaFaultException.h"

namespace GaGCppAPI {

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
    void resetThreadPT (pthread_t& _pt) {
        _pt.p = nullptr;
    }

    bool threatPTisNull (pthread_t& _pt) {
        return (_pt.p == nullptr);
    }
#else
    void resetThreadPT (pthread_t& _pt) {
        _pt = 0L;
    }

    bool threatPTisNull (pthread_t& _pt) {
        return (_pt == 0L);
    }
#endif

    // **************************************************************************************************
    // ** thread start function
    // **************************************************************************************************
    void*
    startThread(void *ptr)
    {
        GaService::getInstance().watchDog();
        return (nullptr);
    }

    // **************************************************************************************************
    // ** GaConnection
    // **************************************************************************************************
    GaService::GaService() noexcept :
            mLogInfo(gc_LOG_SEVERITY_INFO),
            mLogWarning(gc_LOG_SEVERITY_WARNING),
            mLogError(gc_LOG_SEVERITY_ERROR)
    {
        mNameIsSet = false;
        mIsAttached = false;
        mTaskState = gc_TASK_STATE_INITIALIZING;

        mServicePort = 0;
        mConnectTimeout = 1000;

        resetThreadPT(mWatchDogTask);
        mWatchDogWakeUp = PTHREAD_MUTEX_INITIALIZER;
        mWatchDocAbbort = false;
    }

    // **************************************************************************************************
    // ** ~GaConnection
    // **************************************************************************************************
    GaService::~GaService()
    {
        if (threatPTisNull(mWatchDogTask)) {
            stopWatchDog();
        }
        detach();

    }

    // **************************************************************************************************
    // ** GetInstance
    // **************************************************************************************************
    GaService&
    GaService::getInstance()
    {
        static GaService instance;
        return (instance);
    }

    // **************************************************************************************************
    // ** attach
    // **************************************************************************************************
    void
    GaService::attach(bool _startWatchDog /* = true */)
    {
        gc_ErrorID result;

        if (!mIsAttached) {
            if (mNameIsSet) {
                result = gc_attachToServiceByName(mServicePort, mConnectTimeout, mTaskName.c_str());
                if (result != gc_ERROR_SUCCESS.errorID) {
                    THROW_GAMMA_FAULT(result)<< "unable to attach task " << mTaskName << " to gamma service! (Port: " << mServicePort << "; Time: " << mConnectTimeout << "ms)";
                }
            }
            else {
                result = gc_attachToService(mServicePort, mConnectTimeout);
                if (result != gc_ERROR_SUCCESS.errorID) {
                    THROW_GAMMA_FAULT(result) << "unable to attach task to gamma service! (Port: " << mServicePort << "; Time: " << mConnectTimeout << "ms)";
                }
            }
        }

        result = ga_browse_getSpecInfoByIndices (gc_BROWSING_TYPE_SYSTEM, 0, 0, 0, 0, 0, 0, &mSystemInfo);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result) << "get system information from gamma service failed";
        }
        mSystemName = mSystemInfo.info.system.name;

        mIsAttached = true;
        mOnAttach.fire(0);
        if (_startWatchDog) {
            startWatchDog();
        }
    }

    // **************************************************************************************************
    // ** detach
    // **************************************************************************************************
    void
    GaService::detach(bool _suppressEvent /* = false */) noexcept
    {
        gc_ErrorID result;

        if (mIsAttached) {
            result = gc_detachFromService();
            if (result != gc_ERROR_SUCCESS.errorID) {
                CLOG(ERROR, "GaService") << "detach from gamma service failed: " << result << " => " << gc_getErrorDescription(result);
            }
        }
        mIsAttached = false;
        if (!_suppressEvent) {
            mOnDetach.fire(0);
        }
    }

    // **************************************************************************************************
    // ** setTaskName
    // **************************************************************************************************
    void
    GaService::setTaskName(std::string _name)
    {
        if (mIsAttached) {
            THROW_LOGIC_FAULT()<< " application is already attached to gamma service! Unable to change task name to \"" << _name << "\"";
        }
        mNameIsSet = true;
        mTaskName = _name;
    }

    // **************************************************************************************************
    // ** setServicePort
    // **************************************************************************************************
    void
    GaService::setServicePort(uint16_t _port)
    {
        if (mIsAttached) {
            THROW_LOGIC_FAULT()<< " application is already attached to gamma service! Unable to change service port to " << _port;
        }
        mServicePort = _port;
    }

    // **************************************************************************************************
    // ** setConnectTimeout
    // **************************************************************************************************
    void
    GaService::setConnectTimeout(uint32_t _timeout)
    {
        if (mIsAttached) {
            THROW_LOGIC_FAULT()<< " application is already attached to gamma service! Unable to change timeout to " << _timeout;
        }
        mConnectTimeout = _timeout;
    }

    // **************************************************************************************************
    // ** setTaskInitializing
    // **************************************************************************************************
    void
    GaService::setTaskInitializing()
    {
        setTaskState(gc_TASK_STATE_INITIALIZING);
    }

    // **************************************************************************************************
    // ** setTaskOperating
    // **************************************************************************************************
    void
    GaService::setTaskOperating()
    {
        setTaskState(gc_TASK_STATE_OPERATIONAL);
    }

    // **************************************************************************************************
    // ** isInitializing
    // **************************************************************************************************
    bool
    GaService::isInitializing() const
    {
        return ((mIsAttached) && (mTaskState == gc_TASK_STATE_INITIALIZING));
    }

    // **************************************************************************************************
    // ** isOperating
    // **************************************************************************************************
    bool
    GaService::isOperating() const
    {
        return ((mIsAttached) && (mTaskState == gc_TASK_STATE_OPERATIONAL));
    }

    // **************************************************************************************************
    // ** isAttached
    // **************************************************************************************************
    bool
    GaService::isAttached() const
    {
        return (mIsAttached);
    }

    // **************************************************************************************************
    // ** getSystemName
    // **************************************************************************************************
    std::string
    GaService::getSystemName() const
    {
        return (mSystemName);
    }

    // **************************************************************************************************
    // ** watchDog
    // **************************************************************************************************
    void
    GaService::watchDog()
    {
        int retryTime = 2;

        do {
            if (mIsAttached)
            {
                bool isAlive;
                gc_ErrorID result;

                result = gc_isServiceAlive(&isAlive);
                if (result != gc_ERROR_SUCCESS.errorID) {
                    THROW_GAMMA_FAULT(result)<< "unable to check service state!";
                }

                if (isAlive) {
                    retryTime = 2;
                }
                else {
                    CLOG(ERROR, "GaService") << "connection to gamma service is shut down.";
                    mOnConnectionLost.fire(0);
                    detach(true); // clean up internal data
                }
            }
            else {
                try {
                    attach(false);
                    CLOG(INFO, "GaService") << "gamma service becomes alive again";
                }
                catch (...) {
                    retryTime = 5;
                    // nothing to do. attach was just a try!
                }
            }

            // wait some time or until thread is waked up by parent
            struct timespec abs_time;
            time_t timeNow = time(NULL);
            abs_time.tv_sec = timeNow + retryTime;

            pthread_mutex_timedlock(&mWatchDogWakeUp, &abs_time);
        } while (!mWatchDocAbbort);

        detach();
        CLOG(INFO, "GaService") << "monitoring of gamma service connection stopped. Application is detached from service!";
    }

    // **************************************************************************************************
    // ** startWatchDog
    // **************************************************************************************************
    void
    GaService::startWatchDog()
    {
        int result;

        // thread is already started. Skip start.
        if (threatPTisNull(mWatchDogTask)) {
            return;
        }

        if (!mIsAttached) {
            attach();
        }

        pthread_mutex_lock(&mWatchDogWakeUp);

        result = pthread_create(&mWatchDogTask, NULL, startThread, nullptr);
        if (result) {
            THROW_LOGIC_FAULT()<< "create watchdog thread failed: " << result;
        }
    }

    // **************************************************************************************************
    // ** stopWatchDog
    // **************************************************************************************************
    void
    GaService::stopWatchDog() noexcept
    {
        pthread_mutex_unlock(&mWatchDogWakeUp);
        mWatchDocAbbort = true;
        pthread_join(mWatchDogTask, NULL);
        resetThreadPT(mWatchDogTask);
    }

    // **************************************************************************************************
    // ** addScheduler
    // **************************************************************************************************
    void
    GaService::addScheduler(std::string _name)
    {
        for (auto scheduler = mSchedulerList.begin(); scheduler != mSchedulerList.end(); scheduler++) {
            if (scheduler->compare(_name) == 0) {
                return;
            }
        }
        mSchedulerList.push_back(_name);
    }

    // **************************************************************************************************
    // ** startScheduler
    // **************************************************************************************************
    void
    GaService::startScheduler (std::string _name)
    {
        gc_ErrorID result;

        result = gs_startScheduling(_name.c_str(), false);
        if (result != gc_ERROR_SUCCESS.errorID) {
            warning() << "starting scheduler \"" << _name << "\" failed (" << result << ")." << GaLogger::endl;
            THROW_GAMMA_FAULT(result) << "unable to start task " << mTaskName << " in gamma service!";
        }
        else {
            info() << "scheduler \"" << _name << "\" started." << GaLogger::endl;
        }
    }

    // **************************************************************************************************
    // ** stopScheduler
    // **************************************************************************************************
    void
    GaService::stopScheduler (std::string _name)
    {
        gc_ErrorID result;

        result = gs_stopScheduling(_name.c_str(), true);
        if (result != gc_ERROR_SUCCESS.errorID) {
            warning() << "stopping scheduler \"" << _name << "\" failed (" << result << ")." << GaLogger::endl;
            THROW_GAMMA_FAULT(result) << "unable to stop task " << mTaskName << " in gamma service!";
        }
        else {
            info() << "scheduler \"" << _name << "\" stopped." << GaLogger::endl;
        }
    }

    // **************************************************************************************************
    // ** stopScheduler
    // **************************************************************************************************
    void
    GaService::startSchedulerAll ()
    {
        for (auto scheduler = mSchedulerList.begin(); scheduler != mSchedulerList.end(); scheduler++) {
            startScheduler(*scheduler);
        }
    }

    // **************************************************************************************************
    // ** stopScheduler
    // **************************************************************************************************
    void
    GaService::stopSchedulerAll ()
    {
        for (auto scheduler = mSchedulerList.begin(); scheduler != mSchedulerList.end(); scheduler++) {
            stopScheduler(*scheduler);
        }
    }

    // **************************************************************************************************
    // ** stopWatchDog
    // **************************************************************************************************
    GaLogger&
    GaService::info()
    {
        return (mLogInfo);
    }

    // **************************************************************************************************
    // ** stopWatchDog
    // **************************************************************************************************
    GaLogger&
    GaService::warning()
    {
        return (mLogWarning);
    }

    // **************************************************************************************************
    // ** stopWatchDog
    // **************************************************************************************************
    GaLogger&
    GaService::error()
    {
        return (mLogError);
    }

    // **************************************************************************************************
    // ** setTaskState
    // **************************************************************************************************
    void
    GaService::setTaskState(gc_TaskState _state)
    {
        if (!mIsAttached) {
            THROW_LOGIC_FAULT()<<" application is not attached to gamma service! Unable to change state to OPERATIONAL";
    }

    gc_ErrorID result;
    result = gc_setCurrentTaskState(_state);

    if (result != gc_ERROR_SUCCESS.errorID) {
        THROW_GAMMA_FAULT(result)<< "unable to change task state to " << _state;
    }

    mTaskState = _state;
}

}
/* namespace GaGCppAPI */
