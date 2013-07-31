//
//  Message.m
//  Message

//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCMessage.h"

NS_CC_YHLIB_BEGIN


CCMessage::~CCMessage(void)
{
    CCLOG("Message destroy begin");
    CC_SAFE_RELEASE_NULL(m_sender);
    CC_SAFE_RELEASE_NULL(m_receiver);
//    CC_SAFE_RELEASE(m_dData);
    CC_SAFE_RELEASE_NULL(m_pData);
	CC_SAFE_RELEASE_NULL(m_pExtData);
    CCLOG("Message destroy end");
}

NS_CC_YHLIB_END