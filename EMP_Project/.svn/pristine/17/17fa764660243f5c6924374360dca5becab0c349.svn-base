/**
 * @file LibInstance.cpp
 * @short contain declaration of class \c LibInstance methods
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
#include "ModuleInterface/LibInstance.h"

#include <iostream>
#include <dlfcn.h>

// external library header

// local library header
#include "exceptions/ExceptionsMacros.h"

namespace GaAppBaseLib {

    // **************************************************************************************************
    // ** LibInstance
    // **************************************************************************************************
    LibInstance::LibInstance(std::string _libName)
    {
        mLoggerName = "LibInstance.";
        mLoggerName.append(_libName);
        el::Loggers::getLogger(mLoggerName);

        char* lastError = dlerror();

        std::string fileName = "lib" + _libName + ".so";
        CLOG(INFO, mLoggerName.c_str()) << "LibInstance: load library " << _libName << " (search for file: " << fileName << ")";

        mHandle = dlopen(fileName.c_str(), RTLD_NOW);
        lastError = dlerror();
        if (!mHandle)
        {
            CLOG(ERROR, mLoggerName.c_str()) << "unable to load file " << fileName << ": " << lastError;
            THROW_LOGIC_FAULT()<< "unable to load file " << fileName << ": " << lastError;
        }

        mPtCreateFkt = (tFctPtCreateModule)dlsym(mHandle, "createModule");
        lastError = dlerror();
        if (lastError != nullptr) {
            CLOG(ERROR, mLoggerName.c_str()) << "unable to resolve function createModule: " << lastError;
            THROW_LOGIC_FAULT()<< "unable to resolve function createModule: " << lastError;
        }
        if (mPtCreateFkt == nullptr) {
            std::cout << "unable to resolve function createModule: function not found" << std::endl;
            THROW_LOGIC_FAULT()<< "unable to resolve function createModule: function not found";
        }


        mPtDeleteFkt = (tFctPtDeleteModule)dlsym(mHandle, "deleteModule");
        lastError = dlerror();
        if (lastError != nullptr) {
            CLOG(ERROR, mLoggerName.c_str()) << "unable to resolve function deleteModule: " << lastError;
            THROW_LOGIC_FAULT()<< "unable to resolve function deleteModule: " << lastError;
        }
        if (mPtDeleteFkt == nullptr) {
            CLOG(ERROR, mLoggerName.c_str()) << "unable to resolve function deleteModule: function not found";
            THROW_LOGIC_FAULT()<< "unable to resolve function deleteModule: function not found";
        }

        mLibName = _libName;
        mInstanceCounter = 0;
    }

    // **************************************************************************************************
    // ** LibInstance
    // **************************************************************************************************
    LibInstance::~LibInstance()
    {
        CLOG(INFO, mLoggerName.c_str()) << "LibInstance: unload library " << mLibName;
        if (mInstanceCounter > 0) {
            CLOG(ERROR, mLoggerName.c_str()) << "module library " << mLibName << ": not all module instance are deleted, when library is unloaded!";
        }
        dlclose(mHandle);
    }

    // **************************************************************************************************
    // ** createNewInstance
    // **************************************************************************************************
    ModuleInterface*
    LibInstance::createNewInstance(const char* _instanceName,
                                   pugi::xml_node* _configInfo)
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(_instanceName, nullptr);
        VALIDATE_ARGUMENT_NOT_EQUAL(_configInfo, nullptr);
        VALIDATE_ARGUMENT_NOT_EQUAL(mPtCreateFkt, nullptr);

        ModuleInterface* module = mPtCreateFkt(_instanceName, _configInfo);
        if (module == nullptr) {
            THROW_LOGIC_FAULT()<< "lib " << mLibName << ": unable to create module " << _instanceName;
        }
        mInstanceCounter++;
        return (module);
    }

    // **************************************************************************************************
    // ** deleteInstance
    // **************************************************************************************************
    void
    LibInstance::deleteInstance(ModuleInterface* _module)
    {
        VALIDATE_ARGUMENT_NOT_EQUAL(_module, nullptr);
        VALIDATE_ARGUMENT_NOT_EQUAL(mPtDeleteFkt, nullptr);

        mPtDeleteFkt(_module);
        mInstanceCounter--;
    }

    // **************************************************************************************************
    // ** getInstanceCount
    // **************************************************************************************************
    uint32_t
    LibInstance::getInstanceCount()
    {
        return (mInstanceCounter);
    }

    // **************************************************************************************************
    // ** getName
    // **************************************************************************************************
    std::string
    LibInstance::getName()
    {
        return (mLibName);
    }

} /* namespace GaAppBaseLib */
