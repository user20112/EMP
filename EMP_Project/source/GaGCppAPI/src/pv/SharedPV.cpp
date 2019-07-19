/*
 * SharedPV.cpp
 *
 *  Created on: 27.04.2015
 *      Author: s.hegemann
 */

#include "pv/SharedPV.h"

namespace GaGCppAPI {

    SharedPV::SharedPV()
    {
        mPV = std::make_shared<RawPV>();
    }

    SharedPV::SharedPV(const char* const _alias,
                       gc_Flags32Bit _pvProperty)
    {
        mPV = std::make_shared<RawPV>(_alias, _pvProperty);
    }

    SharedPV::SharedPV(const char* const _alias,
                       uint32_t _index,
                       gc_Flags32Bit _pvProperty)
    {
        mPV = std::make_shared<RawPV>(_alias, _index, _pvProperty);
    }

    SharedPV::SharedPV(const gc_Level6Address* _address,
                       gc_Flags32Bit _pvProperty)
    {
        mPV = std::make_shared<RawPV>(_address, _pvProperty);
    }

    SharedPV::~SharedPV()
    {

    }

    void
    SharedPV::connectToPv(const char* const _alias,
                          gc_Flags32Bit _pvProperty)
    {
        mPV->connectToPv(_alias, _pvProperty);
    }

    void
    SharedPV::connectToPv(const char* const _alias,
                          uint32_t _index,
                          gc_Flags32Bit _pvProperty)
    {
        mPV->connectToPv(_alias, _index, _pvProperty);
    }

    void
    SharedPV::connectToPv(const gc_Level6Address* _address,
                          gc_Flags32Bit _pvProperty)
    {
        mPV->connectToPv(_address, _pvProperty);
    }

    std::string
    SharedPV::getName() const
    {
        return (mPV->getName());
    }

    gc_DataType
    SharedPV::getDataType() const
    {
        return (mPV->getDataType());
    }

    bool
    SharedPV::isNumericValue() const
    {
        return (mPV->isNumericValue());
    }

    bool
    SharedPV::isBinaryData() const
    {
        return (mPV->isBinaryData());
    }

    bool
    SharedPV::isFifo() const
    {
        return (mPV->isFifo());
    }

    size_t
    SharedPV::getBinarySize() const
    {
        return (mPV->getBinarySize());
    }

    size_t
    SharedPV::getUsedBuffer() const
    {
        return (mPV->getUsedBuffer());
    }

    gc_Level6Address
    SharedPV::getAddress() const
    {
        return (mPV->getAddress());
    }

    gc_Level6Address
    SharedPV::getAddress(std::string& conformAddress) const
    {
        return (mPV->getAddress(conformAddress));
    }

    gc_NumericValue
    SharedPV::getNumericValue() const
    {
        return (mPV->getNumericValue());
    }

    std::vector<uint8_t>
    SharedPV::getBinaryValue() const
    {
        return (mPV->getBinaryValue());
    }

    std::string
    SharedPV::getValueAsString(const char* _format /* = nullptr */) const
    {
        return (mPV->getValueAsString(_format));
    }


    void
    SharedPV::putNumericValue(const gc_NumericValue& _value)
    {
        return (mPV->putNumericValue(_value));
    }

    void
    SharedPV::putBinaryValue(const std::vector<uint8_t>& _value)
    {
        return (mPV->putBinaryValue(_value));
    }

    void
    SharedPV::putValueFromString(const std::string _value, int _base /* = 10 */)
    {
        return (mPV->putValueFromString(_value, _base));
    }

    std::vector<std::string>
    SharedPV::getPropertyList()
    {
        return (mPV->getPropertyList());
    }

    std::string
    SharedPV::getProperty(std::string _propertyName)
    {
        return (mPV->getProperty(_propertyName));
    }

    bool
    SharedPV::hasProperty(std::string _propertyName)
    {
        return (mPV->hasProperty(_propertyName));
    }

} /* namespace GaGCppAPI */
