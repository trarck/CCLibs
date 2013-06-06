//
//  ZIndexNode.

#ifndef YHLIB_ISOMETRIC_CCZINDEXNODE_H_
#define YHLIB_ISOMETRIC_CCZINDEXNODE_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN


class CCZIndexNode : public CCObject {

public:
    CCZIndexNode();
    ~CCZIndexNode();
    
    void setRect(const CCRect& rect);
    const CCRect& getRect();
    
    //弱引用
    void setEntity(CCObject* entity);
    CCObject* getEntity();
protected:
    CCObject* m_pEntity;
    CCRect m_tRect;
};


NS_CC_YHLIB_END

#endif //YHLIB_ISOMETRIC_CCZINDEXNODE_H_
