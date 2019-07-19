/**
 * @file UDPConnection.h
 * @short contain definition of class \c UDPConnection
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_NETWORK_UDPCONNECTION_H_
#define SOURCE_GaAppBaseLib_INCLUDE_NETWORK_UDPCONNECTION_H_

// System header
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

// external library header
#include "boost/thread.hpp"

// local library header

namespace GaAppBaseLib {

    class UDPConnection
    {
        public:
            /**
             * @short constructor
             */
            UDPConnection();

            /**
             * @short destructor
             */
            virtual
            ~UDPConnection();

            /**
             * @short start connection to \c _host on service port \c _port
             * @param _hostName host name or IP address (IPv4)
             * @param _hostPort host port number
             * @param _localPort local port number
             */
            void
            openConnection (std::string _hostName,
                            uint16_t _hostPort,
                            uint16_t _localPort);

            /**
             * @short close connection and clean up
             */
            void
            closeConnection();

            bool
            isConnected();

            void
            putString (std::string _str);

            bool
            hasData();

            std::string
            getString ();

            char
            getChar ();



        private:

            /**
             * @short function to handle communication. Will be started in own thread
             */
            void
            comThread();

            int mSocketID;                  ///< @short id of created socket
            std::string mHost;
            std::string mIP;
            uint16_t mHostPort;
            uint16_t mLocalPort;
            struct sockaddr_in mLocAddr;    ///< @short UPD Local informations
            struct sockaddr_in mRemAddr;    ///< @short UPD Remote informations
            std::string sendString;         ///< @short Telegram data to send
            std::string receiveString;      ///< @short

            std::string mLoggerName;

            boost::thread* mComThread;      ///< @short thread to handle communication
            bool mStopThread;               ///< @short signal stop to communication thread
    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_NETWORK_UDPCONNECTION_H_ */
