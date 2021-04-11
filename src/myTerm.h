#ifndef MYTERM_H
#define MYTERM_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

enum colors {
    black = 0,
    red = 1,
    green = 2,
    yellow = 3,
    blue = 4,
    pink = 5,
    lightblue = 6,
    white = 7,
};

int mt_clrscr();
int mt_gotoXY(int X, int Y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);
int mt_setdefaultcolor();

#endif