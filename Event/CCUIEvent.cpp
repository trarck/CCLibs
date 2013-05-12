#include "CCUIEvent.h"

NS_CC_YHLIB_BEGIN

CCUIEvent::CCUIEvent()
:m_pView(NULL)
,m_lDetail(0)
{

}

CCUIEvent:: ~CCUIEvent()
{
    CC_SAFE_RELEASE(m_pView);
}

bool CCUIEvent::initUIEvent(const std::string& type, bool canBubble, bool cancelable,cocos2d::CCNode* view, long detail)
{
    if(!CCEvent::initEvent(type,canBubble,cancelable)){
        return false;
    }
    m_pView=view;
    m_lDetail=detail;
}

NS_CC_YHLIB_END