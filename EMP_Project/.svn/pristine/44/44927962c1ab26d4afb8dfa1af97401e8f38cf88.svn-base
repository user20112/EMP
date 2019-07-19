/**
 * @file ArgumentFaultException.h
 * @short contain definition of class \c GaAppBaseLib::ArgumentFaultException
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_EXCEPTIONS_ARGUMENTFAULTEXCEPTION_H_
#define SOURCE_GaAppBaseLib_INCLUDE_EXCEPTIONS_ARGUMENTFAULTEXCEPTION_H_

// System header

// external library header

// local library header
#include "exceptions/ExceptionBase.h"

namespace GaAppBaseLib {

    /**
     * @short Exception: is used for parameter validation. Special Parameter is the name of fault argument or member
     */
    class ArgumentFaultException: public ExceptionBase
    {
        public:
            /**
             * @short constructor
             * @param _file current file name as string. Use __FILE__ for default. The path will be truncated!
             * @param _function current function as string. Use __FUNCTION__ for default.
             * @param _line line in current file. Use __LINE__ for default.
             * @param _argName name of validated argument
             * @param _message a user defined message with further details.
             */
            ArgumentFaultException(const char* const _file,
                                   const char* const _function,
                                   uint32_t _line,
                                   const char* const _argName,
                                   const std::string& _message = std::string()) noexcept;

            /**
             * @short clean up
             */
            virtual
            ~ArgumentFaultException() noexcept;

            /**
             * @short [operator <<]: add string to message (usage like a ostream)
             * @param _value value to add to message
             * @return reference to the exception
             */
            template<typename T>
            ArgumentFaultException&
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

            /**
             * @short name of validated argument
             */
            std::string mArgumentName;
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_EXCEPTIONS_ARGUMENTFAULTEXCEPTION_H_ */
