#import "CCAstar.h"
#import "CCAstarNode.h"

int defaultNears[][2]={
		{-1 ,-1},{0 ,-1},{1,-1},
		{-1 , 0},        {1, 0},
		{-1 , 1},{0 , 1},{1, 1}
	};



void CCAstar::setMinX(int minX)
{
    m_minX = minX;
}

int CCAstar::getMinX()
{
    return m_minX;
}

void CCAstar::setMinY(int minY)
{
    m_minY = minY;
}

int CCAstar::getMinY()
{
    return m_minY;
}

void CCAstar::setMaxX(int maxX)
{
    m_maxX = maxX;
}

int CCAstar::getMaxX()
{
    return m_maxX;
}

void CCAstar::setMaxY(int maxY)
{
    m_maxY = maxY;
}

int CCAstar::getMaxY()
{
    return m_maxY;
}

void CCAstar::setBarriers(MapInfo* barriers)
{
    CC_SAFE_RETAIN(barriers);
    CC_SAFE_RELEASE(m_barriers);
    m_barriers = barriers;
}

MapInfo* CCAstar::getBarriers()
{
    return m_barriers;
}

void CCAstar::setBarrierColumn(int barrierColumn)
{
    m_barrierColumn = barrierColumn;
}

int CCAstar::getBarrierColumn()
{
    return m_barrierColumn;
}

static Astar * _astar=nil;

+(id) sharedAstar
{
	if(_astar==nil){
		_astar=[[self alloc] init];
	}
	return _astar;
}

-(id) init
{
	if ((self=[super init])) {
		start_=nil;
		end_=nil;
		opens_=nil;
		closes_=nil;
		openSeq_=nil;
	}
	return self;
}
-(void) dealloc
{
	[opens_ release];
	[closes_ release];
	[openSeq_ release];
	[start_	release];
	[end_	release];
	[super dealloc];
}
-(void) reset
{
	[opens_ release];
	[closes_ release];
	[openSeq_ release];
	
	openSeq_=[[NSMutableArray alloc] initWithCapacity:10];
	opens_=[[NSMutableDictionary alloc] initWithCapacity:10];
	closes_=[[NSMutableDictionary alloc] initWithCapacity:10];
	
}
/*
 * 搜索范围
 */
-(void) setBounding:(int) minX minY:(int) minY maxX:(int) maxX maxY:(int) maxY
{
	self.minX=minX;
	self.minY=minY;
	self.maxX=maxX;
	self.maxY=maxY;
}

/**
 * 开始点
 */
-(void) setStart:(int) x y:(int) y
{
	[start_ release];
	start_=[[AstarNode alloc] initWithX:x y:y];
	[self addToOpen:start_];
} 

/**
 * 结束点
 */
-(void) setEnd:(int)x y:(int)y
{
	[end_ release];
	end_=[[AstarNode alloc] initWithX:x y:y];	
}



-(void) setBarrier:(MapInfo *) barriers column:(int) column
{
	barriers_=barriers;
	barrierColumn_=column;
}

-(BOOL) search
{
	
	//如果开始和结束点是同一点、终点超出范围,不必寻路。
	if ([self isEnd:start_.x y:start_.y] || [self isOut:end_.x y:end_.y]) {
		return NO;
	}
	
	while ([openSeq_ count]) {
		//取得下一个搜索点 
		[self getNext];
		[self removeFromOpen:current_];
		//添加到closes
		[self addToClose:current_.x y:current_.y];
		
		//处理相邻结点
		if([self checkNearby]){
			return YES;
		}
	}
	return NO;
}

-(BOOL) checkNearby
{
	int i=0,j=0,x=0,y=0,k=0,g=0,h=0;
	
	AstarNode *searchedNode;
	
	for(;k<DEFAULT_NEARS_LENGTH;k++){
		//near=defaultNears[k];
		i=defaultNears[k][0];
		j=defaultNears[k][1];
		
		x=current_.x+i;
		y=current_.y+j;
		
		//结束提前，可对目标是障碍物进行寻路。(例:人物要对某个建筑进行操作，比如攻击，要走到建筑旁边才可以)
		if ([self isEnd:x y:y stepX:i stepY:j]) {//如果是斜着寻路，则要对旁边是否有障碍物进行判断。
			return YES;//查找成功
		}
		
		if(![self isOut:x y:y] && [self isWorkableWithCrossSide:x y:y stepX:i stepY:j]){
			if(![self isInClose:x y:y]){
				g=current_.g+(i==0||j==0?ASTAR_G_LINE:ASTAR_G_CROSS);
				searchedNode=[self getFromOpen:x y:y];
				if(searchedNode!=nil){
					//在开起列表中，比较G值
					if (g < searchedNode.g) {
						//有最小F值，重新排序
						[self setOpenSeqNodeWithG:searchedNode g:g];
					}
				}else {
					//没有搜索过，直接添加到开起列表中
					h=[self getH:x y:y];
					[self addToOpen:[[AstarNode alloc] initWithParent:current_ 
																	x:x 
																	y:y
																	g:g
																	h:h]];
				}
				
			}
		}
	}
	return NO;
}

-(void) getNext
{
	[current_ release];
	current_=[openSeq_ objectAtIndex:0];
	[current_ retain];
}

-(void) setOpenSeqNodeWithG:(AstarNode *) node g:(int) g
{
	[node retain];
	[openSeq_ removeObject:node];
	node.g=g;
	node.f=node.g+node.h;
	int i=0;
	for(AstarNode *it in openSeq_){
		if(node.f<it.f) break;
		i++;
	}
	[openSeq_ insertObject:node atIndex:i];
	[node release];
}

-(void) addToOpen:(AstarNode *) node
{
	int i=0;
	for(AstarNode *it in openSeq_){
		if(node.f<it.f) break;
		i++;
	}
	[openSeq_ insertObject:node atIndex:i];
	
	NSNumber *yKey=[[NSNumber alloc] initWithInt:node.y];
	NSMutableDictionary * ymd=[opens_ objectForKey:yKey];
	if (ymd==nil) {
		ymd=[[NSMutableDictionary alloc] initWithCapacity:10];
		[opens_ setObject:ymd forKey:yKey];
		[ymd release];
	}
	
	NSNumber *xKey=[[NSNumber alloc] initWithInt:node.x];
	[ymd setObject: node forKey:xKey];
	
	[xKey release];
	[yKey release];
}

-(void) removeFromOpen:(AstarNode *) node
{
	[openSeq_ removeObject:node];
	
	NSNumber *yKey=[[NSNumber alloc] initWithInt:node.y];
	NSMutableDictionary * ymd=[opens_ objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:node.x];
	[ymd removeObjectForKey:xKey];
	[yKey release];
	[xKey release];
}

-(BOOL) isInOpen:(int)x y:(int)y
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[opens_ objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return data!=nil;
}

-(AstarNode *) getFromOpen:(int) x y:(int) y
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[opens_ objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	AstarNode *node=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return node;
}

-(void) addToClose:(int) x y:(int) y
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[closes_ objectForKey:yKey];
	if (ymd==nil) {
		ymd=[[NSMutableDictionary alloc] initWithCapacity:10];
		[closes_ setObject:ymd forKey:yKey];
		[ymd release];
	}
	
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[[NSNumber alloc] initWithBool:YES];
	[ymd setObject: data forKey:xKey];
	
	[data release];
	[xKey release];
	[yKey release];
}

-(BOOL) isInClose:(int)x y:(int)y
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[closes_ objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return data!=nil;
	
}

-(int) getH:(int)x y:(int)y
{
	return abs(end_.x-x)*ASTAR_G_LINE+abs(end_.y-y)*ASTAR_G_LINE;
}

-(BOOL) isOut:(int)x y:(int)y
{
	//return y<minY_||y>=maxY_ ||x<minX_ || x>=maxX_;
	return y<minY_||y>maxY_ ||x<minX_ || x>maxX_;
}
//本身是否可以通过
-(BOOL) isWorkable:(int) x y:(int) y 
{
	unsigned short barrier = (*(barriers_+y*barrierColumn_+x)).barrier;
	return barrier==0;
}
//本身和到达时斜对角是否可以通过
-(BOOL) isWorkableWithCrossSide:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	BOOL ret=[self isWorkable:x y:y];
	if (stepX!=0 && stepY !=0) {
		ret&=[self isWorkable:x y:y-stepY] && [self isWorkable:x-stepX y:y];
	}
	return ret;
}
//到达x,y时，斜对角是否可以通过
//x,y搜索点，当前点为x-stepX,y-stepY
-(BOOL) isCrossSideWorkable:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	return stepX==0 || stepY ==0 || ([self isWorkable:x y:y-stepY] && [self isWorkable:x-stepX y:y]);
}

-(BOOL) isEnd:(int) x y:(int) y
{
	return end_.x==x && end_.y==y;
}

-(BOOL) isEnd:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	return end_.x==x && end_.y==y && [self isCrossSideWorkable:x y:y stepX:stepX stepY:stepY];
}

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
//取得路径  路径是反向的，从终点指向起点，不包含终点和起点。
-(NSMutableArray *) getPath
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	AstarNode * node=current_;
	
	while (node && node.parent) {
		CGPoint p;
		p.x=node.x;
		p.y=node.y;
		[paths addObject:[NSValue valueWithCGPoint:p]];
		node=node.parent;
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含起点，不包含终点。
-(NSMutableArray *) getPathWithStart
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	AstarNode * node=current_;
	
	while (node) {
		CGPoint p;
		p.x=node.x;
		p.y=node.y;
		[paths addObject:[NSValue valueWithCGPoint:p]];
		node=node.parent;
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点，不包含起点。
-(NSMutableArray *) getPathWithEnd
{
	NSMutableArray * paths=[self getPath];
	CGPoint p;
	p.x=end_.x;
	p.y=end_.y;
	[paths insertObject: [NSValue valueWithCGPoint:p] atIndex:0];
	
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点和起点。
-(NSMutableArray *) getPathWithStartEnd
{
	NSMutableArray * paths=[self getPathWithStart];
	CGPoint p;
	p.x=end_.x;
	p.y=end_.y;
	[paths insertObject: [NSValue valueWithCGPoint:p] atIndex:0];
	
	return paths;
}
#elif TARGET_OS_MAC
//取得路径  路径是反向的，从终点指向起点，不包含终点和起点。
-(NSMutableArray *) getPath
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	AstarNode * node=current_;
	
	while (node && node.parent) {
		NSPoint p;
		p.x=node.x;
		p.y=node.y;
		[paths addObject:[NSValue valueWithPoint:p]];
		node=node.parent;
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含起点，不包含终点。
-(NSMutableArray *) getPathWithStart
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	AstarNode * node=current_;
	
	while (node) {
		NSPoint p;
		p.x=node.x;
		p.y=node.y;
		[paths addObject:[NSValue valueWithPoint:p]];
		node=node.parent;
	}
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点,不包含起点。
-(NSMutableArray *) getPathWithEnd
{
	NSMutableArray * paths=[self getPath];
	NSPoint p;
	p.x=end_.x;
	p.y=end_.y;
	[paths insertObject: [NSValue valueWithPoint:p] atIndex:0];
	
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点和起点。
-(NSMutableArray *) getPathWithStartEnd
{
	NSMutableArray * paths=[self getPathWithStart];
	NSPoint p;
	p.x=end_.x;
	p.y=end_.y;
	[paths insertObject: [NSValue valueWithPoint:p] atIndex:0];
	
	return paths;
}

#elif TARGET_OS_WIN32

#endif



-(NSString *) description
{
	NSString *desc=[NSString stringWithFormat:
					@" Astar**********\n\
minX=%d,minY=%d,maxX=%d,maxY=%d\n\
start:x:%d,y:%d  end:x:%d,y:%d\n\
barriercolumn:%d",self.minX,self.minY,self.maxX,self.maxY,
					start_.x,start_.y,end_.x,end_.y,
					barrierColumn_
					];
	return desc;
}


@end //Astar
