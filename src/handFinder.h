#ifndef HANDFINDER_H
#define HANDFINDER_H

#include <opencv2/core/core.hpp>
#include "RunTraker.h"

using namespace cv;

extern int foundCount;
extern int foundCountFlag;
extern int rgb_b,rgb_g,rgb_r;
double imgAver(Mat &img,int flag);
int getHand();

#endif // HANDFINDER_H

