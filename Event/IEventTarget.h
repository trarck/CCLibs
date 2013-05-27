#ifndef YHLIB_EVENT_IEVENTTARGET_H_
#define YHLIB_EVENT_IEVENTTARGET_H_

#include "EventListenerManager.h"

NS_CC_YHLIB_BEGIN

class IEventTarget
{
public:

    virtual void addEventListener(const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle)=0;
    
    virtual void removeEventListener(const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle) =0;

    virtual CCArray* getEventListeners(const char*type)=0;

    virtual void dispatchEvent(yhlib::Event event)=0;

    virtual void trigger(const char*type,CCObject*data,bool bubbles)=0;
};

NS_CC_YHLIB_END

#endif //YHLIB_EVENT_IEVENTTARGET_H_