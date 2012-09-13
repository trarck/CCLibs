//
//  IStateParameter.h
//  GameFsm
//
//  具体在游戏里实现.由于CCEntity在不同游戏里实现不一样，所以要在游戏里实现此类。
//  状态对象不能有自己的变更，如果状态需要私有变量，可以放在实体中，实体通过参数传递。
//  状态可以在多个实体之间共用，状态可以使用单例模式。
//  Created by trarck trarck on 11-11-25.
//

#ifndef __CCFSMStateDelegate_H__
#define __CCFSMStateDelegate_H__

#include "cocos2d.h"
#include "CCFSMState.h"

#ifndef CCEntityDefined
#define CCEntityDefined
typedef cocos2d::CCObject CCEntity;
#endif

class CCFSMStateParameter:public CCFSMState
{
public:
	virtual void enter(CCEntity* entity);
	virtual void exit(CCEntity* entity);
	virtual void update(CCEntity* entity);
};

#endif //__CCFSMStateDelegate_H__