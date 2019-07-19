/**
 * @file AppConfig.cpp
 * @short contain declaration of class \c AppControl methods
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

// application header
#include "AppConfig.h"

// ******************************************************************************************************************
// ***  AppControl
// ******************************************************************************************************************
AppControl::AppControl()
        : mModuleContainer(GaAppBaseLib::LibContainer::getInstance())
{
    mFileLoaded = false;
    el::Loggers::getLogger("AppControl");
}

// ******************************************************************************************************************
// ***  ~AppControl
// ******************************************************************************************************************
AppControl::~AppControl()
{
    if (!mConfigFile.save_file(mConfigFileName.c_str())) {
        CLOG(ERROR, "AppControl") << "AppConfig: writing configuration " << mConfigFileName << " failed!";
    }
}

// ******************************************************************************************************************
// ***  loadConfigFile
// ******************************************************************************************************************
void
AppControl::loadConfigFile(std::string _configFileName)
{
    CLOG(INFO, "AppControl") << "Load Application Configuration file " << _configFileName;
    mConfigFileName = _configFileName;

    pugi::xml_parse_result result = mConfigFile.load_file(mConfigFileName.c_str());
    if (result == false) {
        THROW_LOGIC_FAULT() << "unable to load XML File " << _configFileName << ": reason: " << result.description();
    }

    mFileLoaded = true;
}

// ******************************************************************************************************************
// ***  loadModules
// ******************************************************************************************************************
void
AppControl::loadModules()
{
    if (!mFileLoaded) {
        THROW_LOGIC_FAULT() << "load a configuration file before create modules!";
    }

    pugi::xpath_node_set tools = mConfigFile.select_nodes("/AppConfig/ModuleList/Module");

    CLOG(INFO, "AppControl") << "Load Modules from configuration file";

    for (pugi::xpath_node_set::const_iterator it = tools.begin(); it != tools.end(); ++it)
    {
        pugi::xml_node node = it->node();
        if ((node.attribute("name").empty()) || (node.attribute("library").empty())) {
            continue;
        }
        CLOG(DEBUG, "AppControl") << "  => module " << node.attribute("name").value() << " of type " << node.attribute("library").value() << "\n";
        mModuleContainer.addModuleInstance(node.attribute("library").value(), node.attribute("name").value(), node);
    }
    CLOG(INFO, "AppControl") << "Load Modules done.";
}

// ******************************************************************************************************************
// ***  prepareStart
// ******************************************************************************************************************
void
AppControl::prepareStart()
{
    mModuleContainer.modulesPrepareStart();
}

// ******************************************************************************************************************
// ***  cleanUp
// ******************************************************************************************************************
void
AppControl::cleanUp()
{
    mModuleContainer.modulesCleanUp();
}

// ******************************************************************************************************************
// ***  sendCommand
// ******************************************************************************************************************
void
AppControl::sendCommand(std::string& _moduleName,
                        std::string& _commandLine)
{
    try {
        mModuleContainer.getModuleInstance(_moduleName)->execCommand(_commandLine);
    }
    catch (GaAppBaseLib::ExceptionBase &e) {
        CLOG(ERROR, "AppControl") << "\n" << e.what();
    }
    catch (std::out_of_range &e) {
        CLOG(WARNING, "AppControl") << "unknown module " << _moduleName;
    }
    catch (std::exception &e) {
        CLOG(ERROR, "AppControl") << "calling command interface for module " << _moduleName << " failed: \n" << e.what();
    }
    catch (...) {
        CLOG(ERROR, "AppControl") << "calling command interface for module " << _moduleName << " failed: reason unknown";
    }
}

// ******************************************************************************************************************
// ***  printModuleList
// ******************************************************************************************************************
void
AppControl::printModuleList(bool _printVersionInfo /* = false */)
{
    mModuleContainer.printModuleList(_printVersionInfo);
}
