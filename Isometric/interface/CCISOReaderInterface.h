#ifndef ISO_CCISOReaderInterface_H_
#define ISO_CCISOReaderInterface_H_

#include "cocos2d.h"
#include "YHLibMacros.h"

NS_CC_YHLIB_BEGIN

class CCISOTileMap;

class CCISOReaderInterface
{

public:
   
    virtual CCISOTileMap* getMap();
    
    virtual readMap(CCISOTileMap* pMap);
    
};

NS_CC_YHLIB_END

#endif //ISO_CCISOReaderInterface_H_
