//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "CCSpecMessageManager.h"

NS_CC_BEGIN

CCSpecMessageManager::CCSpecMessageManager()
{
    m_regiesterMap=new CCDictionary();
}

CCSpecMessageManager::~CCSpecMessageManager()
{
    CC_SAFE_RELEASE(m_regiesterMap);
}

CCSpecMessageManager* CCSpecMessageManager::s_sharedSpecMessageManagerInstance=NULL;

CCSpecMessageManager* CCSpecMessageManager::sharedSpecMessageManager(void)
{
	if (!s_sharedSpecMessageManagerInstance) {
		s_sharedSpecMessageManagerInstance=new CCSpecMessageManager();
		s_sharedSpecMessageManagerInstance->init();
	}
	return s_sharedSpecMessageManagerInstance;
}



bool CCSpecMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,MessageType type ,CCObject* sender ,CCObject*  handleObject)
{
    bool result=CCCompleteMessageManager::registerReceiver(receiver, handle, type, sender,handleObject);
    //注册成功
    if(result){
        CCDictionary *regiesterMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
        if (regiesterMap==NULL) {
            regiesterMap=new CCDictionary();
            m_regiesterMap->setObject(regiesterMap,receiver->m_uID);
            regiesterMap->release();
        }
        CCDictionary *msgMap=(CCDictionary*) regiesterMap->objectForKey(type);
        if (msgMap==NULL) {
            msgMap=new CCDictionary();
            regiesterMap->setObject(msgMap,type);
            msgMap->release();
        }
        
        sender=sender==NULL?m_globalObject:sender;
        unsigned int senderKey=sender->m_uID;
        CCArray *senderList=(CCArray*)msgMap->objectForKey(senderKey);
        if (!senderList) {
            senderList=new CCArray();
            msgMap->setObject(senderList,senderKey);
            senderList->release();
        }
        //不用检查是否已经注册过，在父类中已经检查过了

        //register for handler
        CCMessageHandler *handler=new CCMessageHandler();
        handler->initWithTarget(handleObject,handle);
        senderList->addObject(handler);
        handler->release();

    }
    
    return result;
}

bool CCSpecMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle,MessageType type ,CCObject* sender)
{
        
    return registerReceiver(receiver, handle, type, sender,receiver);
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver,MessageType type ,CCObject* sender,SEL_MessageHandler handle)
{
    
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver,MessageType type ,CCObject* sender)
{
    
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver,MessageType type)
{
    
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver)
{
    
}

NS_CC_END
