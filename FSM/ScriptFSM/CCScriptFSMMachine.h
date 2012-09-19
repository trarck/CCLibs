#ifndef __CCFSMMachine_H__
#define __CCFSMMachine_H__

#include "CCFSMMachine.h"

NS_CC_BEGIN

class CCFSMMachine:public CCObject
{
public:
	CCFSMMachine(void);
	~CCFSMMachine(void);
	
	// virtual CCFSMState* getCurrentState();
	//     virtual void setCurrentState(CCFSMState* state);
    
    virtual void addState(CCFSMState* state ,CCObject* key);
    virtual void addState(CCFSMState* state ,const std::string& name);
    virtual void addState(CCFSMState* state ,unsigned int guid);
    
    virtual void removeStateWithKey(CCObject* key);
    virtual void removeStateWithName(const std::string& name);
    virtual void removeStateWithGuid(unsigned int guid);
    
    virtual CCFSMState* stateForKey(CCObject* key);
    virtual CCFSMState* stateForName(const std::string& name);
    virtual CCFSMState* stateForGuid(unsigned int guid);
    
    virtual void update();
    
    virtual void handleMessage(CCMessage* message);
    
    virtual void changeState(CCFSMState* state);
};

NS_CC_END

#endif //__CCFSMMachine_H__