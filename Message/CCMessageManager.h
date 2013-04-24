//
//  MessageManager.h
//  Message
//  对消息优先级的支持
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef YHLIB_MESSAGE_CCMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef Globalunsigned int
#define Globalunsigned int 0
#endif

NS_CC_YHLIB_BEGIN

class CCMessageManager : public CCObject {

public:

    CCMessageManager();

    ~CCMessageManager();

    static CCMessageManager* defaultManager();

    void init();
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender);
																															  
	void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

    void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender);

    void removeReceiver(CCObject* receiver,unsigned int type);

    void removeReceiver(CCObject* receiver);
    
    void removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle);
    
    void removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle);
    
    void removeReceiver(CCObject* receiver,CCObject* sender);

    void removeReceiver(CCObject* receiver,SEL_MessageHandler handle);
    
    
    
                                                      
	void dispatchMessage(CCMessage* message ,CCObject*  receiver);

	void dispatchMessage(CCMessage* message);

    void dispatchMessageWithType(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data);
    
//    void dispatchMessageWithType(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);
    
    void dispatchMessageWithType(unsigned int type ,CCObject* sender ,CCObject* receiver);
                                                                                                    
protected:

	void addReceiverMap(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);

	void removeReceiverList(CCArray* list,SEL_MessageHandler handle);

	void removeReceiverList(CCArray* list);

	void removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle);

	void removeReceiverMap(CCObject* receiver,CCDictionary* map);

	void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);
    
	void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);

    CCDictionary* m_messages;

	CCObject* m_globalObject;

	CCDictionary* m_regiesterMap;

private:

	static CCMessageManager* s_sharedMessageManagerInstance;

};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCMESSAGEMANAGER_H_