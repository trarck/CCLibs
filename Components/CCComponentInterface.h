#ifndef YHLIB_COMPONENTS_COMPONENTINTERFACE_H_
#define YHLIB_COMPONENTS_COMPONENTINTERFACE_H_

#include "cocos2d.h"

NS_CC_YHLIB_BEGIN

class CCComponentInterface : public CCObject
{
public:
    virtual bool init();  
    
    virtual bool registerEvents();
	
	virtual GameEntity* getOwner();
	virtual void setOwner(GameEntity* owner);
};

NS_CC_YHLIB_END

#endif // YHLIB_COMPONENTS_COMPONENTINTERFACE_H_
