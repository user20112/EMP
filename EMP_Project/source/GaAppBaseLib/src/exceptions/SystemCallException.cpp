/**
 * @file SystemCallException.cpp
 * @short contain declaration of class \c SystemCallException methods
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
#include <cstring>

// external library header

// local library header
#include "exceptions/SystemCallException.h"

namespace GaAppBaseLib {

    // ******************************************************************************************************************
    // ***  SystemCallException
    // ******************************************************************************************************************
    SystemCallException::SystemCallException(const char* _file,
                                             const char* _function,
                                             uint32_t _line,
                                             int _errno,
                                             const std::string& _message) noexcept :
                                                     ExceptionBase (_file, _function, _line, _message),
                                                     mCode (_errno)
    {

    }

    // ******************************************************************************************************************
    // ***  ~SystemCallException
    // ******************************************************************************************************************
    SystemCallException::~SystemCallException() noexcept
    {
    }

    // ******************************************************************************************************************
    // ***  getMessage
    // ******************************************************************************************************************
    const std::string
    SystemCallException::getMessage() const
    {
        std::stringstream message;
        std::string fileName;

        uint32_t fileStartPos = mFile.find_last_of("/\\");
        if (fileStartPos == std::string::npos)
                {
            fileName = mFile;
        }
        else
        {
            fileName = mFile.substr(fileStartPos + 1);
        }

        message << "===============================================================================================================================================\n"
                << "System Fault in " << fileName << " at line " << mLine << "; function " << mFunction << "\n"
                << "            message: " << mMessage << "\n"
                << "            error: " << mCode << " ==> " << strerror(mCode) << "\n"
                << "===============================================================================================================================================" << std::endl;

        return (message.str());
    }

} /* namespace GaAppBaseLib */
