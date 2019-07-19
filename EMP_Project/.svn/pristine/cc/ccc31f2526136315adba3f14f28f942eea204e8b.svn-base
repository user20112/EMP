/**
 * @file TCPConnection.cpp
 * @short contain declaration of class \c TCPConnection
 *
 * Version Information
 * -------------------
 * $Revision$
 * $HeadURL$
 * $Author$
 * $Date$
 *
 */
// System header
#include "network/TCPClientConnection.h"

#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

// external library header
#include "boost/bind.hpp"

// local library header
#include "exceptions/ExceptionsMacros.h"
#include "log/logger.h"
#include "network/NetworkHelper.h"

namespace GaAppBaseLib {

    TCPConnection::TCPConnection()
    {
        sockfd = -1;
        //serv_addr.sin_addr = (in_addr) 0;
        serv_addr.sin_family = -1;
        serv_addr.sin_port = -1;
        //serv_addr.sin_zero = '0';
        server = NULL;
        mComThread = nullptr;
        mStopThread = false;

        mLoggerName = "TCP";

        std::string sendString;         ///< @short Telegram data to send
        std::string receiveString;      ///< @short
    }

    TCPConnection::~TCPConnection()
    {
        closeConnection();
    }

    /**
     * @short start connection to \c _host on service port \c _port
     * @param _host host name or IP address (IPv4)
     * @param _port host port number
     */
    void
    TCPConnection::openConnection(std::string _hostName,uint16_t _hostPort)
    {
        const char *chostName = _hostName.c_str();
        sockfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
//        sockfd = socket(AF_INET, SOCK_STREAM, 0);
//        int status = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
//        if (status == -1){
//            CLOG(INFO, mLoggerName.c_str()) << "Unable to change TCP sock to non blocking mode \n ";
//            THROW_SYSTEM_FAULT() << "Unable to change TCP sock to non blocking mode";
//        }


        if(sockfd < 0)
        {
            #ifdef DEBUG_OUTPUT
            std::cout << "ERROR unable to connect to TCP socket" << sockfd << "\n";
            #endif
            CLOG(INFO, mLoggerName.c_str()) << "Unable to open TCP socket \n ";
            THROW_SYSTEM_FAULT() << "unable to create TCP socket.";
        }

        server = gethostbyname(chostName);
        if(server == NULL)
        {
            #ifdef DEBUG_OUTPUT
            std::cout << "ERROR to resolve host name " << chostName << "\n";
            #endif
            CLOG(INFO, mLoggerName.c_str()) << "ERROR to resolve host name " << chostName << "\n";
            THROW_SYSTEM_FAULT() << "unable to resolve server name";
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        //inet_aton(chostName,&serv_addr.sin_addr);
        serv_addr.sin_port = htons(_hostPort);

        #ifdef DEBUG_OUTPUT
        std::cout << "\n\n" << "SockFD " << sockfd << "\n";
        std::cout << "Sockaddr/Serv_addr Sin_zero  " << serv_addr.sin_zero << "\n";
        std::cout << "Sockaddr/Serv_addr Sin_Port  " << serv_addr.sin_port << "\n";
        std::cout << "Sockaddr/Serv_addr Sin_Family  " << serv_addr.sin_family << "\n";
        std::cout << "Sockaddr/Serv_addr Sin_Addr  " << serv_addr.sin_addr.s_addr << "\n";
        std::cout << "Host IP  " << chostName  << "\n";
        std::cout << "Host Port  " << _hostPort  << "\n\n";
        #endif

        errno = 0;
        if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) != 0 && errno != EINPROGRESS)
        {
            #ifdef DEBUG_OUTPUT
            std::cout << "ERROR unable to connect to TCP server\n";
            CLOG(INFO, mLoggerName.c_str()) << "ERROR unable to connect to TCP server\n";
            #endif
            THROW_SYSTEM_FAULT() << "unable to connect to server";
            return;
        }
        else
        {
            #ifdef DEBUG_OUTPUT
            std::cout << "TCP connection is established \n";
            #endif

            sleep(1);
            #ifdef DEBUG_OUTPUT
            std::cout << "Try to set socket to nonblocking mode\n";
            CLOG(INFO, mLoggerName.c_str()) << "Try to set socket to nonblocking mode\n";
            #endif
            int status = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) | O_NONBLOCK);
            if (status == -1){
                #ifdef DEBUG_OUTPUT
                std::cout << "Unable to change TCP sock to non blocking mode \n ";
                CLOG(INFO, mLoggerName.c_str()) << "Unable to change TCP sock to non blocking mode \n ";
                #endif
                THROW_SYSTEM_FAULT() << "Unable to change TCP sock to non blocking mode";
            }

            #ifdef DEBUG_OUTPUT
            std::cout << "TCP connection is established\n";
            CLOG(INFO, mLoggerName.c_str()) <<  "TCP connection is established \n";
            #endif

            mStopThread = false;
            mComThread = new boost::thread(boost::bind(&TCPConnection::comThread, this));
            //Wird problemlos durchlaufen
        }
    }

    void
    TCPConnection::closeConnection()
    {
        CLOG(INFO, mLoggerName.c_str()) <<  "close connection";
       if (mComThread != nullptr) {
            mStopThread = true;
            mComThread->join();
            delete mComThread;
            mComThread = nullptr;
        }

        if (sockfd >= 0) {
            close(sockfd);
            sockfd = -2;
        }
        mLoggerName = "TCP";
    }

    bool
    TCPConnection::isConnected()
    {
      return (sockfd >= 0);
    }

    void
    TCPConnection::putString (std::string _str)
    {
        sendString += _str;
    }

    bool
    TCPConnection::hasData()
    {
        return (!receiveString.empty());
    }

    std::string
    TCPConnection::getString ()
    {
        std::string val = receiveString;
        receiveString.clear();
        return (val);
    }

    char
    TCPConnection::getChar ()
    {
        char val = '\0';
        if (!receiveString.empty())
        {
            val = receiveString.at(0);
            receiveString.erase(0, 1);
        }
        return (val);
    }

    void
    TCPConnection::comThread()
    {
        int retVal = 0;
        char buffer[1024+4] = {0};
        //struct sockaddr_in sender;
        //unsigned int senderLen = sizeof(sender);


        CLOG(INFO, mLoggerName.c_str()) <<  "TCP communication thread started!";
        while (!mStopThread) {
            // check for new input data
            // send data
            if (!sendString.empty()) {
                //Debug
                std::cout << "\n\n" << sendString << "\n\n";
                //
                //retVal = sendto(sockfd, (const void*)sendString.c_str(), (unsigned int)sendString.length(), 0, (struct sockaddr *)&mRemAddr, (unsigned int) sizeof(mRemAddr));
                retVal = write(sockfd,(const void*)sendString.c_str(), (unsigned int)sendString.length());
//                if (retVal < 0) {
//                    if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
//                        #ifdef DEBUG_OUTPUT
//                        std::cout << "Unable to send data over tcp \n";
//                        #endif
//                        THROW_SYSTEM_FAULT() << "Unable to send Data over TCP port \n";
//                    }
//                }
                sendString.erase(0, retVal);
            }


            memset (buffer, 0, sizeof(buffer));
            //retVal = recvfrom(mSocketID, (void*)buffer, 1024, 0, (struct sockaddr *) &sender, &senderLen);
            retVal = read(sockfd, buffer, 1024);

            if (retVal < 0) {
                if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {

                    #ifdef DEBUG_OUTPUT
                    std::cout << "Unable to receive data from TCP port \n";
                    CLOG(INFO, mLoggerName.c_str()) << "Unable to receive data from TCP port \n";
                    #endif
                    THROW_SYSTEM_FAULT() << "Unable to receive data from TCP port \n";
                }
            }
            else
            {
               receiveString += buffer;
            }

            usleep(RECSLEEP);
        }
        CLOG(INFO, mLoggerName.c_str()) <<  "TCP communication thread stopped!";
    }




} /* namespace GaAppBaseLib */
