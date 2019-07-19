/**
 * @file NetworkHelper.h
 * @short contain definition of class \c GaAppBaseLib::NetworkHelper
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */#ifndef SOURCE_GaAppBaseLib_INCLUDE_NETWORK_NETWORKHELPER_H_
#define SOURCE_GaAppBaseLib_INCLUDE_NETWORK_NETWORKHELPER_H_

// System header
#include <string>

// external library header

// local library header

namespace GaAppBaseLib {

     /**
      * @short collection of static network functions and constant values
      *
      * @remark
      * this class contains static functions only.
      */
    class NetworkHelper
    {
        public:
            /**
             * @short destructor
             */
            virtual ~NetworkHelper();

            /**
             * @short find IP address of given host
             * @param _hostName name of host
             * @return IP address as string
             */
            static std::string
            getIpByName (std::string _hostName);

            /**
             * @short check if given string is a valid IP-Address (IPv4)
             * @param _IP string to check
             * @return true, when _IP is a IPv4 address, otherwise false
             */
            static bool
            isIpValid (std::string _IP);

        private:
            /**
             * @short regular expression for IPv4 address
             */
            static const std::string ipfilter;

            /**
             * @short constructor
             * @remark
             * the constructor is private! This class is only a container for static functions
             */
            NetworkHelper();
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_NETWORK_NETWORKHELPER_H_ */
