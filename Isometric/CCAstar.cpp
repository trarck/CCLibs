#import "CCAstar.h"
#import "CCAstarNode.h"

NS_CC_BEGIN

int defaultNears[][2]={
		{-1 ,-1},{0 ,-1},{1,-1},
		{-1 , 0},        {1, 0},
		{-1 , 1},{0 , 1},{1, 1}
	};

CCAstar::CCAstar(void)
:m_minX(0)
,m_minY(0)
,m_maxX(0)
,m_maxY(0)
,m_barriers(null)
,m_barrierColumn(0)
,m_start(null)
,m_end(null)
,m_current(null)
{
	
}

void CCAstar::~CCAstar(void)
{
	CC_SAFE_RELEASE(m_opens);
	CC_SAFE_RELEASE(m_closes);
	CC_SAFE_RELEASE(m_openSeq);
	CC_SAFE_RELEASE(m_start);
	CC_SAFE_RELEASE(m_end);
	
}

bool CCAstar::init
{

	m_openSeq=new CCArray(10);
	m_opens=new CCDictionary(10);
	m_closes=new CCDictionary(10);
	
	return true;
}



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

static CCAstar * astarInstance=null;

CCAstar* CCAstar::sharedCCAstar()
{
	if(astarInstance==null){
		astarInstance=new CCAstar();
		astarInstance->init();
	}
	return astarInstance;
}


void CCAstar::reset
{
    CC_SAFE_RELEASE(m_opens);
	CC_SAFE_RELEASE(m_closes);
	CC_SAFE_RELEASE(m_openSeq);


	m_openSeq=new CCArray(10);
	m_opens=new CCDictionary(10);
	m_closes=new CCDictionary(10);

	
}
/*
 * 搜索范围
 */
void CCAstar::setBounding(int minX ,int minY,int maxX,int maxY)
{
	self.minX=minX;
	self.minY=minY;
	self.maxX=maxX;
	self.maxY=maxY;
}

/**
 * 开始点
 */
void CCAstar::setStart(int x ,int y)
{
	[m_start release];
	m_start=[[CCAstarNode alloc] initWithX:x y:y];
	[self addToOpen:m_start];
} 

/**
 * 结束点
 */
void CCAstar::setEnd(int x ,int y)
{
	[m_end release];
	m_end=[[CCAstarNode alloc] initWithX:x y:y];	
}



void CCAstar::setBarrier(MapInfo* barriers ,int column)
{
	barriers_=barriers;
	barrierColumn_=column;
}

bool CCAstar::search()
{
	
	//如果开始和结束点是同一点、终点超出范围,不必寻路。
	if ([self isEnd:m_start.x y:m_start.y] || [self isOut:m_end.x y:m_end.y]) {
		return NO;
	}
	
	while ([m_openSeq count]) {
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

bool CCAstar::checkNearby()
{
	int i=0,j=0,x=0,y=0,k=0,g=0,h=0;
	
	CCAstarNode *searchedNode;
	
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
					[self addToOpen:[[CCAstarNode alloc] initWithParent:current_ 
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

void CCAstar::getNext()
{
	[current_ release];
	current_=[m_openSeq objectAtIndex:0];
	[current_ retain];
}

void CCAstar::setOpenSeqNodeWithG(CCAstarNode* node ,int g)
{
	[node retain];
	[m_openSeq removeObject:node];
	node.g=g;
	node.f=node.g+node.h;
	int i=0;
	for(CCAstarNode *it in m_openSeq){
		if(node.f<it.f) break;
		i++;
	}
	[m_openSeq insertObject:node atIndex:i];
	[node release];
}

void CCAstar::addToOpen(CCAstarNode* node)
{
	int i=0;
	for(CCAstarNode *it in m_openSeq){
		if(node.f<it.f) break;
		i++;
	}
	[m_openSeq insertObject:node atIndex:i];
	
	NSNumber *yKey=[[NSNumber alloc] initWithInt:node.y];
	NSMutableDictionary * ymd=[m_opens objectForKey:yKey];
	if (ymd==nil) {
		ymd=[[NSMutableDictionary alloc] initWithCapacity:10];
		[m_opens setObject:ymd forKey:yKey];
		[ymd release];
	}
	
	NSNumber *xKey=[[NSNumber alloc] initWithInt:node.x];
	[ymd setObject: node forKey:xKey];
	
	[xKey release];
	[yKey release];
}

void CCAstar::removeFromOpen(CCAstarNode* node)
{
	[m_openSeq removeObject:node];
	
	NSNumber *yKey=[[NSNumber alloc] initWithInt:node.y];
	NSMutableDictionary * ymd=[m_opens objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:node.x];
	[ymd removeObjectForKey:xKey];
	[yKey release];
	[xKey release];
}

bool CCAstar::isInOpen(int x ,int y)
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[m_opens objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return data!=nil;
}

-(CCAstarNode *) CCAstar::getFromOpen(int x ,int y)
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[m_opens objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	CCAstarNode *node=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return node;
}

void CCAstar::addToClose(int x,int y)
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[m_closes objectForKey:yKey];
	if (ymd==nil) {
		ymd=[[NSMutableDictionary alloc] initWithCapacity:10];
		[m_closes setObject:ymd forKey:yKey];
		[ymd release];
	}
	
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[[NSNumber alloc] initWithBool:YES];
	[ymd setObject: data forKey:xKey];
	
	[data release];
	[xKey release];
	[yKey release];
}

bool CCAstar::isInClose(int x ,int y)
{
	NSNumber *yKey=[[NSNumber alloc] initWithInt:y];
	NSMutableDictionary * ymd=[m_closes objectForKey:yKey];
	NSNumber *xKey=[[NSNumber alloc] initWithInt:x];
	NSNumber *data=[ymd objectForKey:xKey];
	
	[xKey release];
	[yKey release];
	
	return data!=nil;
	
}

int CCAstar::getH(int x ,int y)
{
	return abs(m_end.x-x)*ASTAR_G_LINE+abs(m_end.y-y)*ASTAR_G_LINE;
}

bool CCAstar::isOut:(int)x y:(int)y
{
	//return y<minY_||y>=maxY_ ||x<minX_ || x>=maxX_;
	return y<minY_||y>maxY_ ||x<minX_ || x>maxX_;
}
//本身是否可以通过
bool CCAstar::isWorkable:(int) x y:(int) y 
{
	unsigned short barrier = (*(barriers_+y*barrierColumn_+x)).barrier;
	return barrier==0;
}
//本身和到达时斜对角是否可以通过
bool CCAstar::isWorkableWithCrossSide:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	BOOL ret=[self isWorkable:x y:y];
	if (stepX!=0 && stepY !=0) {
		ret&=[self isWorkable:x y:y-stepY] && [self isWorkable:x-stepX y:y];
	}
	return ret;
}
//到达x,y时，斜对角是否可以通过
//x,y搜索点，当前点为x-stepX,y-stepY
bool CCAstar::isCrossSideWorkable:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	return stepX==0 || stepY ==0 || ([self isWorkable:x y:y-stepY] && [self isWorkable:x-stepX y:y]);
}

bool CCAstar::isEnd:(int) x y:(int) y
{
	return m_end.x==x && m_end.y==y;
}

bool CCAstar::isEnd:(int) x y:(int) y stepX:(int) stepX stepY:(int) stepY
{
	return m_end.x==x && m_end.y==y && [self isCrossSideWorkable:x y:y stepX:stepX stepY:stepY];
}

#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
//取得路径  路径是反向的，从终点指向起点，不包含终点和起点。
CCArray* CCAstar::getPath
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	CCAstarNode * node=current_;
	
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
CCArray* CCAstar::getPathWithStart
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	CCAstarNode * node=current_;
	
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
CCArray* CCAstar::getPathWithEnd
{
	NSMutableArray * paths=[self getPath];
	CGPoint p;
	p.x=m_end.x;
	p.y=m_end.y;
	[paths insertObject: [NSValue valueWithCGPoint:p] atIndex:0];
	
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点和起点。
CCArray* CCAstar::getPathWithStartEnd
{
	NSMutableArray * paths=[self getPathWithStart];
	CGPoint p;
	p.x=m_end.x;
	p.y=m_end.y;
	[paths insertObject: [NSValue valueWithCGPoint:p] atIndex:0];
	
	return paths;
}
#elif TARGET_OS_MAC
//取得路径  路径是反向的，从终点指向起点，不包含终点和起点。
CCArray* CCAstar::getPath
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	CCAstarNode * node=current_;
	
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
CCArray* CCAstar::getPathWithStart
{
	NSMutableArray * paths=[[NSMutableArray alloc] initWithCapacity:10];
	CCAstarNode * node=current_;
	
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
CCArray* CCAstar::getPathWithEnd
{
	NSMutableArray * paths=[self getPath];
	NSPoint p;
	p.x=m_end.x;
	p.y=m_end.y;
	[paths insertObject: [NSValue valueWithPoint:p] atIndex:0];
	
	return paths;
}

//取得路径  路径是反向的，从终点指向起点，包含终点和起点。
CCArray* CCAstar::getPathWithStartEnd
{
	NSMutableArray * paths=[self getPathWithStart];
	NSPoint p;
	p.x=m_end.x;
	p.y=m_end.y;
	[paths insertObject: [NSValue valueWithPoint:p] atIndex:0];
	
	return paths;
}

#elif TARGET_OS_WIN32

#endif



CCString* CCAstar::description()
{
	NSString *desc=[NSString stringWithFormat:
					@" Astar**********\n\
minX=%d,minY=%d,maxX=%d,maxY=%d\n\
start:x:%d,y:%d  end:x:%d,y:%d\n\
barriercolumn:%d",self.minX,self.minY,self.maxX,self.maxY,
					m_start.x,m_start.y,m_end.x,m_end.y,
					barrierColumn_
					];
	return desc;
}

NS_CC_END
