//
// 执行事件的函数句柄
//

#ifndef YHLIB_EVENT_CCEVENTHANDLER_H_
#define YHLIB_EVENT_CCEVENTHANDLER_H_

#include "cocos2d.h"
#include "EventHandle.h"

NS_CC_YHLIB_BEGIN

class Event;

//定义处理函数类型
typedef void (CCObject::*SEL_EventHandleD)(Event*,CCObject* data);
#define yh_event_selectorD(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class EventHandleD : public EventHandle {
public:
    
	inline EventHandleD()
		 :m_handleD(NULL)
        ,m_data(NULL)
	{

	}

    ~EventHandleD();

	inline SEL_EventHandleD getHandle()
	{
		return m_handle;
	}

	inline void setHandle(SEL_EventHandleD handle)
	{
		m_handle=handle;
	}

	inline bool initWithTarget(CCObject* pTarget,SEL_EventHandleD handle,CCObject* data)
	{
		setTarget(pTarget);
		m_handle=handle;
        setData(data);
		return true;
	}
    
    inline void setData(CCObject* data)
    {
        CC_SAFE_RETAIN(data);
        CC_SAFE_RELEASE(m_data);
        m_data=data;
    }

    inline CCObject* getData()
    {
        return m_data;
    }

	virtual void execute(Event *event);

protected:
	SEL_EventHandleD m_handle;
    CCObject* m_data;
};

//class EventHandleD : public EventHandle {
//public:
//    
//	EventHandleD()
//		:m_pTarget(NULL),
//		 m_handle(NULL)
//	{
//		CCLOG("EventHandle create");
//	}
//
//    ~EventHandleD();
//
//    inline void execute(Event *event)
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
