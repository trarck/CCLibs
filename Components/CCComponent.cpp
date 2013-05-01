#include "CCComponent.h"
#include "Message/CCMessageManager.h"

NS_CC_YHLIB_BEGIN

CCComponent::CCComponent()
:m_pOwner(NULL)
{
    CCLOG("CCComponent create");
}

CCComponent::~CCComponent()
{
    CCLOG("CCComponent destroy");
}

bool CCComponent::init(void)
{
    CCLOG("CCComponent init");
	m_sName="CCComponent";
    return true;
}

void CCComponent::handleMessage(CCMessage *message)
{
    CCLOG("CCComponent::startAttack");
}

bool CCComponent::registerMessages()
{
    CCLOG("CCComponent::registerMessages");
    
    return true;
}

void CCComponent::cleanupMessages()
{
    CCLOG("CCComponent::cleanupMessages");
    CCMessageManager::defaultManager()->removeReceiver(this);
}

NS_CC_YHLIB_END
