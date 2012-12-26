//
//  ZIndex.h
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#include "cocos2d.h"
#import "GameEntity.h"
#import "CCCoordinate.h";

typedef enum zindex_type {
	ZIndex_Static,
	ZIndex_Dynamic
} ZIndexType;

//typedef struct ZIndex_Rect{
//	
//}

@interface CCZIndex : NSObject {
	NSMutableArray *statics_;
	NSMutableArray *dynamics_;
	CCLayer *sortLayer_;
	BOOL isWorking_;
	BOOL staticDirty_;
}

@property(nonatomic,retain) NSMutableArray *statics;
@property(nonatomic,retain) NSMutableArray *dynamics;
@property(nonatomic,assign) CCLayer *sortLayer;

+(id) sharedZIndex;
+(id) zIndexWidthGameWorld:(CCLayer *)sortLayer;
-(id) initWithGameWorld:(CCLayer *)sortLayer;

-(void) insertStatic:(GameEntity *)entity;
-(void) insertDynamic:(GameEntity *)entity;
-(void) removeStatic:(GameEntity *)entity;
-(void) removeDynamic:(GameEntity *)entity;

-(NSMutableArray *) insertSort:(CCNode *)node data:(NSArray *)rects;
-(NSMutableArray *) sort;
-(void) sortStatics;
-(void) update:(ccTime) delta;
-(void) start;
-(void) stop;
-(int) caculateSideFrom:(CGRect)from to:(CGRect)to;

-(CGRect) getMapRect:(GameEntity *)entity;
@end
