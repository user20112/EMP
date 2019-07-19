/**
 * @file GammaFaultException.h
 * @short contain definition of class \c GaGCppAPI::GammaFaultException
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_EXCEPTIONS_INCLUDE_GAMMAFAULTEXCEPTION_H_
#define SOURCE_GAGCPPAPI_EXCEPTIONS_INCLUDE_GAMMAFAULTEXCEPTION_H_

// System header

// external library header
#include "gacommon/errorCodes.h"
#include "exceptions/ExceptionBase.h"

// local library header

/**
 * @short throws an exception, when a gamma api call failed.
 * @param _errorID gamma call return value
 */
#define THROW_GAMMA_FAULT(_errorID) \
            throw GaGCppAPI::GammaFaultException(__FILE__, __FUNCTION__, __LINE__, _errorID)

namespace GaGCppAPI {

    /**
     * @short exception is thrown, when a gamma API call failed. Can convert the gamma error code to a message string.
     */
    class GammaFaultException: public GaAppBaseLib::ExceptionBase
    {
        public:
            /**
             * @short constructor
             * @param _file current file name as string. Use __FILE__ for default. The path will be truncated!
             * @param _function current function as string. Use __FUNCTION__ for default.
             * @param _line line in current file. Use __LINE__ for default.
             * @param _code gamma error code
             * @param _message a user defined message with further details.
             */
            GammaFaultException(const char* const _file,
                                const char* const _function,
                                uint32_t _line,
                                gc_ErrorID _code,
                                const std::string& _message = std::string()) noexcept;

            /**
             * @short clean up
             */
            virtual
            ~GammaFaultException() noexcept;

            /**
             * @short [operator <<]: add string to message (usage like a ostream)
             * @param _value value to add to message
             * @return reference to the exception
             */
            template<typename T>
            GammaFaultException&
            operator<<(const T& _value)
            {
                std::stringstream m;
                m << _value;
                mMessage += m.str();
                return (*this);
            }

        private:
            /**
             * @short create a formated string for output.
             * @return formarted message
             */
            const std::string
            getMessage() const;

            /**
             * @short gamma error code
             */
            gc_ErrorID mCode;
    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_EXCEPTIONS_INCLUDE_GAMMAFAULTEXCEPTION_H_ */
