//
// 执行消息的函数句柄
//

#ifndef YHLIB_MESSAGE_CCMESSAGEHANDLER_H_
#define YHLIB_MESSAGE_CCMESSAGEHANDLER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCMessage;

//定义处理函数类型
typedef void (CCObject::*SEL_MessageHandler)(CCMessage*);
#define message_selector(_SELECTOR) (SEL_MessageHandler)(&_SELECTOR)

class CCMessageHandler : public CCObject {
public:
    
	CCMessageHandler()
		:m_target(NULL),
		 m_handle(NULL)
	{
		CCLOG("CCMessageHandler create");
	}

    ~CCMessageHandler();

	CCObject* getTarget()
	{
		return m_pTarget;
	}

	void setTarget(CCObject* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(m_pTarget);
		m_pTarget=pTarget;
	}

	SEL_MessageHandler getHandle()
	{
		return m_handle;
	}

	void setHandle(SEL_MessageHandler handle)
	{
		m_handle=handle;
	}

	bool initWithTarget(CCObject* pTarget,SEL_MessageHandler handle)
	{
		setTarget(pTarget);
		m_handle=handle;
		return true;
	}

	void execute(CCMessage *msg)
	{
		if(m_handle){
			(m_pTarget->*m_handle)(msg);
		}
	}

private:
	CCObject* m_pTarget;
	SEL_MessageHandler m_handle;
};


NS_CC_YHLIB_END

#endif  // YHLIB_MESSAGE_CCMESSAGEHANDLER_H_
