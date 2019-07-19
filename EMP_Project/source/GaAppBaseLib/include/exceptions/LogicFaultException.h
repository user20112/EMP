/**
 * @file LogicFaultException.h
 * @short contain definition of class \c GaAppBaseLib::LogicFaultException
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB__EXCEPTIONS_INCLUDE_LOGICFAULTEXCEPTION_H_
#define SOURCE_GAAPPBASELIB__EXCEPTIONS_INCLUDE_LOGICFAULTEXCEPTION_H_

// System header

// external library header

// local library header
#include "exceptions/ExceptionBase.h"

namespace GaAppBaseLib {

    /**
     * @short exception is thrown, when a logic error occurred
     */
    class LogicFaultException: public ExceptionBase
    {
        public:
            /**
             * @short constructor
             * @param _file current file name as string. Use __FILE__ for default. The path will be truncated!
             * @param _function current function as string. Use __FUNCTION__ for default.
             * @param _line line in current file. Use __LINE__ for default.
             * @param _message a user defined message with further details.
             */
            LogicFaultException(const char* const _file,
                                const char* const _function,
                                uint32_t _line,
                                const std::string& _message = std::string()) noexcept;

            /**
             * @short clean up
             */
            virtual
            ~LogicFaultException() noexcept;

            /**
             * @short [operator <<]: add string to message (usage like a ostream)
             * @param _value value to add to message
             * @return reference to the exception
             */
            template<typename T>
            LogicFaultException&
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
             * @return formated message
             */
            virtual const std::string
            getMessage() const;
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GAAPPBASELIB__EXCEPTIONS_INCLUDE_LOGICFAULTEXCEPTION_H_ */
