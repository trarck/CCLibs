#include "cocos2d.h"
#include "CCAstarNode.h"
#include "CCAstar.h"

NS_CC_BEGIN

CCAstarFunctionable::CCAstarFunctionable(void)
:m_funCheckBarrierHandle(NULL)
{
	
}

//本身是否可以通过
bool CCAstar::isWorkable(int x,int y) 
{
	return (*m_funCheckBarrierHandle)(x,y);
}

void setCheckBarrierHandle(FUN_CheckBarrierHandler checkBarrierHandle)
{
	m_funCheckBarrierHandle=checkBarrierHandle;
}


NS_CC_END
