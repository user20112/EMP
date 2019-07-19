/**
 * @file EventHandler.h
 * @short contain definition of class \c GaGCppAPI::EventHandler
 *
 * Version Information
 * -------------------
 * $Revision: 29111 $
 * $HeadURL: https://app-aug-svn01.aug.osram.de/svn/aug-sw/TASKS/SOFTWARE/LIBS/CPP/Gamma_IOPlugins/PlugInTemplate/trunk/src/PlugInVersionInfo.template.cpp $
 * $Author: S.Hegemann $
 * $Date: 2014-11-20 11:46:22 +0100 (Do, 20 Nov 2014) $
 *
 */
#ifndef CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENTHANDLER_H_
#define CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENTHANDLER_H_

// System header
#include <vector>
#include <memory>

// external library header

// local library header

namespace GaGCppAPI {

    class EventHandler;
    class Event;

    /**
     * @short call back information. Will be stored by event, when handler is attached.
     *
     */
    using tCallBackInfo = struct _tCallBackInfo {
                              uint32_t handler;
                              Event* event;
                              EventHandler* ptClass;
                              uint32_t arg1;
                          };

    /**
     * @short handler can be attached to an event. function \c callBack will be called, when event is fired.
     */
    class EventHandler
    {
            friend class Event;

        public:
            /**
             * @short default constructor
             */
            EventHandler();

            /**
             * @short move constructor
             * @param _other source instance
             */
            EventHandler(EventHandler&& _other);

            /**
             * @short clean up
             */
            virtual ~EventHandler();

            /**
             * @short call back function. is called, when an attached event is fired.
             * @param _arg1 user argument is given by attach command
             * @param _arg2 user argument is given by fire event
             */
            virtual void
            callBack(uint32_t _arg1, uint32_t _arg2) = 0;

            /**
             * @short attach handler to event \c _event. \c _arg1 is stored and will be the first argument for function \c callBack
             * @param _event event to connect to
             * @param _arg1 user argument 1
             */
            void
            attachToEvent (Event& _event, uint32_t _arg1);

            /**
             * @short detach from event \c _event
             * @param _event event to detach from.
             */
            void
            detachFromEvent (Event& _event);

            /**
             * @short move operator
             * @param _other source instance
             * @return reference to new handler
             */
            EventHandler&
            operator= (EventHandler&& _other);

        private:
            /**
             * @short copy constructor. copy of eventHandler is not possible, because the internal list can't be duplicated!
             * @param _other source instance
             */
            EventHandler(EventHandler& _other) = delete;

            /**
             * @short is called by event, when this is destroyed.
             * @param _c event connection information
             */
            void
            destroyConnection (std::shared_ptr<tCallBackInfo>& _c);

            /**
             * @short copy operator. copy of eventHandler is not possible, because the internal list can't be duplicated!
             * @param _other source instance
             * @return none
             */
            EventHandler&
            operator= (EventHandler& _other) = delete;

            /**
             * @short information list for all active connections
             */
            std::vector<std::shared_ptr<tCallBackInfo>> mHandlerList;
    };

} /* namespace GaGCppAPI */

#endif /* CHUCKCOOLING_SOURCE_GAGCPPAPI_INCLUDE_COMMON_EVENTHANDLER_H_ */
