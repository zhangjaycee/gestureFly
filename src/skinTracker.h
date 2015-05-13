//
//  skintracker.h
//  ctfly
//
//  Created by WangHeng on 15/4/28.
//  Copyright (c) 2015年 ME. All rights reserved.
//

#ifndef __ctfly__skintracker__
#define __ctfly__skintracker__

#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;


void skintracker(Mat frame, Mat &skinmask);

#endif /* defined(__ctfly__skintracker__) */
