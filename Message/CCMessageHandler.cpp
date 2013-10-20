//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "CCMessageHandler.h"

NS_CC_YHLIB_BEGIN

CCMessageHandler::~CCMessageHandler()
{
	//CCLOG("CCMessageHandler destroy begin ");
    CC_SAFE_RELEASE(m_pTarget);
    //CCLOG("CCMessageHandler destroy end ");
}

NS_CC_YHLIB_END