/**
 * @file SkeletonModule
 * @short contain definition of class \c SkeletonModule::SkeletonModule
 *
 * @remark
 * this file is a template file and could be used to create new GaApp - Modules. Do do so replace all "SkeletonModule" by your module name and add your code to all TODO comments
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_SKELETONMODULE_SKELETONMODULE_H_
#define SOURCE_SKELETONMODULE_SKELETONMODULE_H_
// System header
#include <string>
// external library header
#include "GaAppBaseLib.h"
// library header
#include "GaGCppAPI.h"
namespace HwAccessDemo {
    /**
     * @short TODO: add your module description here
     */
    class HwAccessModule : public GaAppBaseLib::ModuleInterface,public GaGCppAPI::GaTask
    {
        private:
            std::string mGammaSlot;
            GaGCppAPI::TypedPV<uint8_t> myOutput;
            GaGCppAPI::TypedPV<uint8_t> myOutput2;
            GaGCppAPI::TypedPV<uint8_t> myInput;
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
            HwAccessModule(const char* _instanceName,
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
            virtual ~HwAccessModule();

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


        protected:
            virtual int32_t
            taskInit() noexcept;

            virtual int32_t
            taskDeinit() noexcept;

            virtual int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

    };

} /* namespace SkeletonModule */

#endif /* SOURCE_SKELETONMODULE_SKELETONMODULE_H_ */
