//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "CCEventHandle.h"

NS_CC_YHLIB_BEGIN

CCEventHandle::~CCEventHandle()
{
	CCLOG("CCEventHandle destroy begin ");
    CC_SAFE_RELEASE(m_pTarget);
    CCLOG("CCEventHandle destroy end ");
}

//void CCEventHandle::execute(CCEvent *event)
//{
//	if(m_handle){
//		(m_pTarget->*m_handle)(event);
//	}
//}


NS_CC_YHLIB_END