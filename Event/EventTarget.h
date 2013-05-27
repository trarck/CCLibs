#ifndef YHLIB_EVENT_EVENTTARGET_H_
#define YHLIB_EVENT_EVENTTARGET_H_

#include "EventListenerManager.h"

NS_CC_YHLIB_BEGIN

class EventTarget:public CCObject
{
public:

    inline void addEventListener(const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle) {
        EventListenerManager::sharedEventListenerManager()->addEventListener(this,type,handleObject,handle);
    }
    
    inline void removeEventListener(const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle) {
        EventListenerManager::sharedEventListenerManager()->removeEventListener(this,type,handleObject,handle);
    }

    inline CCArray* getEventListeners(const char*type){
        return EventListenerManager::sharedEventListenerManager()->getEventListeners(this,type);
    }

    inline void dispatchEvent(yhlib::Event event) {
        EventListenerManager::sharedEventListenerManager()->dispatchEvent(this,event);
    }

    inline void trigger(const char*type,CCObject*data,bool bubbles){
        EventListenerManager::sharedEventListenerManager()->trigger(this,type,data,bubbles);
    }
};

NS_CC_YHLIB_END

#endif //YHLIB_EVENT_EVENTTARGET_H_