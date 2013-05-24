//
//  DelayMessageManager.h
//
//

#ifndef PROJECTFB_UTILS_DelayMessageManager_H_
#define PROJECTFB_UTILS_DelayMessageManager_H_

#include "cocos2d.h"
#include "GameMacros.h"
#include "Message/CCMessage.h"
#include "Message/CCMessageManager.h"

NS_FB_BEGIN

class DelayMessage:public cocos2d::CCObject
{
public:
    
    DelayMessage()
    :m_pMessage(NULL)
    ,m_fDelay(0.0f)
    {
        
    }
    
    DelayMessage(float delay,cocos2d::CCMessage* message)
    :m_pMessage(message)
    ,m_fDelay(delay)
    {
        CC_SAFE_RETAIN(message);
    }
    
    ~DelayMessage()
    {
        CC_SAFE_RELEASE(m_pMessage);
    }
    
    inline void setMessage(cocos2d::CCMessage* pMessage)
    {
        CC_SAFE_RETAIN(pMessage);
        CC_SAFE_RELEASE(m_pMessage);
        m_pMessage = pMessage;
    }
    
    inline cocos2d::CCMessage* getMessage()
    {
        return m_pMessage;
    }
    
    float m_fDelay;

private:
    
    cocos2d::CCMessage* m_pMessage;

    
};

class DelayMessageManager:public cocos2d::CCObject
{
public:
    
    DelayMessageManager();
    
    ~DelayMessageManager();
    
    static DelayMessageManager* sharedDelayMessageManager();
    
    bool init();
    
    void start();
    
    void stop();
    
    void update(float delta);
    
    void dispatchMessage(cocos2d::CCMessage* message,float fDelay);
    
    inline void setMessageManager(cocos2d::CCMessageManager* pMessageManager)
    {
        CC_SAFE_RETAIN(pMessageManager);
        CC_SAFE_RELEASE(m_pMessageManager);
        m_pMessageManager = pMessageManager;
    }
    
    inline cocos2d::CCMessageManager* getMessageManager()
    {
        return m_pMessageManager;
    }
    
private:
    
    cocos2d::CCArray* m_pMessages;
    
    cocos2d::CCMessageManager* m_pMessageManager;
};

NS_FB_END

#endif //PROJECTFB_UTILS_DelayMessageManager_H_
