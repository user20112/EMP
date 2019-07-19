/**
 * @file ExceptionBase.cpp
 * @short contain declaration of class \c ExceptionBase methods
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
#include "exceptions/ExceptionBase.h"

namespace GaAppBaseLib {

    // ******************************************************************************************************************
    // ***  ExceptionBase
    // ******************************************************************************************************************
    ExceptionBase::ExceptionBase(const char* _file,
                                 const char* _function,
                                 uint32_t _line,
                                 const std::string& _message) noexcept:
                                         std::exception (),
                                         mFile (_file),
                                         mFunction (_function),
                                         mLine (_line) ,
                                         mMessage(_message)
    {

    }

    // ******************************************************************************************************************
    // ***  ~ExceptionBase
    // ******************************************************************************************************************
    ExceptionBase::~ExceptionBase() noexcept
    {
    }

    // ******************************************************************************************************************
    // ***  what
    // ******************************************************************************************************************
    const char*
    ExceptionBase::what() const noexcept
    {
        return (getMessage().c_str());
    }

} /* namespace GaAppBaseLib */
