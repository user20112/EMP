/**
 * @file ModuleVersionInfo.template.cpp
 * @short contain declaration of class \c SkeletonModule methods
 *
 * @remark
 * This file is only a template and will be updated during compilation by SVN program SubWCRev
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */

// System header
#include <sstream>
#include <iostream>
#include <iomanip>

#include "../include/CognexSerialVersionInfo.h"
#include "Config.h"

// ******************************************************************************************************************
// ***  these defines are generated by SubWCRev and contain all SVN informations
// ******************************************************************************************************************
/**
 * @def SVN_VERSION_AVAILABLE
 * @short is zero, when no SVN information is given, otherwise the revision number is defined
 */
#define SVN_VERSION_AVAILABLE               $WCREV$
/**
 * @def SVN_COMMIT_DATE
 * @short date and time of last commit
 */
#define SVN_COMMIT_DATE                     "$WCDATE=%Y-%m-%d %H:%M$"
/**
 * @def SVN_BUILD_DATE
 * @short date and time of last file update
 */
#define SVN_BUILD_DATE                      "$WCNOW=%Y-%m-%d %H:%M$"
/**
 * @def SVN_REVISION_NO
 * @short latest revision number as string
 */
#define SVN_REVISION_NO                     "$WCREV$"
/**
 * @def SVN_REVISION_RANGE
 * @short range of used revisions
 */
#define SVN_REVISION_RANGE                  "$WCRANGE$"
/**
 * @def SNV_REVISION
 * @short current SVN revision
 */
#define SNV_REVISION                        $WCMIXED?SVN_REVISION_RANGE:SVN_REVISION_NO$
/**
 * @def SVN_LOCAL_MODIFICATIONS
 * @short is true, when local modifications are detected
 */
#define SVN_LOCAL_MODIFICATIONS             $WCMODS?true:false$
/**
 * @def SVN_UNVERSIOND_FILES
 * @short is true, when unversioned files are detected
 */
#define SVN_UNVERSIOND_FILES                $WCUNVER?true:false$
/**
 * @def SVN_TAGGED_VERSION
 * @short is true, when the source is marked as tagged = released version
 */
#define SVN_TAGGED_VERSION                  $WCISTAGGED?true:false$
/**
 * @def SVN_URL
 * @short URL of used SVN repository
 */
#define SVN_URL                             "$WCURL$"

namespace XLSDispenser {

    // **************************************************************************************************
    // ** SkeletonModule
    // **************************************************************************************************
    ModuleVersionInfo::ModuleVersionInfo()
    {
        mLibName = APPLICATION_NAME;
        mBuildDescription = BUILD_DESC;
        mBuildTime = __DATE__;
        mBuildTime += " - ";
        mBuildTime += __TIME__;

        mMajorVersion = VERSION_MAJOR;
        mMinorVersion = VERSION_MINOR;
        mVersionPatch = VERSION_PATCH;
        mVersionTweak = VERSION_TWEAK;

        if ((mMajorVersion > 0xff) || (mMinorVersion > 0xfff) || (mVersionPatch > 0xfff)) {
            std::cerr << "current version information exceeds limit" << std::endl;
            mInternalVersionInfo = 0;
        }
        else {
            mInternalVersionInfo = ((VERSION_MAJOR << 24) | (VERSION_MINOR << 12) | (VERSION_PATCH));
        }

#if defined NDEBUG
        mIsDebugVersion = false;
#else
        mIsDebugVersion = true;
#endif

#if (SVN_VERSION_AVAILABLE > 0)
        mHasSvnInformations = true;

        mSvnRevision = SVN_VERSION_AVAILABLE;
        mSvnRevisionRange = SNV_REVISION;
        mSvnDateCommit = SVN_COMMIT_DATE;
        mSvnBuildDate = SVN_BUILD_DATE;
        mSvnURL = SVN_URL;
        mSvnHasLocalModifications = SVN_LOCAL_MODIFICATIONS;
        mSvnHasUnversionedFiles = SVN_UNVERSIOND_FILES;
        mSvnIsTaggedVersion = SVN_TAGGED_VERSION;
#else
        mHasSvnInformations = false;

        mSvnRevision = 0;
        mSvnRevisionRange = "0";
        mSvnDateCommit = "";
        mSvnBuildDate = mBuildTime;
        mSvnURL = "";
        mSvnHasLocalModifications = true;
        mSvnHasUnversionedFiles = true;
        mSvnIsTaggedVersion = false;
#endif
    }

    // **************************************************************************************************
    // ** ~ModuleVersionInfo
    // **************************************************************************************************
    ModuleVersionInfo::~ModuleVersionInfo()
    {
    }

    // **************************************************************************************************
    // ** getInstance
    // **************************************************************************************************
    ModuleVersionInfo&
    ModuleVersionInfo::getInstance()
    {
        static ModuleVersionInfo instance;
        return (instance);
    }

    // **************************************************************************************************
    // ** getVersionText
    // **************************************************************************************************
    std::string
    ModuleVersionInfo::getVersionText () const
    {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << mMajorVersion << "."
           << std::setw(3) << std::setfill('0') << mMinorVersion << "."
           << std::setw(3) << std::setfill('0') << mVersionPatch
           << (mIsDebugVersion ? " [Debug] " : "")
           << " -- Date of Build: " << mBuildTime;

        return (ss.str());
    }

    // **************************************************************************************************
    // ** printInfo
    // **************************************************************************************************
    void
    ModuleVersionInfo::printInfo(uint32_t _indent /* = 0 */) const
    {
        std::string tab;
        tab.insert(0, _indent, ' ');
        if (mBuildDescription.length() > 0) {
            std::cout << tab << mLibName << " -- " << mBuildDescription << std::endl;
        }
        else {
            std::cout << tab << mLibName << " Version information" << std::endl;
        }

        std::cout << tab << "    Current Version: " << getVersionText() << std::endl;

        if (mHasSvnInformations) {
            std::cout << tab << "    SVN-URL: " << mSvnURL << std::endl
                      << tab << "    Revision " << mSvnRevision
                             << (mSvnHasLocalModifications ? " (including local modifications)" : "")
                             << (mSvnHasUnversionedFiles ? " (including unversioned files)" : "")
                             << (mSvnIsTaggedVersion ? " (Tagged version)" : "")
                             << " committed on " << mSvnDateCommit
                             << std::endl;
        }
        else {
            std::cout << "    No SVN-Information available." << std::endl;
        }
    }

}    // namespace SkeletonModule
