/**
 * @file logger.h
 * @short wrapping external source easylogging++.h
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_LOG_LOGGER_H_
#define SOURCE_GaAppBaseLib_INCLUDE_LOG_LOGGER_H_

/*
 * **************************************************************************************************
 *  logger setup
 * **************************************************************************************************
 *    here are all compiler depending setting for easylogger++
 *    remove comment to activate flag.
 */
// #define ELPP_DEBUG_ASSERT_FAILURE               ///< @short Aborts application on first assertion failure. This assertion is due to invalid input e.g, invalid configuration file etc.
// #define ELPP_UNICODE                            ///< @short Enables Unicode support when logging. Requires  START_EASYLOGGINGPP
// #define ELPP_THREAD_SAFE                        ///< @short Enables thread-safety - make sure -lpthread linking for linux.
// #define ELPP_FORCE_USE_STD_THREAD               ///< @short Forces to use C++ standard library for threading (Only useful when using  ELPP_THREAD_SAFE
#define ELPP_STACKTRACE_ON_CRASH                ///< @short Applicable to GCC only. Enables stacktrace on application crash
// #define ELPP_DISABLE_DEFAULT_CRASH_HANDLING     ///< @short  Disables default crash handling. You can use el::Helpers::setCrashHandler to use your own handler.
// #define ELPP_DISABLE_LOGS                       ///< @short Disables all logs - (preprocessing)
// #define ELPP_DISABLE_DEBUG_LOGS                 ///< @short Disables debug logs - (preprocessing)
// #define ELPP_DISABLE_INFO_LOGS                  ///< @short Disables info logs - (preprocessing)
// #define ELPP_DISABLE_WARNING_LOGS               ///< @short Disables warning logs - (preprocessing)
// #define ELPP_DISABLE_ERROR_LOGS                 ///< @short Disables error logs - (preprocessing)
// #define ELPP_DISABLE_FATAL_LOGS                 ///< @short Disables fatal logs - (preprocessing)
// #define ELPP_DISABLE_VERBOSE_LOGS               ///< @short Disables verbose logs - (preprocessing)
// #define ELPP_DISABLE_TRACE_LOGS                 ///< @short Disables trace logs - (preprocessing)
// #define ELPP_FORCE_ENV_VAR_FROM_BASH            ///< @short If environment variable could not be found, force using alternative bash command to find value, e.g,  whoami  for username. (DO NOT USE THIS MACRO WITH  LD_PRELOAD  FOR LIBRARIES THAT ARE ALREADY USING Easylogging++ OR YOU WILL END UP IN STACK OVERFLOW FOR PROCESSES ( popen ) (see issue #87 for details))
// #define ELPP_DEFAULT_LOG_FILE                   ///< @short Full filename where you want initial files to be created. You need to embed value of this macro with quotes, e.g,  -DELPP_DEFAULT_LOG_FILE='"logs/el.gtest.log"'  Note the double quotes inside single quotes, double quotes are the values for  const char*  and single quotes specifies value of macro
// #define ELPP_NO_DEFAULT_LOG_FILE                ///< @short If you dont want to initialize library with default log file, define this macro. But be sure to configure your logger with propery log filename or you will end up getting heaps of errors when trying to log to file (and  TO_FILE  is configured to  true )
// #define ELPP_DEBUG_ERRORS                       ///< @short If you wish to find out internal errors raised by Easylogging++ that can be because of configuration or something else, you can enable them by defining this macro. You will get your errors on standard output i.e, terminal or command prompt.
// #define ELPP_DISABLE_CUSTOM_FORMAT_SPECIFIERS   ///< @short Forcefully disables custom format specifiers
// #define ELPP_DISABLE_LOGGING_FLAGS_FROM_ARG     ///< @short Forcefully disables ability to set logging flags using command-line arguments
// #define ELPP_DISABLE_LOG_FILE_FROM_ARG          ///< @short Forcefully disables ability to set default log file from command-line arguments
// #define ELPP_WINSOCK2                           ///< @short On windows system force to use  winsock2.h  instead of  winsock.h  when  WIN32_LEAN_AND_MEAN  is defined

#include "log/easylogging++.h"

#define _QUOTEME(x) #x

#endif /* SOURCE_GaAppBaseLib_INCLUDE_LOG_LOGGER_H_ */
