#ifndef YHLIB_FSM_COMMON_CCFSMMACHINE_H_
#define YHLIB_FSM_COMMON_CCFSMMACHINE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "Message/CCMessage.h"
#include "CCFSMStateInterface.h"

NS_CC_YHLIB_BEGIN

class CCFSMMachineInterface
{
public:
	virtual bool init();

    virtual void addState(CCFSMStateInterface* state ,const std::string& name)=0;
    virtual void addState(CCFSMStateInterface* state ,unsigned int guid)=0;

	virtual void removeStateWithName(const std::string& name)=0;
    virtual void removeStateWithGuid(unsigned int guid)=0;

    virtual CCFSMStateInterface* stateForName(const std::string& name)=0;
    virtual CCFSMStateInterface* stateForGuid(unsigned int guid)=0;
    
	virtual void changeState(CCFSMStateInterface* state)=0;

    virtual void update()=0;
    
	virtual void update(float delta)=0;

    virtual void handleMessage(CCMessage* message)=0;
    
    
};

NS_CC_YHLIB_END

#endif // YHLIB_FSM_COMMON_CCFSMMACHINE_H_