//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "CCAsyncMessageManager.h"

NS_CC_YHLIB_BEGIN

const int kNullObjectId=0;

static CCAsyncMessageManager* s_sharedMessageManagerInstance=NULL;

CCAsyncMessageManager::CCAsyncMessageManager()
{

}

CCAsyncMessageManager::~CCAsyncMessageManager()
{

}

CCAsyncMessageManager* CCAsyncMessageManager::sharedAsyncMessageManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new CCAsyncMessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

bool CCAsyncMessageManager::init()
{
	return true;
}

/**
 * 发送消息。
 */
void CCAsyncMessageManager::dispatchMessage(CCMessage* message,float delay)
{

}

NS_CC_YHLIB_END
