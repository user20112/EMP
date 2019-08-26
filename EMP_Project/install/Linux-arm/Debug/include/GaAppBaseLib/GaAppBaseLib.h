/**
 * @file GaAppBaseLib.h
 * @short container for all library include files. Can be used by external programs or libraries
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAAPPBASELIB_INCLUDE_GAAPPBASELIB_H_
#define SOURCE_GAAPPBASELIB_INCLUDE_GAAPPBASELIB_H_

// library version information
#include "GaAppBaseLibVersionInfo.h"

// logging system
#include "log/logger.h"

// additional exceptions and calling macros
#include "exceptions/ExceptionsMacros.h"

// dynamic module interface
#include "ModuleInterface/LibContainer.h"
#include "ModuleInterface/ModuleInterface.h"

// network functions
#include "network/NetworkHelper.h"
#include "network/UDPConnection.h"

#endif /* SOURCE_GAAPPBASELIB_INCLUDE_GAAPPBASELIB_H_ */
