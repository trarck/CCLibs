#ifndef YHLIB_EVENT_CCEVENT_H_
#define YHLIB_EVENT_CCEVENT_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCEvent:public CCObject
{
public:

    CCEvent();
    ~CCEvent(void);

    bool initEvent(const std::string &eventType, bool canBubble, bool cancelable);

    inline bool initEvent(const std::string &eventType){
        return initEvent(eventType,true,true);
    }
    
    inline void stopPropagation() {
        m_bDispatchStopped=true;
    }

    inline void preventDefault(){
       m_bNoDefault=true;
    }

    inline bool isDispatchStopped() {
       return !m_bBubbles || (m_bBubbles & m_bDispatchStopped);
    }

    inline bool getPreventDefault() {
        return m_bCancelable && m_bNoDefault;
    }

    /**事件的处理阶段*/
    enum{
        CAPTURING_PHASE=1,
        AT_TARGET,
        BUBBLING_PHASE,
    };
//=================get set=====================//
public:
    inline void setType(const std::string & sType)
    {
        m_sType = sType;
    }

    inline const std::string & getType()
    {
        return m_sType;
    }

    inline void setTarget(cocos2d::CCObject* pTarget)
    {
        CC_SAFE_RETAIN(pTarget);
        CC_SAFE_RELEASE(m_pTarget);
        m_pTarget = pTarget;
    }

    inline cocos2d::CCObject* getTarget()
    {
        return m_pTarget;
    }

    inline void setCurrentTarget(cocos2d::CCObject* pCurrentTarget)
    {
        CC_SAFE_RETAIN(pCurrentTarget);
        CC_SAFE_RELEASE(m_pCurrentTarget);
        m_pCurrentTarget = pCurrentTarget;
    }

    inline cocos2d::CCObject* getCurrentTarget()
    {
        return m_pCurrentTarget;
    }

    inline void setEventPhase(int nEventPhase)
    {
        m_nEventPhase = nEventPhase;
    }

    inline int getEventPhase()
    {
        return m_nEventPhase;
    }

    inline void setBubbles(bool bBubbles)
    {
        m_bBubbles = bBubbles;
    }

    inline bool getBubbles()
    {
        return m_bBubbles;
    }

    inline void setCancelable(bool bCancelable)
    {
        m_bCancelable = bCancelable;
    }

    inline bool getCancelable()
    {
        return m_bCancelable;
    }

    inline void setTimeStamp(int nTimeStamp)
    {
        m_nTimeStamp = nTimeStamp;
    }

    inline int getTimeStamp()
    {
        return m_nTimeStamp;
    }

protected:
    /**event类型*/
    std::string m_sType;
    /**event目标*/
    cocos2d::CCObject* m_pTarget;
    /**event 当前处理目标*/
    cocos2d::CCObject* m_pCurrentTarget;
    /**event 处理的阶段*/
    int m_nEventPhase;
    /**event允许冒泡*/
    bool m_bBubbles;
    /**event是否可以取消，用于取消默认操作的执行*/
    bool m_bCancelable;
    /**event时间戳。精确到毫秒*/
    int m_nTimeStamp;

    bool m_bDispatchStopped;

    bool m_bNoDefault
};

NS_CC_YHLIB_END

#endif  // YHLIB_EVENT_CCEVENT_H_