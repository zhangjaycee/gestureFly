#ifndef STRSENDER_H
#define STRSENDER_H
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

extern char ctrlStr[20];
extern struct termios options, oldoptions;
extern int fd;
extern int open_error_flag;

void senderInit();
void sendControlStr();

#endif // STRSENDER_H

