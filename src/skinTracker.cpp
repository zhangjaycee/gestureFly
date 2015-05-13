//
//  skintracker.cpp
//  ctfly
//
//  Created by WangHeng on 15/4/28.
//  Copyright (c) 2015年 ME. All rights reserved.
//

#include "skinTracker.h"
float max(float x, float y, float z)
{
    if (x > y && x > z)
        return x;
    else if(y > x && y > z)
        return y;
    else
        return z;
}

float min(float x, float y, float z)
{
    if (x <= y && x <= z)
        return x;
    else if(y < x && y <= z)
        return y;
    else
        return z;
}

void skintracker(Mat frame , Mat &skinmask)
{

    float R=0,G=0,B=0;
    int i,j;

    for (i = 0; i < skinmask.rows; i ++) {
        uchar * datamask = skinmask.ptr<uchar>(i);
        for(j = 0; j < skinmask.cols*skinmask.channels(); j ++){
            *datamask++ = 0;
        }
    }



    for (i = 0; i < frame.rows; i ++) {
        uchar *data = frame.ptr<uchar>(i);
        uchar *datamask = skinmask.ptr<uchar>(i);
        for (j = 0; j < frame.cols; j ++){
            B = *data++;
            G = *data++;
            R = *data++;

            if (R > 95 && G > 40 && B > 20){
                if (R > G && R > B) {
                    if ((max(R,G,B)-min(R,G,B)>15)&&((R-G)>15||(R-G)<-15)) {
 //                       *datamask = 255;
                        *datamask = 2;
                    
                    }
                }
            }
            datamask ++;

        }
    }

    //imshow("mask", skinmask);
    
}


/*R>95 And G>40 And B>20 And R>G And R>B And Max(R,G,B)-Min(R,G,B)>15 And Abs(R-G)>15 */
