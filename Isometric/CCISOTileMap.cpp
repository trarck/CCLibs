
#include "CCISOTileMap.h"
#include "CCISOTileset.h"

NS_CC_YHLIB_BEGIN

CCISOTileMap::CCISOTileMap()
:m_tMapSize(CCSizeZero)
,m_pTileLayers(NULL)
,m_pObjectGroups(NULL)
,m_pProperties(NULL)
,m_pTileProperties(NULL)
,m_pDynamicComponent(NULL)
,m_pTilesetGroup(NULL)
{
	
}

CCISOTileMap::~CCISOTileMap()
{
    CC_SAFE_RELEASE(m_pTileLayers);
    CC_SAFE_RELEASE(m_pTilesetGroup);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pObjectGroups);
    CC_SAFE_RELEASE(m_pTileProperties);
    CC_SAFE_RELEASE(m_pDynamicComponent);
}

CCISOTileMap * CCISOTileMap::createWithXMLFile(const char *xmlFile)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithXMLFile(xmlFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap * CCISOTileMap::createWithJSONFile(const char *jsonFile)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithJSONFile(jsonFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap* CCISOTileMap::createWithXML(const char* tmxString, const char* resourcePath)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap* CCISOTileMap::createWithJSON(const char* jsonString, const char* resourcePath)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithJSON(jsonString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCISOTileMap::init()
{
    m_pTileLayers=new CCArray();
    m_pTileLayers->init();
    
    m_pObjectGroups=new CCArray();
    m_pObjectGroups->init();
    
    m_pProperties=new CCDictionary();

//    CCLayerColor* lc=CCLayerColor::create(ccc4(0,0,255,255), 600, 400);
//    addChild(lc);
	return true;
}

bool CCISOTileMap::initWithXMLFile(const char *xmlFile)
{
    CCAssert(xmlFile != NULL && strlen(xmlFile)>0, "CCISOTileMap: map file should not bi NULL");
    
    setContentSize(CCSizeZero);
    
//    CCISOXMLParser *xmlParser = CCISOXMLParser::formatWithXMLFile(xmlFile);
//    
//    CCISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    if (! mapInfo)
//    {
//        return false;
//    }
//    CCAssert( mapInfo->getTilesets()->count() != 0, "CCISOTileMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool CCISOTileMap::initWithJSONFile(const char *jsonFile)
{
    CCAssert( false, "CCISOTileMap::initWithJSONFile not support.");
    
    return true;
}

bool CCISOTileMap::initWithXML(const char* xmlString, const char* resourcePath)
{
    setContentSize(CCSizeZero);
        
//    CCISOXMLParser *xmlParser = CCISOXMLParser::formatWithXML(xmlString, resourcePath);
//    CCISOMapInfo *mapInfo=xmlParser->getMapInfo();
//    
//    CCAssert( mapInfo->getTilesets()->count() != 0, "CCISOTileMap: Map not found. Please check the filename.");
//    buildWithMapInfo(mapInfo);
    
    return true;
}

bool CCISOTileMap::initWithJSON(const char* jsonString, const char* resourcePath)
{
    CCAssert( false, "CCISOTileMap::initWithJSON not support.");
    
    return true;
}

CCISOTileLayer* CCISOTileMap::createLayer()
{
    return CCISOTileLayer::create();
}

//=================build from info======================//
// protected
//CCISOTileLayer * CCISOTileMap::parseLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
//{
//    //CCISOTilesetInfo *tileset = this->tilesetForLayer(layerInfo, mapInfo);
//    //CCISOTileLayer *layer = CCISOTileLayer::create(tileset, layerInfo, mapInfo);
//    //
//    //// tell the layerinfo to release the ownership of the tiles map.
//    //layerInfo->m_bOwnTiles = false;
//    //layer->setupTiles();
//    //
//    //return layer;
//	return NULL;
//}
//
//CCISOTilesetInfo * CCISOTileMap::tilesetForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
//{
//    CCSize size = layerInfo->m_tLayerSize;
//    CCArray* tilesets = mapInfo->getTilesets();
//    if (tilesets && tilesets->count()>0)
//    {
//        CCISOTilesetInfo* tileset = NULL;
//        CCObject* pObj = NULL;
//        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
//        {
//            tileset = (CCISOTilesetInfo*)pObj;
//            if (tileset)
//            {
//                for( unsigned int y=0; y < size.height; y++ )
//                {
//                    for( unsigned int x=0; x < size.width; x++ )
//                    {
//                        unsigned int pos = (unsigned int)(x + size.width * y);
//                        unsigned int gid = layerInfo->m_pTiles[ pos ];
//                        
//                        // gid are stored in little endian.
//                        // if host is big endian, then swap
//                        //if( o == CFByteOrderBigEndian )
//                        //    gid = CFSwapInt32( gid );
//                        /* We support little endian.*/
//                        
//                        // XXX: gid == 0 --> empty tile
//                        if( gid != 0 )
//                        {
//                            // Optimization: quick return
//                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
//                            if( (gid & kCCFlippedMask) >= tileset->m_uFirstGid )
//                                return tileset;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    
//    // If all the tiles are 0, return empty tileset
//    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->m_sName.c_str());
//    return NULL;
//}
//
//void CCISOTileMap::buildWithMapInfo(CCISOMapInfo* mapInfo)
//{
//    m_tMapSize = mapInfo->getMapSize();
//    m_tTileSize = mapInfo->getTileSize();
//    m_nMapOrientation = mapInfo->getOrientation();
//    
//    this->setTileLayers(mapInfo->getLayers());
//    this->setObjectGroups( mapInfo->getObjectGroups());
//    this->setProperties(mapInfo->getProperties());
//    this->setTileProperties(mapInfo->getTileProperties());
//
//    this->buildMapLayers(mapInfo);
//}
//
//void CCISOTileMap::buildMapLayers(CCISOMapInfo* mapInfo)
//{
//    int idx=0;
//    
//    CCArray* layers = mapInfo->getLayers();
//    if (layers && layers->count()>0)
//    {
//        CCISOLayerInfo* layerInfo = NULL;
//        CCObject* pObj = NULL;
//        CCARRAY_FOREACH(layers, pObj)
//        {
//            layerInfo = (CCISOLayerInfo*)pObj;
//            if (layerInfo && layerInfo->m_bVisible)
//            {
//                CCISOTileLayer *child = parseLayer(layerInfo, mapInfo);
//                addChild((CCNode*)child, idx, idx);
//                
//                // update content size with the max size
//                const CCSize& childSize = child->getContentSize();
//                CCSize currentSize = this->getContentSize();
//                currentSize.width = MAX( currentSize.width, childSize.width );
//                currentSize.height = MAX( currentSize.height, childSize.height );
//                this->setContentSize(currentSize);
//                
//                idx++;
//            }
//        }
//    }
//}

// public

CCISOTileset* CCISOTileMap::tilesetNamed(const char* tilesetName)
{
    CCAssert(tilesetName != NULL && strlen(tilesetName) > 0, "Invalid tileset name!");
    
    if (m_pTilesetGroup && m_pTilesetGroup->tilesetCount()>0){
        CCArray* pTilesets=m_pTilesetGroup->getTilesets();
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(pTilesets, pObj)
        {
            CCISOTileset* tileset = dynamic_cast<CCISOTileset*>(pObj);
            if(tileset)
            {
                if(0 == strcmp(tileset->getName(), tilesetName))
                {
                    return tileset;
                }
            }
        }
    }
    // layer not found
    return NULL;
}

CCISOTileLayer * CCISOTileMap::layerNamed(const char *layerName)
{
    CCAssert(layerName != NULL && strlen(layerName) > 0, "Invalid layer name!");
    
    if (m_pTileLayers && m_pTileLayers->count()>0){
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pTileLayers, pObj)
        {
            CCISOTileLayer* layer = dynamic_cast<CCISOTileLayer*>(pObj);
            if(layer)
            {
                if(0 == strcmp(layer->getLayerName(), layerName))
                {
                    return layer;
                }
            }
        }
    }
    // layer not found
    return NULL;
}

CCISOObjectGroup * CCISOTileMap::objectGroupNamed(const char *objectGroupName)
{
    CCAssert(objectGroupName != NULL && strlen(objectGroupName) > 0, "Invalid object group name!");
    
    if (m_pObjectGroups && m_pObjectGroups->count()>0)
    {
        CCISOObjectGroup* objectGroup = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pObjectGroups, pObj)
        {
            objectGroup = dynamic_cast<CCISOObjectGroup*>(pObj);
            if(objectGroup)
            {
                if(0 == strcmp(objectGroup->getName(), objectGroupName))
                {
                    return objectGroup;
                }
            }
        }
    }
    
    // objectGroup not found
    return NULL;
}

CCString* CCISOTileMap::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

/**
 * for update component coordinate
 */
void CCISOTileMap::updateComponentMapCoordinate(unsigned int index,float deltaMapX,float deltaMapY)
{
    CCLOG("CCISOTileMap::updateComponentMapCoordinate");
    
    
    //TODO other thing.
    //1.标记地图哪些区域可以显示。
    //2.通知子层更改组件的位置。

}


void CCISOTileMap::scrollLayer(const CCPoint& pos)
{
    CCObject* pObj=NULL;
    CCISOTileLayer* tileLayer;
    
    CCARRAY_FOREACH(m_pTileLayers, pObj){
        tileLayer=(CCISOTileLayer*) pObj;
        tileLayer->scroll(pos);
    }
}


void CCISOTileMap::setMapSize(CCSize tMapSize)
{
    m_tMapSize = tMapSize;
}

CCSize CCISOTileMap::getMapSize()
{
    return m_tMapSize;
}

void CCISOTileMap::setTileSize(const CCSize& tTileSize)
{
    m_tTileSize = tTileSize;
}

const CCSize& CCISOTileMap::getTileSize()
{
    return m_tTileSize;
}

void CCISOTileMap::setName(const char* pName)
{
    m_pName = pName;
}

const char* CCISOTileMap::getName()
{
    return m_pName.c_str();
}

void CCISOTileMap::setMapOrientation(int nMapOrientation)
{
    m_nMapOrientation = nMapOrientation;
}

int CCISOTileMap::getMapOrientation()
{
    return m_nMapOrientation;
}

void CCISOTileMap::setTileLayers(CCArray* pTileLayers)
{
	CC_SAFE_RETAIN(pTileLayers);
    CC_SAFE_RELEASE(m_pTileLayers);
    m_pTileLayers = pTileLayers;
}

CCArray* CCISOTileMap::getTileLayers()
{
	return m_pTileLayers;
}

void CCISOTileMap::setObjectGroups(CCArray* pObjectGroups)
{
    CC_SAFE_RETAIN(pObjectGroups);
    CC_SAFE_RELEASE(m_pObjectGroups);
    m_pObjectGroups = pObjectGroups;
}

CCArray* CCISOTileMap::getObjectGroups()
{
    return m_pObjectGroups;
}

void CCISOTileMap::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTileMap::getProperties()
{
    return m_pProperties;
}

void CCISOTileMap::setIdentifier(int nIdentifier)
{
	m_nIdentifier=nIdentifier;
}

int CCISOTileMap::getIdentifier()
{
	return m_nIdentifier;
}

void CCISOTileMap::setTileProperties(CCDictionary* pTileProperties)
{
    CC_SAFE_RETAIN(pTileProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    m_pTileProperties = pTileProperties;
}

CCDictionary* CCISOTileMap::getTileProperties()
{
    return m_pTileProperties;
}

void CCISOTileMap::setDynamicComponent(CCISODynamicComponent* pDynamicComponent)
{
    CC_SAFE_RETAIN(pDynamicComponent);
    CC_SAFE_RELEASE(m_pDynamicComponent);
    m_pDynamicComponent = pDynamicComponent;
}

CCISODynamicComponent* CCISOTileMap::getDynamicComponent()
{
    return m_pDynamicComponent;
}

void CCISOTileMap::setTilesetGroup(CCISOTilesetGroup* pTilesetGroup)
{
    CC_SAFE_RETAIN(pTilesetGroup);
    CC_SAFE_RELEASE(m_pTilesetGroup);
    m_pTilesetGroup = pTilesetGroup;
}

CCISOTilesetGroup* CCISOTileMap::getTilesetGroup()
{
    return m_pTilesetGroup;
}
NS_CC_YHLIB_END
