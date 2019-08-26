/**
 * @file PruInterface.h
 * @short contain definition of class \c PruInterface
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUINTERFACE_H_
#define SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUINTERFACE_H_

// System header
#include <string>
#include <vector>

namespace BeagleBoneResources {

    /**
     * @short access to processor PRU, load a program and allow direct memory access.
     */
    class PruInterface
    {
        public:
            /**
             * @short constructor
             * @param _pruNumber number of PRU unit [0 .. 1]
             */
            PruInterface(uint32_t _pruNumber);

            /**
             * @short destructor
             */
            virtual
            ~PruInterface();

            /**
             * @short load and start a program code to the PRU
             * @param _code binary code as array of bytes
             */
            void
            loadProgram (std::vector<uint32_t>& _code);

            /**
             * @short load and start a program code to the PRU
             * @param _filePath file including binary program code
             */
            void
            loadProgram (std::string _filePath);

            /**
             * @short run pasm compiler
             * @param _path
             * @param _fileBase
             * @return 0 when compiling was successfully, otherwise pasm error code
             */
            int32_t
            compileProgram(std::string _path,
                           std::string _fileBase);

            /**
             * @short pointer to local memory of PRU
             * @return pointer to local PRU memory
             */
            volatile uint8_t*
            getLocalMemory();

            /**
             * @short pointer to shared memory of PRU
             * @return pointer to shared PRU memory
             */
            volatile uint8_t*
            getSharedMemory();

        private:
            /**
             * @short initialization routine
             * @param _pruNumber number of PRU unit [0 .. 1]
             */
            void
            init (uint32_t _pruNumber);

            std::string mLoggerName;
            uint32_t pruNumber;                 ///< @short used PRU number
            volatile uint8_t* ptDataMemory;     ///< @short pointer to local PRU memory

            bool mPruActive;
    };

} /* namespace BeagleBoneResources */

#endif /* SOURCE_BEAGLEBONERESOURCES_INCLUDE_PRU_PRUINTERFACE_H_ */
