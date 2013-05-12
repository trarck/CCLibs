
#ifndef YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_
#define YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCEvent.h"
#include "CCEventHandle.h"

NS_CC_YHLIB_BEGIN

class CCEventListenerManager:public CCObject
{
public:
    CCEventListenerManager();

    ~CCEventListenerManager();

    bool init();

    void addEventListener(CCObject* target,const char* type,SEL_EventHandle handle,CCObject* handleObject,CCObject* data);
        
    void removeEventListener(CCObject* target,const char* type,SEL_EventHandle handle) ;
        
    void dispatchEvent(CCObject* target,CCEvent* event);

    void handleEvent(CCObject* target,CCEvent* event);

    bool isListened(CCArray* listeners,SEL_EventHandle handle) ;

    int getHandlerIndex(CCArray* listeners,SEL_EventHandle handle) ;

    CCArray* getEventListeners(CCObject* target,const char* type);
    //把new EventObject和dispatchEvent和起来，提供简便方法
    void trigger(CCObject* target,const char* type,CCDictionary* data,bool bubbles);
   
protected:

};
NS_CC_YHLIB_END
#endif  // YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_