#include "IsometricTest.h"
#include "../testResource.h"

#include "CCISOCoordinate.h"
#include "CCAstarNode.h"
#include "CCAstar.h"
#include "CCCoordinate.h"

#include "TestData.h"


MapCellInfo * getBarrier(int barriers[10][10])
{
	MapCellInfo* bs=(MapCellInfo*)malloc(100*sizeof(MapCellInfo));
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			MapCellInfo* cell=bs+i*10+j;
			unsigned short barrier=barriers[i][j]==8?0:barriers[i][j];
			cell->barrier=barrier;
		}
	}
	return bs;
}

void showBarrier(MapCellInfo *barriers)
{
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("%d,", (barriers+i*10+j)->barrier);
		}
		printf("\n");
	}
}

void IsometricTestScene::runThisTest()
{
	CCLOG("in IsometricTestScene");

	CCAstar *astar=new CCAstar();
	astar->init();
	astar->setBounding(0 ,0 ,10 ,10);
	
	CCLOG("test start *********");
	//test0
	MapCellInfo *bs;
	int i=0;
	for(;i<5;i++){
		bs=getBarrier(barriers[i]);
		//showBarrier(bs);
		astar->reset();
		astar->setBarrier(bs ,10);
		astar->setStart(points[i][0] ,points[i][1]);
		astar->setEnd(points[i][2] ,points[i][3]);

		//NSLog(@"%@",astar);
		struct cc_timeval start;

		if (CCTime::gettimeofdayCocos2d(&start, NULL) != 0)
		{
			CCLOG("error in gettimeofday");
			 return;
		}

		bool result=astar->search();
		struct cc_timeval end;

		if (CCTime::gettimeofdayCocos2d(&end, NULL) != 0)
		{
			CCLOG("error in gettimeofday");
			 return;
		}

		double useTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000.0f;
		if(result){
			CCArray* paths=astar->getPathWithEnd();
			
			CCLOG("%d searched:%f length:%d",i,useTime,paths->count());
			//NSLog(@"%@",paths);
			bool ret=true;
			int x,y;
			CCObject* pObject = NULL;
			CCARRAY_FOREACH(paths,pObject){
				CCPoint* p=(CCPoint*)pObject;
				y=(int)p->y;
				x=(int)p->x;
				//NSLog(@"p:%d,%d",x,y);
				ret&= barriers[i][y][x]==8?true:false;
				//NSLog(@"ret=%d",barriers[i][y][x]);
				if(!ret) {
					CCLOG("search failed at:%d",i);
					break;
				}
			}
			CC_SAFE_RELEASE(paths);
		}else {
			CCLOG("%d not searched:%f",i,useTime);
		}

		if (result!=!!(points[i][4])) {
				CCLOG("Astar failed at:%d",i);
		}
		free(bs);
	}
	CCLOG("test Astart end *********");
		
	
	CCCoordinate* coordinate=new CCCoordinate();
	coordinate->init(64,32);
	
	float x,y;
    int col,row;
	
	
	CCPoint mapCoord;
	CCPoint mapGrid;
	CCCell mapCell;
	
	int k=0;
	while(coords[k][0]!=-99999){
			
		x=coords[k][0];
		y=coords[k][1];
		
		mapCoord=coordinate->screenToMap(x ,y);
		mapGrid=coordinate->screenToMapGrid(x ,y);
		mapCell=coordinate->screenToMapCell(x,y);
		col=(int) mapGrid.x;
		row=(int) mapGrid.y;
		
		if(col!=coords[k][2] || row!=coords[k][3]){
		
			CCLOG("transform failed at:%d %f,%f",k,x,y);
			CCLOG("x=%f,y=%f",mapCoord.x,mapCoord.y);
			CCLOG("x=%d,y=%d",col,row);
			CCLOG("x=%d,y=%d",mapCell.x,mapCell.y);
			
		}else{
			CCLOG("transform success at:%d %f,%f",k,x,y);
		}
		k++;
	}

	CCLOG("test coord Class end *********");
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
			
			CCLOG("transform failed at:%d %f,%f",k,x,y);
			CCLOG("x=%f,y=%f",mapCoord.x,mapCoord.y);
			CCLOG("x=%d,y=%d",col,row);
		}else{
			CCLOG("transform success at:%d %f,%f",k,x,y);
		}
		k++;
	}
	CCLOG("test coord macro end *********");

	CCLOG("test All end *********");
	
    CCDirector::sharedDirector()->replaceScene(this);
}
