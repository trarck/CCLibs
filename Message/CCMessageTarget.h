//
//
//
#ifndef YHLIB_MESSAGE_CCMESSAGETARGET_H_
#define YHLIB_MESSAGE_CCMESSAGETARGET_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

NS_CC_YHLIB_BEGIN

class CCMessageTarget : public CCObject {
public:
    
  
    //message operate
    virtual void registerMessage(unsigned int type,SEL_MessageHandler handle , CCObject* pSender);
    virtual void unregisterMessage(unsigned int type ,SEL_MessageHandler handle ,CCObject* pSender);
    virtual void sendMessage(unsigned int type ,CCObject* pReceiver ,CCObject* data);
    virtual void sendMessage(unsigned int type ,CCObject* pReceiver);
	virtual void cleanupMessages();

    
    
protected:

};

NS_CC_YHLIB_END


#endif //YHLIB_MESSAGE_CCMESSAGETARGET_H_
