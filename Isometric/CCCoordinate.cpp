//
//  Coordinate.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CCCoordinate.h"

NS_CC_YHLIB_BEGIN

static CCCoordinate* l_coordinate=NULL;

CCCoordinate::CCCoordinate()
:m_xUnit(0)
,m_yUnit(0)
,m_zUnit(0)
,m_tileWidth(0)
,m_tileHeight(0)
{
    
}

CCCoordinate::~CCCoordinate()
{
    
}


CCCoordinate* CCCoordinate::sharedCoordinate()
{
	if(!l_coordinate){
		l_coordinate=new CCCoordinate();
        l_coordinate->init();
	}
	return l_coordinate;	
}

static CCCoordinate::CCCoordinate* create()
{
	CCCoordinate* pRet=new CCCoordinate();
	if (pRet && pRet->init()){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

static CCCoordinate::CCCoordinate* create(int width,int height)
{
	if (pRet && pRet->init(width,height)){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

static CCCoordinate::CCCoordinate* create(int xUnit,int yUnit,int zUnit)
{
	if (pRet && pRet->init(xUnit,yUnit,zUnit)){ 
        pRet->autorelease(); 
        return pRet; 
    }else{ 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    }
}

void CCCoordinate::setTileSize(int width ,int height)
{
	m_tileWidth=width;
	m_tileHeight=height;
	
	m_xUnit=width/2;
	m_yUnit=height/2;
	m_zUnit=height;
}

void CCCoordinate::setCoordinateUnit(int xUnit ,int yUnit ,int zUnit)
{
	m_xUnit=xUnit;
	m_yUnit=yUnit;
	m_zUnit=zUnit;
	
	m_tileWidth=xUnit*2;
	m_tileHeight=yUnit*2;
}

CCSize CCCoordinate::mapToScreenSize(int l ,int b ,int h)
{
	int s;
	float width,height;
	CCSize size;
	
	s=l+b;
	width=s*m_xUnit;
	height=s*m_yUnit+h*m_zUnit;
	size.width=width;
	size.height=height;
	return size;
}

CCPoint CCCoordinate::mapToScreenAnchor(int l ,int b ,int h)
{
	CCPoint p;
	p.x=b*m_xUnit;
	p.y=h*m_zUnit;
	return p;
}

NS_CC_YHLIB_END
