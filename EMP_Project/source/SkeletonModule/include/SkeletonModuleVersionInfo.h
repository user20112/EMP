/**
 * @file SkeletonModuleVersionInfo.h
 * @short contain definition of class \c SkeletonModule::ModuleVersionInfo
 *
 * source is generated during building project and contains build version and date. Additional several SVN parameter can be requested.
 *
 * Version Information
 * -------------------
 * $Revision: 29149 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/include/PlugInVersionInfo.h $
 * $Author: S.Hegemann $
 * $Date: 2014-11-21 18:02:59 +0100 (Fr, 21 Nov 2014) $
 *
 */
#ifndef SOURCE_SKELETONMODULE_INCLUDE_APPVERSIONINFO_H_
#define SOURCE_SKELETONMODULE_INCLUDE_APPVERSIONINFO_H_

// System header
#include <string>

namespace HwAccessDemo {

    /**
     * @short this class contain build informations, library version and SVN parameter
     *
     * @remark
     * this class is a singelton class. Use static method \c SkeletonModule::getInstance() to get access to the
     * included informations.
     */
    class ModuleVersionInfo
    {
        public:
            /**
             * @short access to global instance
             *
             * @return reference to global class instance
             */
            static ModuleVersionInfo&
            getInstance();

            /**
             * @short class destructor
             */
            virtual
            ~ModuleVersionInfo();

            /**
             * @short print version information to stdout
             *
             * The Terminal output contains current Version number and build date. Also Revision and URL of Subversion is printed, when this information is available
             *
             * @param _indent count of blanks add to each ouput line
             */
            void
            printInfo(uint32_t _indent = 0) const;

            /**
             * @short return name of build configuration (CMake Project Name)
             *
             * @return Project Name
             */
            inline const std::string&
            getName() const
            {
                return (mLibName);
            }

            /**
             * @short return date and time of last build as string
             *
             * @return date and time of build run
             */
            inline const std::string&
            getBuildTime() const
            {
                return (mBuildTime);
            }

            /**
             * @short return a Build desctiption. This Information is set in CMakeLists.txt of tis project
             *
             * @return Build description
             */
            inline const std::string&
            getBuildDescription() const
            {
                return (mBuildDescription);
            }

            /**
             * @short return the build version as integer.
             *
             * Building format:
             *
             * | Position   | Version info
             * |------------|----------------
             * | 0xff000000 | Major Version
             * | 0x00fff000 | Minor Version
             * | 0x00000fff | Patch Version
             *
             * @return build version as single integer
             */
            inline uint32_t
            getVersion() const
            {
                return (mInternalVersionInfo);
            }

            /**
             * @short return the major version information [1 .. 255]
             *
             * @return major version
             */
            inline uint32_t
            getMajorVersion() const
            {
                return (mMajorVersion);
            }

            /**
             * @short return the minor version information [1 .. 4095]
             *
             * @return minor version
             */
            inline uint32_t
            getMinorVersion() const
            {
                return (mMinorVersion);
            }

            /**
             * @short return the patch version information [1 .. 4095]
             *
             * @return debug counter
             */
            inline uint32_t
            getPatchVersion() const
            {
                return (mVersionPatch);
            }

            /**
             * @short return the tweak version information
             *
             * @return debug counter
             */
            inline uint32_t
            getTweakVersion() const
            {
                return (mVersionTweak);
            }

            /**
             * @short create the version information as string
             *
             * @return version as string
             */
            std::string
            getVersionText() const;

            /**
             * @short is true, when the current build include debug informations
             *
             * @return true, when this is a debug version
             */
            inline bool
            isDebugVersion() const
            {
                return (mIsDebugVersion);
            }

            /**
             * @short is true, when SVN informations are available
             *
             * @return true, when SVN informations are available
             */
            inline bool
            hasSvnInfo() const
            {
                return (mHasSvnInformations);
            }

            /**
             * @short return the latest revision number as integer
             *
             * @return the latest revision number
             */
            inline uint32_t
            getSvnRevision() const
            {
                return (mSvnRevision);
            }

            /**
             * @short return the range of revisions. Format: [lowest Revision]:[highest Revision]
             *
             * @return range of revisions
             */
            inline const std::string&
            getSvnRevisionRange() const
            {
                return (mSvnRevisionRange);
            }

            /**
             * @short return the source location in SVN as URL
             *
             * @return source URL
             */
            inline const std::string&
            getSvnUrl() const
            {
                return (mSvnURL);
            }

            /**
             * @short return the date and time of the last commit
             *
             * @return date and time of last commit
             */
            inline const std::string&
            getSvnCommitDate() const
            {
                return (mSvnDateCommit);
            }

            /**
             * @short return the date and time of the last update of all svn informations
             *
             * @return date and time of last update
             */
            inline const std::string&
            getSvnBuildDate() const
            {
                return (mSvnBuildDate);
            }

            /**
             * @short is true, when local modifications are done in the builded source code
             *
             * @return true, when uncommited changed are used in this build, otherwise false.
             */
            inline bool
            hasLocalModifications() const
            {
                return (mSvnHasLocalModifications);
            }

            /**
             * @short is set, when the build has files witch are not included to subversion control
             * @return true, when unversioned files are used in this build, otherwise false,
             */
            inline bool
            hasUnversionedFiles() const
            {
                return (mSvnHasUnversionedFiles);
            }

            /**
             * @short is set, when the source of this build is tagged
             * @return true, when the code is marked as tagged, otherwise false
             */
            inline bool
            isTaggedVersion() const
            {
                return (mSvnIsTaggedVersion);
            }

        private:
            /**
             * @short private constructor: use static method \c getInstance to get access.
             */
            ModuleVersionInfo();

            /**
             * @short copy constructor
             * @warning
             * this constructor is not implemented, to protect singelton class
             *
             * @param _other reference of instance to copy
             */
            ModuleVersionInfo(ModuleVersionInfo& _other) = delete;

            /**
             * @short (assignment operator): copy operator
             * @warning
             * this operator is not implemented, to protect singelton class
             *
             * @param _other reference of instance to copy
             */
            ModuleVersionInfo&
            operator =(const ModuleVersionInfo& _other) = delete;

            std::string mLibName;           ///< @short name of library
            std::string mBuildTime;         ///< @short date and time of last build
            std::string mBuildDescription;  ///< @short description given in CMakeLists.txt
            uint32_t mMajorVersion;         ///< @short major version number (see CMakeFile.txt)
            uint32_t mMinorVersion;         ///< @short minor version number (see CMakeFile.txt)
            uint32_t mVersionPatch;         ///< @short patch version number (see CMakeFile.txt)
            uint32_t mVersionTweak;         ///< @short tweak version number (see CMakeFile.txt)
            uint32_t mInternalVersionInfo;  ///< @short internal version number (see \c AppVersionInfo::getVersion() )

            bool mIsDebugVersion;           ///< @short is true, when build include debug informations
            bool mHasSvnInformations;       ///< @short is true, when SVN informations are available

            uint32_t mSvnRevision;          ///< @short svn revision number
            std::string mSvnRevisionRange;  ///< @short svn revision range
            std::string mSvnDateCommit;     ///< @short date and time of last commit
            std::string mSvnBuildDate;      ///< @short date and time of last svn data update
            std::string mSvnURL;            ///< @short URL of SVN repository
            bool mSvnHasLocalModifications; ///< @short is set, when files are changed and committed to the server
            bool mSvnHasUnversionedFiles;   ///< @short is set, when files are not added to the repository
            bool mSvnIsTaggedVersion;       ///< @short is set, when the code is marked as tagged (released version)

    };
}    // namespace SkeletonModule

#endif /* SOURCE_SKELETONMODULE_INCLUDE_APPVERSIONINFO_H_ */
