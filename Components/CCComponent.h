#ifndef YHLIB_COMPONENTS_CCCOMPONENT_H_
#define YHLIB_COMPONENTS_CCCOMPONENT_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "Message/CCMessage.h"

NS_CC_YHLIB_BEGIN

//typedef CCObject GameEntity;

class CCComponent : public CCObject
{
public:
    CCComponent();
    ~CCComponent();
    
    virtual bool init(void);  
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
	virtual void cleanupMessages();
    //使用GameEntity也没有意义，具体还要使用强制类型转换
    //弱连接
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

	inline void setName(const std::string& sName)
	{
		m_sName = sName;
	}

	inline const std::string& getName()
	{
		return m_sName;
	}
protected:
    CCObject* m_pOwner;
	std::string m_sName;
};

NS_CC_YHLIB_END

#endif // YHLIB_COMPONENTS_CCCOMPONENT_H_
