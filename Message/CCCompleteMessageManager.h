//
//  MessageManager.h
//  Message
//  对消息优先级的支持
//  另外一个实现：receiver,sender用int型，handle直接使用函数指针
//  Created by trarck on 11-11-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#ifndef __CCComplete_Message_Manager_H__
#define __CCComplete_Message_Manager_H__

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef GlobalMessageType
#define GlobalMessageType 0
#endif

NS_CC_BEGIN

class CCCompleteMessageManager : public CCObject {
public:
    CCCompleteMessageManager();
    ~CCCompleteMessageManager();

    static CCCompleteMessageManager* sharedCompleteMessageManager();

//	static CCIMessageManager* sharedMessageManager();

    void init();

    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    //返回注册是成功还是失败。true--成功，false--失败  
    bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,MessageType type ,CCObject* sender ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,MessageType type ,CCObject* sender);
                                                             
    void removeReceiver(MessageType type ,CCObject* sender,CCObject* receiver ,SEL_MessageHandler handle);
    void removeReceiver(CCObject* receiver ,SEL_MessageHandler handle ,MessageType type ,CCObject* sender){
        removeReceiver(type,sender,receiver,handle);
    };
    void removeReceiver(MessageType type ,CCObject* sender,CCObject* receiver);
                                                                           
	void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);

	void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);
	                                                                                             
    void dispatchMessage(CCMessage* message);
                                                                                             
    void dispatchMessageWithType(MessageType type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);
                                                                                     
    void dispatchMessage(CCMessage* message ,CCObject*  receiver);
                                                                                                    
protected:
    CCDictionary* m_messages;
	CCObject* m_globalObject;
private:
	static CCCompleteMessageManager* s_sharedCompleteMessageManagerInstance;
};

NS_CC_END

#endif // __CCComplete_Message_Manager_H__