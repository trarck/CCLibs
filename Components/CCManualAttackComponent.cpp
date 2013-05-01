#include "CCManualAttackComponent.h"
#include "Message/CCMessageManager.h"

USING_NS_CC;

NS_CC_YHLIB_BEGIN

CCManualAttackComponent::CCManualAttackComponent()
{
    CCLOG("CCManualAttackComponent create");
}

CCManualAttackComponent::~CCManualAttackComponent()
{
    CCLOG("CCManualAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool CCManualAttackComponent::init()
{
    CCLOG("CCManualAttackComponent init");
	m_sName="CCManualAttackComponent";
    return true;
}

NS_CC_YHLIB_END

