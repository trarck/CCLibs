#include "CCAttackComponent.h"
#include "Message/CCMessageManager.h"


USING_NS_CC;

NS_CC_YHLIB_BEGIN

CCAttackComponent::CCAttackComponent()
:m_target(NULL)
{
    CCLOG("CCAttackComponent create");
    m_sName="CCAttackComponent";
}

CCAttackComponent::~CCAttackComponent()
{
    CCLOG("CCAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool CCAttackComponent::init()
{
    CCLOG("CCAttackComponent init");
    return true;
}

void CCAttackComponent::handleMessage(CCMessage *message)
{
    CCLOG("CCAttackComponent::handleMessage");
    CCLOG("get message %d",message->getType());
}

bool CCAttackComponent::registerMessages()
{
    CCLOG("CCAttackComponent::registerMessages");
    
    return true;
}

void CCAttackComponent::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}

void CCAttackComponent::attack()
{
    //if(m_target){
    //    CCLOG("CCAttackComponent::startAttack");
    //    int targetHp=m_target->getHealth();
    //    CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
    //    m_target->setHealth(targetHp-1);
    //}else {
    //    CCLOG("CCAttackComponent::startAttack no target");
    //}
}

void CCAttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

void CCAttackComponent::didTargetDie()
{
    CCLOG("target is die");
    
    ////remove message
    //CCMessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(CCAttackComponent::handleMessage));
    //CC_SAFE_RELEASE(m_target);
    //m_target=NULL;
}

CCObject* CCAttackComponent::getTarget()
{
    return m_target;
}

void CCAttackComponent::setTarget(CCObject* target)
{
    if(target!=m_target){
        //CCMessageManager::defaultManager()->removeReceiver(this, DIE, m_target, message_selector(CCAttackComponent::handleMessage));
        CC_SAFE_RETAIN(target);
        CC_SAFE_RELEASE(m_target);
        m_target=target;

        //CCMessageManager::defaultManager()->registerReceiver(this, message_selector(CCAttackComponent::handleMessage), DIE, m_target);
    }
}

NS_CC_YHLIB_END

