#include "handFinder.h"

int foundCount=0;
int foundCountFlag=0;
int rgb_b=0,rgb_g=0,rgb_r=255;

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


int getHand()
{
    rectangle(frame, box, Scalar(rgb_b,rgb_g,rgb_r));
    flip(frame, frame, 1);
    imshow("CT", frame);
    aver=imgAver(fore_frame,1);

    if(averInitCount!=16){
        if(averInitCount<15){
            averAver+=aver;
            averInitCount++;
        }else if(averInitCount==15){
              averAver/=15;
              averInitCount++;
              first_flag=1;
        }
        return 0;
    }

    if(aver>0.1/*&& aver>averAver*/){
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
        rgb_r=0;
        return 1;
    }
    return 0;
}
