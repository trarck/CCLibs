//
//  MessageHandler.h
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#ifndef YHLIB_MESSAGE_CCMESSAGEHANDLER_H_
#define YHLIB_MESSAGE_CCMESSAGEHANDLER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCMessage;

typedef void (CCObject::*SEL_MessageHandler)(CCMessage*);
#define message_selector(_SELECTOR) (SEL_MessageHandler)(&_SELECTOR)

class CCMessageHandler : public CCObject {
public:
    CCMessageHandler();
    ~CCMessageHandler();
    CCObject* getTarget();
    void setTarget(CCObject* target);
    
    SEL_MessageHandler getHandle();
    void setHandle(SEL_MessageHandler handle);
    
    bool initWithTarget(CCObject* target,SEL_MessageHandler handle);
    void execute(CCMessage* msg);
private:
	CCObject* m_target;
	SEL_MessageHandler m_handle;
};


NS_CC_YHLIB_END

#endif  // YHLIB_MESSAGE_CCMESSAGEHANDLER_H_
