/**
 * @file SkeletonModule
 * @short contain declaration of class \c SkeletonModule methods
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
// System header
#include <iostream>

// external library header

// local library header
#include "SkeletonModule.h"
#include "SkeletonModuleVersionInfo.h"

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
EXPORT_FUNCTIONS(HwAccessDemo, HwAccessModule)

namespace HwAccessDemo {

    // **************************************************************************************************
    // ** SkeletonModule
    // **************************************************************************************************
    HwAccessModule::HwAccessModule(const char* _instanceName,
                                   pugi::xml_node* _configInfo)
        : GaAppBaseLib::ModuleInterface (_instanceName, _configInfo)
    {
        /*
         * TODO: add your stuff here:
         *  - initialize your module
         *  - create your gamma variables
         */
    }

    // **************************************************************************************************
    // ** ~SkeletonModule
    // **************************************************************************************************
    HwAccessModule::~HwAccessModule()
    {
        /*
         * TODO: add your stuff here:
         *  - clean up internal resources
         */
    }

    // **************************************************************************************************
    // ** prepareStart
    // **************************************************************************************************
    void
    HwAccessModule::prepareStart()
    {
        /*
         * TODO: add your stuff here:
         *  - get connection to other modules
         */
    }

    // **************************************************************************************************
    // ** cleanUp
    // **************************************************************************************************
    void
    HwAccessModule::cleanUp()
    {
        /*
         * TODO: add your stuff here:
         *  -  last chance to get Gamma-Variables
         *  -  close connections to other modules
         */
    }

    // **************************************************************************************************
    // ** execCommand
    // **************************************************************************************************
    void
    HwAccessModule::execCommand (std::string& _cmdLine)
    {
        // extract given command
        std::string cmd = _cmdLine.substr(0, _cmdLine .find(' '));

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
            std::string moduleCmd = _cmdLine.substr(delimitPos+1, std::string::npos);

            // TODO: call submodule command interface
            std::cout << "  " << getName() << ": command for submodule \"" << moduleName << "\": \"" << moduleCmd << "\"" << std::endl;
        }
        // -------------------------------------------------------------------------------------------------------
        // unknown command
        // -------------------------------------------------------------------------------------------------------
        else if (_cmdLine .length() > 0) {
            std::cerr << "  " << getName() << ": unknown command \"" << cmd << "\"" << std::endl;
        }
    }

} /* namespace SkeletonModule */
