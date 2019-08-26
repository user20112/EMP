/**
 * @file ModuleInterface.h
 * @short contain definition of class \c GaAppBaseLib::ModuleInterface
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_MODULEINTERFACE_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_MODULEINTERFACE_H_

// System header

// external library header
#include <pugixml.hpp>

// library header
#include "log/logger.h"

namespace GaAppBaseLib {

    /**
     * @short interface definition for external GaApp Modules.
     *
     * external GaApp Modules need to be derived from this class.
     */
    class ModuleInterface
    {
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
            ModuleInterface(const char* _instanceName,
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
            virtual ~ModuleInterface();

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
             * @short request name of module instance
             * @return name of module instance
             */
            std::string
            getName();

            /**
             * @short request the xml configuration node
             * @return xml configuration node
             */
            pugi::xml_node&
            getConfigNode();

        protected:
            std::string mLoggerName;        ///< @short loggerName

        private:
            std::string mModuleName;        ///< @short instance name
            pugi::xml_node& mConfigNode;    ///< @short configuration node

    };

} /* namespace GaAppBaseLib */


/**
 * @def EXPORT_FUNCTIONS(NameSpace, ModuleName)
 * @short create export functions with specified module
 *
 * @param NameSpace library namespace
 * @param ModuleName module class name
 */
#define EXPORT_FUNCTIONS(NameSpace, ModuleName) \
    \
    GaAppBaseLib::ModuleInterface* \
    create##ModuleName (const char* _instanceName, \
                        pugi::xml_node* _configInfo) \
    { \
        try { \
            NameSpace::ModuleName* module = new NameSpace::ModuleName(_instanceName, _configInfo); \
            return (module); \
        } \
        catch (std::exception &e) { \
            LOG(ERROR) << "create module " << _instanceName << " failed: \n" << e.what(); \
        } \
        return (nullptr); \
    } \
    \
    extern "C" { \
        GaAppBaseLib::ModuleInterface* \
        createModule (const char* _instanceName, \
                      pugi::xml_node* _configInfo) \
        { \
            return (create##ModuleName(_instanceName, _configInfo)); \
        } \
        \
        void \
        deleteModule (GaAppBaseLib::ModuleInterface* _module) \
        { \
            delete _module; \
        } \
    } \

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_MODULEINTERFACE_H_ */
