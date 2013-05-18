//
//  MessageManager.m
//  Message
//
//  Created by trarck on 11-11-27.
//

#include "CCMessageManager2.h"

NS_CC_YHLIB_BEGIN

const int kNullObjectId=0;

static CCMessageManager* s_sharedMessageManagerInstance=NULL;

CCMessageManager::CCMessageManager()
:m_messages(NULL)
,m_globalObject(NULL)
{
	CCLOG("CCMessageManager create");
}

CCMessageManager::~CCMessageManager()
{
	CCLOG("CCMessageManager destroy begin");
	CC_SAFE_RELEASE(m_messages);
	CC_SAFE_RELEASE(m_globalObject);
	//CC_SAFE_RELEASE(m_regiesterMap);
	CCLOG("CCMessageManager destroy end");
}

CCMessageManager* CCMessageManager::defaultManager(void)
{
	if (!s_sharedMessageManagerInstance) {
		s_sharedMessageManagerInstance=new CCMessageManager();
		s_sharedMessageManagerInstance->init();
	}
	return s_sharedMessageManagerInstance;
}

bool CCMessageManager::init()
{
	m_messages=new CCDictionary();
	m_globalObject=new CCObject();
	return true;
}

bool CCMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject)
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
    //register for receiver
	unsigned int receiverKey=receiver->m_uID;
    CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiverKey);
	if (!receiverMap) {
		receiverMap=new CCDictionary();
	    msgMap->setObject(receiverMap ,receiverKey);
		receiverMap->release();
	}

	//register for sender
	//sender 为空，则注册到全局对象上
	unsigned int senderKey=sender==NULL?kNullObjectId:sender->m_uID;
	CCArray *handleList=(CCArray*)receiverMap->objectForKey(senderKey);
	if (!handleList) {
        handleList=new CCArray();
		receiverMap->setObject(handleList,receiverKey);
		handleList->release();
	}

	//检查是否已经注册过
    bool isRegisted=false;
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(handleList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
        if (handler->getHandle()==handle && handler->getTarget()==handleObject) {
			CCAssert(0,"Handle has register");
            isRegisted=true;
            break;
		}
    }

    if(!isRegisted){
       
        //register for handler
        CCMessageHandler *handler=new CCMessageHandler();
        handler->initWithTarget(handleObject,handle);
        handleList->addObject(handler);
        handler->release();
    }
	return !isRegisted;
}

//使receiver可以接收sender发送过来的叫type的消息，并用handle来处理
//关注的对象是receiver
bool CCMessageManager::registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender)
{
	return registerReceiver(receiver ,handle,type ,sender ,receiver);
}

void CCMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManager:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManager:removeReceiver:handle can't be null!");
    
    //if(sender==NULL){
    //    removeReceiver(receiver, type, handle);
    //}else if(handle==NULL){
    //    removeReceiver(receiver,type,sender);
    //}else {
        CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

        if(msgMap){
            CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
            if(sender){
                //移除注册到sender的记录
                CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
                if(handleList){
                     removeHandleList(handleList, handle);
                }
            }else{
                //移除所有receiver记录
                removeReceiverMap(receiverMap, handle);
            }
        }
    //}
}

void CCMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManager:removeReceiver:sender can't be null!");

    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(sender){
            //移除注册到sender的记录
            CCArray* handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
            if(handleList){
                 removeHandleList(handleList);
            }
        }else{
            //移除所有receiver记录
            removeReceiverMap(receiverMap);
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManager:removeReceiver:handle can't be null!");
    
    CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        //移除所有receiver记录
        removeReceiverMap(receiverMap,handle);
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,unsigned int type)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");

	 CCDictionary *msgMap=(CCDictionary*) m_messages->objectForKey(type);

    if(msgMap){
        CCDictionary *receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        //移除所有receiver记录
        removeReceiverMap(receiverMap);
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    
    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    
    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        //移除所有receiver记录
        removeReceiverMap(receiverMap);
    }
}


void CCMessageManager::removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
	CCAssert(sender!=NULL,"CCMessageManager:removeReceiver:sender can't be null!");
	CCAssert(handle!=NULL,"CCMessageManager:removeReceiver:handle can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
        //移除所有receiver记录
        removeHandleList(handleList,handle);
    }
    
}

void CCMessageManager::removeReceiver(CCObject* receiver,CCObject* sender)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
    CCAssert(sender!=NULL,"CCMessageManager:removeReceiver:sender can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        if(receiverMap){
            handleList=(CCArray*)receiverMap->objectForKey(sender->m_uID);
            if(handleList)
                //移除所有receiver记录
                removeHandleList(handleList);
        }
    }
}

void CCMessageManager::removeReceiver(CCObject* receiver,SEL_MessageHandler handle)
{
    CCAssert(receiver!=NULL,"CCMessageManager:removeReceiver:receiver can't be null!");
	CCAssert(handle!=NULL,"CCMessageManager:removeReceiver:handle can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCDictionary* msgMap=NULL;
	CCDictionary* receiverMap=NULL;

    CCDICT_FOREACH(m_messages,msgMapElement){
        msgMap=(CCDictionary*) msgMapElement->getObject();
        receiverMap=(CCDictionary*)msgMap->objectForKey(receiver->m_uID);
        //移除所有receiver记录
         removeReceiverMap(receiverMap,handle);
    }
}

void CCMessageManager::removeHandleList(CCArray* handleList,SEL_MessageHandler handle){
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(handleList,pObject){
		CCMessageHandler* handler=(CCMessageHandler*) pObject;
		if (handler->getHandle()==handle) {
			handleList->removeObject(handler);
		}
	}
}

void CCMessageManager::removeHandleList(CCArray* handleList){
    handleList->removeAllObjects();
}

void CCMessageManager::removeReceiverMap(CCDictionary* receiverMap,SEL_MessageHandler handle){
	CCAssert(receiverMap!=NULL,"CCMessageManager:removeReceiverMap:receiverMap can't be null!");

    CCDictElement* msgMapElement = NULL;
    CCArray* handleList=NULL;

    CCDICT_FOREACH(receiverMap,msgMapElement){
        //移除所有receiver记录
        handleList=(CCArray*)msgMapElement->getObject();
        removeHandleList(handleList,handle);
    }
}

void CCMessageManager::removeReceiverMap(CCDictionary* receiverMap){
	CCAssert(receiverMap!=NULL,"CCMessageManager:removeReceiverMap:receiverMap can't be null!");
    receiverMap->removeAllObjects();
}

void CCMessageManager::dispatchMessage(CCMessage* message)
{
	CCAssert(message!=NULL,"CCMessageManager:dispatchMessage:message can't be null!");

    CCObject* receiver=NULL;
	CCObject* sender=NULL;
	//CCAssert(message.type!=0,)
	//如果message的type不为0，则需要执行一个type为global的所有消息
	if (message->getType()!=GlobalMessageType) {
		//message for global
		CCDictionary* msgMap=(CCDictionary*)m_messages->objectForKey(GlobalMessageType);
		if (msgMap) {
            dispatchMessageMap(msgMap,message);
		}
	}
	
	//message for type
	CCDictionary* msgMap= (CCDictionary*)m_messages->objectForKey(message->getType());
	if (msgMap) {
		dispatchMessageMap(msgMap,message);
	}
}


//适应message中没有receiver的情况
void CCMessageManager::dispatchMessage(CCMessage* message ,CCObject*  receiver)
{
	CCAssert(message!=NULL,"CCMessageManager:dispatchMessage:message can't be null!");
	CCAssert(receiver!=NULL,"CCMessageManager:dispatchMessage:receiver can't be null!");
    message->setReceiver(receiver);
    dispatchMessage(message);
}


void CCMessageManager::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManager::dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver);
	dispatchMessage(message);
	message->release();
}

void CCMessageManager::dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data)
{
	CCMessage* message=new CCMessage();
	message->initWithType(type ,sender ,receiver ,data);
	dispatchMessage(message);
	message->release();
}

void CCMessageManager::dispatchMessageMap(CCDictionary* msgMap,CCMessage* message)
{
        CCAssert(msgMap!=NULL,"CCMessageManager:dispatchMessageMap:msgMap can't be null!");
        CCObject* receiver=message->getReceiver();
        CCObject* sender=message->getSender();
        if(receiver){
                CCDictionary* receiverMap=(CCDictionary *)msgMap->objectForKey(receiver->m_uID);
                CCArray* handleList=NULL;
                if(sender){
                    //执行注册到送送者为sender的消息的处理方法
                    handleList=(CCArray *)receiverMap->objectForKey(sender->m_uID);
                    execHandleList(handleList,message);
//                        //执行注册到送送者为null的消息的处理方法
//
//                    }else{
//                        //执行注册到送送者为null的消息的处理方法
//                    }
                }

                //执行注册到送送者为null的消息的处理方法
                handleList=(CCArray *)receiverMap->objectForKey(kNullObjectId);

                execHandleList(handleList,message);
        }else{
                //发送到注册时的接收者为sender的所有接收者
                dispathMessageToAllReceiverWithSender(message,msgMap,sender);
        }
}

void CCMessageManager::dispathMessageToAllReceiverWithSender(CCMessage* message,CCDictionary* msgMap,CCObject* sender)
{
        CCAssert(msgMap!=NULL,"CCMessageManager:dispatchMessageMap:msgMap can't be null!");

        int senderKey=sender==NULL?kNullObjectId:sender->m_uID;

        CCDictElement* pElement = NULL;
        CCDictionary* receiverMap=NULL;

        CCDICT_FOREACH(msgMap,pElement){
            receiverMap=(CCDictionary*)pElement->getObject();
            execHandleList((CCArray*)receiverMap->objectForKey(senderKey),message);
        }
}

void CCMessageManager::execHandleList(CCArray* handleList ,CCMessage* message)
{
	CCAssert(handleList!=NULL,"CCMessageManager:execRegisterReceiverList:handleList can't be null!");
	CCObject* pObject = NULL;
    CCARRAY_FOREACH(handleList,pObject){
        CCMessageHandler* handler=(CCMessageHandler*) pObject;
		handler->execute(message);
    }
}

//
//void CCMessageManager::execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
//{
//	CCAssert(senderMap!=NULL,"CCMessageManager:execAllRegisterWithSenderMap:senderMap can't be null!");
//	//send to all
//	CCDictElement* pElement = NULL;
//	CCDICT_FOREACH(senderMap,pElement){
//		execRegisterReceiverList((CCArray*)pElement->getObject(),message);
//	}
//}
//
//void CCMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message)
//{
//	CCObject* receiver=message->getReceiver();
//	if (receiver) {
//		//message for receiver
//		CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//		if(receiverList) execRegisterReceiverList(receiverList,message);
//	}else {
//		//send to all receiver
//		execAllRegisterWithSenderMap(senderMap ,message);
//	}
//}
//
//void CCMessageManager::execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver)
//{
//	CCAssert(senderMap!=NULL,"CCMessageManager:execRegisterWithSenderMap:senderMap can't be null!");
//	CCAssert(receiver!=NULL,"CCMessageManager:execRegisterWithSenderMap:receiver can't be null!");
//	CCArray* receiverList=(CCArray*)senderMap->objectForKey(receiver->m_uID);
//	if(receiverList) 
//		execRegisterReceiverList(receiverList,message);
//}

NS_CC_YHLIB_END
