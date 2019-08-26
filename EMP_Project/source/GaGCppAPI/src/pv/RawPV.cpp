/*
 * RawPV.cpp
 *
 *  Created on: 05.12.2014
 *      Author: s.hegemann
 */

#include <iostream>
#include <regex>
#include <stdlib.h>

#include <gacommon/misc.h>

#include "exceptions/ExceptionsMacros.h"

#include "common/GaService.h"
#include "pv/RawPV.h"
#include "exceptions/GammaFaultException.h"

namespace GaGCppAPI {

    RawPV::RawPV()
    {
        prepareOpen(false);
    }

    RawPV::RawPV(const char* const _alias,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_alias);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_open(&mPV, _alias, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _alias;
        }
        finalizeOpen(_pvProperty);
    }

    RawPV::RawPV(const char* const _alias,
                 uint32_t _index,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_alias);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_openByIndex(&mPV, _alias, _index, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _alias;
        }
        finalizeOpen(_pvProperty);
    }

    RawPV::RawPV(const gc_Level6Address* _address,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_address);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_openByAddress(&mPV, _address, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _address->system << ":" << _address->index1 << "." << _address->index2 << "." << _address->index3 << "." << _address->index4 << "." << _address->index5;
        }
        finalizeOpen(_pvProperty);
    }

    RawPV::~RawPV()
    {
        if (mIsConnected) {
            gc_ErrorID result;
            result = ga_pv_close(&mPV);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
        }
    }


    void
    RawPV::connectToPv(const char* const _alias,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_alias);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_open(&mPV, _alias, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _alias;
        }
        finalizeOpen(_pvProperty);
    }

    void
    RawPV::connectToPv(const char* const _alias,
                 uint32_t _index,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_alias);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_openByIndex(&mPV, _alias, _index, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _alias;
        }
        finalizeOpen(_pvProperty);
    }

    void
    RawPV::connectToPv(const gc_Level6Address* _address,
                 gc_Flags32Bit _pvProperty)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_address);

        prepareOpen();
        gc_ErrorID result;
        result = ga_pv_openByAddress(&mPV, _address, _pvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "Unable to open PV " << _address->system << ":" << _address->index1 << "." << _address->index2 << "." << _address->index3 << "." << _address->index4 << "." << _address->index5;
        }
        finalizeOpen(_pvProperty);
    }

    void
    RawPV::reconnect()
    {
        gc_ErrorID result;

        // first try to disconnect
        if (!mIsConnected) {
            result = ga_pv_close(&mPV);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
        }

        // reset internal data
        prepareOpen();

        // create new connection
        result = ga_pv_open(&mPV, mPvName.c_str(), mPvProperty);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result);
        }
        finalizeOpen(mPvProperty, false);
    }

    std::string
    RawPV::getName() const
    {
        return (mPvName);
    }

    gc_DataType
    RawPV::getDataType() const
    {
        return (mDataType);
    }

    bool
    RawPV::isNumericValue() const
    {
        return (mIsNumericValue);
    }

    bool
    RawPV::isBinaryData() const
    {
        return (!mIsNumericValue);
    }

    bool
    RawPV::isFifo() const
    {
        return (mIsFifo);
    }

    size_t
    RawPV::getBinarySize() const
    {
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, false);
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        size_t size;

        gc_ErrorID result;
        result = ga_pv_getLength(mPV, nullptr, &size);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        return (size);
    }

    size_t
    RawPV::getUsedBuffer() const
    {
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, false);
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        size_t size;

        gc_ErrorID result;
        result = ga_pv_getLength(mPV, &size, nullptr);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        return (size);
    }

    gc_Level6Address
    RawPV::getAddress() const
    {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        gc_Level6Address numericAddress;

        gc_ErrorID result;
        result = ga_pv_getAddress(mPV, nullptr, nullptr, &numericAddress);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        return (std::move(numericAddress));
    }

    gc_Level6Address
    RawPV::getAddress(std::string& conformAddress) const
                      {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        gc_Level6Address numericAddress;
        const char* conformAddressPt;

        gc_ErrorID result;
        result = ga_pv_getAddress(mPV, nullptr, &conformAddressPt, &numericAddress);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        conformAddress = conformAddressPt;
        return (std::move(numericAddress));
    }

    gc_NumericValue
    RawPV::getNumericValue() const
    {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        gc_NumericValue value;

        gc_ErrorID result;
        result = ga_pv_getValue(mPV, &value);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        return (value);
    }

    std::vector<uint8_t>
    RawPV::getBinaryValue() const
    {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, false);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        std::vector<uint8_t> dataContainer;

        gc_ErrorID result;
        uint8_t* pt;
        size_t len = 0;
        result = ga_pv_getBinaryValue(mPV, &pt, 0, &len);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        for (size_t i = 0; i < len; i++) {
            dataContainer.push_back(pt[i]);
        }

        result = gc_freeMemory(pt);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }

        return (std::move(dataContainer));
    }

    std::string
    RawPV::getValueAsString(const char* _format /* = nullptr */) const
    {
        std::string value;
        std::string format;
        char buffer[1024];
        std::vector<uint8_t> val;

        switch (mDataType) {
        case gc_DATA_TYPE_SINT_8:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().sint8);
            value = buffer;
            break;

        case gc_DATA_TYPE_UINT_8:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().uint8);
            value = buffer;
            break;

        case gc_DATA_TYPE_SINT_16:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().sint16);
            value = buffer;
            break;

        case gc_DATA_TYPE_UINT_16:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().uint16);
            value = buffer;
            break;

        case gc_DATA_TYPE_SINT_32:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().sint32);
            value = buffer;
            break;

        case gc_DATA_TYPE_UINT_32:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%d";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().uint32);
            value = buffer;
            break;

        case gc_DATA_TYPE_SINT_64:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%lld";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().sint64);
            value = buffer;
            break;

        case gc_DATA_TYPE_UINT_64:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%lld";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().uint64);
            value = buffer;
            break;

        case gc_DATA_TYPE_IEEE_32:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%g";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().ieee32);
            value = buffer;
            break;

        case gc_DATA_TYPE_IEEE_64:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%g";
            }
            snprintf(buffer, 1023, format.c_str(), getNumericValue().ieee64);
            value = buffer;
            break;


        case gc_DATA_TYPE_STRING:
            val = getBinaryValue();
            for (size_t i = 0; i < val.size(); i++) {
                if (val[i] == 0) {
                    break;
                }
                value += val[i];
            }
            break;

        case gc_DATA_TYPE_BLOB:
            if (_format != nullptr) {
                format = _format;
            }
            else {
                format = "%02x";
            }
            val = getBinaryValue();
            for (size_t i = 0; i < val.size(); i++) {
                snprintf(buffer, 1023, format.c_str(), val[i]);
                value += buffer;
            }
            break;

        case gc_DATA_TYPE_INVALID:
        default:
            break;
        } // switch (mDataType)

        return (value);
    }

    void
    RawPV::putNumericValue(const gc_NumericValue& _value)
    {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, true);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        gc_ErrorID result;
        result = ga_pv_putValue(mPV, &_value);
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }
    }

    void
    RawPV::putBinaryValue(const std::vector<uint8_t>& _value)
    {
        VALIDATE_ARGUMENT_EQUAL(mIsConnected, true);
        VALIDATE_ARGUMENT_EQUAL(mIsNumericValue, false);
        if (!mIsConnected) {
            THROW_LOGIC_FAULT()<< "connection to gamma service lost.";
        }

        gc_ErrorID result;

        result = ga_pv_putBinaryValue(mPV, _value.data(), (size_t) _value.size());
        if (result != gc_ERROR_SUCCESS.errorID) {
            mIsConnected = false;
            THROW_GAMMA_FAULT(result);
        }
    }

    void
    RawPV::putValueFromString(const std::string _value, int _base /* = 10 */)
    {
        std::vector<uint8_t> valBlob;
        gc_NumericValue valNumber;
        char buffer[4] =  {0};
        uint8_t tempVal = 0;

        switch (mDataType) {
        case gc_DATA_TYPE_SINT_8:
            valNumber.sint8 = strtol(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_UINT_8:
            valNumber.uint8 = strtoul(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_SINT_16:
            valNumber.sint16 = strtol(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_UINT_16:
            valNumber.uint16 = strtoul(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_SINT_32:
            valNumber.sint32 = strtol(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_UINT_32:
            valNumber.uint32 = strtoul(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_SINT_64:
            valNumber.uint64 = strtoll(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_UINT_64:
            valNumber.sint64 = strtoull(_value.c_str(), nullptr, _base);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_IEEE_32:
            valNumber.ieee32 = strtod(_value.c_str(), nullptr);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_IEEE_64:
            valNumber.ieee64 = strtod(_value.c_str(), nullptr);
            putNumericValue(valNumber);
            break;

        case gc_DATA_TYPE_STRING:
            for (size_t i = 0; i < _value.length(); i++) {
                valBlob.push_back(_value.at(i));
            }
            putBinaryValue(valBlob);
            break;

        case gc_DATA_TYPE_BLOB:
            for (size_t i = 0; i < _value.length(); i+=2) {
                buffer[0] = _value.at(i);
                buffer[1] = _value.at(i+1);
                tempVal = strtol(buffer, nullptr, 16);
                valBlob.push_back(tempVal);
            }
            putBinaryValue(valBlob);
            break;

        case gc_DATA_TYPE_INVALID:
        default:
            break;
        } // switch (mDataType)
    }


    void
    RawPV::callBack(uint32_t _arg1, uint32_t _arg2)
    {
        eventType t = (eventType) _arg1;
        switch (t)
        {
        case eventType::SERVICE_ATTACHED:
            reconnect();
            break;
        case eventType::SERVICE_DETACHED:
            mIsConnected = false;
            break;
        case eventType::SERVICE_LOST:
            mIsConnected = false;
            break;
        }
    }

    void
    RawPV::prepareOpen(bool _checkConnection /* = true */)
    {
        mPV = nullptr;
        mIsConnected = false;
        mIsNumericValue = false;
        mIsFifo = false;
        mDataType = gc_DATA_TYPE_INVALID;

        if (_checkConnection) {
            GaService& con = GaService::getInstance();
            if (!con.isAttached()) {
                THROW_LOGIC_FAULT()<< "unable to open PV when application is not attached to Gamma service";
            }
        }
    }

    void
    RawPV::finalizeOpen(gc_Flags32Bit _pvProperty,
    bool _attachEvents /* = true */)
    {
        gc_ErrorID result;

        result = ga_pv_getDataType(mPV, &mDataType);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result);
        }
        result = ga_pv_getPVType(mPV, &mPVType);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result);
        }

        mIsConnected = true;

        mPvAddress = std::move(getAddress(mPvName));
        mPvProperty = _pvProperty;

        mIsNumericValue = ((mDataType >= gc_DATA_TYPE_SINT_8) && (mDataType <= gc_DATA_TYPE_IEEE_64));
        mIsFifo = (mPVType == ga_PV_TYPE_FIFO);
        readProperties();

        if (_attachEvents) {
            GaService& gaService = GaService::getInstance();

            attachToEvent(gaService.onAttach(), (uint32_t) eventType::SERVICE_ATTACHED);
            attachToEvent(gaService.onDetach(), (uint32_t) eventType::SERVICE_DETACHED);
            attachToEvent(gaService.onConnectionLost(), (uint32_t) eventType::SERVICE_LOST);
        }

    }

    void
    RawPV::readProperties()
    {
        gc_ErrorID result;
        size_t propertyNameCount = 0;
        char** propertyNames = nullptr;

        result = ga_pv_getDataModelPropertyNames(mPV, &propertyNameCount, &propertyNames);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result)<< "unable to get properties from PV " << mPvName;
        }

        for (size_t i = 0; i < propertyNameCount; i++) {
            std::string propName = propertyNames[i];
            gc_Value propertyValue;
            char* textualPropertyValue = nullptr;

            result = ga_pv_getDataModelProperty(mPV, propertyNames[i], &propertyValue);
            if (result != gc_ERROR_SUCCESS.errorID) {
                THROW_GAMMA_FAULT(result)<< "unable to read properties " << propertyNames[i] << " from PV " << mPvName;
            }

            result = gc_Value_print(&propertyValue, &textualPropertyValue, 0, 0);
            std::string propValue = textualPropertyValue;

            try {
                pvPropertyListEntry entry(propName, propValue);
                mPropertyList.insert(entry);
            }
            catch (std::exception &e) {
                THROW_LOGIC_FAULT()<< "unable to add property " << propName << " to List of PV " << mPvName << ": " << e.what();
            }

            result = gc_Value_free(&propertyValue);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
            result = gc_freeMemory(textualPropertyValue);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
            result = gc_freeMemory(propertyNames[i]);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
        }

        if (propertyNameCount != 0) {
            result = gc_freeMemory(propertyNames);
            if (result != gc_ERROR_SUCCESS.errorID) {
                std::cerr << "error during clean up! (File: " << __FILE__ << "; Line " << __LINE__ - 2 << ")" << " Error code: " << result << std::endl;
            }
        }
    }

    std::vector<std::string>
    RawPV::getPropertyList()
    {
        std::vector<std::string> list;

        for (auto entry = mPropertyList.begin(); entry != mPropertyList.end(); entry++) {
            list.push_back(entry->first);
        }

        return (std::move(list));
    }

    std::string
    RawPV::getProperty(std::string _propertyName)
    {
        std::string value;
        try {
            value = mPropertyList.at(_propertyName);
        }
        catch (std::exception &e) {
            THROW_LOGIC_FAULT()<< "PV " << mPvName << ": unable to get property " << _propertyName << ": " << e.what();
        }
        return (value);
    }

    bool
    RawPV::hasProperty(std::string _propertyName)
    {
        auto search = mPropertyList.find(_propertyName);
        if (search != mPropertyList.end()) {
            return (true);
        }
        else {
            return (false);
        }
    }


} /* namespace GaGCppAPI */
