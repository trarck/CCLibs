//
// 执行事件的函数句柄
//

#ifndef YHLIB_EVENT_CCEVENTHANDLER_H_
#define YHLIB_EVENT_CCEVENTHANDLER_H_

#include "cocos2d.h"
#include "CCEventHandle.h"

NS_CC_YHLIB_BEGIN

//定义处理函数类型
typedef void (CCObject::*SEL_EventHandleD)(CCEvent* evt,CCObject* data);
#define yh_event_selectorD(_SELECTOR) (SEL_EventHandleD)(&_SELECTOR)

class CCEventHandleWrap : public CCObject {
public:
    
	inline CCEventHandleWrap()
        :m_pTarget(NULL)
		,m_handle(NULL)
        ,m_data(NULL)
	{

	}

    ~CCEventHandleWrap();

    inline void handle(CCEvent* event){
        if(m_handle){
		    (m_pTarget->*m_handle)(event,m_data);
	    }
    }

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

protected:
	CCObject* m_pTarget;
	SEL_EventHandleD m_handle;
    CCObject* m_data;
};

NS_CC_YHLIB_END

#endif  // YHLIB_EVENT_CCEVENTHANDLER_H_
