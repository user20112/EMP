/**
 * @file UDPConnection.cpp
 * @short contain declaration of class \c UDPConnection
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
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

// external library header
#include "boost/bind.hpp"

// local library header
#include "exceptions/ExceptionsMacros.h"
#include "network/NetworkHelper.h"
#include "network/UDPConnection.h"

namespace GaAppBaseLib {

    UDPConnection::UDPConnection()
    {
        mSocketID = -1;
        mHost = "";
        mIP = "";
        mHostPort = 0;
        mLocalPort = 1234;

        mComThread = nullptr;
        mStopThread = false;
    }

    UDPConnection::~UDPConnection()
    {
        closeConnection();
    }

    /**
     * @short start connection to \c _host on service port \c _port
     * @param _host host name or IP address (IPv4)
     * @param _port host port number
     */
    void
    UDPConnection::openConnection(std::string _hostName,
                              uint16_t _hostPort,
                              uint16_t _localPort)
    {
        std::string ip;
        if (!NetworkHelper::isIpValid(_hostName)) {
            mIP = NetworkHelper::getIpByName(_hostName);
        }
        else {
            mIP = _hostName;
        }
        mHostPort = _hostPort;
        mLocalPort = _localPort;

        mSocketID = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, IPPROTO_UDP);
        if (mSocketID < 0) {
            THROW_SYSTEM_FAULT() << "unable to create UDP socket.";
        }

        bzero((void*) &mLocAddr, (unsigned int) sizeof(mLocAddr));
        mLocAddr.sin_family = AF_INET;
        mLocAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        mLocAddr.sin_port = htons(mLocalPort);

        bzero((void*) &mRemAddr, (unsigned int) sizeof(mRemAddr));
        mRemAddr.sin_family = AF_INET;
        mRemAddr.sin_addr.s_addr = inet_addr(mIP.c_str());
        mRemAddr.sin_port = htons(mHostPort);

        int32_t retVal = bind(mSocketID, (const sockaddr*) &mLocAddr, (unsigned int) sizeof(mLocAddr));
        if (retVal < 0) {
            THROW_SYSTEM_FAULT() << "unable to open UDP port " << mLocalPort << ").";
        }

        mStopThread = false;
        mComThread = new boost::thread(boost::bind(&UDPConnection::comThread, this));
    }

    void
    UDPConnection::closeConnection()
    {
        if (mComThread != nullptr) {
            mStopThread = true;
            mComThread->join();
            delete mComThread;
            mComThread = nullptr;
        }
        if (mSocketID >= 0) {
            close(mSocketID);
            mSocketID = -2;
        }
    }

    void
    UDPConnection::putString (std::string _str)
    {
        sendString += _str;
    }

    bool
    UDPConnection::hasData()
    {
        return (!receiveString.empty());
    }

    std::string
    UDPConnection::getString ()
    {
        std::string val = receiveString;
        receiveString.clear();
        return (val);
    }

    char
    UDPConnection::getChar ()
    {
        char val = '\0';
        if (!receiveString.empty()) {
            receiveString.at(0);
            receiveString.erase(0, 1);
        }
        return (val);
    }

    void
    UDPConnection::comThread()
    {
        int retVal = 0;
        char buffer[1024+4] = {0};
        struct sockaddr_in sender;
        unsigned int senderLen = sizeof(sender);

        std::cout << mIP << ":" << mHostPort <<  ": UDP communication thread started!" << std::endl;
        while (!mStopThread) {
            // check for new input data
            // send data
            if (!sendString.empty()) {
                retVal = sendto(mSocketID, (const void*)sendString.c_str(), (unsigned int)sendString.length(), 0, (struct sockaddr *)&mRemAddr, (unsigned int) sizeof(mRemAddr));
                if (retVal < 0) {
                    if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
                        THROW_SYSTEM_FAULT() << "unable to send data to " << mIP << ":" << mHostPort;
                    }
                }
                /* std::cout << mIP << ":" << mHostPort <<  ": send data \"" << sendString.substr(0, retVal) << "\"" << std::endl; */
                sendString.erase(0, retVal);
            }

            memset (buffer, 0, sizeof(buffer));
            retVal = recvfrom(mSocketID, (void*)buffer, 1024, 0, (struct sockaddr *) &sender, &senderLen);
            if (retVal < 0) {
                if ((errno != EAGAIN) && (errno != EWOULDBLOCK)) {
                    THROW_SYSTEM_FAULT() << "unable to send data to " << mIP << ":" << mHostPort;
                }
            }
            else {
                receiveString += buffer;
            }

            usleep(1000);
        }
        std::cout << mIP << ":" << mHostPort <<  ": UDP communication thread stopped!" << std::endl;
    }

} /* namespace GaAppBaseLib */
