/************************************************************************
* File:	RunTracker.cpp
* Brief: C++ demo for Kaihua Zhang's paper:"Real-Time Compressive Tracking"
* Version: 1.0
* Author: Yang Xian
* Email: yang_xian521@163.com
* Date:	2012/08/03
* History:
************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "CompressiveTracker.h"
#include "RunTraker.h"
#include "controlStr.h"
#include "skinTracker.h"
#include "handFinder.h"
#include "strSender.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/types.h>
#include<string.h>

using namespace cv;
using namespace std;

Rect box; // tracking object
bool gotHand = false;	// got hand or not
string video;
char c;
int tempX;
int first_flag=1;
int averInitCount=0;
int ctInitFlag=0;
double averAver=0;
double aver=0;
Mat first_frame;
Mat frame;
Mat skinmask;
Mat fore_frame;
Mat current_gray;

int main(int argc, char * argv[])
{
    //init UART
    senderInit();
    VideoCapture capture;
    capture.open(0);
    // Init camera
    if (!capture.isOpened())
    {
        cout << "capture device failed to open!" << endl;
        return 1;
    }
    namedWindow("CT", CV_WINDOW_NORMAL);
   // setWindowProperty("CT", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    // CT framework
    CompressiveTracker ct;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    //box Init
    box = Rect(130, 130, 60, 70);//Rect(x,y,width,height)
    int x0=box.x;
	int xt=box.x;
    int y0=box.y;
    int dx=0,dy=0;
	int dirFlag=0;//<0:lefting   >0:righting;
    // Run-time
    if(!open_error_flag)
       write(fd,unlock, strlen(unlock));
    while(capture.read(frame))
    {
        if(first_flag){
            cvtColor(frame, first_frame, CV_RGB2GRAY);
            first_flag=0;
        }
        skinmask = cvCreateMat(frame.rows, frame.cols, CV_8UC1);
        // get frame
        cvtColor(frame, current_gray, CV_RGB2GRAY);
        absdiff(first_frame,current_gray,fore_frame);
       //imshow("foreFrame",fore_frame);
        if(!gotHand){
            gotHand=getHand();
            if(gotHand){
                ctInitFlag=1;
            }
            if ((c = waitKey(15)) == 27){
                return 0;
            }
            continue;
        }
        // Process Frame
        skintracker(frame,skinmask);
        fore_frame = fore_frame.mul(skinmask);
        // CT initialization
        if(ctInitFlag){
            ct.init(fore_frame, box);
            ctInitFlag=0;
        }
        //imshow("fore&skinmasked", fore_frame);
        ct.processFrame(fore_frame, box);
        rectangle(frame, box, Scalar(rgb_b,rgb_g,rgb_r));
        // Display
        flip(frame, frame, 1);
        imshow("CT", frame);
        //dx=x0-box.x;
        dx=box.x-xt;
//	printf("dx=%d\n",dx);
		dy=y0-box.y;
		xt=box.x;
        getGasValue(dy);
        dirFlag=getDirValue(dx,dirFlag);
        calControlStr(gasValue,dirValue);
        sendControlStr();
        if ((c = waitKey(15)) == 27){
            if(!open_error_flag)
                write(fd,lock, strlen(lock));
            sleep(1);
            break;
        }
    }
    
    return 0;
}
