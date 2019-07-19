/*
 * HardWareDriver.h
 *
 *  Created on: 17.02.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_HARDWAREDRIVER_H_
#define CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_HARDWAREDRIVER_H_

#include <vector>
#include <string>

namespace BBBResources {

    class HardWareDriver
    {
        public:
            HardWareDriver();
            virtual ~HardWareDriver();

            static void
            activateModule (std::string _moduleName);

            static bool
            isModuleActive (std::string _moduleName);

        private:

    };

} /* namespace BBBResources */

#endif /* CHUCKCOOLING_SOURCE_BEAGLEBONERESOURCES_INCLUDE_HARDWAREDRIVER_H_ */
