/*
 *  Isometric.h
 *  Dungeons
 *
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef __Isometric_H
#define __Isometric_H

#import <Foundation/Foundation.h>
#import "CISOCoordinate.h"

static inline  CGPoint calcDirection(CGPoint from ,CGPoint to)
{
	CGPoint dir;
	float dx,dy;
	dx=to.x-from.x;
	dy=to.y-from.y;
	if (dx>0) {
		dir.x=0;
		dir.y=dy>0?1:dy<0?-1:0;
	}else {
		//-2.4142 <tan<-0.4142,0.4142<tan<2.4142
		dir.x=dx>0?1:-1;
		if(dy==0){
			dir.y=0;
		}else{
			dir.y=dy>0?1:-1;
			float tan=dy/dx;
			if(tan<-2.4142 || tan>2.4142){
				dir.x=0;
			}else if(tan>-0.4142 && tan<0.4142){//-0.4142<tan<0.4142
				dir.y=0;
			}
		}
	}
	return dir;
}


#endif