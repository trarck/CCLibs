
#include "CCFSMMachine.h"

NS_CC_BEGIN

CCFSMMachine::CCFSMMachine(void)
{
    CCLOG("CCFSMMachine create");
}


CCFSMMachine::~CCFSMMachine(void)
{
    CCLOG("CCFSMMachine destroy");
}

// CCFSMState* CCFSMMachine::getCurrentState()
// {
// 	
// }
// 
// void CCFSMMachine::setCurrentState(CCFSMState* state)
// {
// 	
// }

void CCFSMMachine::addState(CCFSMState* state ,CCObject* key)
{
	
}

void CCFSMMachine::addState(CCFSMState* state ,const std::string& name)
{
	
}

void CCFSMMachine::addState(CCFSMState* state ,unsigned int guid)
{
	
}

void CCFSMMachine::removeStateWithKey(CCObject* key)
{
	
}

void CCFSMMachine::removeStateWithName(const std::string& name)
{
	
}

void CCFSMMachine::removeStateWithGuid(unsigned int guid)
{
	
}

CCFSMState* CCFSMMachine::stateForKey(CCObject* key)
{
	
}

CCFSMState* CCFSMMachine::stateForName(const std::string& name)
{
	
}

CCFSMState* CCFSMMachine::stateForGuid(unsigned int guid)
{
	
}

void CCFSMMachine::update()
{
	CCLOG("CCFSMMachine update");
}

void CCFSMMachine::handleMessage(CCMessage* message)
{
	CCLOG("CCFSMMachine handleMessage");
}

void CCFSMMachine::changeState(CCFSMState* state)
{
	CCLOG("CCFSMMachine changeState");
}

NS_CC_END
