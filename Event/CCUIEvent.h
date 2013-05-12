#ifndef YHLIB_EVENT_CCUIEVENT_H_
#define YHLIB_EVENT_CCUIEVENT_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCUIEvent:public CCObject
{
public:
    CCUIEvent();

    ~CCUIEvent();

    bool initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::CCNode* view, long detail);

    inline void setView( cocos2d::CCNode* view)
    {
        CC_SAFE_RETAIN(view);
        CC_SAFE_RELEASE(m_pView);
        m_pView = view;
    }

    inline  cocos2d::CCNode* getView()
    {
        return m_pView;
    }

    inline void setDetail(long detail)
    {
        m_lDetail = detail;
    }

    inline long getDetail()
    {
        return m_lDetail;
    }

private:
    cocos2d::CCNode* m_pView;
    long m_lDetail;

NS_CC_YHLIB_END

#endif  // YHLIB_EVENT_CCUIEVENT_H_