#include"fly.h"

char * lock=":PWOFC4/";
char * unlock=":PWONBC/";
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
