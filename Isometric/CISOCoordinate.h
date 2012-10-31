/*
 *  CISOCoordinate.h
 *  
 *  使用基于2的幂次方的数值，乘除直接使用位移操作
 *  每个游戏的tile大小都是固定的，直接定义好，可以提高效率
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef __C_ISO_Coordinate_H
#define __C_ISO_Coordinate_H

#import <Foundation/Foundation.h>

//tile width 
#ifndef TileWidth
#define TileWidth 64 
#endif
//tile height
#ifndef TileHeight
#define TileHeight 32 
#endif

#ifndef XUnit
#define XUnit TileWidth/2 
#endif

#ifndef YUnit
#define YUnit TileHeight/2 
#endif

#ifndef ZUnit
#define ZUnit TileHeight 
#endif
//tileWidth=64,tileHeight=32

static inline CGPoint isoViewToGame2F(float x,float y)
{
	CGPoint p;
	x=x/TileWidth;//x=x/64
	y=y/TileHeight;//y=y/32
	p.x=x+y;
	p.y=y-x;
	return p;
}

static inline CGPoint isoViewToGameCGPoint(CGPoint point)
{
	return isoViewToGame2F(point.x,point.y);
}

static inline CGPoint isoViewToGameGrid2F (float x,float  y)
{
	CGPoint p=isoViewToGame2F(x,y);
	p.x=floor(p.x);
	p.y=floor(p.y);
	return p;
}

static inline CGPoint isoViewToGameGridCGPoint (CGPoint point)
{
	return isoViewToGameGrid2F(point.x,point.y);
}

static inline CGPoint isoGameToView3F(float x ,float y ,float z)
{
	double sx=x-y,sy=x+y;
	CGPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*YUnit-z*ZUnit;//sy*16-z*32
	return p;
}

static inline CGPoint isoGameToView2F(float x, float y)
{
	double sx=x-y,sy=x+y;
	CGPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*YUnit;//sy*16
	return p;
}

static inline CGPoint isoGameToViewCGPoint(CGPoint  point)
{
	return isoGameToView2F(point.x,point.y);
}
#endif //__C_ISO_Coordinate_H