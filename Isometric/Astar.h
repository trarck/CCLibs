//
//  Astar.h
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import <Foundation/Foundation.h>


#define defaultNearsLength 8

#define WorkDisable 0x1

#define ASTAR_G_LINE 10
#define ASTAR_G_CROSS 14
//typedef struct AstarNode_{
//	struct AstarNode_ *parent;
//	int x;
//	int y;
//	float g;
//	float h;
//} AstarNode;

#ifndef ISO_MapInfo
#define ISO_MapInfo
typedef struct MapInfo{
	unsigned short barrier; 
	int state;
	id entity;
	NSMutableSet *items;
} MapInfo;
#endif


@class AstarNode;


@interface Astar : NSObject {
	int minX_;
	int minY_;
	int maxX_;
	int maxY_;
	MapInfo *barriers_;//二维数组
	int barrierColumn_;//数组的列数 
	
	AstarNode *start_;
	AstarNode *end_;
	AstarNode *current_;
	
	NSMutableArray *openSeq_;//开启队列，存放每个结点。结点属性,parent 父结点，x,y地图坐,f,g,h路径评分
	
	//opens closes与地图相关，一般用二维数组
	//这里使用"y,x"做为关键字，BOOL做为值的dictionary来在存储。键可替换y右移16位加上x的数值
	//当然也可以根据搜索范围(minX,minY,maxX,maxY)来生成数组，数组值是BOOL
	//TODO 比较二种方法哪种快。最好应该是关于x，y的二维hash表算法最快。
	//二元hash:先创建关于y的hash,值为关于x的hash。这样查找时间为O(2)
	NSMutableDictionary *opens_;//开起列表,设置地图上的坐标，表示开启状态
	NSMutableDictionary *closes_;//关闭列表,存放已经到达过的点
	
	
	
}

@property(nonatomic) int minX;
@property(nonatomic) int minY;
@property(nonatomic) int maxX;
@property(nonatomic) int maxY;

@property(nonatomic) MapInfo *barriers;
@property(nonatomic) int barrierColumn;

+(id) sharedAstar;
-(void) setBounding:(int)minX minY:(int)minY maxX:(int)maxX maxY:(int)maxY;
-(void) setStart:(int) x y:(int) y ;
-(void) setEnd:(int) x y:(int) y;
-(void) setBarrier:(MapInfo *) barriers column:(int) column;
-(void) reset;

-(void) getNext;
-(void) addToOpen: (AstarNode *) node;
-(void) removeFromOpen:(AstarNode *) node;
-(BOOL) isInOpen:(int) x y:(int) y;
-(void) setOpenSeqNodeWithG:(AstarNode *)node g:(int)g;
-(AstarNode *) getFromOpen:(int) x y:(int) y;

-(void) addToClose:(int) x y:(int) y;
-(BOOL) isInClose : (int) x y:(int) y;

-(int) getH:(int) x y:(int) y;

-(BOOL) isOut:(int) x y:(int) y;
-(BOOL) isWorkable:(int) x y:(int) y ;
-(BOOL) isWorkableWithCrossSide:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY;
-(BOOL) isCrossSideWorkable:(int)x y:(int)y stepX:(int)stepX stepY:(int)stepY;
-(BOOL) isEnd:(int)x y:(int) y ;
-(BOOL) isEnd:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY;

-(BOOL) search;
-(BOOL) checkNearby;

-(NSMutableArray *) getPath;
-(NSMutableArray *) getPathWithStart;
-(NSMutableArray *) getPathWithEnd;
-(NSMutableArray *) getPathWithStartEnd;



//-(AstarNode) getNext;
@end
