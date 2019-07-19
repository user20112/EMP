/**
 * @file PruDriver.h
 * @short contain definition of class \c PruDriver
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUDRIVER_H_
#define CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUDRIVER_H_

// System header
#include <mutex>
#include <stdint.h>

namespace BeagleBoneResources {

    class PruDriver
    {
            friend class PruInterface;

        public:
            enum class PRU_STATE {
                UNUSED,
                INITIALIZING,
                OPERATING
            };

            static const uint8_t PRU_COUNT = 2;

            /**
             * @short access to global instance
             * @return reference to global class instance
             */
            static PruDriver&
            getInstance();

            /**
             * @short destructor
             */
            virtual ~PruDriver();

            /**
             * @short
             * @param _pruNumber
             */
            void
            usePru (uint8_t _pruNumber);

            void
            setPruState (uint8_t _pruNumber, PRU_STATE _state);

            void
            releasePru (uint8_t _pruNumber);

        private:

            volatile uint8_t*
            getSharedMemory ();

            /**
             * @short default constructor.
             * @remark this class is a singelton class. Use static method \c getInstance to get the reference to the global instance
             */
            PruDriver();

            /**
             * @short copy constructor.
             * @warning This is not implemented
             * @param other source instance
             */
            PruDriver(const PruDriver& other) = delete;

            /**
             * @short copy operator
             * @warning This is not implemented
             * @param other source instance
             * @return none
             */
            PruDriver&
            operator =(const PruDriver& other) = delete;

            PRU_STATE pruState[PRU_COUNT];
            volatile uint8_t* ptSharedMemory;
            std::mutex lock;
    };

} /* namespace BeagleBoneResources */

#endif /* CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUDRIVER_H_ */
