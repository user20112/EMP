/**
 * @file TypedPVMapping.h
 * @short contain definition of class \c GaGCppAPI::PVConverter
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPVMAPPING_H_
#define SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPVMAPPING_H_

// System header
#include <memory>

// external library header
#include "gacommon/dataTypes.h"

// local library header



namespace GaGCppAPI {

    // **************************************************************************************************
    // ** type template
    // **************************************************************************************************
    /**
     * @class PVConverter
     * @short convert gamma NumericValues to given system data type
     *
     * @warning
     * this class is only for internal use. See \c TypedPV for user interface.
     *
     * @remark
     * implemented data types:
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
     */
    template<typename T>
    class PVConverter
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to specific class type
             */
            static T
            getValue(const gc_NumericValue& _src);

            /**
             * @short transfer specific class type to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const T& _src);

    };

    // **************************************************************************************************
    // ** Specialization for bool
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c bool
     */
    template<>
    class PVConverter<bool>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c bool
             */
            static bool
            getValue(const gc_NumericValue& _src)
            {
                return (_src.uint8 != 0 ? true : false);
            }

            /**
             * @short transfer \c bool to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const bool& _src)
            {
                gc_NumericValue dest;
                dest.uint8 = (_src ? 1 : 0);
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for int8_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c int8_t
     */
    template<>
    class PVConverter<int8_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c int8_t
             */
            static int8_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.sint8);
            }

            /**
             * @short transfer \c int8_t to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const int8_t& _src)
            {
                gc_NumericValue dest;
                dest.sint8 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for int16_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c int16_t
     */
    template<>
    class PVConverter<int16_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c int16_t
             */
            static int16_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.sint16);
            }

            /**
             * @short transfer \c int16_t to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const int16_t& _src)
            {
                gc_NumericValue dest;
                dest.sint16 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for int32_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c int32_t
     */
    template<>
    class PVConverter<int32_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c int32_t
             */
           static int32_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.sint32);
            }

           /**
            * @short transfer \c int32_t to gc_NumericValue
            */
            static gc_NumericValue
            putValue(const int32_t& _src)
            {
                gc_NumericValue dest;
                dest.sint32 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for int64_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c int64_t
     */
    template<>
    class PVConverter<int64_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c int64_t
             */
           static int64_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.sint64);
            }

           /**
            * @short transfer \c int64_t to gc_NumericValue
            */
            static gc_NumericValue
            putValue(const int64_t& _src)
            {
                gc_NumericValue dest;
                dest.sint64 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for uint8_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c uint8_t
     */
    template<>
    class PVConverter<uint8_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c uint8_t
             */
           static uint8_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.uint8);
            }

           /**
            * @short transfer \c uint8_t to gc_NumericValue
            */
            static gc_NumericValue
            putValue(const uint8_t& _src)
            {
                gc_NumericValue dest;
                dest.uint8 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for uint16_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c uint16_t
     */
    template<>
    class PVConverter<uint16_t>
    {
        public:
            /**
             * @short required gamma data type
             */
           static gc_DataType mType;

           /**
            * @short transfer gc_NumericValue to \c uint16_t
            */
            static uint16_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.uint16);
            }

            /**
             * @short transfer \c uint16_t to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const uint16_t& _src)
            {
                gc_NumericValue dest;
                dest.uint16 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for uint32_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c uint32_t
     */
    template<>
    class PVConverter<uint32_t>
    {
        public:
            /**
             * @short required gamma data type
             */
            static gc_DataType mType;

            /**
             * @short transfer gc_NumericValue to \c uint32_t
             */
            static uint32_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.uint32);
            }

            /**
             * @short transfer \c uint32_t to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const uint32_t& _src)
            {
                gc_NumericValue dest;
                dest.uint32 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for uint64_t
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c uint64_t
     */
    template<>
    class PVConverter<uint64_t>
    {
        public:
            /**
             * @short required gamma data type
             */
           static gc_DataType mType;

           /**
            * @short transfer gc_NumericValue to \c uint64_t
            */
           static uint64_t
            getValue(const gc_NumericValue& _src)
            {
                return (_src.uint64);
            }

           /**
            * @short transfer \c uint64_t to gc_NumericValue
            */
            static gc_NumericValue
            putValue(const uint64_t& _src)
            {
                gc_NumericValue dest;
                dest.uint64 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for float
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c float
     */
    template<>
    class PVConverter<float>
    {
        public:
            /**
             * @short required gamma data type
             */
           static gc_DataType mType;

           /**
            * @short transfer gc_NumericValue to \c float
            */
            static float
            getValue(const gc_NumericValue& _src)
            {
                return (_src.ieee32);
            }

            /**
             * @short transfer \c float to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const float& _src)
            {
                gc_NumericValue dest;
                dest.ieee32 = _src;
                return (std::move(dest));
            }

    };

    // **************************************************************************************************
    // ** Specialization for double
    // **************************************************************************************************
    /**
     * @short specialization of template class \c PVConverter for \c double
     */
    template<>
    class PVConverter<double>
    {
        public:
            /**
             * @short required gamma data type
             */
           static gc_DataType mType;

           /**
            * @short transfer gc_NumericValue to \c double
            */
            static double
            getValue(const gc_NumericValue& _src)
            {
                return (_src.ieee64);
            }

            /**
             * @short transfer \c double to gc_NumericValue
             */
            static gc_NumericValue
            putValue(const double& _src)
            {
                gc_NumericValue dest;
                dest.ieee64 = _src;
                return (std::move(dest));
            }

    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_INCLUDE_PV_TYPEDPVMAPPING_H_ */
