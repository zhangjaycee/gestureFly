
#include<string.h>
#ifndef FLY_H
#define FLY_H

extern char * lock;
extern char * unlock;
extern int gasValue;
extern int dirValue;
extern char gasValueChars[2];
extern char dirValueChars[2];
extern char last2[2];
extern char ctrlStr[20];

void gasDeToHex(int gasValue);
void dirDeToHex(int dirValue);
void calLast2(char * str);
void getGasValue(int dy);
void getDirValue(int dx);
void calControlStr(int gasValue,int dirValue);

#endif // FLY_H
