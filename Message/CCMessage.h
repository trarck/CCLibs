//
//  Message.h
//  Message
//  
//  消息是基于投递的，不存在父子关系。一个消息对应消息的处理函数（一个或多个），不存捕捉和冒泡。可以延迟发关。可以设置优先级。
//  注意和事件的区别，事件要复杂些。消息通常和简单发送执行，所以性能要高一些。
//  当然事件可以定义的很简单或遵循一定模式(dom事件模型)。
//  Created by trarck on 11-11-27.
//
#ifndef YHLIB_MESSAGE_CCMESSAGE_H_
#define YHLIB_MESSAGE_CCMESSAGE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

typedef unsigned int MessageType;
typedef CCObject* MessageParty;

class CCMessage : public CCObject {

public:
    CCMessage()
		:m_type(0),
		 m_sender(NULL),
		 m_receiver(NULL),
		 m_pData(NULL),
		 m_timeStamp(0.0f)
	{
		
	}

    ~CCMessage(void);
    
	bool initWithType(MessageType type,MessageParty sender ,MessageParty receiver ,CCObject *data){
		 m_type=type;
		setSender(sender);
		setReceiver(receiver);
		setData(data);
		return true;
	}

    bool initWithType(MessageType type,MessageParty sender ,MessageParty receiver){
		m_type=type;
		setSender(sender);
		setReceiver(receiver);
    	return true;
	}

    bool initWithType(MessageType type,MessageParty sender){
		m_type=type;
		setSender(sender);
  		return true;
	}

	MessageType getType(){
		return m_type;
	}
	void setType(MessageType type){
	    m_type=type;
	}

	MessageParty getSender(){
		return m_sender;
	}

	void setSender(MessageParty sender){
		CC_SAFE_RETAIN(sender);
		CC_SAFE_RELEASE(m_sender);
		m_sender=sender;
	}

	MessageParty getReceiver(){
		return m_receiver;
	}

	void setReceiver(MessageParty receiver){
		CC_SAFE_RETAIN(receiver);
		CC_SAFE_RELEASE(m_receiver);
		m_receiver=receiver;
	}
    
	CCObject* getData(){
		return m_pData;
	}

    void setData(CCObject* data){
		CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_pData);
		m_pData=data;
	}

    CCDictionary* getDictionary(){
		 return (CCDictionary*) m_pData;
	}

    void setDictionary(CCDictionary* data){
		CC_SAFE_RETAIN(data);
		CC_SAFE_RELEASE(m_pData);
		m_pData=data;
	}

private:
    MessageType m_type;//消息的类型或ID。
    MessageParty m_sender;//消息的发送者
	MessageParty m_receiver;//消息的接收者
    float m_timeStamp;//发送时间
    CCObject* m_pData;
};

NS_CC_YHLIB_END

#endif  // YHLIB_MESSAGE_CCMESSAGE_H_
