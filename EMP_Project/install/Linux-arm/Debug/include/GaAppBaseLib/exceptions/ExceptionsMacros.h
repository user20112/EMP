/**
 * @file ExceptionsMacros.h
 * @short contain macros for throwing several exceptions with predefined parameter
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONSMACROS_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONSMACROS_H_

// System header

// external library header

// local library header
#include "ArgumentFaultException.h"
#include "LogicFaultException.h"
#include "SystemCallException.h"

/**
 * @short check given pointer for \c nullptr and throw exception GaAppBaseLib::ArgumentFaultException when true
 */
#define VALIDATE_ARGUMENT_NO_NULL_PT(_arg) \
            if ((_arg) == nullptr) { \
                throw GaAppBaseLib::ArgumentFaultException(__FILE__, __FUNCTION__, __LINE__, #_arg) << "unexpected null pointer"; \
            }

/**
 * @short throws a GaAppBaseLib::ArgumentFaultException when value \c _arg is less than \c _min or greater \c _max is
 */
#define VALIDATE_ARGUMENT_RANGE_INCLUDE(_arg, _min, _max) \
            if (((_arg) < (_min)) || ((_arg) > (_max))) { \
                throw GaAppBaseLib::ArgumentFaultException(__FILE__, __FUNCTION__, __LINE__, #_arg) << "value out of range: (" << #_min << ": " << (_min) << ") <= " << (_arg) << " <= (" << #_max << ": " << (_max) << ")"; \
            }

/**
 * @short throws a GaAppBaseLib::ArgumentFaultException when value \c _arg is less than or equal to \c _min or greater than or equal to \c _max is
 */
#define VALIDATE_ARGUMENT_RANGE_EXCLUDE(_arg, _min, _max) \
            if (((_arg) <= (_min)) || ((_arg) >= (_max))) { \
                throw GaAppBaseLib::ArgumentFaultException(__FILE__, __FUNCTION__, __LINE__, #_arg) << "value out of range: (" << #_min << ": " << (_min) << ") < " << (_arg) << " < (" << #_max << ": " << (_max) << ")"; \
            }

/**
 * @short throws a GaAppBaseLib::ArgumentFaultException when value \c _arg is not equal to \c _value
 */
#define VALIDATE_ARGUMENT_EQUAL(_arg, _value) \
            if ((_arg) != (_value)) { \
                throw GaAppBaseLib::ArgumentFaultException(__FILE__, __FUNCTION__, __LINE__, #_arg) << "value is \"" << (_arg) << "\", but \"" << #_value << "\" (" << (_value) << ") was expected"; \
            }

/**
 * @short throws a GaAppBaseLib::ArgumentFaultException when value \c _arg is equal to \c _value
 */
#define VALIDATE_ARGUMENT_NOT_EQUAL(_arg, _value) \
            if ((_arg) == (_value)) { \
                throw GaAppBaseLib::ArgumentFaultException(__FILE__, __FUNCTION__, __LINE__, #_arg) << "value has invalid value: \"" << (_arg) << "\" (" << #_value << ")"; \
            }

/**
 * @short throws an exception, when a logical error occurs.
 */
#define THROW_LOGIC_FAULT() \
            throw GaAppBaseLib::LogicFaultException(__FILE__, __FUNCTION__, __LINE__)

/**
 * @short throws an exception, when a system call failed.
 */
#define THROW_SYSTEM_FAULT() \
            throw GaAppBaseLib::SystemCallException(__FILE__, __FUNCTION__, __LINE__, errno)

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_EXCEPTIONS_EXCEPTIONSMACROS_H_ */
