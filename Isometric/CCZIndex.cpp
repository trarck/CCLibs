//
//  ZIndex.m
//  Dungeons
//
//  Created by trarck trarck on 11-11-3.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#import "ZIndex.h"

@implementation ZIndex

@synthesize statics=statics_;
@synthesize dynamics=dynamics_;
@synthesize sortLayer=sortLayer_;

static ZIndex *zIndex_=nil;

+(id) sharedZIndex
{
	if(!zIndex_){
		assert("none init ZIndex before.before used ,init it.");
	}
	return zIndex_;
}

+(id) zIndexWidthGameWorld:(CCLayer *) sortLayer
{
	if(!zIndex_){
		zIndex_=[[self alloc] initWithGameWorld:sortLayer];
	}
	return zIndex_;
}

-(id) init
{
	if((self=[super init])){
		statics_=[[NSMutableArray alloc] initWithCapacity:20];
		dynamics_=[[NSMutableArray alloc] initWithCapacity:20];
		sortLayer_=nil;
		isWorking_=NO;
	}
	return self;
}

-(id) initWithGameWorld:(CCLayer *) sortLayer
{
	if((self=[self init])){
		self.sortLayer=sortLayer;
	}
	return self;
}

-(void) dealloc
{
	CCLOG(@"zIndex dealloc");
	self.statics=nil;
	self.dynamics=nil;
	self.sortLayer=nil;
	//[self stop];
	[super dealloc];
}


-(void) insertStatic:(GameEntity *) entity
{
	//注意insertSort反回的数组已经是加1的，如果使用self.statics=[self insertSort:entity data:statics_]，
	//则会使statics_的引用数为2，下一次再执行该函数时，则已以前的statics_无法释放。
	NSMutableArray *results=[self insertSort:entity data:statics_];
	[statics_ release];
	statics_=results;
	staticDirty_=YES;
}

-(void) insertDynamic:(GameEntity *) entity
{
	[dynamics_ addObject:entity];
}

//-(void) insert:(Entity *) entity type:(ZIndexType) type
//{
//	
//}


-(void) removeStatic:(GameEntity *) entity
{
	[statics_ removeObject:entity];
}
-(void) removeDynamic:(GameEntity *) entity
{
	[dynamics_ removeObject:entity];
}

-(CGRect) getMapRect:(GameEntity *) entity
{
	CGRect rect;
	
	rect.origin=entity.coordinate;
	rect.size.width=(float)entity.l;
	rect.size.height=(float)entity.b;
	return rect;
}

-(NSMutableArray *) insertSort:(GameEntity *) node data:(NSArray *) rects
{
	CGRect src,rect=[self getMapRect:node];
	int side,l=[rects count];
	NSMutableArray *results;
	BOOL maxAppear=NO;

		if(l>0){
		
		side=[self caculateSideFrom:[self getMapRect:[rects objectAtIndex:l-1]] to:rect];
		
		if(side<0){
			results=[[NSMutableArray alloc] initWithCapacity:l+1];
			[results addObjectsFromArray:rects];
			[results addObject:node];
		}else{
			NSMutableArray *maxs=[[NSMutableArray alloc] initWithCapacity:l/2];
			NSMutableArray *mins=[[NSMutableArray alloc] initWithCapacity:l/2];

			for (GameEntity *it in rects ) {
				src=[self getMapRect:it];
				side=[self caculateSideFrom:src to:rect];
				//NSLog(@"side:%d,from:%f,%f to:%f,%f",side,src.origin.x,src.origin.y,rect.origin.x,rect.origin.y);
				switch (side) {
					case -1:
					case -2:
						[mins addObject:it];
						break;
					case 1:
					case 2:
						[maxs addObject:it];
						maxAppear=YES;
						break;
					case 0:
						if (maxAppear) {
							[maxs addObject:it];
						}else {
							[mins addObject:it];
						}
						break;

					default:
						break;
				}
			}
			[mins addObject:node];
			[mins addObjectsFromArray:maxs];
			results=mins;
			[maxs release];
		}
	}else{
		results=[[NSMutableArray alloc] initWithObjects:node,nil];
	}
	return results;
}

-(NSMutableArray *) sort
{
	NSArray *tmps=[[NSArray alloc] initWithArray:statics_];
	NSMutableArray *items=nil;
	
	//sort dynamics
	for (CCNode *it in dynamics_) {
		items=[self insertSort:it data:tmps];
		[tmps release];
		tmps=items;
	}
	return items;
}

//-(void) sortStatics
//{
//	if ([statics_ count]) {
//		NSArray *tmps=[[NSArray alloc] init];
//		NSArray *items;
//		for (CCNode *it in statics_) {
//			items=[self insertSort:it  data:tmps];
//			[tmps release];
//			tmps=items;
//		}
//		[statics_ release];
//		statics_=items;
//	}
//}

-(void) update:(ccTime) delta
{
	//update z-index

	if ([dynamics_ count]>0) {
		
		NSMutableArray *items=[self sort];
		//NSLog(@"%@",sortLayer_);
		int i=1;
		for (GameEntity *entity in items) {
			[sortLayer_ reorderChild:entity z:i++];
		}
		[items release];
	}else if (staticDirty_) {
		int i=1;
		for (GameEntity *entity in statics_) {
			[sortLayer_ reorderChild:entity z:i++];
		}
		staticDirty_=NO;
	}
}

-(void) start
{
	if(isWorking_) return;
	isWorking_=YES;
	[[CCScheduler sharedScheduler] scheduleUpdateForTarget:self priority:0 paused:NO];
	//[[CCScheduler sharedScheduler] scheduleSelector:@selector(update:) forTarget:self interval:1 paused:NO];
}

-(void) stop
{
	if (isWorking_) {
		[[CCScheduler sharedScheduler] unscheduleUpdateForTarget:self];
		isWorking_=NO;
	}
	
}

-(int) caculateSideFrom:(CGRect ) from to:(CGRect) to
{
	int lr, tb;//如果要确切的知道8个方位。上下左右分别用1,4,2,8表示，中还是用0。这样二二之各就可以确定方位。

	if (to.origin.x > from.origin.x+from.size.width|| fabs(to.origin.x- (from.origin.x+from.size.width))<0.0001 ) {
		//右
		lr = 1;
	}else if(to.origin.x+to.size.width<from.origin.x||fabs(to.origin.x+to.size.width-from.origin.x)<0.0001){
		//左
		lr = -1;
	} else  {//desc.right<=src.right && desc.left>=src.left(内中),desc.right>=src.right && desc.left<=src.left(外中) 都算中
		//中
		lr = 0;
	}
	
	if (to.origin.y > from.origin.y+from.size.height||fabs(to.origin.y-( from.origin.y+from.size.height))<0.0001) {
		//下
		tb = 1;
	} else if (to.origin.y+to.size.height < from.origin.y ||fabs(to.origin.y+to.size.height -from.origin.y)<0.0001) {
		//上
		tb = -1;
	} else {
		//中
		tb = 0;
	}

	return lr + tb;
}

-(NSString *) description
{
	NSString *desc=[NSString stringWithFormat:@"statics:%@,dynamics:%@",statics_,dynamics_];
	return desc;
}
@end
