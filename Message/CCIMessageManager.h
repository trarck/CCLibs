//
//  MessageManager.h
//  Message
//  对消息优先级的支持
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef __CCIMessage_Manager_H__
#define __CCIMessage_Manager_H__

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef GlobalMessageType
#define GlobalMessageType 0
#endif

NS_CC_YHLIB_BEGIN

class CCIMessageManager : public CCObject {
public:
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    virtual bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,MessageType type ,CCObject* sender ,CCObject*  handleObject);
    
	virtual bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,MessageType type ,CCObject* sender);
    
    virtual void removeReceiver(MessageType type ,CCObject* sender,CCObject* receiver ,SEL_MessageHandler handle);
    virtual void removeReceiver(MessageType type ,CCObject* sender,CCObject* receiver);
                                                                           
	virtual void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);

	virtual void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    virtual void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	virtual void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);                                                                                     
                                                                                             
    virtual void dispatchMessage(CCMessage* message);
                                                                                             
    virtual void dispatchMessageWithType(MessageType type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);

    virtual void dispatchMessage(CCMessage* message ,CCObject*  receiver);
};

NS_CC_YHLIB_END

#endif // __CCIMessage_Manager_H__