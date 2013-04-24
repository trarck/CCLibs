//
//  TODO:对消息优先级的支持,延迟消息
//
//  没有全局消息，当发送者为空时，不是收到所有人发来的消息，而只能收到由空发送人发来的消息。
//	空可以用一个全局对象表示，和普通的对象处理一样处理.当投递普通对象的消息时不，触发全局消息。
//
//

#ifndef YHLIB_MESSAGE_CCSPECMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCSPECMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCCompleteMessageManager.h"

NS_CC_YHLIB_BEGIN

class CCSpecMessageManager: public CCCompleteMessageManager 
{
public:
    
    CCSpecMessageManager();
    ~CCSpecMessageManager();
    
	static CCSpecMessageManager* sharedSpecMessageManager();
    
    bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle ,unsigned int type ,CCObject* sender ,CCObject*  handleObject);
    
	bool registerReceiver(CCObject* receiver,SEL_MessageHandler handle,unsigned int type ,CCObject* sender);

    void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender,SEL_MessageHandler handle);
    void removeReceiver(CCObject* receiver,unsigned int type ,CCObject* sender);
    void removeReceiver(CCObject* receiver,unsigned int type);
    void removeReceiver(CCObject* receiver);
	void removeReceiverList(CCArray* list,SEL_MessageHandler handle);
	void removeReceiverList(CCArray* list);
	void removeReceiverMap(CCDictionary* map,SEL_MessageHandler handle);
	void removeReceiverMap(CCDictionary* map);
protected:
    CCDictionary* m_regiesterMap;
    
private:
	static CCSpecMessageManager* s_sharedSpecMessageManagerInstance;
};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCSPECMESSAGEMANAGER_H_
