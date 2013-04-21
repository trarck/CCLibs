#ifndef YHLIB_ISOMETRIC_CCISOBATCHDYNAMICCOMPONENT_H_
#define YHLIB_ISOMETRIC_CCISOBATCHDYNAMICCOMPONENT_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCISOComponentNode.h"
#include "CCISODynamicComponent.h"

NS_CC_YHLIB_BEGIN

class CCISOTileLayer;

class CCISOBatchDynamicComponent : public CCISODynamicComponent {

public:
	
	CCISOBatchDynamicComponent();
    
	~CCISOBatchDynamicComponent(void);
	
    virtual bool init();
    
	void createComponents();
protected:
    
    virtual void updateNode(CCISOComponentNode* node,float mx,float my);
    
protected:
    
    CCSpriteBatchNode* m_pBatchNode;
    
};



NS_CC_YHLIB_END

#endif //YHLIB_ISOMETRIC_CCISOBATCHDYNAMICCOMPONENT_H_
