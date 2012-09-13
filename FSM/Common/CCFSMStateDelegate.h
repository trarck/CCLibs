//
//  IStateDelegate.h
//  GameFsm
//  具体在游戏里实现。由于owner在不同游戏里实现不一样，所以要在游戏里实现此类
//
//  状态使用代理模式。状态可以保存自己的变量，每个实体都有一个状态对象。
//  Created by trarck trarck on 11-11-25.
//

#ifndef __CCFSMStateDelegate_H__
#define __CCFSMStateDelegate_H__

#include "cocos2d.h"
#include "CCFSMState.h"

class CCFSMStateDelegate:public CCFSMState
{
public:
    //状态的拥有者，状态机或实体对象
    virtual void setOwner(CCObject* owner);
    virtual CCObject* getOwner();
}

#endif //__CCFSMStateDelegate_H__
