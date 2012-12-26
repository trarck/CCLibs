#include "IsometricTest.h"
#include "../testResource.h"

void IsometricTestScene::runThisTest()
{
	CCLOG("in IsometricTestScene");

    CCDirector::sharedDirector()->replaceScene(this);
}
