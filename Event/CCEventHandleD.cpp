//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "CCEventHandle.h"

NS_CC_YHLIB_BEGIN

CCEventHandleD::~CCEventHandle()
{
	CCLOG("CCEventHandle destroy begin ");
    CC_SAFE_RELEASE(m_data);
    CCLOG("CCEventHandle destroy end ");
}

void CCEventHandleD::execute(CCEvent *event)
{
	if(m_handle){
		(m_pTarget->*m_handle)(event,m_data);
	}
}


NS_CC_YHLIB_END