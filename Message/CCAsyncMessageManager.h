//
//  TODO:对消息优先级的支持
//

#ifndef YHLIB_MESSAGE_CCASYNCMESSAGEMANAGER_H_
#define YHLIB_MESSAGE_CCASYNCMESSAGEMANAGER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

NS_CC_YHLIB_BEGIN

/**
 *
 * 存储结构hash(消息).hash(接收者).hash(发送者).array(处理单元)
 */
class CCAsyncMessageManager : public CCObject {

public:

    CCAsyncMessageManager();

    ~CCAsyncMessageManager();

    static CCAsyncMessageManager* sharedAsyncMessageManager();

    bool init();
 
    /**
	 * 发送消息。
	 */
    void dispatchMessage(CCMessage* message,float delay);


protected:
  
};

NS_CC_YHLIB_END

#endif // YHLIB_MESSAGE_CCASYNCMESSAGEMANAGER_H_