//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "CCMessageManagerComplex.h"

NS_CC_YHLIB_BEGIN

static CCMessageManagerComplex* s_sharedMessageManagerInstance=NULL;

CCMessageManagerComplex::CCMessageManagerComplex()
:m_messages(NULL)
,m_globalObject(NULL)
{
	CCLOG("CCMessageManagerComplex create");
}

CCMessageManagerComplex::~CCMessageManagerComplex()
{
	CCLOG("CCMessageManagerComplex destroy begin");
	CC_SAFE_RELEASE(m_messages);
	CC_SAFE_RELEASE(m_globalObject);
	//CC_SAFE_RELEASE(m_regiesterMap);
	CCLOG("CCMessageManagerComplex destroy end");
}

CCMessageManagerComplex* CCMessageManagerComplex::defaultManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new CCMessageManagerComplex();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

bool CCMessageManagerComplex::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new CCObject();
	return true;
}

bool CCMessageManagerComplex::registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		msgMap=new CCDictionary();
		m_messages->setObject(msgMap,type);
		msgMap->release();
	}
	//register for sender
	//sender 为空，则注册到全局对象上
	sender=sender==NULL?m_globalObject:sender;
	unsigned int senderKey=sender->m_uID;
	CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(senderKey);
	if (!senderMap) {
		senderMap=new CCDictionary();
	    msgMap->setObject(senderMap ,senderKey);
		senderMap->release();
	}
	//register for receiver
	unsigned int receiverKey=receiver->m_uID;
	CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiverKey);
	if (!receiverList) {
		receiverList=new CCArray();
		senderMap->setObject(receiverList,receiverKey);
		receiverList->release();
	}
	
	//检查是否已经注册过
    bool isRegisted=false;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(receiverList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			CCAssert(0,"Handle has register");
            isRegisted=true;
            break;
		}
    }

    if(!isRegisted){
        //注册时不需要时间
        //struct timeval now;
        //	gettimeofday(&now,NULL);
        
        //register for handler
        CCMessageHandler *handler=new CCMessageHandler();
        handler->initWithTarget(handleObject,handle);
        receiverList->addObject(handler);
        handler->release();

//		addReceiverMap(receiver,handle,type,sender,handleObject);
    }
	return !isRegisted;
}

//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
bool CCMessageManagerComplex::registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
	return registerReceiver(receiver ,type ,sender ,handle,receiver);
}

/**
 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
 */
void CCMessageManagerComplex::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject)
{
	    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap, handle,handleObject);
        }
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerComplex:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerComplex:removeReceiver:handle can't be null!");
    
    //if(sender==NULL){
    //    removeReceiver(receiver, type, handle);
    //}else if(handle==NULL){
    //    removeReceiver(receiver,type,sender);
    //}else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap, handle);
        }
    //}
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerComplex:removeReceiver:sender can't be null!");

    //if(sender==NULL){
    //    removeReceiver(receiver,type);
    //}else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap);
        }
    //}
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerComplex:removeReceiver:handle can't be null!");
    
    //if(handle==NULL){
    //    removeReceiver(receiver,type);
    //}else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
        if(msgMap){
            CCDictElement* pElement = NULL;
            CCDICT_FOREACH(msgMap,pElement){
                CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
                removeReceiverMap(receiver, senderMap,handle);
            }
        }
    //}
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,unsigned int type)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");

	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if(msgMap){
        //删除消息type中接收者为ceceiver的注册信息
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(msgMap,pElement){
            CCDictionary *senderMap=(CCDictionary*)pElement->getObject();
            removeReceiverMap(receiver, senderMap);
        }
    }
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
    
    CCDictElement* msgMapElement = NULL;
    CCDictElement* senderMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* senderMap=NULL;
    
    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        
        CCDICT_FOREACH(msgMap,senderMapElement){
            senderMap=(CCDictionary*)senderMapElement->getObject();
            
            removeReceiverMap(receiver, senderMap);
        }
    }
}


void CCMessageManagerComplex::removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"CCMessageManagerComplex:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerComplex:removeReceiver:handle can't be null!");

    //if(sender==NULL){
    //    removeReceiver(receiver, handle);
    //}else if(handle==NULL){
    //    removeReceiver(receiver,sender);
    //}else{
        CCDictElement* msgMapElement = NULL;
        
        CCDICT_FOREACH(m_messages,msgMapElement){
            CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap,handle);
        }
    //}
    
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerComplex:removeReceiver:sender can't be null!");

    //if(sender==NULL){
    //    removeReceiver(receiver);
    //}else {
        CCDictElement* msgMapElement = NULL;
        
        CCDICT_FOREACH(m_messages,msgMapElement){
            CCDictionary *msgMap=(CCDictionary*) msgMapElement->getObject();
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap);
        }
    //}
}

void CCMessageManagerComplex::removeReceiver(CCObject* receiver,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerComplex:removeReceiver:handle can't be null!");

	CCDictElement* msgMapElement = NULL;
    CCDictElement* senderMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* senderMap=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        
        CCDICT_FOREACH(msgMap,senderMapElement){
            senderMap=(CCDictionary*)senderMapElement->getObject();
            
            removeReceiverMap(receiver, senderMap,handle);
        }
    }
}

/**
 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
 */
void removeReceiverList(CCArray* list,SEL_MessageHandler handle,CCObject* handleObject)
{
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		CCMessageHandler* handler=(CCMessageHandler*) pObject;
		if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			list->removeObject(handler);
		}
	}
}

void CCMessageManagerComplex::removeReceiverList(CCArray* list,SEL_MessageHandler handle){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		CCMessageHandler* handler=(CCMessageHandler*) pObject;
		if (handler->getHandle()==handle) {
			list->removeObject(handler);
		}
	}
}

void CCMessageManagerComplex::removeReceiverList(CCArray* list){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(list,pObject){
		list->removeObject(pObject);
	}
}

/**
 * 删除接收者的注册列表。
 */
void removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle,CCObject* handleObject)
{
	CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList,handle,handleObject);
        }
    }
}

void CCMessageManagerComplex::removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle){
	CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList,handle);
        }
    }

}

void CCMessageManagerComplex::removeReceiverMap(CCObject* receiver,CCDictionary* map){
	CCAssert(receiver!=NULL,"CCMessageManagerComplex:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList);
        }
    }
}

//
void CCMessageManagerComplex::dispatchMessage(CCMessage* message)
{
	CCAssert(message!=NULL,"CCMessageManagerComplex:dispatchMessage:message can't be null!");

	CCObject* sender;
	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(GlobalMessageType);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap ,message);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap,message);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message);
			}
		}
	}
	
	//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		sender=message->getSender();
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary *)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap,message);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap,message);
		}
	}
}


//适应message中没有receiver的情况
void CCMessageManagerComplex::dispatchMessage(CCMessage* message ,CCObject*  receiver)
{
	CCAssert(message!=NULL,"CCMessageManagerComplex:dispatchMessage:message can't be null!");
	CCAssert(receiver!=NULL,"CCMessageManagerComplex:dispatchMessage:receiver can't be null!");

	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(m_globalObject->m_uID);
		if (msgMap) {
			//parse for sender
			//如果sender不为空，则还要触发一次全局消息。
			CCObject* sender=message->getSender();
			if (sender) {
				//执行注册到sender的消息的处理方法
				CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
				//如果注册则执行
				if (senderMap)  execRegisterWithSenderMap(senderMap,message,receiver);
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}else {
				//执行注册到global的消息的处理方法
				CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
				//如果注册则执行
				if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
			}
		}
	}
	//message for type
	CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		//parse for sender
		//如果sender不为空，则还要触发一次全局消息。
		CCObject* sender=message->getSender();
		if (sender) {
			//执行注册到sender的消息的处理方法
			CCDictionary* senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
			//如果注册则执行
			if (senderMap)  execRegisterWithSenderMap(senderMap ,message ,receiver);
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}else {
			//执行注册到global的消息的处理方法
			CCDictionary* globalMap=(CCDictionary*)msgMap->objectForKey(m_globalObject->m_uID);
			//如果注册则执行
			if (globalMap)  execRegisterWithSenderMap(globalMap ,message ,receiver);
		}
	}
}


void CCMessageManagerComplex::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerComplex::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerComplex::dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerComplex::execRegisterReceiverList(CCArray* receiverList ,CCMessage* message)
{
	
	CCAssert(receiverList!=NULL,"CCMessageManagerComplex:execRegisterReceiverList:receiverList can't be null!");
	CCObject* pObject = NULL;
    CCARRAY_FOREACH(receiverList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
		handler->execute(message);
    }
}


void CCMessageManagerComplex::execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
{
	CCAssert(senderMap!=NULL,"CCMessageManagerComplex:execAllRegisterWithSenderMap:senderMap can't be null!");
	//send to all
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		execRegisterReceiverList((CCArray*)pElement->getObject(),message);
	}
}

void CCMessageManagerComplex::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
{
	CCObject* receiver=message->getReceiver();
	if (receiver) {
		//message for receiver
		CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
		if(receiverList) execRegisterReceiverList(receiverList,message);
	}else {
		//send to all receiver
		execAllRegisterWithSenderMap(senderMap ,message);
	}
}

void CCMessageManagerComplex::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver)
{
	CCAssert(senderMap!=NULL,"CCMessageManagerComplex:execRegisterWithSenderMap:senderMap can't be null!");
	CCAssert(receiver!=NULL,"CCMessageManagerComplex:execRegisterWithSenderMap:receiver can't be null!");
	CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
	if(receiverList) 
		execRegisterReceiverList(receiverList,message);
}

NS_CC_YHLIB_END
