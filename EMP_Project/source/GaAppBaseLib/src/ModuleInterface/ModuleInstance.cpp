/**
 * @file ModuleInstance.cpp
 * @short contain declaration of class \c ModuleInstance methods
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
#include "exceptions/ExceptionsMacros.h"
#include "ModuleInterface/ModuleInstance.h"

namespace GaAppBaseLib {

    // **************************************************************************************************
    // ** ModuleInstance
    // **************************************************************************************************
    ModuleInstance::ModuleInstance(tShdPtLibInstnace& _lib,
                                   std::string& _instanceName,
                                   pugi::xml_node& _configNode)
            : mLibInstance(_lib),
              mConfigNode(_configNode)
    {
        mInstanceName = _instanceName;
        instance = mLibInstance->createNewInstance(mInstanceName.c_str(), &mConfigNode);
        VALIDATE_ARGUMENT_NOT_EQUAL(instance, nullptr);
    }

    // **************************************************************************************************
    // ** ~ModuleInstance
    // **************************************************************************************************
    ModuleInstance::~ModuleInstance()
    {
        mLibInstance->deleteInstance(instance);
    }

    // **************************************************************************************************
    // ** getName
    // **************************************************************************************************
    std::string
    ModuleInstance::getName()
    {
        return (mInstanceName);
    }

    // **************************************************************************************************
    // ** getLibInstance
    // **************************************************************************************************
    tShdPtLibInstnace&
    ModuleInstance::getLibInstance()
    {
        return (mLibInstance);
    }

    // **************************************************************************************************
    // ** prepareStart
    // **************************************************************************************************
    void
    ModuleInstance::prepareStart()
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(instance, nullptr);
        instance->prepareStart();
    }

    // **************************************************************************************************
    // ** cleanUp
    // **************************************************************************************************
    void
    ModuleInstance::cleanUp()
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(instance, nullptr);
        instance->cleanUp();
    }

    // **************************************************************************************************
    // ** execCommand
    // **************************************************************************************************
    void
    ModuleInstance::execCommand(std::string& _cmdLine)
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(instance, nullptr);
        instance->execCommand(_cmdLine);
    }

} /* namespace GaAppBaseLib */
