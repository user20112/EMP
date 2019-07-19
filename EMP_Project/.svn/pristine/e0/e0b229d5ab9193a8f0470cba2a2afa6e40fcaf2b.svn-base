/**
 * @file ModuleInterface.cpp
 * @short contain declaration of class \c ModuleInterface methods
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

// external library header

// local library header
#include "ModuleInterface/ModuleInterface.h"

namespace GaAppBaseLib {

    // **************************************************************************************************
    // ** ModuleInterface
    // **************************************************************************************************
    ModuleInterface::ModuleInterface(const char* _instanceName,
                                     pugi::xml_node* _configInfo)
        : mConfigNode(*_configInfo)
    {
        mModuleName = _instanceName;
        mLoggerName = mModuleName;
        mLogger = el::Loggers::getLogger(mLoggerName);
    }

    // **************************************************************************************************
    // ** ~ModuleInterface
    // **************************************************************************************************
    ModuleInterface::~ModuleInterface()
    {
    }

    // **************************************************************************************************
    // ** prepareStart
    // **************************************************************************************************
    void
    ModuleInterface::prepareStart()
    {
    }

    // **************************************************************************************************
    // ** cleanUp
    // **************************************************************************************************
    void
    ModuleInterface::cleanUp()
    {
    }

    // **************************************************************************************************
    // ** execCommand
    // **************************************************************************************************
    void
    ModuleInterface::execCommand (std::string& _cmdLine)
    {
        // extract given command
        std::string cmd = _cmdLine.substr(0, _cmdLine.find(' '));

        if (_cmdLine.length() > 0) {
            std::cout << "  " << getName() << ": unknown command \"" << cmd << "\"" << std::endl;
        }
    }

    // **************************************************************************************************
    // ** getName
    // **************************************************************************************************
    std::string
    ModuleInterface::getName()
    {
        return (mModuleName);
    }

    // **************************************************************************************************
    // ** getConfigNode
    // **************************************************************************************************
    pugi::xml_node&
    ModuleInterface::getConfigNode()
    {
        return (mConfigNode);
    }


} /* namespace GaAppBaseLib */




