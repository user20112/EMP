/**
 * @file LibInstance.h
 * @short contain definition of class \c GaAppBaseLib::LibInstance
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_LIBINSTANCE_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_LIBINSTANCE_H_

// System header
#include <memory>

// external library header

// library header
#include "ModuleInterface/ModuleInterface.h"

namespace GaAppBaseLib {

    /**
     * @short function pointer definition for imported function createModule
     * @param _instanceName name of module instance
     * @param _configInfo pointer to xml configuration node for module setup
     * @return pointer to created instance
     */
    typedef GaAppBaseLib::ModuleInterface* (*tFctPtCreateModule)(const char* _instanceName, pugi::xml_node* _configInfo);

    /**
     * @short function pointer definition for imported function deleteModule
     * @param _module pointer to module instance, witch should be destroyed
     */
    typedef void (*tFctPtDeleteModule)(GaAppBaseLib::ModuleInterface* _module);

    /**
     * @short container class for library instance.
     *
     * this class load a shared library, and keep handle until the instance is deleted.
     *
     * to create a new module from loaded library call \c LibInstance::createNewInstance . Each created instance need to deleted by
     * calling \c deleteInstance . The count of actual existing instances can be requested by calling \c getInstanceCount
     */
    class LibInstance
    {
        public:
            /**
             * @short constructor. will load library \param _libName
             * @param _libName name of library to load (without default file name extensions)
             */
            LibInstance(std::string _libName);

            /**
             * @short destructor. will unload external library.
             */
            virtual ~LibInstance();

            /**
             * @short calling function createModule from loaded library
             * @param _instanceName name of instance to create
             * @param _configInfo pointer to xml configuration node
             * @return pointer to created module
             */
            ModuleInterface*
            createNewInstance(const char* _instanceName,
                              pugi::xml_node* _configInfo);

            /**
             * @short destroy created module by calling library function deleteModule
             * @param _module pointer to module witch should be deleted
             */
            void
            deleteInstance(ModuleInterface* _module);

            /**
             * @short request count of existing modules
             * @return count of existing modules
             */
            uint32_t
            getInstanceCount();

            /**
             * @short request name of loaded library
             * @return name of loaded library
             */
            std::string
            getName();

        private:
            std::string mLibName;                   ///< @short library name

            void* mHandle;                          ///< @short handle to library instance
            tFctPtCreateModule mPtCreateFkt;        ///< @short function pointer to imported function createModule
            tFctPtDeleteModule mPtDeleteFkt;        ///< @short function pointer to imported function deleteModule

            uint32_t mInstanceCounter;              ///< @short counter for active modules, depending on internal library
    };

    /**
     * @short type definition to keep \c LibInstance as \c std::shared_ptr
     */
    typedef std::shared_ptr<LibInstance> tShdPtLibInstnace;

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_MODULEINTERFACE_LIBINSTANCE_H_ */
