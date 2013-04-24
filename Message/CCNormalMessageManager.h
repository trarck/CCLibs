//
//  MessageManager.h
//  TODO:对消息优先级的支持,延迟消息
//
//  没有全局消息，当发送者为空时，不是收到所有人发来的消息，而只能收到由空发送人发来的消息。
//	空可以用一个全局对象表示，和普通的对象处理一样处理.当投递普通对象的消息时不，触发全局消息。
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef YHLIB_MESSAGE_CCNORMALMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCNORMALMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCCompleteMessageManager.h"

NS_CC_YHLIB_BEGIN

class CCNormalMessageManager: public CCCompleteMessageManager 
{
public:
	static CCNormalMessageManager* sharedNormalMessageManager();
    void dispatchMessage(CCMessage* message);
private:
	static CCNormalMessageManager* s_sharedNormalMessageManagerInstance;
};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCNORMALMESSAGEMANAGER_H_
