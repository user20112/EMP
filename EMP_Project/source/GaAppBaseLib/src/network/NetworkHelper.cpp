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
 */
// System header
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>

// external library header
#include <boost/regex.hpp>

// local library header
#include "exceptions/ExceptionsMacros.h"
#include "network/NetworkHelper.h"


namespace GaAppBaseLib {

    const std::string NetworkHelper::ipfilter = "(((25[0-5])|(2[0-4][0-9])|([12]?[0-9][0-9]?))\\.){3}((25[0-5])|(2[0-4][0-9])|([1]?[0-9][0-9]?))";

    // ******************************************************************************************************************
    // ***  NetworkHelper
    // ******************************************************************************************************************
    NetworkHelper::NetworkHelper()
    {
    }

    // ******************************************************************************************************************
    // ***  ~NetworkHelper
    // ******************************************************************************************************************
    NetworkHelper::~NetworkHelper()
    {
    }

    // ******************************************************************************************************************
    // ***  getIpByName
    // ******************************************************************************************************************
    std::string
    NetworkHelper::getIpByName(std::string _hostName)
    {
        std::string ipAddr;

        struct hostent *he;
        struct in_addr **addr_list;
        int i;

        if ((he = gethostbyname(_hostName.c_str())) == NULL)
        {
            THROW_SYSTEM_FAULT() << "unable to resolve host name " << _hostName;
        }

        addr_list = (struct in_addr **) he->h_addr_list;

        for (i = 0; addr_list[i] != NULL; i++)
        {
            //Return the first one;
            ipAddr = inet_ntoa(*addr_list[i]);
            break;
        }

        return (ipAddr);
    }

    // ******************************************************************************************************************
    // ***  isIpValid
    // ******************************************************************************************************************
    bool
    NetworkHelper::isIpValid (std::string _IP)
    {
        bool fit = false;
        try {
            fit = boost::regex_match(_IP, boost::regex(ipfilter));
        }
        catch (std::runtime_error& e) {
            std::cerr << "isIpValid: regular expression failed: " << e.what() << std::endl;
            fit = false;
        }
        return (fit);
    }

} /* namespace GaAppBaseLib */
