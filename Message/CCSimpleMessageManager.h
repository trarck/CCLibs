//
//
//	每个对象只有一个处理消息的函数，和window的消息类似
//	hash(接收者)→hash(发送者)→handler
//

#ifndef YHLIB_MESSAGE_CCSIMPLEMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCSIMPLEMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

#ifndef Globalunsigned int
#define Globalunsigned int 0
#endif

NS_CC_YHLIB_BEGIN

class CCSimpleMessageManager : public CCObject {
public:
	CCSimpleMessageManager();
    ~CCSimpleMessageManager();

    static CCSimpleMessageManager* sharedSimpleMessageManager();

//	static CCIMessageManager* sharedMessageManager();

    void init();

    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
      
    bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender);
                                                                                                                              
    void removeReceiver(unsigned int type ,CCObject* sender,CCObject* receiver ,SEL_MessageHandler handle){
        removeReceiver(type,sender,receiver);
    };
    void removeReceiver(CCObject* receiver ,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender){
        removeReceiver(type,sender,receiver);
    };
    void removeReceiver(unsigned int type ,CCObject* sender,CCObject* receiver);
                                                                                                                                                                      
	void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

    void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);

	void dispatchMessage(CCMessage* message);
                                                                                             
    void dispatchMessageWithType(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);
                                                                                     
    void dispatchMessage(CCMessage* message ,CCObject*  receiver);

private:
    CCDictionary *m_messages;
	CCObject *m_globalObject;
	static CCSimpleMessageManager* s_sharedSimpleMessageManagerInstance;
};

NS_CC_YHLIB_END

#endif //YHLIB_MESSAGE_CCSIMPLEMESSAGEMANAGER_H_
