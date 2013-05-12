#include "CCEvent.h"

NS_CC_YHLIB_BEGIN

CCEvent::CCEvent()
:m_sType(""),
,m_pTarget(NULL)
,m_pCurrentTarget(NULL)
{

}

CCEvent::~CCEvent()
{
    CC_SAFE_RELEASE(m_pTarget);
    CC_SAFE_RELEASE(m_pCurrentTarget);
}

bool CCEvent::initEvent(const std::string &eventType, bool canBubble, bool cancelable)
{
    m_sType=eventType;
    m_bBubbles=canBubble;
    m_bCancelable=cancelable;
    
    m_nTimeStamp=0;

    m_bDispatchStopped=false;
    m_bNoDefault=false;

    return true;
}


NS_CC_YHLIB_END