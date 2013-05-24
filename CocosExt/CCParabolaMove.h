//
//  Parabola.h
//  ProjectFB
//
//
//

#ifndef YHLIB_COCOSEXT_CCPARABOLAMOVE_H_
#define YHLIB_COCOSEXT_CCPARABOLAMOVE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"


NS_CC_YHLIB_BEGIN


NS_FB_BEGIN

class CCParabolaMove : public cocos2d::CCActionInterval
{
public:
    //负的表示向下
    CCParabolaMove():m_fGravity(-1000.0f){}
    
    /** initializes the action */
    bool initWithDuration(float duration, const cocos2d::CCPoint& deltaPosition);
    
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void step(float delta);
    virtual void update(float time);
    
public:
    /** creates the action */    
    static CCParabolaMove* create(float duration,const cocos2d::CCPoint& speed);
    
    inline void setGravity(float fGravity)
    {
        m_fGravity = fGravity;
    }
    
    inline float getGravity()
    {
        return m_fGravity;
    }
    
protected:
    cocos2d::CCPoint m_positionDelta;
    cocos2d::CCPoint m_startPosition;
    cocos2d::CCPoint m_previousPosition;
    
    cocos2d::CCPoint m_tSpeed;
    
    float m_fGravity;
};


class CCParabolaMoveTo : public CCParabolaMove
{
public:
    CCParabolaMoveTo()
    :m_fHeight(0.0f)
    ,m_bUseHight(false)
    {
        
    }
    /** initializes the action */
    bool initWithDuration(float duration, const cocos2d::CCPoint& position);
    
    bool initWithDuration(float duration, const cocos2d::CCPoint& position,float height);
        
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    
    
    void stop();
    
    inline void setHeight(float fHeight)
    {
        m_fHeight = fHeight;
    }
    
    inline float getHeight()
    {
        return m_fHeight;
    }
    
public:
    /** creates the action */
    static CCParabolaMoveTo* create(float duration,const cocos2d::CCPoint& position);
    static CCParabolaMoveTo* create(float duration,const cocos2d::CCPoint& position,float height);
    
protected:
    cocos2d::CCPoint m_endPosition;
    float m_fHeight;;
    bool m_bUseHight;
};


NS_FB_END

#endif //YHLIB_COCOSEXT_CCPARABOLAMOVE_H_
