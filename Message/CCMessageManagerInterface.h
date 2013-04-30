//
//  对消息优先级的支持
//

#ifndef YHLIB_MESSAGE_CCMESSAGEMANAGERINTERFACE_H_
#define YHLIB_MESSAGE_CCMESSAGEMANAGERINTERFACE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef GlobalMessageType
#define GlobalMessageType 0
#endif

NS_CC_YHLIB_BEGIN

class CCMessageManagerInterface : public CCObject {
public:
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    virtual bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);
    
	virtual bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender);
    
    virtual void removeReceiver(unsigned int type ,CCObject* sender,CCObject* receiver ,SEL_MessageHandler handle);
    virtual void removeReceiver(unsigned int type ,CCObject* sender,CCObject* receiver);
                                                                           
	virtual void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);

	virtual void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    virtual void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	virtual void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);                                                                                     
                                                                                             
    virtual void dispatchMessage(CCMessage* message);
                                                                                             
    virtual void dispatchMessageWithType(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);

    virtual void dispatchMessage(CCMessage* message ,CCObject*  receiver);
};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCMESSAGEMANAGERINTERFACE_H_