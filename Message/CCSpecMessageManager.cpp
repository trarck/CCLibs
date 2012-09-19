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

        //map for handler
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
    CCAssert(receiver!=NULL,"CompleteMessageManage:removeReceiver:receiver can't be null!");
	CCDictionary *regiesterMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
	if (regiesterMap) {
		CCDictionary *msgMap=(CCDictionary*) regiesterMap->objectForKey(type);
		if(msgMap){
			if(sender){
				CCArray *senderList=(CCArray*)msgMap->objectForKey(sender->m_uID);
				if(handle){
					removeReceiverList(senderList,handle);
				}else{
					removeReceiverList(senderList);
				}
			}else{
				//删除所有
				if(handle){
					removeReceiverMap(msgMap,handle);
				}else{
					removeReceiverMap(msgMap);
				}
			}
		}
	}
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver,MessageType type ,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CompleteMessageManage:removeReceiver:receiver can't be null!");
	CCDictionary *regiesterMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
	if (regiesterMap) {
		CCDictionary *msgMap=(CCDictionary*) regiesterMap->objectForKey(type);
		if(msgMap){
			if(sender){
				CCArray *senderList=(CCArray*)msgMap->objectForKey(sender->m_uID);
				removeReceiverList(senderList);
			}else{
				removeReceiverMap(msgMap);
			}
		}
	}
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver,MessageType type)
{
    CCAssert(receiver!=NULL,"CompleteMessageManage:removeReceiver:receiver can't be null!");
	CCDictionary *regiesterMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
	if (regiesterMap) {
		CCDictionary *msgMap=(CCDictionary*) regiesterMap->objectForKey(type);
		if(msgMap){
			removeReceiverMap(msgMap);
		}
	}
}

void CCSpecMessageManager::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"CompleteMessageManage:removeReceiver:receiver can't be null!");
	CCDictionary *regiesterMap=(CCDictionary*) m_regiesterMap->objectForKey(receiver->m_uID);
	if (regiesterMap) {
		CCDictElement* pElement = NULL;
		CCDICT_FOREACH(senderMap,pElement){
			removeReceiverMap((CCDictionary*)pElement->getObject());
		}
	}
}

void CCSpecMessageManager::removeReceiverList(CCArray* list,SEL_MessageHandler handle){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		CCMessageHandler* handler=(CCMessageHandler*) pObject;
		if (handler->getHandle()==handle) {
			list->removeObject(handler);
		}
	}
}

void CCSpecMessageManager::removeReceiverList(CCArray* list){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		list->removeObject(pObject);
	}
}

void CCSpecMessageManager::removeReceiverMap(CCDictionary* map,SEL_MessageHandler handle){
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		removeReceiverList((CCArray*)pElement->getObject(),handle);
	}
}

void CCSpecMessageManager::removeReceiverMap(CCDictionary* map){
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		removeReceiverList((CCArray*)pElement->getObject());
	}
}

NS_CC_END
