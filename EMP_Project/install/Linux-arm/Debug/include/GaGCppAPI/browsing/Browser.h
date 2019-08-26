/**
 * @file Browser.h
 * @short contain definition of class \c GaGCppAPI::Browser
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSER_H_
#define SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSER_H_

// System header
#include <vector>

// external library header

// local library header
#include "pv/SharedPV.h"
#include "BrowserFilter.h"

namespace GaGCppAPI {

    /**
     * @short class for browsing gamma data model
     */
    class Browser
    {
        public:
            /**
             * @short constructor
             */
            Browser();

            /**
             * @short destructor
             */
            virtual ~Browser();

            /**
             * @short search for PV's in gamma data model and create a vector with all matching PV's
             * @remark
             *   The result list contains SharedPV. There is no type casting now.
             *
             * @param _filter Filter settings for browsing
             * @return list of matching PV's
             */
            std::vector<SharedPV>
            findPVs(BrowserFilter& _filter);

        private:
            /**
             * @short read gamma browsing information
             *
             * @remark
             * see Gamma API reference, chapter gaapi/browsing.h for further details
             *
             * @param _type type of data to search for
             * @param _params address of type
             * @return list of browsing result
             */
            std::vector<gc_BrowserInfo>
            browseInfo(const gc_BrowsingType _type,
                       gc_Level6Address _params);

    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSER_H_ */
