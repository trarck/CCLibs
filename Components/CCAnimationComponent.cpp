#include "CCAnimationComponent.h"
#include "Message/CCMessageManager.h"

USING_NS_CC;

NS_CC_YHLIB_BEGIN

CCAnimationComponent::CCAnimationComponent()
:m_animations(NULL)
,m_lastAction(NULL)
{
	CCLOG("CCAnimationComponent create");
}

CCAnimationComponent::~CCAnimationComponent()
{
	CCLOG("CCAnimationComponent destroy");

	CC_SAFE_RELEASE(m_animations);
    CC_SAFE_RELEASE(m_lastAction);
}


bool CCAnimationComponent::init()
{
	m_animations=new CCDictionary();
	return true;
}

bool CCAnimationComponent::init(const std::string& file)
{
	init();
	return true;
}

bool CCAnimationComponent::init(CCDictionary* data)
{
	init();
	return true;
}

void CCAnimationComponent::handleMessage(CCMessage *message)
{
    CCLOG("CCAnimationComponent::handleMessage");
    CCLOG("get message %d",message->getType());
    
}

bool CCAnimationComponent::registerMessages()
{
    CCLOG("CCAnimationComponent::registerMessages");

    return true;
}

void CCAnimationComponent::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}

CCObject* CCAnimationComponent::animationForName(const std::string& name)
{
	return m_animations->objectForKey(name);
}

CCAction* CCAnimationComponent::actionForName(const std::string& name)
{
	return (CCAction*) m_animations->objectForKey(name);
}

CCAction* CCAnimationComponent::actionForName(const std::string& name ,int index)
{
	return (CCAction*)((CCArray*)(m_animations->objectForKey(name)))->objectAtIndex(index);
}

CCAction* CCAnimationComponent::actionForName(const std::string& name ,const std::string& key)
{
	return (CCAction*)((CCDictionary*)(m_animations->objectForKey(name)))->objectForKey(key);
}

CCArray* CCAnimationComponent::actionListForName(const std::string& name)
{
	return (CCArray*)(m_animations->objectForKey(name));
}

CCDictionary* CCAnimationComponent::actionMapForName(const std::string& name)
{
	return (CCDictionary*)m_animations->objectForKey(name);
}

void CCAnimationComponent::addAnimation(CCObject* animation,const std::string&  name)
{
	m_animations->setObject(animation ,name);
}

void CCAnimationComponent::addAction(CCAction* action ,const std::string& name)
{
	m_animations->setObject(action ,name);
}

void CCAnimationComponent::addActionList(CCArray* actionList ,const std::string& name)
{
	m_animations->setObject(actionList ,name);
}

void CCAnimationComponent::addActionMap(CCDictionary* actionMap ,const std::string& name)
{
	m_animations->setObject(actionMap ,name);
}

void CCAnimationComponent::removeAnimationNamed(const std::string& name)
{
	m_animations->removeObjectForKey(name);
}

CCArray* CCAnimationComponent::eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay)
{
	CCTexture2D *texture=CCTextureCache::sharedTextureCache()->addImage(file);
	
	CCArray* actions=new CCArray();
	actions->initWithCapacity(8);
	//move action
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(frameCount);
		for (int j=0; j<frameCount; j++) {
			CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(texture ,CCRectMake(j*frameSize.width, i*frameSize.height, frameSize.width, frameSize.height));
			animFrames->addObject(frame);
		}
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,delay);
		CCAnimate *animate= CCAnimate::create(animation);
		actions->addObject(CCRepeatForever::create((CCActionInterval*)CCSequence::create(animate,NULL)));
		animFrames->release();
	}
	return actions;
}

CCArray* CCAnimationComponent::eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay,const char* pathFormat)
{
	CCArray *actions=new CCArray();
	actions->initWithCapacity(8);
	
	//move action
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(frameCount);
		CCAnimation* animation = CCAnimation::create();
		for (int j=0; j<frameCount; j++) {
			sprintf(str,pathFormat,dir,i,j);//"%s/%02d%03d.png"
			animation->addSpriteFrameWithFileName(str);
		}
		animation->setDelayPerUnit(delay);
		animation->setRestoreOriginalFrame(true);
		//animation.delay=delay;
		CCAnimate *animate= CCAnimate::create(animation);
		actions->addObject(CCRepeatForever::create((CCActionInterval*)CCSequence::create(animate,NULL)));
		animFrames->release();
	}
	return actions;
}

void CCAnimationComponent::changeAction(CCDictionary* pData)
{
	CCString* animationName=(CCString*)pData->objectForKey("name");
    int direction=((CCInteger*) pData->objectForKey("direction"))->getValue();
            
    CCAction* action=(CCAction*)actionForName(animationName->getCString(),direction);
    if(action && m_lastAction!=action){
        CCNode* owner=(CCNode*) m_pOwner;
        owner->stopAction(m_lastAction);
        owner->runAction(action);
        setLastAction(action);
    }else {
        CCLOG("unknow animation name %s",animationName);
    }
}

NS_CC_YHLIB_END