#include "CCFSMState.h"

NS_CC_BEGIN

void CCFSMState::enter()
{
	CCLOG("CCFSMState enter");
}

void CCFSMState::exit()
{
	CCLOG("CCFSMState exit");
}

void CCFSMState::update()
{
	CCLOG("CCFSMState update");
}

void CCFSMState::onMessage(CCMessage* message)
{
	CCLOG("CCFSMState onMessage");
}

NS_CC_END