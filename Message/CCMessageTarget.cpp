#include "CCMessageManager.h"
#include "CCMessageTarget.h"

NS_CC_YHLIB_BEGIN


void CCMessageTarget::registerMessage(unsigned int type,SEL_MessageHandler handle , CCObject* pSender)
{
    CCMessageManager::defaultManager()->registerReceiver(this,type,pSender,handle);
}

void CCMessageTarget::unregisterMessage(unsigned int type ,SEL_MessageHandler handle ,CCObject* pSender)
{
    CCMessageManager::defaultManager()->removeReceiver(this,type,pSender,handle);
}

void CCMessageTarget::sendMessage(unsigned int type ,CCObject* pReceiver ,CCObject* data)
{
    CCMessageManager::defaultManager()->dispatchMessage(type,this,pReceiver,data);
}

void CCMessageTarget::sendMessage(unsigned int type ,CCObject* pReceiver)
{
    CCMessageManager::defaultManager()->dispatchMessage(type,this,pReceiver);
}

void CCMessageTarget::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}

NS_CC_YHLIB_END
