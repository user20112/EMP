/**
 * @file GaTask.h
 * @short contain definition of class \c GaGCppAPI::GaTask
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_SCHEDULER_GATASK_H_
#define CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_SCHEDULER_GATASK_H_

// System header
#include <string.h>

// external library header
#include <gasched/task.h>

// local library header



namespace GaGCppAPI {

    int32_t
    ga_task_init(void* userData);

    int32_t
    ga_task_deinit(void* userData);

    int32_t
    ga_task_run(void* userData,
                gs_Task taskHandle,
                const uint32_t* frameNumber);

    class GaTask
    {
        public:
            GaTask();

            GaTask(std::string& _name);

            virtual
            ~GaTask();

            void
            connect(std::string& _name);

            friend int32_t
            ga_task_init(void* userData);

            friend int32_t
            ga_task_deinit(void* userData);

            friend int32_t
            ga_task_run(void* userData,
                        gs_Task taskHandle,
                        const uint32_t* frameNumber);

        protected:
            virtual int32_t
            taskInit() noexcept = 0;

            virtual int32_t
            taskDeinit() noexcept = 0;

            virtual int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept = 0;

            void
            updateStatistics();

            void
            waitNextFrame(const uint32_t  _framesToWait);

            std::string mName;
            bool mConnected;

            gs_Task mTaskHandler;

            gs_TaskStatistics mStatistics;

    };

} /* namespace GaGCppAPI */

#endif /* CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_SCHEDULER_GATASK_H_ */
