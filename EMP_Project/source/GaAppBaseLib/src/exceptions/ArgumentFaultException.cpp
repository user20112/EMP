/**
 * @file ArgumentFaultException.cpp
 * @short contain declaration of class \c ArgumentFaultException methods
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
#include "exceptions/ArgumentFaultException.h"

namespace GaAppBaseLib {

    // ******************************************************************************************************************
    // ***  ArgumentFaultException
    // ******************************************************************************************************************
    ArgumentFaultException::ArgumentFaultException(const char* _file,
                                                   const char* _function,
                                                   uint32_t _line,
                                                   const char* const _argName,
                                                   const std::string& _message) noexcept:
                                                           ExceptionBase (_file, _function, _line, _message),
                                                           mArgumentName (_argName)
    {

    }

    // ******************************************************************************************************************
    // ***  ~ArgumentFaultException
    // ******************************************************************************************************************
    ArgumentFaultException::~ArgumentFaultException() noexcept
    {
    }

    // ******************************************************************************************************************
    // ***  getMessage
    // ******************************************************************************************************************
    const std::string
    ArgumentFaultException::getMessage() const
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
                << "Invalid Argument in " << fileName << " at line " << mLine << "; function " << mFunction << "\n"
                << "                 argument: " << mArgumentName << "\n"
                << "                 message: " << mMessage << "\n"
                << "===============================================================================================================================================" << std::endl;

        return (message.str());
    }
} /* namespace GaAppBaseLib */
