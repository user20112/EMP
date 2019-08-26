/**
 * @file SystemCallException.h
 * @short contain definition of class \c GaAppBaseLib::SystemCallException
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_SYSTEMCALLEXCEPTION_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_SYSTEMCALLEXCEPTION_H_

// System header

// external library header

// local library header
#include "ExceptionBase.h"

namespace GaAppBaseLib {

    /**
     * @short exception is thrown, when a system call failed
     */
    class SystemCallException: public ExceptionBase
    {
        public:
            /**
             * @short constructor
             * @param _file current file name as string. Use __FILE__ for default. The path will be truncated!
             * @param _function current function as string. Use __FUNCTION__ for default.
             * @param _line line in current file. Use __LINE__ for default.
             * @param _errno error code (usually use call \c errno )
             * @param _message a user defined message with further details.
             */
            SystemCallException(const char* const _file,
                                const char* const _function,
                                uint32_t _line,
                                int _errno,
                                const std::string& _message = std::string()) noexcept;

            /**
             * @short clean up
             */
            virtual
            ~SystemCallException() noexcept;

            /**
             * @short [operator <<]: add string to message (usage like a ostream)
             * @param _value value to add to message
             * @return reference to the exception
             */
            template<typename T>
            SystemCallException&
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
            virtual const std::string
            getMessage() const;

            int mCode;  ///< @short given error code
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_SYSTEMCALLEXCEPTION_H_ */
