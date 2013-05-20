//
//  TODO:对消息优先级的支持
//

#ifndef YHLIB_MESSAGE_CCMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

NS_CC_YHLIB_BEGIN

class CCMessageManagerComplex : public CCObject {

public:

    CCMessageManagerComplex();

    ~CCMessageManagerComplex();

    static CCMessageManagerComplex* defaultManager();

    bool init();
    
    /**
     * observer 消息接收者
     * sender   消息发送者
     */
    //receiver对sender发来的type消息可以有多个响应方法，实际中情况会很少
    
    bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle ,CCObject*  handleObject);

	bool registerReceiver(CCObject* receiver ,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);
	
	/**
	 * 取消接收者的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);

    /**
	 * 取消注册到接收者的处理对象的处理方法，该方法注册到发送者的某个消息。
	 */
	void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle,CCObject*  handleObject);
	/**
	 * 取消接收者注册到某个发送者的某个消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender);

	/**
	 * 取消接收者注册到某个消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type);

	/**
	 * 取消接收者的所以注册信息。
	 */
    void removeReceiver(CCObject* receiver);
    
	/**
	 * 取消接收者处理某个消息的某个方法。
	 */
    void removeReceiver(CCObject* receiver,unsigned int type ,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的任意消息的某个处理方法。
	 */
    void removeReceiver(CCObject* receiver,CCObject* sender,SEL_MessageHandler handle);
    
	/**
	 * 取消接收者注册到发送者的所有消息的所有处理方法。
	 */
    void removeReceiver(CCObject* receiver,CCObject* sender);

	/**
	 * 取消接收者注册到任意发送者任意消息的某个处理方法。
	 */
    void removeReceiver(CCObject* receiver,SEL_MessageHandler handle);
   	
	/**
	 * 发送消息。
	 */
	void dispatchMessage(CCMessage* message);

	/**
	 * 发送消息到某个接收者。
	 */
	void dispatchMessage(CCMessage* message ,CCObject*  receiver);


	/**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver,CCObject* data);
    
    /**
	 * 发送消息的工具方法。
	 */
    void dispatchMessage(unsigned int type ,CCObject* sender ,CCObject* receiver);

	/**
	 * 发送消息的工具方法。
	 * 数据是一个字典
	 */
	void dispatchMessageWithDictionary(unsigned int type ,CCObject* sender ,CCObject* receiver,CCDictionary* data);
         
	enum{
		GlobalMessageType=0
	};

protected:
    // /**
	// * 添加接收者的注册表。
	// */
	//void addReceiverMap(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);

	/**
	 * 删除接收者的处理方法列表的处理方法为参数指定的函数。
	 */
	void removeReceiverList(CCArray* list,SEL_MessageHandler handle);

	/**
	 * 删除接收者的处理方法列表。
	 */
	void removeReceiverList(CCArray* list);

	/**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMap(CCObject* receiver,CCDictionary* map,SEL_MessageHandler handle);

	/**
	 * 删除接收者的注册列表。
	 */
	void removeReceiverMap(CCObject* receiver,CCDictionary* map);

	/**
	 * 执行接收者的处理列表的所有处理方法。
	 */
	void execRegisterReceiverList(CCArray* receiverList ,CCMessage* message);
    
	/**
	 * 按发送者表执行消息处理函数。
	 */
	void execAllRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	/**
	 * 如果消息有接收者，则处理接收列表的方法
	 * 如果没有，则按发送者表执行消息处理函数。
	 * 
	 */
    void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message);

	/**
	 * 如果消息有接收者，则处理接收列表的方法
	 * 如果没有，则按发送者表执行消息处理函数。
	 * 接收者是指定的，与消息里定义的无关
	 */
	void execRegisterWithSenderMap(CCDictionary* senderMap,CCMessage* message,CCObject*  receiver);

	/**
	 * 消息表
	 */
    CCDictionary* m_messages;

	/**
	 * 消息的全局对像
	 */
	CCObject* m_globalObject;

	///**
	// * 消息的注册表
	// */
	//CCDictionary* m_regiesterMap;
};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCMESSAGEMANAGER_H_