#include "strSender.h"

struct termios options, oldoptions;
int fd;
int open_error_flag=0;

void senderInit(){
    fd = open("/dev/ttyACM0", O_RDWR);
    if(fd <0){
        printf("fd=%d,open error!\n",fd);
        open_error_flag=1;
    }

    tcgetattr(fd, &oldoptions);
    tcgetattr(fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    tcsetattr(fd, TCSANOW, &options);
}

void sendControlStr()
{
    if(!open_error_flag){
        write(fd,ctrlStr, strlen(ctrlStr));
        printf("[send success] %s\n",ctrlStr);
    }//else
        printf("[send failed] %s\n",ctrlStr);
}
