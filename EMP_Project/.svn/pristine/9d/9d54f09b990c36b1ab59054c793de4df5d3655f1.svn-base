/*
 * BrowserFilter.cpp
 *
 *  Created on: 28.04.2015
 *      Author: s.hegemann
 */
#include <regex>

#include "common/GaService.h"
#include "browsing/BrowserFilter.h"
#include "exceptions/ExceptionsMacros.h"

namespace GaGCppAPI {

    BrowserFilter::BrowserFilter()
    {
        clear();
    }

    BrowserFilter::~BrowserFilter()
    {
        clear();
    }


    void
    BrowserFilter::add(FilterType _type, std::string _expression)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        if (_type ==  FilterType::System) {
            if (_expression == "[[local]]") {
                _expression = GaService::getInstance().getSystemName();
            }
        }

        switch (_type) {
        case FilterType::System:
        case FilterType::Node:
        case FilterType::Memory:
        case FilterType::Group:
        case FilterType::PV_Name:
        case FilterType::Property_Name:
            mFilterUsed[_type] = true;
            if (mFilterExpression[_type].empty()) {
                mFilterExpression[_type] = "(";
            } else {
                mFilterExpression[_type] += "|(";
            }
            mFilterExpression[_type] += _expression;
            mFilterExpression[_type] += ")";
            break;

        case FilterType::PV_Type:
        case FilterType::Property_Type:
        case FilterType::Property_Name_And_Value:
            THROW_LOGIC_FAULT() << "filter is not implemented yet! (Type " << _type << ")";
            break;

        default:
            THROW_LOGIC_FAULT() << "invalid filter type " << _type;
            break;
        }

    }

    std::string
    BrowserFilter::getFilterExpression(FilterType _type)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        std::string expr;
        if (mFilterUsed[_type]) {
            expr = mFilterExpression[_type];
        }
        else {
            expr = "[[inactive]]";
        }
        return (std::move(expr));
    }

    void
    BrowserFilter::remove(FilterType _type)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        mFilterUsed[_type] = false;
        mFilterExpression[_type].clear();
    }

    void
    BrowserFilter::clear()
    {
        for (size_t i = 0; i < FilterType::FILTER_TYPE_COUNT; i++) {
            mFilterUsed[i] = false;
            mFilterExpression[i].clear();
        }
    }


    bool
    BrowserFilter::fit (FilterType _type, std::string _value)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        // check if filter type is used
        if (!mFilterUsed[_type]) {
            return (true);
        }

        switch (_type) {
        case FilterType::System:
        case FilterType::Node:
        case FilterType::Memory:
        case FilterType::Group:
        case FilterType::PV_Name:
            if (std::regex_match (_value.c_str(), std::regex(mFilterExpression[_type]))) {
                return (true);
            }
            break;

        case FilterType::PV_Type:
        case FilterType::Property_Type:
        case FilterType::Property_Name:
        case FilterType::Property_Name_And_Value:
            THROW_LOGIC_FAULT() << "invalid parameter for filter type " << _type;
            break;

        default:
            THROW_LOGIC_FAULT() << "invalid filter type " << _type;
            break;
        }

        return (false);
    }


    bool
    BrowserFilter::fit (FilterType _type, gc_DataType _DataType)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        // check if filter type is used
        if (!mFilterUsed[_type]) {
            return (true);
        }

        switch (_type) {
        case FilterType::PV_Type:
            break;

        case FilterType::System:
        case FilterType::Node:
        case FilterType::Memory:
        case FilterType::Group:
        case FilterType::PV_Name:
        case FilterType::Property_Type:
        case FilterType::Property_Name:
        case FilterType::Property_Name_And_Value:
            THROW_LOGIC_FAULT() << "invalid parameter for filter type " << _type;
            break;

        default:
            THROW_LOGIC_FAULT() << "invalid filter type " << _type;
            break;
        }

        return (false);
    }


    bool
    BrowserFilter::fit (FilterType _type, SharedPV _pv)
    {
        VALIDATE_ARGUMENT_RANGE_INCLUDE(_type, 0, FilterType::FILTER_TYPE_COUNT);

        // check if filter type is used
        if (!mFilterUsed[_type]) {
            return (true);
        }

        std::vector<std::string> propList = _pv.getPropertyList();

        switch (_type) {
        case FilterType::Property_Name:
            for (auto key = propList.begin(); key != propList.end(); key++) {
                if (std::regex_match (key->c_str(), std::regex(mFilterExpression[_type]))) {
                    return (true);
                }
            }
            break;

        case FilterType::Property_Type:
        case FilterType::Property_Name_And_Value:
            break;

        case FilterType::System:
        case FilterType::Node:
        case FilterType::Memory:
        case FilterType::Group:
        case FilterType::PV_Name:
        case FilterType::PV_Type:
            THROW_LOGIC_FAULT() << "invalid parameter for filter type " << _type;
            break;

        default:
            THROW_LOGIC_FAULT() << "invalid filter type " << _type;
            break;
        }

        return (false);
    }


} /* namespace GaGCppAPI */
