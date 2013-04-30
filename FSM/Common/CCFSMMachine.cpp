
#include "CCFSMMachine.h"

NS_CC_YHLIB_BEGIN

CCFSMMachine::CCFSMMachine(void)
:m_pCurrentState(NULL)
,m_pStates(NULL)

{
    CCLOG("CCFSMMachine create");
}


CCFSMMachine::~CCFSMMachine(void)
{
    CCLOG("CCFSMMachine destroy");
	CC_SAFE_RELEASE(m_pCurrentState);
	CC_SAFE_RELEASE(m_pStates);
}

bool CCFSMMachine::init()
{
	m_pStates=new CCDictionary();
	return true;
}

void CCFSMMachine::addState(CCFSMState* state ,const std::string& name)
{
	m_pStates->setObject(state,name);
}

void CCFSMMachine::addState(CCFSMState* state ,unsigned int uId)
{
	m_pStates->setObject(state,uId);
}

void CCFSMMachine::removeStateWithName(const std::string& name)
{
	m_pStates->removeObjectForKey(name);
}

void CCFSMMachine::removeStateWithGuid(unsigned int uId)
{
	m_pStates->removeObjectForKey(uId);
}

CCFSMState* CCFSMMachine::stateForName(const std::string& name)
{
	return static_cast<CCFSMState*>(m_pStates->objectForKey(name));
}

CCFSMState* CCFSMMachine::stateForGuid(unsigned int uId)
{
	return static_cast<CCFSMState*>(m_pStates->objectForKey(uId));
}

void CCFSMMachine::changeState(CCFSMState* state)
{
	m_pCurrentState->exit();
	setCurrentState(state);
	m_pCurrentState->enter();
}

void CCFSMMachine::update()
{
	m_pCurrentState->update();
}

void CCFSMMachine::update(float delta)
{
	m_pCurrentState->update(delta);
}

void CCFSMMachine::handleMessage(CCMessage* message)
{
	m_pCurrentState->onMessage(message);
}

NS_CC_YHLIB_END
