#include"controlStr.h"

char * lock=":PWOFC4/";
char * unlock=":PWONBC/";
int gasValue=0;
int dirValue=0;
char gasValueChars[2];
char dirValueChars[2];
char last2[2];
char ctrlStr[20];


void gasDeToHex(int gasValue)
{

    int wei[2];
    int i=0;
    wei[0]=gasValue/16;
    wei[1]=gasValue%16;
    for(i=0;i<2;i++){
        if(wei[i]>9){
            gasValueChars[i]='A'+wei[i]-10;
        }else{
            gasValueChars[i]='0'+wei[i];
        }
    }
}
void dirDeToHex(int dirValue)
{

    int wei[2];
    int i=0;
    wei[0]=dirValue/16;
    wei[1]=dirValue%16;
    for(i=0;i<2;i++){
        if(wei[i]>9){
            dirValueChars[i]='A'+wei[i]-10;
        }else{
            dirValueChars[i]='0'+wei[i];
        }
    }
}
void calLast2(char * str){
    int i,n,sum=0;
    int high,low;
    n=strlen(str);
//printf("strlen:%d\n",n=strlen(str));
    for(i=1;i<n;i++){
        sum+=str[i];
    }
    sum=256-(sum&0xff);
    high=(sum&0x0f0)/16;
    low=sum&0x0f;
    if(low<10)
        low+=48;
    else
        low+=55;
    if(high<10)
        high+=48;
    else
        high+=55;
    //printf("last2:%c%c\n",high,low);
    last2[0]=high;
    last2[1]=low;
}

void getGasValue(int dy)
{
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
}
void getDirValue(int dx)
{
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
}

void calControlStr(int gasValue,int dirValue)
{
    ctrlStr[0]=':'; ctrlStr[1]='R';ctrlStr[2]='C';
    ctrlStr[3]=gasValueChars[0];ctrlStr[4]=gasValueChars[1];
    for(int i=5;i<=10;i++){
        ctrlStr[i]='0';
    }
    ctrlStr[7]=dirValueChars[0];
    ctrlStr[8]=dirValueChars[1];
    //crtlStr[9/10] is 0
    ctrlStr[11]='\0';
    calLast2(ctrlStr);
    ctrlStr[11]=last2[0];
    ctrlStr[12]=last2[1];
    ctrlStr[13]='/';
}
