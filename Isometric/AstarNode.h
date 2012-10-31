//
//  AstarNode.h
//  isometric
//
//  Created by trarck trarck on 11-10-20.
//  Copyright 2011 yitengku.com. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface AstarNode : NSObject {
	AstarNode *_parent;
	int _x;
	int _y;
	int _g;
	int _h;
	int _f;
}
@property(nonatomic) int x;
@property(nonatomic) int y;
@property(nonatomic) int g;
@property(nonatomic) int h;
@property(nonatomic) int f;
@property(nonatomic,retain) AstarNode *parent;

-(id) initWithParent:(AstarNode *)parent x:(int)x y:(int)y g:(int)g h:(int)h;
-(id) initWithX:(int)x y:(int)y;
@end //AstarNode
