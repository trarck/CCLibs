#ifndef YHLIB_COMPONENTS_CCANIMATIONCOMPONENT_H_
#define YHLIB_COMPONENTS_CCANIMATIONCOMPONENT_H_

#include "cocos2d.h"
#include "CCComponent.h"

NS_CC_YHLIB_BEGIN

class CCAnimationComponent : public CCComponent
{
public:
	CCAnimationComponent();
	~CCAnimationComponent();
	//extend from parent
	virtual bool init();  

	bool init(const std::string&  file);
    bool init(CCDictionary* data);

	virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    virtual void cleanupMessages();

	CCObject* animationForName(const std::string& name);
	CCAction* actionForName(const std::string& name);
	CCAction* actionForName(const std::string& name ,int index);
	CCAction* actionForName(const std::string& name ,const std::string& key);

	CCArray* actionListForName(const std::string& name);
	CCDictionary* actionMapForName(const std::string& name);

	void addAction(CCAction* action, const std::string& name);
	void addActionList(CCArray* actionList ,const std::string& name);
	void addActionMap(CCDictionary* actionMap,const std::string& name);
	void addAnimation(CCObject* animation ,const std::string& name);
	void removeAnimationNamed(const std::string& name);

	static CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay);
	static CCArray* eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat);

	void changeAction(CCDictionary* pData);

	CCAction* getLastAction()
	{
		return m_lastAction;
	}

	void setLastAction(CCAction* action)
	{
		CC_SAFE_RETAIN(action);
		CC_SAFE_RELEASE(m_lastAction);
		m_lastAction=action;
	}

	CCAction* moveAction();
	void moveActoin(CCAction* action);

	CCArray* actionArray();
	void actionArray(CCArray* actionArray);

	CCDictionary* animations();
	void animations(CCDictionary* animations);

protected:
	CCDictionary* m_animations;
    
    CCAction* m_lastAction;
};

NS_CC_YHLIB_END

#endif // YHLIB_COMPONENTS_CCANIMATIONCOMPONENT_H_
