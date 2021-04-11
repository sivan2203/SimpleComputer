
#include "myTerm.h"
#
int mt_clrscr() {

	printf("\E[H\E[J");

	return 0;

}

int mt_gotoXY(int X, int Y) {

	printf("\E[%d;%dH", X, Y);

	return 0;
}

int mt_getscreensize(int* rows, int* cols) {

	struct winsize ws;
	if(!ioctl(1, TIOCGWINSZ, &ws)) {
		*rows = ws.ws_row;
		*cols = ws.ws_col;
	}
	else
		return -1;

	return 0;
}

int mt_setfgcolor(enum colors color) {

	if (color < 0 || color > 7) 
		return -1;
	printf("\E[3%dm", color);
	
	return 0;
}

int mt_setbgcolor(enum colors color) {

    if (color < 0 || color > 7) {
        return -1;
    }
    printf("\E[4%dm", color);
    return 0;
}

int mt_setdefaultcolor() {
	
    printf("\E[0m");
    return 0;
}