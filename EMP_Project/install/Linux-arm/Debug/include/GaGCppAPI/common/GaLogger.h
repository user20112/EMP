/*
 * GaLogger.h
 *
 *  Created on: 08.12.2014
 *      Author: s.hegemann
 */

/**
 * @file GaLogger.h
 * @short contain definition of class \c GaGCppAPI::GaLogger
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_GALOGGER_H_
#define CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_GALOGGER_H_

// System header
#include <sstream>

// external library header
#include "gacommon/common.h"

// local library header


namespace GaGCppAPI {

    /**
     *  @short logger wrapper class. receive messages as stream and forward these to gamma logger
     */
    class GaLogger
    {
        public:

            /**
             * @short type definition for logger manipulator
             * @param _ins instance to logger
             * @return instance to logger
             */
            typedef GaLogger& (*GaLoggerManipulator)(GaLogger& _ins);

            /**
             * @short create a new logger with level
             *
             * __List of known level__
             *  * gc_LOG_SEVERITY_INFO
             *  * gc_LOG_SEVERITY_WARNING
             *  * gc_LOG_SEVERITY_ERROR
             *
             *  further information can be found in gamma API documentation
             *
             * @param _level logging level
             */
            GaLogger(gc_LogSeverity _level);

            /**
             * @short clean up
             */
            virtual ~GaLogger();

            /**
             * @short (operator <<) receive a value and forward this to gamma logger
             * @param _value
             * @return reference to logger
             */
            template <typename T>
            GaLogger&
            operator << (T& _value);

            /**
             * @short (operator <<) for internal logger manipulator
             * @param _manip function pointer for manipulator
             * @return reference to logger
             */
            GaLogger&
            operator<<(GaLoggerManipulator _manip);

            /**
             * @short manipulator \c endl . Is used to send message to gamma service
             * @param _ins instance to logger
             * @return reference to logger
             */
            static GaLogger&
            endl(GaLogger& _ins);
        private:
            /**
             * @short temporary buffer for input stream
             */
            std::stringstream mBuffer;

            /**
             * @short level for messages
             */
            gc_LogSeverity mLevel;
    };

    // **************************************************************************************************
    // ** operator <<
    // **************************************************************************************************
    template <typename T>
    GaLogger&
    GaLogger::operator << (T& _value)
    {
        mBuffer << _value;
        return (*this);
    }

} /* namespace GaGCppAPI */

#endif /* CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_GALOGGER_H_ */
