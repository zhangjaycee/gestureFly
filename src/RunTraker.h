#ifndef RUNTRAKER_H
#define RUNTRAKER_H
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;


extern Rect box; // tracking object

extern bool gotHand;	// got hand or not
extern string video;

extern char c;
extern int tempX;
extern int first_flag;
extern int averInitCount;
extern int ctInitFlag;
extern int rgb_b,rgb_g,rgb_r;
extern double averAver;
extern double aver;

extern Mat first_frame;
extern Mat frame;
extern Mat skinmask;
extern Mat fore_frame;
extern Mat current_gray;

#endif // RUNTRAKER_H

