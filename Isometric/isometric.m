#import <Foundation/Foundation.h>

#import "AstarNode.h"
#import "Astar.h"
#import "Coordinate.h"

#import "TestData.h"
#import "CISOCoordinate.h"

@interface Test : NSObject

@end
@implementation Test

-(void) dealloc
{
	NSLog(@"test dealloc");
	[super dealloc];	
}

@end

MapInfo * getBarrier(int barriers[10][10])
{
	MapInfo * bs=malloc(100*sizeof(MapInfo));
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			(bs+i*10+j)->barrier=barriers[i][j]==8?0:barriers[i][j];
		}
	}
	return bs;
}

void showBarrier(MapInfo *barriers)
{
	NSMutableString *s=[NSMutableString stringWithCapacity:100];
	MapInfo * bs=malloc(100*sizeof(MapInfo));
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			[s appendFormat:@"%d,",(barriers+i*10+j)->barrier];
		}
		[s appendString:@"\n"];
	}
	NSLog(@"%@",s);
	return bs;
}

int main (int argc, const char * argv[]) {
	
	#if (TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)
		NSLog(@"test:in iphone");
	#elif TARGET_OS_MAC
		NSLog(@"test:in mac");
	#endif
	
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    Astar *astar=[[Astar alloc] init];
	
	
	[astar setBounding:0 minY:0 maxX:10 maxY:10];
	
	NSLog(@"test start *********");
	//test0
	MapInfo *bs;
	int i=0;
	for(;i<5;i++){
		bs=getBarrier((int *)barriers[i]);
		//showBarrier(bs);
		[astar reset];
		[astar setBarrier:bs column:10];
		[astar setStart:points[i][0] y:points[i][1]];
		[astar setEnd:points[i][2] y:points[i][3]];

		//NSLog(@"%@",astar);

		NSTimeInterval st=[[NSDate date] timeIntervalSince1970];
		BOOL result=[astar search];
		NSTimeInterval et=[[NSDate date] timeIntervalSince1970];
		double useTime=et-st;
		if(result){
			NSArray *paths=[astar getPathWithEnd];
			
			NSLog(@"%d searched:%f length:%d",i,useTime,[paths count]);
			//NSLog(@"%@",paths);
			BOOL ret=YES;
			int x,y;
			for(NSValue *it in paths){
				NSPoint p=[it pointValue];
				y=(int)p.y;
				x=(int)p.x;
				//NSLog(@"p:%d,%d",x,y);
				ret&= barriers[i][y][x]==8?YES:NO;
				//NSLog(@"ret=%d",barriers[i][y][x]);
				if(!ret) {
					NSLog(@"search failed at:%d",i);
					break;
				}
			}
			[paths release];
		}else {
			NSLog(@"%d not searched:%f",i,useTime);
		}

		if (result!=points[i][4]) {
				NSLog(@"Astar failed at:%d",i);
		}
		free(bs);
	}
	NSLog(@"test end *********");
		
	
	Coordinate *coordinate=[[Coordinate alloc] initWithTileWidth:64 height:32];
	
	float x,y;
    int col,row;
	
	
	NSPoint mapCoord;
	NSPoint mapGrid;
	CCell mapCell;
	
	int k=0;
	while(coords[k][0]!=-99999){
			
		x=coords[k][0];
		y=coords[k][1];
		
		mapCoord=[coordinate screenToMap:x y:y];
		mapGrid=[coordinate screenToMapGrid:x y:y];
		mapCell=[coordinate screenToMapCell:x y:y];
		col=(int) mapGrid.x;
		row=(int) mapGrid.y;
		
		if(col!=coords[k][2] || row!=coords[k][3]){
		
			NSLog(@"transform failed at:%d %f,%f",k,x,y);
			NSLog(@"x=%f,y=%f",mapCoord.x,mapCoord.y);
			NSLog(@"x=%d,y=%d",col,row);
			NSLog(@"x=%d,y=%d",mapCell.x,mapCell.y);
			
		}
		k++;
	}
	//c only
	k=0;
	while(coords[k][0]!=-99999){
		
		x=coords[k][0];
		y=coords[k][1];
		
		mapCoord=isoViewToGame2F(x, y);
		mapGrid=isoViewToGameGrid2F(x, y);
		
		col=(int) mapGrid.x;
		row=(int) mapGrid.y;
		
		if(col!=coords[k][2] || row!=coords[k][3]){
			
			NSLog(@"transform failed at:%d %f,%f",k,x,y);
			NSLog(@"x=%f,y=%f",mapCoord.x,mapCoord.y);
			NSLog(@"x=%d,y=%d",col,row);
		}
		k++;
	}
		
	[pool drain];
    return 0;
}
