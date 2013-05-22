//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCNormalMessageManager.h"

NS_CC_YHLIB_BEGIN

static CCNormalMessageManager* s_sharedNormalMessageManagerInstance=NULL;

CCNormalMessageManager* CCNormalMessageManager::sharedNormalMessageManager(void)
{
	if (!s_sharedNormalMessageManagerInstance) {
		s_sharedNormalMessageManagerInstance=new CCNormalMessageManager();
		s_sharedNormalMessageManagerInstance->init();
	}
	return s_sharedNormalMessageManagerInstance;
}

void CCNormalMessageManager::dispatchMessage(CCMessage* message)
{
	//NSAssert(message.type!=0,)
		//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		dispatchMessageMap(msgMap,message);
	}
}

NS_CC_YHLIB_END
