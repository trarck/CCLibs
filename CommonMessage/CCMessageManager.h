//
//  MessageManager.h
//  Message
//  对消息优先级的支持
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef __CCMessage_Manager_H__
#define __CCMessage_Manager_H__

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef GlobalMessageType
#define GlobalMessageType 0
#endif

NS_CC_BEGIN

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
    
    bool registerReceiver(MessageParty receiver,SEL_MessageHandler handle ,MessageType type ,MessageParty sender ,CCObject*  handleObject);

	bool registerReceiver(MessageParty receiver,CCMessageHandler handle,MessageType type ,MessageParty sender);
																															  
	void removeReceiver(MessageParty receiver,MessageType type ,MessageParty sender,SEL_MessageHandler handle);

    void removeReceiver(MessageParty receiver,MessageType type ,MessageParty sender);

    void removeReceiver(MessageParty receiver,MessageType type);

    void removeReceiver(MessageParty receiver);
    
    void removeReceiver(MessageParty receiver,MessageType type ,SEL_MessageHandler handle);
    
    void removeReceiver(MessageParty receiver,MessageParty sender,SEL_MessageHandler handle);
    
    void removeReceiver(MessageParty receiver,MessageParty sender);

    void removeReceiver(MessageParty receiver,SEL_MessageHandler handle);
    
    
    
                                                      
	void dispatchMessage(CCMessage* message ,MessageParty  receiver);

	void dispatchMessage(CCMessage* message);

    void dispatchMessageWithType(MessageType type ,MessageParty sender ,MessageParty receiver,CCObject* data);
    
    void dispatchMessageWithType(MessageType type ,MessageParty sender ,MessageParty receiver,CCDictionary* data);
    
    void dispatchMessageWithType(MessageType type ,MessageParty sender ,MessageParty receiver);
                                                                                                    
protected:

	void removeReceiverList(CCArray* list,SEL_MessageHandler handle);

	void removeReceiverList(CCArray* list);

	void removeReceiverMap(MessageParty receiver,CCDictionary* map,SEL_MessageHandler handle);

	void removeReceiverMap(MessageParty receiver,CCDictionary* map);

	void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);
    
	void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,MessageParty  receiver);

    CCDictionary* m_messages;

	MessageParty m_globalObject;

private:

	static CCMessageManager* s_sharedMessageManagerInstance;

};

NS_CC_END

#endif // __CCMessage_Manager_H__