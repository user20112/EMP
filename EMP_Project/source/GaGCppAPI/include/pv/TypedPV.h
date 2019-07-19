/**
 * @file TypedPV.h
 * @short contain definition of class \c GaGCppAPI::TypedPV
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPV_H_
#define CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPV_H_
// System header

// external library header
#include "exceptions/ExceptionsMacros.h"

// local library header
#include "pv/SharedPV.h"
#include "pv/TypedPVMapping.h"




//  some nodes to the file layout:
// ================================
//
//   at first all operator templates which need to be implemented as "friend" operator to TypedPV<T>
//   are declared and defined. To do so, a declaration of the class TypedPV is needed.
//
//   After that, the template class TypedPV<T> is defined as usual.
//
//   The definition of the class methods is also done in this file. This is required, because
//   the class TypedPV<T> is a template class and all definitions need to be known in the complete program.
//
// 06.12.2014; S. Hegemann
//

namespace GaGCppAPI {

    /**
     * @internal
     * @class TypedPV
     */
    template<typename T>
    class TypedPV;

    // **************************************************************************************************
    // ** global operator definition: operator==
    // **************************************************************************************************
    template<typename T>
    bool
    operator== (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
       return (_o1.get() == _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator==
    // **************************************************************************************************
    template<typename T>
    bool
    operator== (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1.get() == _o2);
    }

    // **************************************************************************************************
    // ** global operator definition: operator==
    // **************************************************************************************************
    template<typename T>
    bool
    operator== (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1 == _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator!=
    // **************************************************************************************************
    template<typename T>
    bool
    operator!= (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() != _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator!=
    // **************************************************************************************************
    template<typename T>
    bool
    operator!= (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1.get() != _o2);
    }

    // **************************************************************************************************
    // ** global operator definition: operator!=
    // **************************************************************************************************
    template<typename T>
    bool
    operator!= (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1 != _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator>=
    // **************************************************************************************************
    template<typename T>
    bool
    operator>= (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() >= _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator>=
    // **************************************************************************************************
    template<typename T>
    bool
    operator>= (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1 >= _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator>=
    // **************************************************************************************************
    template<typename T>
    bool
    operator>= (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() >= _o2);
    }

    // **************************************************************************************************
    // ** global operator definition: operator<=
    // **************************************************************************************************
    template<typename T>
    bool
    operator<= (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() <= _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator<=
    // **************************************************************************************************
    template<typename T>
    bool
    operator<= (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1 <= _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator<=
    // **************************************************************************************************
    template<typename T>
    bool
    operator<= (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() <= _o2);
    }

    // **************************************************************************************************
    // ** global operator definition: operator>
    // **************************************************************************************************
    template<typename T>
    bool
    operator> (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() > _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator>
    // **************************************************************************************************
    template<typename T>
    bool
    operator> (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1 > _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator>
    // **************************************************************************************************
    template<typename T>
    bool
    operator> (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() > _o2);
    }

    // **************************************************************************************************
    // ** global operator definition: operator<
    // **************************************************************************************************
    template<typename T>
    bool
    operator< (TypedPV<T>& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() < _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator<
    // **************************************************************************************************
    template<typename T>
    bool
    operator< (TypedPV<T>& _o1, T& _o2)
    {
        return (_o1 < _o2.get());
    }

    // **************************************************************************************************
    // ** global operator definition: operator<
    // **************************************************************************************************
    template<typename T>
    bool
    operator< (T& _o1, TypedPV<T>& _o2)
    {
        return (_o1.get() < _o2);
    }

    /**
     * @class TypedPV
     * @short casting a gamma process variable to basic system data types T
     *
     * each instance is connected to a gamma process variable. Inside the code the instance can be used as
     * the specified system data type.
     *
     * __An Example:__
     * @code
     *   // create an instance and connect to gamma process variable
     *   GaGCppAPI::TypedPV<uint32_t> aliveCounter("LocalService:App1.App1Mem.Channel1.Debug.AliveCounter", ga_PV_PROPERTY_ACC_NON_BLOCKING);
     *   GaGCppAPI::TypedPV<bool> serviceActive("LocalService:App1.App1Mem.Channel1.Debug.ServiceActive", ga_PV_PROPERTY_ACC_NON_BLOCKING);
     *
     *   // get numeric address of the gamma process variable
     *   std::string addr;
     *   gc_Level6Address addrNum = aliveCounter.getAddress(addr);
     *   std::cout << "connected to PV \""  << addr << "\" (Numeric Address: " << addrNum.system << ":"
     *                                                                         << addrNum.index1 << ":"
     *                                                                         << addrNum.index2 << ":"
     *                                                                         << addrNum.index3 << ":"
     *                                                                         << addrNum.index4 << ":"
     *                                                                         << addrNum.index5 << ")" << std::endl;;
     *
     *   // deal with the process variable as system values
     *   serviceActive = true;
     *
     *   aliveCounter++;
     *   std::cout << "alive counter: " << aliveCounter << std::endl;
     *
     *   serviceActive = false;
     *
     *   // no clean up necessary, this is done by \c TypedPV
     *
     * @endcode
     *
     * __implemented data types:__
     *     | System Data Type | Gamma Data Type      | union name |
     *     |------------------|----------------------|------------|
     *     | bool             | gc_DATA_TYPE_UINT_8  | uint8      |
     *     | int8_t           | gc_DATA_TYPE_SINT_8  | sint8      |
     *     | int16_t          | gc_DATA_TYPE_SINT_16 | sint16     |
     *     | int32_t          | gc_DATA_TYPE_SINT_32 | sint32     |
     *     | int61_t          | gc_DATA_TYPE_SINT_64 | sint64     |
     *     | uint8_t          | gc_DATA_TYPE_UINT_8  | uint8      |
     *     | uint16_t         | gc_DATA_TYPE_UINT_16 | uint16     |
     *     | uint32_t         | gc_DATA_TYPE_UINT_32 | uint32     |
     *     | uint61_t         | gc_DATA_TYPE_UINT_64 | uint64     |
     *     | float            | gc_DATA_TYPE_IEEE_32 | ieee32     |
     *     | double           | gc_DATA_TYPE_IEEE_64 | ieee64     |
     *
     */
    template<typename T>
    class TypedPV: public SharedPV
    {
        public:
            /**
             * @short create new instance for a gamma process variable, but will not connect
             *
             * @warning
             * call \c connectToPv() before access to this PV
             */
            TypedPV();

            /**
             * @short connect to existing gamma process variable by alias name
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * further description, how the alias name is defined see gamma API reference.
             *
             * @param _alias PV alias name
             * @param _pvProperty connection properties.
             */
            TypedPV(const char* const _alias,
                    gc_Flags32Bit _pvProperty);

            /**
             * @short connect to existing gamma process variable by alias name and array index
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * further description, how the alias name and index is defined see gamma API reference.
             *
             * @param _alias PV alias name
             * @param _index index of PV
             * @param _pvProperty connection properties.
             */
            TypedPV(const char* const _alias,
                    uint32_t _index,
                    gc_Flags32Bit _pvProperty);

            /**
             * @short connect to existing gamma process variable by numeric address.
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * the numeric address need to be generated by searching functions and should not be defined fixed!
             * See the browsing API how to search for PV's
             *
             * @param _address PV numeric address
             * @param _pvProperty connection properties.
             */
            TypedPV(const gc_Level6Address* _address,
                    gc_Flags32Bit _pvProperty);


            /**
             * @short clean up when gamma process variable isn't in use anymore.
             */
            virtual ~TypedPV();

            /**
             * @short connect to existing gamma process variable by alias name
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * further description, how the alias name is defined see gamma API reference.
             *
             * @param _alias PV alias name
             * @param _pvProperty connection properties.
             */
            virtual void
            connectToPv(const char* const _alias,
                        gc_Flags32Bit _pvProperty);

            /**
             * @short connect to existing gamma process variable by alias name and array index
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * further description, how the alias name and index is defined see gamma API reference.
             *
             * @param _alias PV alias name
             * @param _index index of PV
             * @param _pvProperty connection properties.
             */
            virtual void
            connectToPv(const char* const _alias,
                        uint32_t _index,
                        gc_Flags32Bit _pvProperty);

            /**
             * @short connect to existing gamma process variable by numeric address.
             *
             * @remark
             * default connection properties:
             *     | location | property, that should be used   |
             *     |----------|---------------------------------|
             *     | local    | ga_PV_PROPERTY_ACC_NON_BLOCKING |
             *     | remote   | ga_PV_PROPERTY_ACC_BLOCKING     |
             *
             * @remark
             * the numeric address need to be generated by searching functions and should not be defined fixed!
             * See the browsing API how to search for PV's
             *
             * @param _address PV numeric address
             * @param _pvProperty connection properties.
             */
            virtual void
            connectToPv(const gc_Level6Address* _address,
                    gc_Flags32Bit _pvProperty);

            /**
             * @short request the current value from gamma service
             *
             * @return current value as specified data type
             */
            inline T
            get() const;

            /**
             * @short put a new value to gamma service
             * @param _value new value
             */
            inline void
            put(const T& _value);

            /**
             * @short (cast operator) implicit type cast to specified data type (const)
             *
             * @remark
             * a mutable type cast isn't useful, because the generated value can't be put back to gamma service and will be lost!
             */
            operator T() const;

            /**
             * @short (assignment operator) set the PV to a given value
             * @param _src new value
             * @return reference to current instance
             */
            TypedPV<T>&
            operator= (const T& _src);

            /**
             * @short (increment operator (POSTFIX]) count the PV up by 1
             * @return reference to current instance
             */
            // the parameter is just a dummy value and is needed to get the POSTFIX operator
            TypedPV<T>&
            operator++ (int);

            /**
             * @short (decrement operator [POSTFIX]) count the PV down by 1
             * @return reference to current instance
             */
            // the parameter is just a dummy value and is needed to get the POSTFIX operator
            TypedPV<T>&
            operator-- (int);

            /**
             * @short (increment operator [PREFIX]) count the PV up by 1
             * @return reference to current instance
             */
            TypedPV<T>&
            operator++ ();

            /**
             * @short (decrement operator [PREFIX]) count the PV down by 1
             * @return reference to current instance
             */
            TypedPV<T>&
            operator-- ();

            /**
             * @short (operator +=) add \c _src to the current value and put the result back to gamma service
             * @param _src value to add to PV
             * @return reference to current instance
             */
            TypedPV<T>&
            operator+= (const T& _src);

            /**
             * @short (operator -=) subtract \c _src from the current value and put the result back to gamma service
             * @param _src value to subtract from PV
             * @return reference to current instance
             */
            TypedPV<T>&
            operator-= (const T& _src);

            /**
             * @short (operator *=) multiply the current value by \c _src and put the result back to gamma service
             * @param _src multiplier
             * @return reference to current instance
             */
            TypedPV<T>&
            operator*= (const T& _src);

            /**
             * @short (operator *=) divide the current value by \c _src and and put the result back to gamma service
             * @param _src  divisor
             * @return reference to current instance
             */
            TypedPV<T>&
            operator/= (const T& _src);

            /**
             * @short (comparison operator) compare the value of two PV's and return true, when they are equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value of _o1 is equal to the value of _o2, otherwise false
             */
            friend bool
            operator== <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (comparison operator) compare the value of a PV and another value and return true, when they are equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value of _o1 is equal to the value of _o2, otherwise false
             */
            friend bool
            operator== <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (comparison operator) compare the value of a PV and another value and return true, when they are equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value of _o1 is equal to the value of _o2, otherwise false
             */
            friend bool
            operator== <> (T& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator !=) compare the value of two PV's and return true, when they are not equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when values of _o1 and _o2 are not equal, otherwise false
             */
            friend bool
            operator!= <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator !=) compare the value of a PV and another value and return true, when they are not equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when values  _o1 and _o2 are not equal, otherwise false
             */
            friend bool
            operator!= <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (operator !=) compare the value of a PV and another value and return true, when they are not equal
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when values of _o1 and _o2 are not equal
             */
            friend bool
            operator!= <> (T& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >=) compare the value of two PV's and return true, when they the first one is greater than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than or equal to the second one, otherwise false
             */
            friend bool
            operator>= <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >=) compare the value of a PV and another value and return true, when they the first one is greater than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than or equal to the second one, otherwise false
             */
            friend bool
            operator>= <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (operator >=) compare the value of a PV and another value and return true, when they the first one is greater than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than or equal to the second one, otherwise false
             */
            friend bool
            operator>= <> (T& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >=) compare the value of two PV's and return true, when they the first one is less than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than or equal to the second one, otherwise false
             */
            friend bool
            operator<= <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >=) compare the value of a PV and another value and return true, when they the first one is less than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than or equal to the second one, otherwise false
             */
            friend bool
            operator<= <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (operator >=) compare the value of a PV and another value and return true, when they the first one is less than or equal to the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than or equal to the second one, otherwise false
             */
            friend bool
            operator<= <> (T& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >) compare the value of two PV's and return true, when they the first one is greater than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than the second one, otherwise false
             */
            friend bool
            operator> <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator >) compare the value of a PV and another value and return true, when they the first one is greater than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than the second one, otherwise false
             */
            friend bool
            operator> <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (operator >) compare the value of a PV and another value and return true, when they the first one is greater than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is greater than the second one, otherwise false
             */
            friend bool
            operator> <> (T& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator <) compare the value of two PV's and return true, when they the first one is less than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than the second one, otherwise false
             */
            friend bool
            operator< <> (TypedPV<T>& _o1, TypedPV<T>& _o2);

            /**
             * @short (operator <) compare the value of a PV and another value and return true, when they the first one is less than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than the second one, otherwise false
             */
            friend bool
            operator< <> (TypedPV<T>& _o1, T& _o2);

            /**
             * @short (operator <) compare the value of a PV and another value and return true, when they the first one is less than the second one.
             * @param _o1 first value
             * @param _o2 second value
             * @return true, when value _o1 is less than the second one, otherwise false
             */
            friend bool
            operator< <> (T& _o1, TypedPV<T>& _o2);
    };

    // **************************************************************************************************
    // ** TypedPV<T>::TypedPV
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::TypedPV() :
                            SharedPV()
    {
    }

    // **************************************************************************************************
    // ** TypedPV<T>::TypedPV
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::TypedPV(const char* const _alias,
                        gc_Flags32Bit _pvProperty) :
                            SharedPV(_alias, _pvProperty)
    {
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::TypedPV
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::TypedPV(const char* const _alias,
                        uint32_t _index,
                        gc_Flags32Bit _pvProperty) :
                            SharedPV(_alias, _index, _pvProperty)
    {
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::TypedPV
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::TypedPV(const gc_Level6Address* _address,
                        gc_Flags32Bit _pvProperty) :
                            SharedPV(_address, _pvProperty)
    {
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::~TypedPV
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::~TypedPV()
    {

    }

    // **************************************************************************************************
    // ** TypedPV<T>::connectToPv
    // **************************************************************************************************
    template<typename T>
    void
    TypedPV<T>::connectToPv(const char* const _alias,
                        gc_Flags32Bit _pvProperty)
    {
        SharedPV::connectToPv(_alias, _pvProperty);
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::connectToPv
    // **************************************************************************************************
    template<typename T>
    void
    TypedPV<T>::connectToPv(const char* const _alias,
                        uint32_t _index,
                        gc_Flags32Bit _pvProperty)
    {
        SharedPV::connectToPv(_alias, _index, _pvProperty);
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::connectToPv
    // **************************************************************************************************
    template<typename T>
    void
    TypedPV<T>::connectToPv(const gc_Level6Address* _address,
                        gc_Flags32Bit _pvProperty)
    {
        SharedPV::connectToPv(_address, _pvProperty);
        VALIDATE_ARGUMENT_EQUAL(getDataType(), PVConverter<T>::mType);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::get()
    // **************************************************************************************************
    template<typename T>
    T
    TypedPV<T>::get() const
    {
        return (PVConverter<T>::getValue(getNumericValue()));
    }

    // **************************************************************************************************
    // ** TypedPV<T>::put()
    // **************************************************************************************************
    template<typename T>
    void
    TypedPV<T>::put(const T& _value)
    {
        putNumericValue(PVConverter<T>::putValue(_value));
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator()
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>::operator T() const
    {
        return (get());
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator=
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator= (const T& _src)
    {
        put(_src);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator++ [POSTFIX]
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator++ (int)
    {
        put(get()+1);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator-- [POSTFIX]
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator-- (int)
    {
        put(get()-1);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator++
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator++ ()
    {
        put(get()+1);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator--
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator-- ()
    {
        put(get()-1);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator+=
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator+= (const T& _src)
    {
        put(get()+_src);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator-=
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator-= (const T& _src)
    {
        put(get()-_src);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator*=
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator*= (const T& _src)
    {
        put(get()*_src);
        return (*this);
    }

    // **************************************************************************************************
    // ** TypedPV<T>::operator/=
    // **************************************************************************************************
    template<typename T>
    TypedPV<T>&
    TypedPV<T>::operator/= (const T& _src)
    {
        put(get()/_src);
        return (*this);
    }


} /* namespace GaGCppAPI */

#endif /* CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPV_H_ */
