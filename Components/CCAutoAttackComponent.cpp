#include "CCAutoAttackComponent.h"
#include "Message/CCMessageManager.h"

USING_NS_CC;

NS_CC_YHLIB_BEGIN

CCAutoAttackComponent::CCAutoAttackComponent()
:m_attackSpeed(2)
{
    CCLOG("CCAutoAttackComponent create");
}

CCAutoAttackComponent::~CCAutoAttackComponent()
{
    CCLOG("CCAutoAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool CCAutoAttackComponent::init()
{
    CCLOG("CCAutoAttackComponent init");
	 m_sName="CCAutoAttackComponent";
    return true;
}

void CCAutoAttackComponent::handleMessage(CCMessage *message)
{

}

bool CCAutoAttackComponent::registerMessages()
{
    
//    bool ret= AttackComponent::registerMessages();
    
    return true;

}


void CCAutoAttackComponent::attack()
{
    CCLOG("CCAutoAttackComponent::startAttack");
	if (m_target) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(CCAutoAttackComponent::updateAttack),this, m_attackSpeed, false);
	}
}

void CCAutoAttackComponent::stopAttack()
{
    CCLOG("CCAutoAttackComponent::stopAttack");
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(CCAutoAttackComponent::updateAttack),this);
}

void CCAutoAttackComponent::updateAttack(float delta)
{
    CCLOG("CCAutoAttackComponent::updateAttack");
	//check attack stop
	/*
	 1.target die
	 2.if use skill, mp less then the skill requirement

	 */
	//int targetHp=m_target->getHealth();
 //   CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
 //   m_target->setHealth(targetHp-1);
}

void CCAutoAttackComponent::didTargetDie()
{
    stopAttack();
}

float CCAutoAttackComponent::getAttackSpeed()
{
	return m_attackSpeed;
}

void CCAutoAttackComponent::setAttackSpeed(float attackSpeed)
{
	m_attackSpeed=attackSpeed;
}

NS_CC_YHLIB_END

