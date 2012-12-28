/**
 * MapCellInfo由函数来实现
 */

#ifndef ISO_CCAstarFunctionable_H_
#define ISO_CCAstarFunctionable_H_

#include "cocos2d.h"
#include "CCAstarNode.h"
#include "CCAstar.h"

NS_CC_BEGIN


typedef bool (*FUN_CheckBarrierHandler)(int x,int y);

class CCAstarFunctionable : public CCAstar {
public:
	
	CCAstarFunctionable();
	// ~CCAstarFunctionable(void);

	//由具体应用实现
	bool isWorkable(int x ,int y) ;
	void setCheckBarrierHandle(FUN_CheckBarrierHandler checkBarrierHandle);

protected:	
	//若引用
	FUN_CheckBarrierHandler m_funCheckBarrierHandle;
};

NS_CC_END

#endif // ISO_CCAstarFunctionable_H_