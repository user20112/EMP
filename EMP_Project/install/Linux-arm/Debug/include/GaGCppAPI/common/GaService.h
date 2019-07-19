/**
 * @file GaService.h
 * @short contain definition of class \c GaGCppAPI::GaService
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_INCLUDE_COMMON_GACONNECTION_H_
#define SOURCE_GAGCPPAPI_INCLUDE_COMMON_GACONNECTION_H_

// System header
#include <iostream>
#include <vector>
#include <pthread.h>

// external library header
#include "gacommon/common.h"
#include "exceptions/ExceptionsMacros.h"

// local library header
#include "common/Event.h"
#include "common/GaLogger.h"

namespace GaGCppAPI {

    /**
     * @short access to gamma service interface.
     * @remark this class is a singelton class. Use \c GaGCppAPI::GaService::getInstance() to get a reference to the global instance.
     */
    class GaService
    {
        public:
            /**
             * @short access to global instance
             * @return reference to global class instance
             */
            static GaService&
            getInstance();

            /**
             * @short destructor: clean up
             */
            virtual
            ~GaService();

            /**
             * @short attach application to gamma service
             * @param _startWatchDog when set, the watch dog will be started automatically.
             */
            void
            attach(bool _startWatchDog = true);

            /**
             *  @short detach application from gamma service
             *  @param _suppressEvent when set, event onDetach won't be fired.
             */
            void
            detach(bool _suppressEvent = false) noexcept;

            /**
             * @short set name of application. Used when attach to gamma service
             * @remark the name can only be changed, when this application is not attached to gamma service
             * @param _name new application name
             */
            void
            setTaskName(std::string _name);

            /**
             * @short get current gamma application name
             * @return current name
             */
            inline const std::string&
            getTaskName() const
            {
                return (mTaskName);
            }

            /**
             * @short set gamma service port.
             * @remark the port can only be changed, when this application is not attached to gamma service
             * @param _port gamma service port. Use 0 for default configuration
             */
            void
            setServicePort(uint16_t _port);

            /**
             * @short request the current port configuration
             * @return current gamma service port
             */
            uint16_t
            GetServicePort() const
            {
                return (mServicePort);
            }

            /**
             * @short set the connection waiting time. The unit is [ms]
             * @remark the waiting time can only be changed, when this application is not attached to gamma service
             * @param _timeout waiting time in ms
             */
            void
            setConnectTimeout(uint32_t _timeout);

            /**
             * @short request the current waiting time
             * @return current waiting time in ms
             */
            uint32_t
            GetConnectTimeout() const
            {
                return (mConnectTimeout);
            }

            /**
             * @short change the current task state to INITIALIZING
             * @remark the state can only be changed, when the application is connected to gamma service
             */
            void
            setTaskInitializing();

            /**
             * @short change the current task state to OPERATIONAL
             * @remark the state can only be changed, when the application is connected to gamma service
             */
            void
            setTaskOperating();

            /**
             * @short examine the current task state
             * @return true when application is attached and operating state is INITIALIZING, otherwise false
             */
            bool
            isInitializing() const;

            /**
             * @short examine the current task state
             * @return true when application is attached and operating state is OPERATIONAL, otherwise false
             */
            bool
            isOperating() const;

            /**
             * @short examine the current connection state
             * @return true when application is attached
             */
            bool
            isAttached() const;

            /**
             * @short get the name of the gamma service
             * @return name of local gamma system
             */
            std::string
            getSystemName() const;

            /**
             * @short start gamma service watchdog
             */
            void
            startWatchDog ();

            /**
             * @short stop gamma service watchdog
             */
            void
            stopWatchDog() noexcept;


            /**
             * @short add a scheduler to service list
             * @param _name name of scheduler
             */
            void
            addScheduler(std::string _name);

            /**
             * @short start a gamma scheduler
             * @param _name name of scheduler
             */
            void
            startScheduler (std::string _name);

            /**
             * short stop a gamma scheduler
             * @param _name name of scheduler
             */
            void
            stopScheduler (std::string _name);

            /**
             * @short start all connected gamma scheduler
             */
            void
            startSchedulerAll ();

            /**
             * short stop all connected gamma scheduler
             */
            void
            stopSchedulerAll ();

            /**
             * @short access for attach event
             * @return event reference
             */
            Event&
            onAttach()
            {
                return (mOnAttach);
            }

            /**
             * @short access for detach event
             * @return event reference
             */
            Event&
            onDetach()
            {
                return (mOnDetach);
            }

            /**
             * @short access for connection lost event
             * @return event reference
             */
            Event&
            onConnectionLost()
            {
                return (mOnConnectionLost);
            }

            /**
             * @short logger for info messages. just pipe messages to the logger.
             * @return instance to logger instance
             */
            GaLogger&
            info();

            /**
             * @short logger for warning messages. just pipe messages to the logger.
             * @return instance to logger instance
             */
            GaLogger&
            warning();

            /**
             * @short logger for error messages. just pipe messages to the logger.
             * @return instance to logger instance
             */
            GaLogger&
            error();

            /**
             * @short friend class. is needed to start watch dog as thread.
             * @param ptr [unused] thread parameter
             * @return [unused] thread result
             */
            friend void*
            startThread(void *ptr);

        private:
            /**
             * @short name of task. is send to gamma service, when application is attached to service
             */
            std::string mTaskName;

            /**
             * @short name is set by application
             */
            bool mNameIsSet;

            /**
             * @short signal when application is attached to gamma service
             */
            bool mIsAttached;

            /**
             * @short name of local gamma service
             */
            std::string mSystemName;

            /**
             * @short gamma service system info
             */
            gc_BrowserInfo mSystemInfo;

            /**
             * @short current task state
             */
            gc_TaskState mTaskState;

            /**
             * @short port of gamma service
             */
            uint16_t mServicePort;

            /**
             * @short connection time out
             */
            uint32_t mConnectTimeout;

            std::vector<std::string> mSchedulerList;

            /**
             * @short watch dog handle
             */
            pthread_t mWatchDogTask;

            /**
             * @short mutex to wake watch dog up
             */
            pthread_mutex_t mWatchDogWakeUp;

            /**
             * @short signal to watch dog thread => terminate thread
             */
            bool mWatchDocAbbort;

            /**
             * @short event. will be fired, when application is attached to gamma service.
             */
            Event mOnAttach;

            /**
             * @short event, will be fired, when application is detached from gamma service.
             */
            Event mOnDetach;

            /**
             * @short event, will be fired, when connection to gamma service is lost.
             */
            Event mOnConnectionLost;

            /**
             * @short logger for info messages. Message are forwarded to gamma service
             */
            GaLogger mLogInfo;

            /**
             * @short logger for warning messages. Message are forwarded to gamma service
             */
            GaLogger mLogWarning;

            /**
             * @short logger for error messages. Message are forwarded to gamma service
             */
            GaLogger mLogError;

            /**
             * @short default constructor.
             * @remark this class is a singelton class. Use static method \c getInstance to get the reference to the global instance
             */
            GaService() noexcept;

            /**
             * @short copy constructor.
             * @warning This is not implemented
             * @param other source instance
             */
            GaService(const GaService& other) = delete;

            /**
             * @short copy operator
             * @warning This is not implemented
             * @param other source instance
             * @return none
             */
            GaService&
            operator =(const GaService& other) = delete;

            /**
             * @short set the application _state state to gamma service
             * @param _state new application state
             */
            void
            setTaskState(gc_TaskState _state);

            /**
             * @short gamma service watchdog
             * task done in this thread:
             *  - attach application to gamma service
             *  - check for lost connections
             *  - reconnect, when service is available
             */
            void
            watchDog();
    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_INCLUDE_COMMON_GACONNECTION_H_ */
