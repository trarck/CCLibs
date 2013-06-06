
#ifndef YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_
#define YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "Event.h"
#include "EventHandle.h"

NS_CC_YHLIB_BEGIN

class EventListenerManager:public CCObject
{
public:
    EventListenerManager();

    ~EventListenerManager();

    bool init();

    static EventListenerManager* sharedEventListenerManager();

    void addEventListener(CCNode* target,const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle);
        
    void removeEventListener(CCNode* target,const char* type,CCObject* handleObject,yhlib::SEL_EventHandle handle);

	void removeEventListener(CCNode* target,const char* type,CCObject* handleObject);

	void removeEventListenerForHandle(CCNode* target,const char* type,yhlib::SEL_EventHandle handle);
        
    void dispatchEvent(CCNode* target,yhlib::Event* evt);

    void handleEvent(CCNode* target,yhlib::Event* evt);

    bool isListened(CCArray* listeners,yhlib::SEL_EventHandle handle,CCObject* handleObject) ;

    CCArray* getEventListeners(CCNode* target,const char* type);
    //把new EventObject和dispatchEvent和起来，提供简便方法
    void trigger(CCNode* target,const char* type,CCObject* data,bool bubbles);
  
protected:

    void removeListeners(CCArray* listeners,CCObject* handleObject);
    void removeListeners(CCArray* listeners,CCObject* handleObject,yhlib::SEL_EventHandle handle);
	void removeListenersForHandle(CCArray* listeners,yhlib::SEL_EventHandle handle);

	void removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject);
	void removeListenerMap(CCDictionary* listenerMap,CCObject* handleObject,yhlib::SEL_EventHandle handle);
	void removeListenerMapForHandle(CCDictionary* listenerMap,yhlib::SEL_EventHandle handle);

protected:
	CCDictionary* m_pListeners;
};
NS_CC_YHLIB_END
#endif  // YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_