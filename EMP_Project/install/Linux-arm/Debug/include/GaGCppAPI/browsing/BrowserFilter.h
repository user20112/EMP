/**
 * @file BrowserFilter.h
 * @short contain definition of class \c GaGCppAPI::BrowserFilter
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSERFILTER_H_
#define SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSERFILTER_H_

// System header
#include <string>

// external library header

// local library header
#include "pv/SharedPV.h"


namespace GaGCppAPI {

    /**
     * @short class contains several filter settings for browsing gamma PV's
     *
     * use \c add(type, filter) to add a new filter. Filter for each type, that is added to the filter, has to fit, several expressions for one filter type are linked by 'OR'
     *
     * @remark
     * The given expression is read as an regular expression.
     */
    class BrowserFilter
    {
        public:
            /**
             * @short list of filter types.
             *
             * @warning
             * currently following filter types are not implemented yet:
             * - PV_Type
             * - Property_Type
             * - Property_Name_And_Value
             */
            enum FilterType: size_t {
                System = 0,             ///< @short search for a specific system name or use "[[local]]" for local system
                Node,                   ///< @short search for node name
                Memory,                 ///< @short search for memory name
                Group,                  ///< @short search for group name
                PV_Name,                ///< @short search for pv name
                PV_Type,                ///< @short search for pv type
                Property_Type,          ///< @short search for property type
                Property_Name,          ///< @short search for property name
                Property_Name_And_Value,///< @short search for property with given name and value

                // this is always the last entry!
                FILTER_TYPE_COUNT       ///< @short count of known filter types
            };

            /**
             * @short constructor
             */
            BrowserFilter();

            /**
             * @short destructor
             */
            virtual
            ~BrowserFilter();

            /**
             * @short add a filter expression.
             *
             * @remark
             * when an expression is already specified for the given type, the expressions will be linked by "OR"
             *
             * @param _type filter type
             * @param _expression regular expression
             */
            void
            add(FilterType _type, std::string _expression);

            /**
             * @short clear a filter type expression and disable filtering for given type.
             * @param _type type of filter to remove.
             */
            void
            remove(FilterType _type);

            /**
             * @short request current filter expression for a specific type
             * @param _type requested filter type
             * @return current filter expression as string or "[[inactive]]" when filter type is not used.
             */
            std::string
            getFilterExpression(FilterType _type);

            /**
             * @short clear all filter settings
             */
            void
            clear();

            /**
             * @short check if _value fits given filter type.
             *
             * @remark
             * this function can only be used with following filter types:
             * - FilterType::System
             * - FilterType::Node
             * - FilterType::Memory
             * - FilterType::Group
             * - FilterType::PV_Name
             *
             * @param _type filter type to check
             * @param _value value to check as string
             * @return true, when value fit filter type or filter type is not active, otherwise false.
             */
            bool
            fit (FilterType _type, std::string _value);

            /**
             * @short check if _value fits given filter type.
             *
             * @remark
             * this function can only be used with following filter types:
             * - FilterType::PV_Type
             *
             * @param _type filter type to check
             * @param _DataType PV data type to check
             * @return true, when value fit filter type or filter type is not active, otherwise false.
             */
            bool
            fit (FilterType _type, gc_DataType _DataType);

            /**
             * @short check if _value fits given filter type.
             *
             * @remark
             * this function can only be used with following filter types:
             * - FilterType::Property_Type
             * - FilterType::Property_Name
             * - FilterType::Property_Name_And_Value
             *
             * @param _type filter type to check
             * @param _pv PV instance to check
             * @return true, when value fit filter type or filter type is not active, otherwise false.
             */
            bool
            fit (FilterType _type, SharedPV _pv);

        private:
            bool            mFilterUsed[FilterType::FILTER_TYPE_COUNT];         ///< @short flags, which filter is used
            std::string     mFilterExpression[FilterType::FILTER_TYPE_COUNT];   ///< @short list of active filter expressions
    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_INCLUDE_BROWSING_BROWSERFILTER_H_ */
