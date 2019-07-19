/*
 * Event.cpp
 *
 *  Created on: 07.12.2014
 *      Author: hegesimo
 */

#include "common/Event.h"
#include "exceptions/ArgumentFaultException.h"
#include "exceptions/ExceptionsMacros.h"

namespace GaGCppAPI {

    // **************************************************************************************************
    // ** Event
    // **************************************************************************************************
    Event::Event()
    {
        mLastIndex = 0;
    }

    // **************************************************************************************************
    // ** Event (move constructor)
    // **************************************************************************************************
    Event::Event(Event&& _other)
    {
        mHandlerList = std::move(_other.mHandlerList);
        mLastIndex = _other.mLastIndex;

        _other.mHandlerList.clear();

        for (auto info : mHandlerList) {
            info->event = this;
        }
    }

    // **************************************************************************************************
    // ** ~Event
    // **************************************************************************************************
    Event::~Event()
    {
        for (auto info : mHandlerList) {
            const_cast<EventHandler*>(info->ptClass)->destroyConnection(info);
        }
        mHandlerList.clear();
    }

    // **************************************************************************************************
    // ** fire
    // **************************************************************************************************
    void
    Event::fire (uint32_t _arg2)
    {
        for (auto cb : mHandlerList) {
            cb->ptClass->callBack(cb->arg1, _arg2);
        }
    }

    // **************************************************************************************************
    // ** attach
    // **************************************************************************************************
    void
    Event::attach(std::shared_ptr<tCallBackInfo>& _c)
    {
        VALIDATE_ARGUMENT_NO_NULL_PT(_c->ptClass);
        VALIDATE_ARGUMENT_EQUAL(_c->handler, 0);

        mLastIndex++;
        _c->handler = mLastIndex;
        _c->event = this;
        mHandlerList.push_back(_c);
    }

    // **************************************************************************************************
    // ** detach
    // **************************************************************************************************
    void
    Event::detach(std::shared_ptr<tCallBackInfo>& _c)
    {
        VALIDATE_ARGUMENT_EQUAL(_c->event, this);

        for (auto cbi = mHandlerList.begin(); cbi != mHandlerList.end(); cbi++ ) {
            if ((*cbi)->handler == _c->handler) {
                mHandlerList.erase(cbi);
                break;
            }
        }
    }

    // **************************************************************************************************
    // ** operator=
    // **************************************************************************************************
    Event&
    Event::operator= (Event&& _other)
    {
        mHandlerList = std::move(_other.mHandlerList);
        mLastIndex = _other.mLastIndex;

        _other.mHandlerList.clear();

        for (auto info : mHandlerList) {
            info->event = this;
        }

        return (*this);
    }

} /* namespace GaGCppAPI */
