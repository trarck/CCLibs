#ifndef YHLIB_COMPONENTS_CCATTACKCOMPONENT_H_
#define YHLIB_COMPONENTS_CCATTACKCOMPONENT_H_

#include "cocos2d.h"
#include "CCComponent.h"

NS_CC_YHLIB_BEGIN


class CCAttackComponent : public CCComponent 
{
public:
    CCAttackComponent();
    ~CCAttackComponent();
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    virtual void cleanupMessages();
    
    virtual void attack();
    virtual void attackWithSkillId(int skillId);
    
    virtual void didTargetDie();
    
    virtual void setTarget(CCObject* target);
    CCObject* getTarget();
    
protected:
    CCObject* m_target;
};

NS_CC_YHLIB_END

#endif //YHLIB_COMPONENTS_CCATTACKCOMPONENT_H_
