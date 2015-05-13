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

#include <cvaux.h>
#include "CompressiveTracker.h"
#include "fly.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include<string.h>


using namespace cv;
using namespace std;

Rect box; // tracking object

bool gotHand = false;	// got hand or not
string video;


int first_flag=1;
int open_error_flag=0;
//define the first frame
Mat first_frame;
Mat frame;
Mat fliped_frame;

int tempX;

/***********************v4.0*******************************/
    double imgAver(Mat &img,int flag)
    {
        int i,j,i0,j0,it,jt,width,height;//循环变量
        if(flag==1){
            it=box.y+box.height;
            jt=box.x+box.width;
            width=box.width;
            height=box.height;
            i0=box.y;
            j0=box.x;
        }else{
            it=height=img.rows;
            jt=width=img.cols;
            i0=0;
            j0=0;
        }
        //int step=img.widthStep/sizeof(uchar);
        uchar *data=(uchar*)img.data;

        double aver=0.0;

        for(i=i0;i<it;i++)
        {
            for(j=j0;j<jt;j++)
            {
               // printf("%d",data[i*])
               if(data[i*img.cols+j]>10){
                   aver+=1;
               }
            }
        }
        aver=1.0*aver/(height*width);
        return aver;
    }

  /********************************************************/


int main(int argc, char * argv[])
{
    /******************************************************************/

        struct termios options, oldoptions;
        int fd;

        fd = open("/dev/ttyACM0", O_RDWR);
        printf("%d\n",fd);
        if(fd <0){
            printf("open error!\n");
            open_error_flag=1;
            //exit(-1);
        }     // Žò¿ªŽ®¿Ú1

        tcgetattr(fd, &oldoptions);			// »ñµÃµ±Ç°µÄŽ®¿ÚÉèÖÃÐÅÏ¢
        tcgetattr(fd, &options);
        cfsetispeed(&options, B115200);			// ÉèÖÃÊäÈë²šÌØÂÊÎª115200
        cfsetospeed(&options, B115200);			// ÉèÖÃÊä³ö²šÌØÂÊÎª115200

        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;
        options.c_cflag &= ~PARENB;			// ÉèÖÃŽ®¿ÚÊôÐÔÎª£ºÊýŸÝÎ»Îª8Î»£¬Í£Ö¹Î»Îª1Î»£¬ÎÞÆæÅŒÐ£Ñé
        options.c_cflag &= ~CSTOPB;

        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);		// ÉèÖÃŽ®¿ÚÎªRawÄ£Êœ
        options.c_oflag &= ~OPOST;

        tcsetattr(fd, TCSANOW, &options);		// œ«ÉÏÊöÉèÖÃÉúÐ§
            printf("ok START!\n");

            char c;
    /******************************************************************/
    VideoCapture capture;

    capture.open(0);
    // Init camera
    if (!capture.isOpened())
    {
        cout << "capture device failed to open!" << endl;
        return 1;
    }
    // Register mouse callback to draw the tracking box
    namedWindow("CT", CV_WINDOW_NORMAL);

    //setWindowProperty("CT", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    // CT framework
    CompressiveTracker ct;

    Mat last_gray;
    Mat first;

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    /***************************************************/
    box = Rect(145, 150, 30, 30);//recr(x,y,w,h)
    int x0=box.x;
    int y0=box.y;
    int dx=0,dy=0;
    int gasValue=0;
    int dirValue=0;
    /***************************************************/
    printf("Initial Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);
    // CT initialization
    ct.init(last_gray, box);

    // Run-time
    Mat fore_frame;
    Mat current_gray;
    CvAdaptiveSkinDetector filter(1, CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE_DILATE);
    IplImage *maskImg = cvCreateImage( cvSize(320,240), IPL_DEPTH_8U, 1);

    int averInitCount=0;
    int foundCount=0;
    int foundCountFlag=0;
    double averAver=0;
    double averAverAll=0;
    double aver;
    double averAll;
    int rgb_b=0,rgb_g=0,rgb_r=255;

    if(!open_error_flag)
    write(fd,unlock, strlen(unlock));
    sleep(1);

    while(capture.read(frame))
    {
        if(first_flag){
            //Mat first_frame;
            //flip(frame,tmp_frame,1);
            cvtColor(frame, first_frame, CV_RGB2GRAY);
            first_flag=0;
        }
        // get frame
        cvtColor(frame, current_gray, CV_RGB2GRAY);
        //split(frame,frame_split);
        absdiff(first_frame,current_gray,fore_frame);
      // imshow("foreFrame",fore_frame);
        if(!gotHand){
            rectangle(frame, box, Scalar(rgb_b,rgb_g,rgb_r));
            flip(frame, frame, 1);
            imshow("CT", frame);
            aver=imgAver(fore_frame,1);
            averAll=imgAver(fore_frame,0);

        if(averInitCount!=16){
            if(averInitCount<15){
                averAver+=aver;
                averAverAll+=averAll;
                averInitCount++;
            }else if(averInitCount==15){
                averAver/=15;
                averAverAll/=15;
                averInitCount++;
                first_flag=1;
            }
            continue;
         }

            printf("aver=%lf averAver=%lf\n",aver,averAver);
            if(aver>0.7 && aver>averAver){
                if(foundCountFlag){
                    foundCount++;
                }
                foundCountFlag=1;
            }else{
                foundCountFlag=0;
                foundCount=0;
            }
            if(foundCount>0){
                rgb_g=255;
            }else{
                rgb_g=0;
            }
            if(foundCount>10){
                printf("i have got a hand~!\n");
                gotHand=1;
                rgb_r=0;
                continue;
            }
            if ((c = waitKey(15)) == 27){
                return 0;
            }
            continue;
        }
        /*****************************************************************/
        // Process Frame
        IplImage  pImg=frame;
        IplImage  fore_Ipl=fore_frame;
        IplImage  fore_Ipl2=fore_frame;
        filter.process(&pImg, maskImg);
       Mat mask=maskImg;
        // Mat mask=maskImg);
        copy(fore_frame,fore_frame,mask);
        //fore_frame=Mat(&fore_Ipl2);
        printf("ok\n");
        //imshow("new",fore_frame);
        ct.processFrame(fore_frame, box);
        // Display
        rectangle(frame, box, Scalar(rgb_b,rgb_g,rgb_r));
        flip(frame, frame, 1);
        imshow("CT", frame);
        /***************************************************/
        dx=x0-box.x;
        dy=y0-box.y;
        //printf("Current Tracking Box = x:%d y:%d h:%d w:%d\n", box.x, box.y, box.width, box.height);
        printf("dx=%d dy=%d",dx,dy);
        if(dy>0){
            if(dy<30){
                gasValue=dy*4;
            }else if(dy<60){
                gasValue=(dy-30)*1+120;
            }else if(dy<70){
                gasValue=(dy-60)*0.8+150;
            }else if(dy>=70){
                gasValue=160;
            }
        }else{
            gasValue=0;
        }
        gasDeToHex(gasValue);
        if(dx>20){
           dirValue=15;
            // if(dx>125)
              //  dx=125;
          //  dirValue=128+dx-20;
        }else if(dx<-20){
         dirValue=143;
            //  if(dx<-125)
            //   dx=-125;
          // dirValue=-dx+20;
        }else{
            dirValue=0;
        }
        dirDeToHex(dirValue);

        ctrlStr[0]=':'; ctrlStr[1]='R';ctrlStr[2]='C';
        ctrlStr[3]=gasValueChars[0];ctrlStr[4]=gasValueChars[1];
        for(int i=5;i<=10;i++){
            ctrlStr[i]='0';
        }
        ctrlStr[7]=dirValueChars[0];ctrlStr[8]=dirValueChars[1];
        ctrlStr[11]='\0';
       calLast2(ctrlStr);
       ctrlStr[11]=last2[0];
       ctrlStr[12]=last2[1];
        ctrlStr[13]='/';
        //ctrlStr[12]='\0';
        printf("%s\n",ctrlStr);
        if(!open_error_flag)
            write(fd,ctrlStr, strlen(ctrlStr));
        else
            printf("open errer! cant be writed!\n");
        //printf("dy= %d,gas=%d gas0x=%c%c\n",dy,FgasValue,gasValueChars[0],gasValueChars[1]);

        /***************************************************/

        if ((c = waitKey(15)) == 27){
            if(!open_error_flag)
                write(fd,lock, strlen(lock));
            sleep(1);
            break;
        }
    }
    return 0;
}
