//
// 执行事件的函数句柄
//

#ifndef YHLIB_EVENT_CCEVENTHANDLER_H_
#define YHLIB_EVENT_CCEVENTHANDLER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCEvent;

//定义处理函数类型
typedef void (CCObject::*SEL_EventHandle)(CCEvent*);
#define yh_event_selector(_SELECTOR) (SEL_EventHandle)(&_SELECTOR)

class CCEventHandle : public CCObject {
public:
    
	inline CCEventHandle()
		:m_pTarget(NULL),
		 m_handle(NULL)
	{
		CCLOG("CCEventHandle create");
	}

    ~CCEventHandle();

	inline CCObject* getTarget()
	{
		return m_pTarget;
	}

	inline void setTarget(CCObject* pTarget)
	{
		CC_SAFE_RETAIN(pTarget);
		CC_SAFE_RELEASE(m_pTarget);
		m_pTarget=pTarget;
	}

	inline SEL_EventHandle getHandle()
	{
		return m_handle;
	}

	inline void setHandle(SEL_EventHandle handle)
	{
		m_handle=handle;
	}

	inline bool initWithTarget(CCObject* pTarget,SEL_EventHandle handle)
	{
		setTarget(pTarget);
		m_handle=handle;
		return true;
	}

	inline void execute(CCEvent *event)
	{
		if(m_handle){
			(m_pTarget->*m_handle)(event);
		}
	}

protected:
	CCObject* m_pTarget;
	SEL_EventHandle m_handle;
};

//class CCEventHandleD : public CCEventHandle {
//public:
//    
//	CCEventHandleD()
//		:m_pTarget(NULL),
//		 m_handle(NULL)
//	{
//		CCLOG("CCEventHandle create");
//	}
//
//    ~CCEventHandleD();
//
//    inline void execute(CCEvent *event)
//	{
//		if(m_handle){
//			(m_pTarget->*m_handle)(event);
//		}
//	}
//    
//private:
//
//    CCObject* m_pData;
//
//};

NS_CC_YHLIB_END

#endif  // YHLIB_EVENT_CCEVENTHANDLER_H_
