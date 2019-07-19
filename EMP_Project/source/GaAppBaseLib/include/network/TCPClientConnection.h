/**
 * @file TCPConnection.h
 * @short contain definition of class \c TCPConnection
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
#ifndef SOURCE_GaAppBaseLib_INCLUDE_NETWORK_TCPCLIENTCONNECTION_H_
#define SOURCE_GaAppBaseLib_INCLUDE_NETWORK_TCPCLIENTCONNECTION_H_

// System header
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

#define DEBUG_OUTPUT 1
#define RECSLEEP 1000

// external library header
#include "boost/thread.hpp"

// local library header

namespace GaAppBaseLib {

    class TCPConnection
    {
        public:
            /**
             * @short constructor
             */
            TCPConnection();

            /**
             * @short destructor
             */
            virtual
            ~TCPConnection();

            /**
             * @short start connection to \c _host on service port \c _port
             * @param _hostName host name or IP address (IPv4)
             * @param _hostPort host port number
             * @param _localPort local port number
             */
            struct tcpReceive
            {
                    std::string input;
                    bool newDataReady;
            };

            void
            openConnection (std::string _hostName,uint16_t _hostPort);
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

            int sockfd;
            struct sockaddr_in serv_addr;
            struct hostent *server;

            std::string sendString;         ///< @short Telegram data to send
            std::string receiveString;      ///< @short

            std::string mLoggerName;

            boost::thread* mComThread;      ///< @short thread to handle communication
            bool mStopThread;               ///< @short signal stop to communication thread


    };

} /* namespace GaAppBaseLib */

#endif /* SOURCE_GaAppBaseLib_INCLUDE_NETWORK_TCPCONNECTION_H_ */
