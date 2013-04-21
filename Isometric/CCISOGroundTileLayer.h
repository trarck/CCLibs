#ifndef YHLIB_ISOMETRIC_CCISOGROUNDTILELAYER_H_
#define YHLIB_ISOMETRIC_CCISOGROUNDTILELAYER_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCISOTileLayer.h"
#include "CCISOInfos.h"
#include "cocoa/CCArray.h"

NS_CC_YHLIB_BEGIN

struct _ccCArray;

class CCISOGroundTileLayer : public CCISOTileLayer {

public:
	
	CCISOGroundTileLayer();
    
	~CCISOGroundTileLayer(void);

    /**
     * 初始化显示tiles
     */
    virtual void setupTiles();
    
    /**
     * 获取tile
     */
    
	virtual CCSprite* tileSpriteAt(const CCPoint& pos);
    
    /**
     * 删除tile
     */
    virtual void removeSpriteTileAt(const CCPoint& pos);

public:
        
    void setTileSet(CCISOTilesetInfo* pTileSet);
    CCISOTilesetInfo* getTileSet();
    
    void setTileSets(CCArray* pTileSets);
    CCArray* getTileSets();


protected:
    
    /**
     * 添加tile
     */
	CCSprite* appendTile(unsigned int gid, const CCPoint& pos);
    CCSprite* appendTile(unsigned int gid, float x,float y);
    
    /**
     * 插入tile
     */
    CCSprite* insertTile(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTile(unsigned int gid, float x,float y);
    
    /**
     * 更新tile
     */
    CCSprite* updateTile(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTile(unsigned int gid, float x,float y);
    
   
    /**
     * 设置tile
     */
    void setupTileSprite(CCSprite* sprite, CCPoint mapCoord, unsigned int gid);
    
    CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
    CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);
    
protected:

};



NS_CC_YHLIB_END

#endif //YHLIB_ISOMETRIC_CCISOGROUNDTILELAYER_H_
