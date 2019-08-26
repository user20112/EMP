/**
 * @file Event.h
 * @short contain definition of class \c GaGCppAPI::Event
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENT_H_
#define SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENT_H_

// System header
#include <iostream>
#include <vector>
#include <memory>

// external library header

// local library header
#include "common/EventHandler.h"


namespace GaGCppAPI {

    /**
     * @short Event class. several instances of \c EventHandler can attach to event and will be called, when event is fired.
     */
    class Event
    {
        public:
            /**
             * @short default constructor
             */
            Event();

            /**
             * @short move constructor
             * @param _other source instance
             */
            Event(Event&& _other);

            /**
             * @short clean up, when event is not needed anymore
             */
            virtual ~Event();

            /**
             * @short fire event and call all call backs, listed in vector \c mHandlerListm
             * @param _arg2 free parameter, defined by event sender
             */
            void
            fire (uint32_t _arg2);

            /**
             * @short add event handler to event handler list
             * @param _c eventHandler to add to list
             */
            void
            attach(std::shared_ptr<tCallBackInfo>& _c);

            /**
             * @short remove event handler from event handler list
             * @param _c eventHandler to remove from list
             */
            void
            detach(std::shared_ptr<tCallBackInfo>& _c);

            /**
             * @short move operator
             * @param _other source instance
             */
            Event&
            operator= (Event&& _other);

        private:
            /**
             * @short copy constructor. copy of event is not possible, because the internal list can't be duplicated!
             * @param _other source instance
             */
            Event(Event& _other) = delete;

            /**
             * @short copy operator. copy of event is not possible, because the internal list can't be duplicated!
             * @param _other source instance
             * @return none
             */
            Event&
            operator= (Event& _other) = delete;

            /**
             * @short list of attached event handler. All member will be called, when event is fired.
             */
            std::vector<std::shared_ptr<tCallBackInfo>> mHandlerList;

            /**
             * @short last hander index
             */
            uint32_t mLastIndex;
    };

} /* namespace GaGCppAPI */

#endif /* SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENT_H_ */
