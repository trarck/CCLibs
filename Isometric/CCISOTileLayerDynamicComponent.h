#ifndef ISO_CCISOTileLayerDynamicComponent_H_
#define ISO_CCISOTileLayerDynamicComponent_H_

#include "cocos2d.h"
#include "YHLibMacros.h"
#include "CCISOOptimizedTileLayer.h"
#include "CCISOComponentNode.h"

NS_CC_YHLIB_BEGIN

class CCISOTileLayerDynamicComponent : public CCISOOptimizedTileLayer {

public:
	
	CCISOTileLayerDynamicComponent();
    
	~CCISOTileLayerDynamicComponent(void);
	
    virtual bool init();
    
	virtual void initOffset(const CCPoint& tOffset);
    virtual void initOffset(float x,float y);
    
    CCSprite* createTile();

	bool beforeUpdateContent();
	void doUpdateContent();
    void doUpdateComponents();

	void calcComponentsCount();
	void createComponents();
    void initComponents();
    void setupComponents(int iComponentNodeExtendCount);
	void setupComponents(int iComponentNodeExtendCount,const CCPoint& position);
//    virtual void draw();
    
    virtual void setComponentTileColumn(int iComponentTileColumn);
    virtual int getComponentTileColumn();
    
    virtual void setComponentTileRow(int iComponentTileRow);
    virtual int getComponentTileRow();
    
    virtual void setComponentTileExtendCount(int iComponentNodeExtendCount);
    virtual int getComponentTileExtendCount();


    virtual void scroll(const CCPoint& tOffset);
    virtual void scroll(float x,float y);


protected:
    int m_iComponentTileColumn;
    int m_iComponentTileRow;
    
    int m_iComponentTileTotalColumn;
    int m_iComponentTileTotalRow;
    //x,y增加相同的格子数
    int m_iComponentNodeExtendCount;
    
	//CCISOComponentNode** m_pComponents;
	CCArray* m_pComponents;
    
    int m_iLastStartX;
    int m_iLastStartY;
    
    int m_iComponentIndexX;
    int m_iComponentIndexY;
    
};



NS_CC_YHLIB_END

#endif //ISO_CCISOTileLayerDynamicComponent_H_
