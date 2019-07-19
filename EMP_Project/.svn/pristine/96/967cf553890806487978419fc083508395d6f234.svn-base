/**
 * @file ModuleInstance.h
 * @short contain definition of class \c GaAppBaseLib::ModuleInstance
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_MODULEINSTANCE_H_
#define SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_MODULEINSTANCE_H_

// System header

// external library header
#include "pugixml.hpp"

// library header
#include "ModuleInterface/ModuleInterface.h"
#include "ModuleInterface/LibInstance.h"

namespace GaAppBaseLib {

    /**
     * @short class \c ModuleInstance wrapped the instance pointer to an external application module derived from \c GaAppBaseLib::ModuleInterface
     *
     * To create a ModuleInstance a \c GaAppBaseLib::LibInstance is needed. From this library the function \c createNewInstance is called.
     * System calls are forwarded to the external module.
     */
    class ModuleInstance
    {
        public:
            /**
             * @short create a new external module by using library \param _lib
             * @param _lib LibInstance of external library
             * @param _instanceName name of module instance
             * @param _configNode pointer to module configuration node
             */
            ModuleInstance(tShdPtLibInstnace& _lib,
                           std::string& _instanceName,
                           pugi::xml_node& _configNode);

            /**
             * @short destructor, this will also destroy the external module
             */
            virtual ~ModuleInstance();

            /**
             * @short request name of module instance
             * @return name of module instance
             */
            std::string
            getName();

            /**
             * @short request used external library instance reference
             * @return external library instance reference
             */
            tShdPtLibInstnace&
            getLibInstance();

            /**
             * @short call function \c prepareStart from external module
             */
            void
            prepareStart();

            /**
             * @short call function \c cleanUp from external module
             */
            void
            cleanUp();

            /**
             * @short call function \c execCommand from external module
             * @param _cmdLine command to be executed
             */
            void
            execCommand (std::string& _cmdLine);

        private:
            tShdPtLibInstnace mLibInstance;     ///< @short used library instance
            std::string mInstanceName;          ///< @short name of created module
            pugi::xml_node& mConfigNode;        ///< @short pointer to xml configuration node

            ModuleInterface* instance;          ///< @short pointer to external module
    };

    /**
     * @short type definition to keep \c ModuleInstance as \c std::shared_ptr
     */
    typedef std::shared_ptr<ModuleInstance> sptModuleInterface;

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_MODULEINSTANCE_H_ */
