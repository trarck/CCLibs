//
//  ComponentEntity.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef YHLIB_COMPONENTS_CCCOMPONENTENTITYINTERFACE_H_
#define YHLIB_COMPONENTS_CCCOMPONENTENTITYINTERFACE_H_

#include "cocos2d.h"
#include "CCComponent.h"


NS_CC_YHLIB_BEGIN

class CCComponentEntityInterface
{
public:
    
    virtual void setupComponents();
    
    void addComponent(CCComponent* component);
    void addComponent(CCComponent* component,const char* name);
};

NS_CC_YHLIB_END


#endif //YHLIB_COMPONENTS_CCCOMPONENTENTITYINTERFACE_H_
