/**
 * @file LibContainer.h
 * @short contain definition of class \c GaAppBaseLib::LibContainer
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_LIBCONTAINER_H_
#define SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_LIBCONTAINER_H_

// System header
#include <string>
#include <map>

#include "ModuleInterface/LibInstance.h"
#include "ModuleInterface/ModuleInstance.h"
// external library header
#include "pugixml.hpp"

// library header

namespace GaAppBaseLib {

    /**
     * @short container class for loaded module libraries
     * @remark this class is a singelton class. Use \c GaAppBaseLib::LibContainer::getInstance() to get a reference to the global instance.
     */
    class LibContainer
    {
        public:
            /**
             * @short access to global instance
             * @return reference to global class instance
             */
            static LibContainer&
            getInstance();

            /**
             * @short destructor: clean up
             */
            virtual ~LibContainer();

            /**
             * @short load specified library and create a new module instance with given name
             * @param _libName name of library to load
             * @param _instanceName name of instance to create
             * @param _configNode reference to XML Node including configuration informations
             */
            void
            addModuleInstance(std::string _libName,
                              std::string _instanceName,
                              pugi::xml_node& _configNode);

            /**
             * @short remove specified module instance. Will unload library, when no other instance is used
             * @param _instanceName name of instance to remove
             */
            void
            removeModuleInstance(std::string _instanceName);

            /**
             * @short return instance to loaded module
             * @param _instanceName name of instance
             * @return reference to requested module instance
             */
            sptModuleInterface
            getModuleInstance(std::string _instanceName);

            /**
             * @short print list of active modules
             * @param _printVersionInfo when set, the library version information is printed, too.
             */
            void
            printModuleList(bool _printVersionInfo = false);

            /**
             * @short call function \c prepareStart() for all loaded modules
             */
            void
            modulesPrepareStart();

            /**
             * @short call function \c cleanUp() for all loaded modules
             */
            void
            modulesCleanUp();

        protected:
            /**
             * @short load library with name \par _libName and add instance to library list
             * @param _libName name of library to load
             */
            void
            loadLib(std::string _libName);

            /**
             * @short unload library with name \par _libName and remove instance from library list
             * @param _libName name of library to unload
             */
            void
            unloadLib(std::string _libName);

        private:

            /**
             * @short private constructor: use static method \c getInstance to get access.
             */
            LibContainer() noexcept;

            /**
             * @short copy constructor
             * @warning
             * this constructor is not implemented, to protect singelton class
             *
             * @param _other reference of instance to copy
             */
            LibContainer(const LibContainer& _other) = delete;

            /**
             * @short (assignment operator): copy operator
             * @warning
             * this operator is not implemented, to protect singelton class
             *
             * @param _other reference of instance to copy
             */
            LibContainer&
            operator =(const LibContainer& _other) = delete;

            std::map<std::string, tShdPtLibInstnace> mLibraryList;          ///< @short list of loaded libraries
            std::map<std::string, sptModuleInterface> mModuleList;      ///< @short list of active module instances

    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_MODULEINTERFACE_LIBCONTAINER_H_ */
