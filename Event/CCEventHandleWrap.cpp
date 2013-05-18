//
//  MessageHandler.m
//  Message
//
//  Created by trarck trarck on 11-12-27.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "CCEventHandleWrap.h"

NS_CC_YHLIB_BEGIN

CCEventHandleWrap::~CCEventHandleWrap()
{
     CC_SAFE_RELEASE(m_pTarget);
    CC_SAFE_RELEASE(m_data);
}

NS_CC_YHLIB_END