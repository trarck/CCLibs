//
//  Coordinate.h
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 trarck. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef struct {
	int x;
	int y;
} CCell;

@interface Coordinate : NSObject {
	int xUnit_;
	int yUnit_;
	int zUnit_;
	
	int tileWidth_;
	int tileHeight_;
}
+(id) sharedCoordinate;

-(id) initWithTileWidth:(int)width height:(int)height;
-(id) initWithCoordinateUnit:(int)xUnit yUnit:(int)yUnit zUint:(int)zUnit;

-(void) setTileWidth:(int) width height:(int) height;
-(void) setCoordinateUnit:(int) xUnit yUnit:(int) yUnit zUint:(int) zUnit;
-(void) setCoordinateUnit:(int) xUnit yUnit:(int) yUnit;

-(CGPoint) screenToMap:(float) x y:(float) y;
-(CGPoint) screenToMap:(CGPoint) point;
-(CGPoint) screenToMapGrid:(float) x y:(float) y;
-(CGPoint) screenToMapGrid:(CGPoint) point;
-(CCell) screenToMapCell:(float) x y:(float) y;

-(CGPoint) mapToScreen:(float) x y:(float) y z:(float) z;
-(CGPoint) mapToScreen:(float) x y:(float) y;
-(CGPoint) mapToScreen:(CGPoint) point;

-(CGSize) mapToscreenSize:(int) l b:(int) b h:(int) h;
-(CGPoint) mapToscreenAnchor:(int) l b:(int) b h:(int) h;

@end
