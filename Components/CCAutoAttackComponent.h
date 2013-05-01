#ifndef YHLIB_COMPONENTS_CCAUTOATTACKCOMPONENT_H_
#define YHLIB_COMPONENTS_CCAUTOATTACKCOMPONENT_H_

#include "cocos2d.h"

#include "CCAttackComponent.h"

NS_CC_YHLIB_BEGIN


class CCAutoAttackComponent : public CCAttackComponent 
{
public:
    CCAutoAttackComponent();
    ~CCAutoAttackComponent();
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    
    virtual void attack();
    virtual void didTargetDie();
    
    void stopAttack();
    void updateAttack(float delta);
    
    //property
    
    float getAttackSpeed();
    void setAttackSpeed(float attackSpeed);
protected:
    float m_attackSpeed;
};

NS_CC_YHLIB_END

#endif //YHLIB_COMPONENTS_CCAUTOATTACKCOMPONENT_H_
