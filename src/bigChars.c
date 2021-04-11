
#include "bigChars.h"

#include "myTerm.h"

int zero[2] = {1111638588, 1010975298};
int one[2] = {404364312, 2115508248};
int two[2] = {1615096888, 2081167408};
int three[2] = {1615086648, 943998016};
int four[2] = {1145324612, 1077952636};
int five[2] = {1006896252, 1010843712};
int six[2] = {1006896248, 943998020};
int seven[2] = {1077952636, 1077952576};
int eight[2] = {943998008, 943998020};
int nine[2] = {2084848764, 2084585536};
int plus[2] = {2081427456, 4112};
int A[2] = {1145317392, 1145324668};
int B[2] = {1011106876, 1011106884};
int C[2] = {67372152, 2013529092};
int D[2] = {1145316380, 472138820};
int E[2] = {1006896252, 2080637956};
int F[2] = {1006896252, 67372036};

int bc_printA(char* str) {
  printf("\E(0%s\E(B", str);
  return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
  mt_gotoXY(x1, y1);
  bc_printA("l");
  mt_gotoXY(x1 + x2, y1);
  bc_printA("m");

  for (int i = 1; i < x2; i++) {  // выводим левую часть рамки
    mt_gotoXY(x1 + i, y1);
    bc_printA("x");
  }

  for (int i = 1; i <= y2; i++) {
    mt_gotoXY(x1, y1 + i);
    bc_printA("q");
  }

  mt_gotoXY(x1, y1 + y2);
  bc_printA("k");

  for (int i = 1; i <= x2; i++) {
    mt_gotoXY(x1 + i, y1 + y2);
    bc_printA("x");
  }

  for (int i = 1; i <= y2; i++) {
    mt_gotoXY(x1 + x2, y1 + i);
    bc_printA("q");
  }

  mt_gotoXY(x1 + x2, y1 + y2);
  bc_printA("j");

  mt_gotoXY(x1 + x2 + 1, 0);

  return 0;
}

int bc_printbigchar(int* digit, int x, int y, enum colors fgcolor,
                    enum colors bgcolor) {
  mt_setfgcolor(fgcolor);
  mt_setbgcolor(bgcolor);
  mt_gotoXY(x, y);

  for (int i = 0; i < 2; i++) {
    for (int byte = 0; byte < 4; byte++) {
      for (int bit = 0; bit < 8; bit++) {
        if (((digit[i] >> (bit + (byte * 8))) & 1) == 1)
          bc_printA("a");
        else
          printf(" ");
      }
      x++;
      mt_gotoXY(x, y);
    }
  }
  mt_setdefaultcolor();

  return 0;
}

int bc_setbigcharpos(int* big, int x, int y, int value) {
  if (value > 1 || value < 0 || x > 7 || x < 0 || y > 7 || y < 0) 
    return -1;

  int index = 0;

  if (x > 3) 
    index = 1;

  if (value == 1)
    big[index] = big[index] | 1 << (x * 8 + y);
  else
    big[index] = big[index] & ~(1 << (x * 8 + y));

  return 0;
}

int bc_getbigcharpos(int* big, int x, int y, int* value) {
  if (x > 7 || x < 0 || y > 7 || y < 0) 
    return -1;

  int index = 0;

  if (x > 3) 
    index = 1;

  *value = ((big[index] >> (x * 8 + y)) & 1);

  return 0;
}

int bc_bigcharwrite(int fd, int* digit, int count)
{
    if (!digit || fd < 0) {
        return -1;
    }

    while (count > 0) {
        int result;
        if ((result = write(fd, digit, sizeof(int) * 2)) == -1)
            return -1;
        count--;
    }

    return 0;
}

int bc_bigcharread(int fd, int* digit, int need_count, int* count)
{
    if (fd < 0)
        return -1;

    while (need_count > 0) {
        int result;
        if ((result = read(fd, digit, sizeof(int) * 2)) == -1)
            return -1;

        need_count--;
        *count = *count + 1;
    }

    return 0;
}

void interface() {

    srand(time(NULL));
    mt_clrscr();
    int* rs = malloc(sizeof(int));
    int* cs = malloc(sizeof(int));

    mt_getscreensize(rs, cs);
    if (*rs < 30 || *cs < 100) {
        printf("Увеличьте размер окна терминала.\n");
        exit(-1);
    }
    int x, y;

    bc_box(5, 3, 11, 62);
    x = 5;
    y = 30;
    mt_gotoXY(x, y);
    printf(" Memory ");
        srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        x++;
        mt_gotoXY(x, 4);
        for (int j = 0; j < 10; j++) {
            int value = rand() % 65535;
            printf("+%04X ", value);
        }
    }

    bc_box(5, 66, 2, 25);
    x = 5;
    y = 75;
    mt_gotoXY(x,y - 2);
    printf("accumulator");
    x++, y++;
    mt_gotoXY(x,y);
    printf("+9999");

    bc_box(8, 66, 2, 25);
    x = x + 2;
    mt_gotoXY(x, y - 5);
    printf("instructionCounter");
    x++;
    mt_gotoXY(x, y);
    printf("+0000");

    bc_box(11, 66, 2, 25);
    x = x + 2;
    mt_gotoXY(x, y - 2);
    printf("Operation");
    x++;
    mt_gotoXY(x,y-2);
    printf("+00 : 00");

    bc_box(14, 66, 2, 25);
    x = x + 2;
    mt_gotoXY(x, y);
    printf("Flags");
    x++;
    mt_gotoXY(x,y - 2);
    printf("P O M T E");

    bc_box(17, 3, 9, 41);
    bc_printbigchar(plus, 18, 4, 7, 0);
    bc_printbigchar(nine, 18, 12, 7, 0);
    bc_printbigchar(nine, 18, 20, 7, 0);
    bc_printbigchar(nine, 18, 28, 7, 0);
    bc_printbigchar(nine, 18, 36, 7, 0);

    bc_box(17, 45, 9, 46);
    x = 17;
    y = 47;

    mt_gotoXY(x,y);
    printf("Keys:");
    y--;
    mt_gotoXY(x + 1, y);
    printf("l - load");
    mt_gotoXY(x + 2, y);
    printf("s - save");
    mt_gotoXY(x + 3, y);
    printf("r - run");
    mt_gotoXY(x + 4, y); 
    printf("t - step");
    mt_gotoXY(x + 5, y);
    printf("i - reset");
    mt_gotoXY(x + 6, y);
    printf("F5 - accumulator");
    mt_gotoXY(x + 7, y);
    printf("F6 - instructionCounter");

    mt_gotoXY(80, 0);


}