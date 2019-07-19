/*
 * EventHandler.cpp
 *
 *  Created on: 07.12.2014
 *      Author: hegesimo
 */

#include <iostream>

#include "common/EventHandler.h"
#include "common/Event.h"

namespace GaGCppAPI {

    // **************************************************************************************************
    // ** EventHandler
    // **************************************************************************************************
    EventHandler::EventHandler()
    {
    }

    // **************************************************************************************************
    // ** EventHandler (move constructor)
    // **************************************************************************************************
    EventHandler::EventHandler(EventHandler&& _other)
    {
        mHandlerList = std::move(_other.mHandlerList);
        for (auto info : mHandlerList) {
            info->ptClass = this;
        }
        _other.mHandlerList.clear();
    }

    // **************************************************************************************************
    // ** ~EventHandler
    // **************************************************************************************************
    EventHandler::~EventHandler()
    {
        for (auto info : mHandlerList) {
            info->event->detach(info);
        }
        mHandlerList.clear();
    }

    // **************************************************************************************************
    // ** attachToEvent
    // **************************************************************************************************
    void
    EventHandler::destroyConnection (std::shared_ptr<tCallBackInfo>& _c)
    {
        for (auto info = mHandlerList.begin(); info != mHandlerList.end(); info++) {
            if ((*info) == _c) {
                mHandlerList.erase(info);
                break;
            }
        }
    }

    // **************************************************************************************************
    // ** attachToEvent
    // **************************************************************************************************
    void
    EventHandler::attachToEvent (Event& _event, uint32_t _arg1)
    {
        std::shared_ptr<tCallBackInfo> info = std::make_shared<tCallBackInfo>(tCallBackInfo {0, nullptr, this, _arg1});
        _event.attach(info);
        mHandlerList.push_back(info);
    }

    // **************************************************************************************************
    // ** detachFromEvent
    // **************************************************************************************************
    void
    EventHandler::detachFromEvent (Event& _event)
    {
        for (auto info = mHandlerList.begin(); info != mHandlerList.end(); info++) {
            if ((*info)->event == &_event) {
                (*info)->event->detach((*info));
                mHandlerList.erase(info);
                break;
            }
        }
    }

    // **************************************************************************************************
    // ** operator= (move operator)
    // **************************************************************************************************
    EventHandler&
    EventHandler::operator= (EventHandler&& _other)
    {
        mHandlerList = std::move(_other.mHandlerList);
        for (auto info : mHandlerList) {
            info->ptClass = this;
        }
        _other.mHandlerList.clear();

        return (*this);
    }


} /* namespace GaGCppAPI */
