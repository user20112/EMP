/*
 * Browser.cpp
 *
 *  Created on: 28.04.2015
 *      Author: s.hegemann
 */

#include <iostream>

#include <gaapi/api.h>

#include "log/Logger.h"
#include "exceptions/ExceptionsMacros.h"


#include "browsing/Browser.h"
#include "exceptions/GammaFaultException.h"

namespace GaGCppAPI {

    Browser::Browser()
    {
    }

    Browser::~Browser()
    {
    }


    std::vector<SharedPV>
    Browser::findPVs(BrowserFilter& _filter)
    {
        el::Loggers::getLogger("Browser");

        std::vector<SharedPV> resutlList;
        gc_Level6Address addr;

        CLOG(INFO, "Browser") << "start browsing:";

        CLOG(DEBUG, "Browser") << "used filter settings:";
        CLOG(DEBUG, "Browser") << "  filter System                    ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::System);
        CLOG(DEBUG, "Browser") << "  filter Node                      ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Node);
        CLOG(DEBUG, "Browser") << "  filter Memory                    ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Memory);
        CLOG(DEBUG, "Browser") << "  filter Group                     ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Group);
        CLOG(DEBUG, "Browser") << "  filter PV_Name                   ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::PV_Name);
        CLOG(DEBUG, "Browser") << "  filter Property_Type             ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Property_Type);
        CLOG(DEBUG, "Browser") << "  filter Property_Name             ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Property_Name);
        CLOG(DEBUG, "Browser") << "  filter Property_Name_And_Value   ==> " << _filter.getFilterExpression(BrowserFilter::FilterType::Property_Name_And_Value);


        std::vector<gc_BrowserInfo> systemList = browseInfo(gc_BROWSING_TYPE_SYSTEM, addr);
        for (std::vector<gc_BrowserInfo>::iterator systemInfo =  systemList.begin(); systemInfo < systemList.end(); systemInfo++ ) {
            const gc_SystemInfo* curSystemInfo = &systemInfo->info.system;

            if (!_filter.fit(BrowserFilter::FilterType::System, curSystemInfo->name)) {
                continue;
            }

            addr.system = curSystemInfo->address;

            std::vector<gc_BrowserInfo> nodeList = browseInfo(gc_BROWSING_TYPE_NODE, addr);
            for (std::vector<gc_BrowserInfo>::iterator nodeInfo =  nodeList.begin(); nodeInfo < nodeList.end(); nodeInfo++ ) {
                const gc_NodeInfo* curNodeInfo = &nodeInfo->info.node;

                if (!_filter.fit(BrowserFilter::FilterType::Node, curNodeInfo->name)) {
                    continue;
                }

                addr.index1 = curNodeInfo->address.index1;
                std::vector<gc_BrowserInfo> memoryList = browseInfo(gc_BROWSING_TYPE_MEMORY, addr);
                for (std::vector<gc_BrowserInfo>::iterator memoryInfo =  memoryList.begin(); memoryInfo < memoryList.end(); memoryInfo++ ) {
                    const gc_MemoryInfo* curMemoryInfo = &memoryInfo->info.memory;

                    if (!_filter.fit(BrowserFilter::FilterType::Memory, curMemoryInfo->modelName)) {
                        continue;
                    }

                    addr.index2 = curMemoryInfo->address.index2;
                    std::vector<gc_BrowserInfo> groupList = browseInfo(gc_BROWSING_TYPE_GROUP, addr);
                    for (std::vector<gc_BrowserInfo>::iterator groupInfo =  groupList.begin(); groupInfo < groupList.end(); groupInfo++ ) {
                        const gc_GroupInfo* curGroupInfo = &groupInfo->info.group;

                        if (!_filter.fit(BrowserFilter::FilterType::Group, curGroupInfo->name)) {
                            continue;
                        }

                        addr.index3 = curGroupInfo->address.index3;
                        std::vector<gc_BrowserInfo> pvArrayList = browseInfo(gc_BROWSING_TYPE_PV_ARRAY, addr);
                        for (std::vector<gc_BrowserInfo>::iterator pvArrayInfo =  pvArrayList.begin(); pvArrayInfo < pvArrayList.end(); pvArrayInfo++ ) {
                            const gc_PVArrayInfo* curPVArrayInfo = &pvArrayInfo->info.pvArray;

                            if (!_filter.fit(BrowserFilter::FilterType::PV_Name, curPVArrayInfo->name)) {
                                continue;
                            }
                            if (!_filter.fit(BrowserFilter::FilterType::PV_Type, pvArrayInfo->info.pvArray.type)) {
                                continue;
                            }

                            addr.index4 = curPVArrayInfo->address.index4;
                            for (size_t pvIndex = 0; pvIndex < curPVArrayInfo->noElements; pvIndex++ ) {
                                addr.index5 = pvIndex;

                                gc_Flags32Bit flag;
                                if (curSystemInfo->address == gc_LOCAL_SYSTEM_ADDRESS_VALUE) {
                                    flag = ga_PV_PROPERTY_ACC_NON_BLOCKING;
                                }
                                else {
                                    flag = ga_PV_PROPERTY_ACC_BLOCKING;
                                }
                                SharedPV PV(&addr, flag);

                                if (!_filter.fit(BrowserFilter::FilterType::Property_Type, PV)) {
                                    continue;
                                }
                                if (!_filter.fit(BrowserFilter::FilterType::Property_Name, PV)) {
                                    continue;
                                }
                                if (!_filter.fit(BrowserFilter::FilterType::Property_Name_And_Value, PV)) {
                                    continue;
                                }

                                resutlList.push_back(PV);

                                CLOG(TRACE, "Browser") << " --> add PV " << PV.getName();
                            } // for (size_t pvIndex
                        } // for (vector<gc_BrowserInfo>::iterator pvArrayInfo
                    } // for (vector<gc_BrowserInfo>::iterator
                } // for (vector<gc_BrowserInfo>::iterator memoryInfo
            } // for (vector<gc_BrowserInfo>::iterator nodeInfo
        } // for (vector<gc_BrowserInfo>::iterator systemInfo

        return (std::move(resutlList));
    }


    std::vector<gc_BrowserInfo>
    Browser::browseInfo (const gc_BrowsingType _type,
                         gc_Level6Address _params)
    {
        std::vector<gc_BrowserInfo> resultList;
        gc_ErrorID result;
        size_t numElementsSystem;

        result = ga_browse_startByIndices(_type, _params.system, _params.index1, _params.index2, _params.index3, _params.index4, &numElementsSystem);
        if (result != gc_ERROR_SUCCESS.errorID) {
            THROW_GAMMA_FAULT(result) << "unable to browse by Indices: type = " << _type
                                                               << "; system = " << _params.system
                                                               << "; index1 = " << _params.index1
                                                               << "; index2 = " << _params.index2
                                                               << "; index3 = " << _params.index3
                                                               << "; index4 = " << _params.index4;
        }

        if (numElementsSystem != 0)
        {
            gc_BrowserInfo systemInfo[numElementsSystem];
            result = ga_browse_getInfo (systemInfo, numElementsSystem, 0, 0);
            if (result != gc_ERROR_SUCCESS.errorID) {
                THROW_GAMMA_FAULT(result) << "unable to get browsing info for " << _type << ": numElementsSystem = " << numElementsSystem;
            }

            for (size_t iSystem = 0; iSystem < numElementsSystem; iSystem++) {
                resultList.push_back(systemInfo[iSystem]);
            }
        }

        ga_browse_stop();
        return (std::move(resultList));
    }

} /* namespace GaGCppAPI */
