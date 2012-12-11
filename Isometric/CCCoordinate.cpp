//
//  Coordinate.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Coordinate.h"


@implementation Coordinate

static Coordinate *_coordinate=nil;

+(id) sharedCoordinate
{
	if(!_coordinate){
		_coordinate=[[self alloc] init];
	}
	return _coordinate;	
}

-(id) initWithTileWidth:(int) width height:(int) height
{
	if((self=[super	init])){
		[self setTileWidth:width height:height];
	}
	return self;
}

-(id) initWithCoordinateUnit:(int)xUnit yUnit:(int)yUnit zUint:(int) zUnit 
{
	if((self=[super	init])){
		[self setCoordinateUnit:xUnit yUnit:yUnit zUint:zUnit];
	}
	return self;
}

-(void) dealloc
{
	_coordinate=nil;
	[super dealloc];
}

-(void) setTileWidth:(int)width height:(int)height
{
	tileWidth_=width;
	tileHeight_=height;
	
	xUnit_=width/2;
	yUnit_=height/2;
	zUnit_=height;
}

-(void) setCoordinateUnit:(int)xUnit yUnit:(int)yUnit zUint:(int) zUnit
{
	xUnit_=xUnit;
	yUnit_=yUnit;
	zUnit_=zUnit;
	
	tileWidth_=xUnit*2;
	tileHeight_=yUnit*2;
}

-(void) setCoordinateUnit:(int)xUnit yUnit:(int)yUnit
{
	[self setCoordinateUnit:xUnit yUnit:yUnit zUint:yUnit*2];
}


-(CGPoint) screenToMap:(float)x y:(float)y
{
	x=x/tileWidth_;
	y=y/tileHeight_;
	CGPoint p;
	p.x=x+y;
	p.y=y-x;
	return p;
}

-(CGPoint) screenToMap:(CGPoint) point
{
	return [self screenToMap:point.x y:point.y];
}

-(CGPoint) screenToMapGrid:(float) x y:(float) y
{
	CGPoint p=[self screenToMap:x y:y];
	p.x=floor(p.x);
	p.y=floor(p.y);
	return p;
}

-(CGPoint) screenToMapGrid:(CGPoint) point
{
	return [self screenToMapGrid:point.x y:point.y];
}

-(CCell) screenToMapCell:(float) x y:(float) y
{
	CGPoint p=[self screenToMap:x y:y];
	CCell cell;
	cell.x=(int) p.x;
	cell.y=(int) p.y;
	return cell;
}

-(CGPoint) mapToScreen:(float)x y:(float)y z:(float) z
{
	double sx=x-y,sy=x+y;
	CGPoint p;
	p.x=sx*xUnit_;
	p.y=sy*yUnit_-z*zUnit_;
	return p;
}

-(CGPoint) mapToScreen:(float)x y:(float)y
{
	return [self mapToScreen:x y:y z:0];
}

-(CGPoint) mapToScreen:(CGPoint) point
{
	return [self mapToScreen:point.x y:point.y z:0];
}

-(CGSize) mapToscreenSize:(int)l b:(int)b h:(int)h
{
	int s;
	float width,height;
	CGSize size;
	
	s=l+b;
	width=s*xUnit_;
	height=s*yUnit_+h*zUnit_;
	size.width=width;
	size.height=height;
	return size;
}

-(CGPoint) mapToscreenAnchor:(int)l b:(int)b h:(int)h
{
	CGPoint p;
	p.x=b*xUnit_;
	p.y=h*zUnit_;
	return p;
}

-(NSString *) description
{
	NSString *desc=[NSString stringWithFormat:@"unit:%d,%d,%d",xUnit_,yUnit_,zUnit_];
	return desc;
}
-(void) release
{
	
}
@end
