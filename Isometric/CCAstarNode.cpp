//
//  AstarNode.m
//  isometric
//
//  Created by trarck trarck on 11-10-20.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#import "AstarNode.h"


@implementation AstarNode

@synthesize x=_x;
@synthesize y=_y;
@synthesize g=_g;
@synthesize h=_h;
@synthesize f=_f;
@synthesize parent=_parent;

-(id) init
{
	if((self=[super init])){
		self.x=0;
		self.y=0;
		self.g=0;
		self.h=0;
		self.f=0;
		self.parent=nil;
	}
	return self;
}
-(id) initWithParent:(AstarNode *) parent x:(int) x y:(int) y g:(int) g h:(int) h
{
	if((self=[super init])){
		self.parent=parent;
		self.x=x;
		self.y=y;
		self.g=g;
		self.h=h;
		self.f=g+h;
	}
	return self;
}
-(id) initWithX:(int) x y:(int) y
{
	return [self initWithParent:nil x:x y:y g:0 h:0];
}
@end //AstarNode
