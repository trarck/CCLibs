
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

    void addEventListener(CCNode* target,const char* type,CCObject* handleObject,SEL_EventHandle handle);
        
    void removeEventListener(CCNode* target,const char* type,CCObject* handleObject,SEL_EventHandle handle);
        
    void dispatchEvent(CCNode* target,CCEvent* evt);

    void handleEvent(CCNode* target,CCEvent* evt);

    bool isListened(CCArray* listeners,SEL_EventHandle handle,CCObject* handleObject) ;

    CCArray* getEventListeners(CCNode* target,const char* type);
    //把new EventObject和dispatchEvent和起来，提供简便方法
    void trigger(CCNode* target,const char* type,CCDictionary* data,bool bubbles);
  
protected:
    void removeListeners(CCDictionary* listeners,CCObject* handleObject);
    void removeListeners(CCArray* listeners,CCObject* handleObject);
    void removeListeners(CCArray* listeners,CCObject* handleObject,SEL_EventHandle handle);

protected:
	CCDictionary* m_pListeners;
};
NS_CC_YHLIB_END
#endif  // YHLIB_EVENT_CCEVENTLISTENERMANAGER_H_