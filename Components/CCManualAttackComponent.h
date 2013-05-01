#ifndef YHLIB_COMPONENTS_CCMANUALATTACKCOMPONENT_H_
#define YHLIB_COMPONENTS_CCMANUALATTACKCOMPONENT_H_

#include "cocos2d.h"
#include "CCAttackComponent.h"

USING_NS_CC;

NS_CC_YHLIB_BEGIN


class CCManualAttackComponent : public CCAttackComponent 
{
public:
    CCManualAttackComponent();
    ~CCManualAttackComponent();
    virtual bool init();
};

NS_CC_YHLIB_END

#endif //YHLIB_COMPONENTS_CCMANUALATTACKCOMPONENT_H_
