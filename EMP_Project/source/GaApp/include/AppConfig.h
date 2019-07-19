/**
 * @file AppConfig.h
 * @short contain definition of class \c AppControl
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPP_INCLUDE_APPCONTROL_H_
#define SOURCE_GAAPP_INCLUDE_APPCONTROL_H_

// System header
#include <string>

// external library header
#include "pugixml.hpp"

// application header
#include "GaAppBaseLib.h"

/**
 * @short class load configuration file and manage additional modules
 */
class AppControl
{
    public:
        /**
         * @short default constructor
         */
        AppControl();

        /**
         * @short class destructor
         */
        virtual
        ~AppControl();

        /**
         * @short load application configuration file and create XML document structure
         * @param _configFileName path and name of application configuration file
         */
        void
        loadConfigFile (std::string _configFileName);

        /**
         * @short load modules defined in configuration file
         *
         * all modules need to be described in configuration path "/AppConfig/ModuleList/". For each module there need to be a
         * node named "Module" and contains the attributes "name" and "library".
         *
         * attribute "name" defines the name of the module, attribute "library" give the name of the library. It is important, that the
         * file "lib[libraryName].so" is stored in the project folder "bin"
         *
         */
        void
        loadModules ();

        /**
         * @short call routine \c prepareStart for all loaded modules.
         */
        void
        prepareStart();

        /**
         * @short call routine \c cleanUp for all loaded modules.
         */
        void
        cleanUp();

        /**
         * @short send a string formated command to loaded module.
         * @param _moduleName name of module instance
         * @param _commandLine command including all parameter as string
         */
        void
        sendCommand (std::string& _moduleName,
                     std::string& _commandLine);

        /**
         * @short print a list of all loaded modules to stdout. When \param _printVersionInfo is set, the library version information is printed, too.
         * @param _printVersionInfo print library version information additionally
         */
        void
        printModuleList (bool _printVersionInfo = false);

    private:
        std::string mConfigFileName;                    ///< @short name of loaded configuration file (XML-Format)
        pugi::xml_document mConfigFile;                 ///< @short parsed configuration file (DOM)

        bool mFileLoaded;                               ///< @short is set, when a file is loaded successfully

        GaAppBaseLib::LibContainer& mModuleContainer;   ///< @short instance to central module container
};

#endif /* SOURCE_GAAPP_INCLUDE_APPCONTROL_H_ */
