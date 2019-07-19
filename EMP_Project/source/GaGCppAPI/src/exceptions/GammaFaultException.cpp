/*
 * GammaFaultException.cpp
 *
 *  Created on: 04.12.2014
 *      Author: s.hegemann
 */

#include "exceptions/GammaFaultException.h"

namespace GaGCppAPI {

    // ******************************************************************************************************************
    // ***  GammaFaultException
    // ******************************************************************************************************************
    GammaFaultException::GammaFaultException(const char* _file,
                                             const char* _function,
                                             uint32_t _line,
                                             gc_ErrorID _code,
                                             const std::string& _message) noexcept :
                                                     ExceptionBase (_file, _function, _line, _message),
                                                     mCode (_code)
    {

    }

    // ******************************************************************************************************************
    // ***  ~GammaFaultException
    // ******************************************************************************************************************
    GammaFaultException::~GammaFaultException() noexcept
    {
    }

    // ******************************************************************************************************************
    // ***  getMessage
    // ******************************************************************************************************************
    const std::string
    GammaFaultException::getMessage() const
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
                << "Gamma Fault in " << fileName << " at line " << mLine << "; function " << mFunction << "\n"
                << "            message: " << mMessage << "\n"
                << "            error: " << mCode << " ==> " << gc_getErrorDescription(mCode) << "\n"
                << "===============================================================================================================================================" << std::endl;

        return (message.str());
    }

} /* namespace GaGCppAPI */
