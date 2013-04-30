#ifndef YHLIB_FSM_COMMON_CCFSMMACHINE_H_
#define YHLIB_FSM_COMMON_CCFSMMACHINE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "Message/CCMessage.h"
#include "CCFSMState.h"

NS_CC_YHLIB_BEGIN

class CCFSMMachine:public CCObject
{
public:
	CCFSMMachine(void);
	~CCFSMMachine(void);
	
	virtual bool init();

    virtual void addState(CCFSMState* state ,const std::string& name);
    virtual void addState(CCFSMState* state ,unsigned int uId);
    
    virtual void removeStateWithName(const std::string& name);
    virtual void removeStateWithGuid(unsigned int uId);
    
    virtual CCFSMState* stateForName(const std::string& name);
    virtual CCFSMState* stateForGuid(unsigned int uId);

	virtual void changeState(CCFSMState* state);

    virtual void update();
    
	virtual void update(float delta);

    virtual void handleMessage(CCMessage* message);
 
public:

	inline void setCurrentState(CCFSMState* pCurrentState)
	{
		CC_SAFE_RETAIN(pCurrentState);
		CC_SAFE_RELEASE(m_pCurrentState);
		m_pCurrentState = pCurrentState;
	}

	inline CCFSMState* getCurrentState()
	{
		return m_pCurrentState;
	}

	inline void setOwner(CCObject* pOwner)
	{
		CC_SAFE_RETAIN(pOwner);
		CC_SAFE_RELEASE(m_pOwner);
		m_pOwner = pOwner;
	}

	inline CCObject* getOwner()
	{
		return m_pOwner;
	}

	inline void setStates(CCDictionary* pStates)
	{
		CC_SAFE_RETAIN(pStates);
		CC_SAFE_RELEASE(m_pStates);
		m_pStates = pStates;
	}

	inline CCDictionary* getStates()
	{
		return m_pStates;
	}

protected:

	CCFSMState* m_pCurrentState;
	CCObject* m_pOwner;
	CCDictionary* m_pStates;

};

NS_CC_YHLIB_END

#endif // YHLIB_FSM_COMMON_CCFSMMACHINE_H_