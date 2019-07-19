/**
 * @file LibContainer.cpp
 * @short contain declaration of class \c LibContainer methods
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
#include "ModuleInterface/LibContainer.h"

#include <iostream>

// external library header

// application header
#include "ModuleInterface/ModuleInstance.h"
#include "ModuleInterface/ModuleInterface.h"

namespace GaAppBaseLib {

    // **************************************************************************************************
    // ** LibContainer
    // **************************************************************************************************
    LibContainer::LibContainer() noexcept
    {
    }

    // **************************************************************************************************
    // ** LibContainer
    // **************************************************************************************************
    LibContainer::~LibContainer()
    {
        mModuleList.clear();
        mLibraryList.clear();
    }

    // **************************************************************************************************
    // ** GetInstance
    // **************************************************************************************************
    LibContainer&
    LibContainer::getInstance()
    {
        static LibContainer instance;
        return (instance);
    }

    // **************************************************************************************************
    // ** addModuleInstance
    // **************************************************************************************************
    void
    LibContainer::addModuleInstance(std::string _libName,
                                    std::string _instanceName,
                                    pugi::xml_node& _configNode)
    {
        if (mLibraryList.count(_libName) == 0) {
            loadLib(_libName);
        }

        sptModuleInterface instance = std::make_shared<ModuleInstance>(mLibraryList.at(_libName), _instanceName, _configNode);
        mModuleList.insert(std::pair<std::string, sptModuleInterface>(_instanceName, instance));
    }

    // **************************************************************************************************
    // ** removeModuleInstance
    // **************************************************************************************************
    void
    LibContainer::removeModuleInstance(std::string _instanceName)
    {
        tShdPtLibInstnace lib = mModuleList[_instanceName]->getLibInstance();
        mModuleList.erase(_instanceName);
        if (lib->getInstanceCount() == 0) {
            unloadLib(lib->getName());
        }

    }

    // **************************************************************************************************
    // ** getModuleInstance
    // **************************************************************************************************
    sptModuleInterface
    LibContainer::getModuleInstance(std::string _instanceName)
    {
        return (mModuleList.at(_instanceName));
    }

    // **************************************************************************************************
    // ** printModuleList
    // **************************************************************************************************
    void
    LibContainer::printModuleList(bool _printVersionInfo /* = false */)
    {
        std::string cmd = "info";
        for (auto module = mModuleList.begin(); module != mModuleList.end(); module++) {
            if (_printVersionInfo) {
                module->second->execCommand(cmd);
            }
            else {
                std::cout << "  " << module->first << " (Type: " << module->second->getLibInstance()->getName() << ")" << std::endl;;
            }
        }
    }

    // **************************************************************************************************
    // ** ModulesPrepareStart
    // **************************************************************************************************
    void
    LibContainer::modulesPrepareStart()
    {
        for (auto module = mModuleList.begin(); module != mModuleList.end(); module++) {
            module->second->prepareStart();
        }
    }

    // **************************************************************************************************
    // ** ModulesCleanUp
    // **************************************************************************************************
    void
    LibContainer::modulesCleanUp()
    {
        for (auto module = mModuleList.begin(); module != mModuleList.end(); module++) {
            module->second->cleanUp();
        }
    }

    // **************************************************************************************************
    // ** loadLib
    // **************************************************************************************************
    void
    LibContainer::loadLib (std::string _libName)
    {
        tShdPtLibInstnace lib = std::make_shared<LibInstance>(_libName);
        mLibraryList.insert(std::pair<std::string, tShdPtLibInstnace>(_libName, lib));
    }

    // **************************************************************************************************
    // ** unloadLib
    // **************************************************************************************************
    void
    LibContainer::unloadLib (std::string _libName)
    {
        mLibraryList.erase(_libName);
    }


} /* namespace GaAppBaseLib */
