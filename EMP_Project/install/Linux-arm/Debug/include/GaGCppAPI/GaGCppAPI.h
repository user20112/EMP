/**
 * @file GaGCppAPI.h
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
#ifndef SOURCES_LIBS_GAGCPPAPI_INCLUDE_GAGCPPAPI_H_
#define SOURCES_LIBS_GAGCPPAPI_INCLUDE_GAGCPPAPI_H_

// library version information
#include "GaGCppAPIVersionInfo.h"

// additional exceptions and calling macros
#include "exceptions/GammaFaultException.h"

// common gamma informations
#include "common/EventHandler.h"
#include "common/GaService.h"

// process variables
#include "pv/RawPV.h"
#include "pv/TypedPV.h"

// scheduler
#include "scheduler/GaTask.h"

// browsing library
#include "browsing/Browser.h"

#endif /* SOURCES_LIBS_GAGCPPAPI_INCLUDE_GAGCPPAPI_H_ */
