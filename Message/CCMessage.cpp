//
//  Message.m
//  Message

//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCMessage.h"

using namespace std;

NS_CC_YHLIB_BEGIN


CCMessage::~CCMessage(void)
{
    CCLOG("Message destroy begin");
    CC_SAFE_RELEASE(m_sender);
    CC_SAFE_RELEASE(m_receiver);
//    CC_SAFE_RELEASE(m_dData);
    CC_SAFE_RELEASE(m_pData);
    CCLOG("Message destroy end");
}

NS_CC_YHLIB_END