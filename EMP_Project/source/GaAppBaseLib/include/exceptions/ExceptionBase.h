/**
 * @file ExceptionBase.h
 * @short contain definition of class \c GaAppBaseLib::ExceptionBase
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONBASE_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONBASE_H_

// System header
#include <exception>
#include <string>
#include <sstream>

// external library header

// local library header

namespace GaAppBaseLib {

    /**
     * @short base class for exception used in this library
     */
    class ExceptionBase: public std::exception
    {
        public:
            /**
             * @short default constructor
             * @param _file current file name as string. Use __FILE__ for default. The path will be truncated!
             * @param _function current function as string. Use __FUNCTION__ for default.
             * @param _line line in current file. Use __LINE__ for default.
             * @param _message a user defined message with further details.
             */
            ExceptionBase(const char* const _file,
                          const char* const _function,
                          uint32_t _line,
                          const std::string& _message) noexcept;

            /**
             * @short clean up
             */
            virtual
            ~ExceptionBase() noexcept;

            /**
             * @short get exception message
             * @return formated message string
             */
            virtual const char*
            what() const noexcept;

            /**
             * @short enable usage of ostreams in exceptions. given stream will be append to the formated message.
             * @param _os used output stream
             * @param _e exception for output
             * @return reference to used output stream
             */
            friend std::ostream&
            operator<<(std::ostream& _os,
                       const ExceptionBase& _e)
            {
                _os << _e.getMessage();
                return (_os);
            }

        protected:
            /**
             * @short create a formated message string
             * @return formated message string
             */
            virtual const std::string
            getMessage() const = 0;

            std::string mFile;          ///< @short filename, where exception is thrown
            std::string mFunction;      ///< @short function name, where exception is thrown
            uint32_t mLine;             ///< @short line number, where exception is thrown
            std::string mMessage;       ///< @short user message
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONBASE_H_ */
