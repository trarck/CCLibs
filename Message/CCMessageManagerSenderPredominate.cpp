//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "CCMessageManagerSenderPredominate.h"

NS_CC_YHLIB_BEGIN

const int kNullObjectId=0;

static CCMessageManagerSenderPredominate* s_sharedMessageManagerSenderPredominateInstance=NULL;

CCMessageManagerSenderPredominate::CCMessageManagerSenderPredominate()
:m_messages(NULL)
,m_globalObject(NULL)
{
	CCLOG("CCMessageManagerSenderPredominate create");
}

CCMessageManagerSenderPredominate::~CCMessageManagerSenderPredominate()
{
	CCLOG("CCMessageManagerSenderPredominate destroy begin");
	CC_SAFE_RELEASE_NULL(m_messages);
	CC_SAFE_RELEASE_NULL(m_globalObject);
	//CC_SAFE_RELEASE(m_regiesterMap);
	CCLOG("CCMessageManagerSenderPredominate destroy end");
}

CCMessageManagerSenderPredominate* CCMessageManagerSenderPredominate::defaultManager(void)
{
	if (!s_sharedMessageManagerSenderPredominateInstance) {
		s_sharedMessageManagerSenderPredominateInstance=new CCMessageManagerSenderPredominate();
		s_sharedMessageManagerSenderPredominateInstance->init();
	}
	return s_sharedMessageManagerSenderPredominateInstance;
}

bool CCMessageManagerSenderPredominate::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new CCObject();
	return true;
}

bool CCMessageManagerSenderPredominate::registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject)
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
	//sender 为空，则注册到kNullObjectId上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
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
#ifdef MESSAGE_REGIEST_REPEAT
	CCMessageHandler *handler=new CCMessageHandler();
	handler->initWithTarget(handleObject,handle);
	receiverList->addObject(handler);
	handler->release();
	
	return true;
	
#else	
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
#endif
}

//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
bool CCMessageManagerSenderPredominate::registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
	return registerReceiver(receiver ,type ,sender ,handle,receiver);
}


/**
 * 检查是否已经注册某个消息。
 */
bool CCMessageManagerSenderPredominate::isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject)
{
	CCAssert(receiver!=NULL,"MessageManage:registerReceiver:receiver can't be null");
	CCAssert(handle!=NULL,"MessageManage:registerReceiver:handle");
	CCAssert(handleObject!=NULL,"MessageManage:registerReceiver:handleObject");

	//type等于0，则所有消息都会发送
	//register for type
	CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);
	if (msgMap==NULL) {
		return false;
	}
	//register for sender
	//sender 为空，则注册到kNullObjectId上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
	CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(senderKey);
	if (!senderMap) {
		return false;
	}
	//register for receiver
	unsigned int receiverKey=receiver->m_uID;
	CCArray *receiverList=(CCArray*)senderMap->objectForKey(receiverKey);
	if (!receiverList) {
		return false;
	}

	bool isRegisted=false;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(receiverList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
            isRegisted=true;
            break;
		}
    }

	return isRegisted;
}

bool CCMessageManagerSenderPredominate::isRegisterReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
	return isRegisterReceiver(receiver,type,sender,handle,receiver);
}


/**
 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
 */
void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject)
{
	    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

        if(msgMap){
            CCDictionary *senderMap=(CCDictionary*)msgMap->objectForKey(sender->m_uID);
            removeReceiverMap(receiver, senderMap, handle,handleObject);
        }
}

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:handle can't be null!");
    
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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:sender can't be null!");

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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:handle can't be null!");
    
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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,unsigned int type)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");

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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
    
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


void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:handle can't be null!");

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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:sender can't be null!");

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

void CCMessageManagerSenderPredominate::removeReceiver(CCObject* receiver,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManagerSenderPredominate:removeReceiver:handle can't be null!");

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
void CCMessageManagerSenderPredominate::removeReceiverList(CCArray* list,SEL_MessageHandler handle,CCObject* handleObject)
{
	if (list && list->data->num > 0){         
        int len=list->data->num;
        CCObject** arr = list->data->arr;
        for(int i=0;i<len;){
		    CCMessageHandler* handler=(CCMessageHandler*)(*(arr+i));
		    if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			    list->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void CCMessageManagerSenderPredominate::removeReceiverList(CCArray* list,SEL_MessageHandler handle){
	if (list && list->data->num > 0){         
        int len=list->data->num;
        CCObject** arr = list->data->arr;
        for(int i=0;i<len;){
		    CCMessageHandler* handler=(CCMessageHandler*)(*(arr+i));
		    if (handler->getHandle()==handle) {
			    list->removeObjectAtIndex(i);
                --len;
		    }else{
                ++i;
            }
	    }
    }
}

void CCMessageManagerSenderPredominate::removeReceiverList(CCArray* list){
	list->removeAllObjects();
}

/**
 * 删除接收者的注册列表。
 */
void CCMessageManagerSenderPredominate::removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle,CCObject* handleObject)
{
	CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList,handle,handleObject);
        }
    }
}

void CCMessageManagerSenderPredominate::removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle){
	CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList,handle);
        }
    }

}

void CCMessageManagerSenderPredominate::removeReceiverMap(CCObject* receiver,CCDictionary* map){
	CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:removeReceiverMap:receiver can't be null!");
	if (map) {
        CCArray *receiverList=(CCArray*)map->objectForKey(receiver->m_uID);
        if(receiverList){
            removeReceiverList(receiverList);
        }
    }
}

//
void CCMessageManagerSenderPredominate::dispatchMessage(CCMessage* message)
{
	CCAssert(message!=NULL,"CCMessageManagerSenderPredominate:dispatchMessage:message can't be null!");

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
void CCMessageManagerSenderPredominate::dispatchMessage(CCMessage* message ,CCObject*  receiver)
{
	CCAssert(message!=NULL,"CCMessageManagerSenderPredominate:dispatchMessage:message can't be null!");
	CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:dispatchMessage:receiver can't be null!");

	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(m_globalObject->m_uID);
		if (msgMap) {
			dispatchMessageMap(msgMap,message);
		}
	}
	//message for type
	CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		dispatchMessageMap(msgMap,message);
	}
}

void CCMessageManagerSenderPredominate::dispatchMessageMap(CCDictionary* msgMap,CCMessage* message)
{
	CCAssert(msgMap!=NULL,"CCMessageManager:dispatchMessageMap:msgMap can't be null!");
	CCObject* receiver=message->getReceiver();
	CCObject* sender=message->getSender();
	//parse for sender
	//如果sender不为空，则还要触发一次全局消息。
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


void CCMessageManagerSenderPredominate::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerSenderPredominate::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerSenderPredominate::dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManagerSenderPredominate::execRegisterReceiverList(CCArray* receiverList ,CCMessage* message)
{
	
	CCAssert(receiverList!=NULL,"CCMessageManagerSenderPredominate:execRegisterReceiverList:receiverList can't be null!");
	CCObject* pObject = NULL;
	CCArray* receiverListCopy=new CCArray();
	receiverListCopy->initWithArray(receiverList);
    CCARRAY_FOREACH(receiverListCopy,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
		handler->execute(message);
    }
	receiverListCopy->release();
}


void CCMessageManagerSenderPredominate::execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
{
	CCAssert(senderMap!=NULL,"CCMessageManagerSenderPredominate:execAllRegisterWithSenderMap:senderMap can't be null!");
	//send to all
	CCDictElement* pElement = NULL;
	CCDICT_FOREACH(senderMap,pElement){
		execRegisterReceiverList((CCArray*)pElement->getObject(),message);
	}
}

void CCMessageManagerSenderPredominate::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
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

void CCMessageManagerSenderPredominate::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver)
{
	CCAssert(senderMap!=NULL,"CCMessageManagerSenderPredominate:execRegisterWithSenderMap:senderMap can't be null!");
	CCAssert(receiver!=NULL,"CCMessageManagerSenderPredominate:execRegisterWithSenderMap:receiver can't be null!");
	CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
	if(receiverList) 
		execRegisterReceiverList(receiverList,message);
}

NS_CC_YHLIB_END
