#include <iostream.h> 
#include <fstream.h> 
#include <dos.h> 
#include <string.h> 
#include <time.h> 
#include <bios.h> 
#include <graphics.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <conio.h>

int killscore = 0;
int shotscount = 5;
long int xx = 8, yy = 375;
char uname[15];
int msgc = 0;
char far * ttime;
long sctime;
unsigned int shots = 0;
int width = 32;
int life = 100;
long int midx, midy;
long int initpos[1000];
int nbots = 0;
int emidx[100], emidy[100];
long int estat[1000];
int ex[100], ey[100];
unsigned long xb[1000], yb[1000];
int statb[1000];
char ch[100];
long char edir[1000];
char dir;
int mcount = 0;
int bcount = 0;
int xg[100], yg[100];
int xr[100], yr[100];
int xw[100], yw[100];
long int xm[1000], ym[1000];

class score

{

  public:

  int kills;
  long time;
  char name[50];

  //////////////////////////////////////////////////////////////////////////////

  void input(char nam[50], int k, long t)

  {

    kills = k;
    strcpy(name, nam);
    time = t;

  }

}

obj;

//****************************************************************************

void tank();
void destroy(int);
void bullet();
void main();
void help();

//****************************************************************************

void selecttank();

void drawscr(int i[])

{

  int midx = getmaxx() / 2;
  int midy = getmaxy() / 2;

  setfillstyle(1, RED);
  fillellipse(2 * midx + 25, midy, 500, 500);

  setcolor(RED);
  circle(2 * midx + 15, midy, 500);

  setfillstyle(1, DARKGRAY);
  setcolor(WHITE);

  setfillstyle(1, i[0]);
  fillellipse(115, 110, 35, 35);

  setfillstyle(1, i[1]);
  fillellipse(100, 245, 35, 35);

  setfillstyle(1, i[2]);
  fillellipse(115, 370, 35, 35);

  settextstyle(1, 0, 1);
  outtextxy(98, 105, "START");
  outtextxy(85, 242, "HELP");
  outtextxy(101, 367, "EXIT");

  settextstyle(2, 0, 4);

  setcolor(BLACK);

  flushall();

  settextstyle(10, 0, 7);
  outtextxy(235, 15, "BATTLE");
  outtextxy(255, 110, "TANKS");

  {

    settextstyle(0, 0, 2);
    outtextxy(340, 365, "NeLLeX Corp.");
    outtextxy(365, 395, "SMR Inc.");

  }

  setcolor(WHITE);


}

/////////////////////////////////////////////////////////////////////////////

int start(void)

{

  int i[3];
  i[0] = 4;
  i[1] = 8;
  i[2] = 8;
  drawscr(i);
  int key;
  int c = 0;

  while (1)

  {

    while (bioskey(1) == 0);
    key = bioskey(0);

    switch (key)

    {

    case 20480:
      if (c >= 2) break;
      c++;
      i[c] = 4;
      i[c - 1] = 8;
      break;
    case 18432:
      if (c == 0) break;
      c--;
      i[c] = 4;
      i[c + 1] = 8;
      break;

    case 283:
      exit(0);

    case 7181:
      if (c == 2) exit(0);
      if (c == 0) {
        selecttank();
        return 0;
      }

      if (c == 1) help();

      break;

    }

    drawscr(i);

  }

}

//

void help()

{

  setfillstyle(1, RED);
  fillellipse(getmaxx() + 25, getmaxy() / 2, 500, 500);

  settextstyle(3, 0, 7);
  outtextxy(325, 10, "HELP");
  settextstyle(2, 0, 5);
  outtextxy(185, 120, "<>- Use arrow keys to navigate the map. SPACE to shoot. ");
  outtextxy(185, 150, "<>- TANKS tread on the GRASS but NOT on WATER and WALLS.");
  outtextxy(185, 180, "<>- Walls can be broken by a single shot.");
  outtextxy(185, 210, "<>- The BATTLE TANK has a 4 bullet chamber.");
  outtextxy(185, 240, "<>- Press 'R' to RELOAD chamber after every shot.");
  outtextxy(185, 270, "<>- Higher the accuracy - Higher the points scored. ");

  settextstyle(1, HORIZ_DIR, 2);

  setfillstyle(11, LIGHTRED);
  bar(280, 320, 280 + width, 320 + width); //WALL
  outtextxy(280, 360, "WALL");

  setfillstyle(11, CYAN);
  bar(340, 320, 340 + width, 320 + width);
  outtextxy(337, 360, "WATER");

  setfillstyle(9, GREEN);
  bar(400, 320, 400 + width, 320 + width);
  outtextxy(397, 360, "GRASS");

  getch();

}

int col = 7, col2 = 3;

//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

void tankdraw()

{

  int midx, midy;
  int width = 47;
  int xx = 300;
  int yy = 290;
  int x1 = 465;

  line(x1, yy - 7, x1 + 20, yy - 7);
  line(x1, yy + width + 7, x1 + 20, yy + width + 7);
  line(x1, yy - 7, x1 + 10, yy - 25);
  line(x1 + 10, yy - 25, x1 + 20, yy - 7);
  line(x1, yy + width + 7, x1 + 10, yy + width + 25);
  line(x1 + 10, yy + width + 25, x1 + 20, yy + width + 7);

  midx = (xx + xx + width) / 2;
  midy = (yy + yy + width) / 2;

  setfillstyle(9, col);
  bar(xx, yy + 2, xx + width, yy + width - 2); //body

  setfillstyle(9, col2);
  bar(xx, yy, xx + 5, yy + width); //LEFT TREAD
  bar(xx + width, yy, xx + width - 5, yy + width); //RIGHT TREAD

  setfillstyle(9, col2);

  bar(midx - 2, midy - 42, midx + 2, midy);

  setfillstyle(9, LIGHTRED);

  setcolor(YELLOW);
  fillellipse(midx, midy, 13, 13);

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

void selecttank()

{

  setfillstyle(1, RED);
  fillellipse(getmaxx() + 25, getmaxy() / 2, 500, 500);

  settextstyle(3, 0, 7);
  outtextxy(215, 20, "RECRUITMENT");
  settextstyle(2, 0, 7);
  outtextxy(310, 120, "Select BATTLE TANK");
  int key;
  tankdraw();

  while (1)

  {

    while (bioskey(1) == 0);
    key = bioskey(0);

    switch (key)

    {

    case 20480:
      if (col > 15) break;
      col++;
      break;
    case 18432:
      if (col < 1) break;
      col--;
      break;
    case 19712:
      if (col2 > 15) break;
      col2++;
      break;
    case 19200:
      if (col2 < 1) break;
      col2--;
      break;

    case 7181:
      return;;

    case 283:
      start();

    }

    tankdraw();

  }

}

///////////////////////////////////////////////////////

void init()

{

  randomize();

  for (int i = 0; i < 50; i++) //GRASS

  {

    xg[i] = random(100) % 16 + 2;
    yg[i] = random(100) % 12 + 1;

    xm[mcount] = xg[i];
    ym[mcount] = yg[i];
    mcount++;

  }

  for (i = 0; i < 40; i++) //BRICKS

  {

    xw[i] = random(100) % 16 + 2;
    yw[i] = random(100) % 12 + 1;

    xm[mcount] = xw[i];
    ym[mcount] = yw[i];
    mcount++;

  }

  for (i = 0; i < 10; i++) //RIVER

  {

    xr[i] = random(100) % 16 + 2;
    yr[i] = random(100) % 12 + 1;
    xm[mcount] = xr[i];
    ym[mcount] = yr[i];
    mcount++;

  }

  setfillstyle(2, WHITE);
  bar(0 * width, 13 * width, 20 * width, 15 * width);

}

//*************************************************//

void enemy()

{

  for (int q = 0; q < nbots; q++)

  {

    if (estat[q] != 1)

    {

      emidx[q] = (ex[q] + ex[q] + width) / 2;
      emidy[q] = (ey[q] + ey[q] + width) / 2;
      setfillstyle(9, LIGHTRED);

      if (edir[q] == 's' || edir[q] == 'w')

      {

        bar(ex[q], ey[q] + 2, ex[q] + width, ey[q] + width - 2); //body

      } else

      {

        bar(ex[q] + 2, ey[q], ex[q] + width - 2, ey[q] + width);

      }

      if (edir[q] == 's' || edir[q] == 'w')

      {

        setfillstyle(9, LIGHTGRAY);
        bar(ex[q], ey[q], ex[q] + 3, ey[q] + width); //LEFT TREAD
        bar(ex[q] + width, ey[q], ex[q] + width - 3, ey[q] + width); //RIGHT TREAD

      } else

      {

        setfillstyle(9, LIGHTGRAY);
        bar(ex[q], ey[q], ex[q] + width, ey[q] + 3); //LEFT TREAD
        bar(ex[q], ey[q] + width, ex[q] + width, ey[q] + width - 3); //RIGHT TREAD

      }

      setfillstyle(9, LIGHTGRAY);

      if (edir[q] == 's')

      {

        bar(emidx[q] - 2, emidy[q], emidx[q] + 2, emidy[q] + 28); //TURRET

      } else if (edir[q] == 'w')

      {

        bar(emidx[q] - 2, emidy[q] - 28, emidx[q] + 2, emidy[q]);

      } else if (edir[q] == 'd')

      {

        bar(emidx[q], emidy[q] - 2, emidx[q] + 28, emidy[q] + 2);

      } else if (edir[q] == 'a')

      {

        bar(emidx[q] - 28, emidy[q] - 2, emidx[q], emidy[q] + 2);

      }

      setfillstyle(9, 5);

      setcolor(WHITE);
      fillellipse(emidx[q], emidy[q], 9, 9);

    }

  }

}

//********************************************************//

void emove()

{

  int flag1 = 0;
  int flag = 0;

  for (int q = 0; q < nbots; q++)

  {

    if (estat[q] != 1)

    {

      int mov = 4;
      int xmax = getmaxx();
      int ymax = getmaxy();
      int x[5], y[5];

      y[0] = emidy[q] + mov + 16; //DOWN
      x[0] = emidx[q];

      y[1] = emidy[q] - mov - 16; //UP
      x[1] = emidx[q];

      x[2] = emidx[q] + mov + 16; //RIGHT
      y[2] = emidy[q];

      x[3] = emidx[q] - mov - 16; //LEFT
      y[3] = emidy[q];

      int m;
      int n;

      int ed[5];
      int cc = 0;

      for (int o = 0; o < 4; o++)

      {

        m = (x[o] / width);
        n = (y[o] / width);

        flag = 0;

        for (int i = 50; i < mcount; i++)

        {

          if ((xm[i] == m && ym[i] == n))

          {

            flag++;

          }

          if ((x[o] > xmax) || (y[o] > ymax - (2 * width)) || (x[o] < 0) || (y[o] < 0))

          {
            flag++;
          }

        }

        if (flag == 0)

        {

          ed[cc] = o;
          cc++;

        }

      }

      int r;
      {

        flag1 = 0;

        /**RELATIVE POSTN OF PLAYER */

        int reli[2];

        reli[0] = -1;
        reli[1] = -1;
        if (midx + 16 > emidx[q])

        {
          reli[0] = 2;
        }

        if (midx - 16 < emidx[q])

        {
          reli[0] = 3;
        }

        if (midy + 16 > emidy[q])

        {
          reli[1] = 0;
        }

        if (midy - 16 < emidy[q])

        {
          reli[1] = 1;
        }

        for (int u = 0; u < cc; u++)

        {

          if (ed[u] == initpos[q])

          {
            flag1++;
            r = u;
          }

          if ((ed[u] == reli[0] || ed[u] == reli[1]) && random(100) % 50 == 0)

          {

            r = u;

          }


        }

        int ran = random(100);
        if (flag1 == 0 || (ran % 99) == 0)

        {
          r = random(cc + 1);
        }

        initpos[q] = ed[r];

        if (ran % 30 == 0)

        {

          if (ed[r] == 0)

          {

            xb[bcount] = emidx[q];
            yb[bcount] = emidy[q] + 28;
            ch[bcount] = 's';

          } else if (ed[r] == 1)

          {

            xb[bcount] = emidx[q];
            yb[bcount] = emidy[q] - 28;
            ch[bcount] = 'w';

          } else if (ed[r] == 2)

          {

            xb[bcount] = emidx[q] + 28;
            yb[bcount] = emidy[q];
            ch[bcount] = 'd';

          } else if (ed[r] == 3)

          {

            ch[bcount] = 'a';
            xb[bcount] = emidx[q] - 28;
            yb[bcount] = emidy[q];

          }

          statb[bcount] = 3;
          bcount++;

        }

        switch (ed[r])

        {

        case 0:
          ey[q] = ey[q] + mov;
          edir[q] = 's';

          break;

        case 1:
          ey[q] = ey[q] - mov;
          edir[q] = 'w';

          break;

        case 2:
          ex[q] = ex[q] + mov;
          edir[q] = 'd';

          break;

        case 3:
          ex[q] = ex[q] - mov;
          edir[q] = 'a';

          break;

        }

      }


    }

  }

}

//___________________________________________________________________

void message() {

  int xmax = getmaxx();
  int ymax = getmaxy();

  setfillstyle(2, BLACK);
  bar(5, 13 * width + 5, xmax - 5, ymax - 5);

  setfillstyle(6, RED);
  bar(10, 13 * width + 10, 47, ymax - 10);

  setfillstyle(1, YELLOW);

  int amm = 13 * width + 10 + 11;
  amm += ((4 - shotscount)) * 11;

  bar(50, amm, 53, ymax - 10);

  char msg[50][50] = {
    "BITE ME!!",
    "Carnage!",
    "Mayhem!",
    "Missile Madness!",
    "Take THAT F@$%@# !",
    "HELL YEAH !!",
    "In Your FACE!",
    "Live for the pain!!"
  }

  ;
  char far * text = msg[msgc];

  int l = 13 * width + 10;

  l = l + ((100 - life) / 25) * 11;

  // 469 426           11
  setfillstyle(1, GREEN);

  bar(57, l, 65, ymax - 10);

  setcolor(CYAN);
  settextstyle(DEFAULT_FONT, VERT_DIR, 1);
  outtextxy(49, ymax - 48, "AMMO");

  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(95, ymax - 46, "SCORE: ");

  setcolor(WHITE);
  settextstyle(0, VERT_DIR, 1);
  outtextxy(75, ymax - 55, "HEALTH");

  setcolor(WHITE);

  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1.5);

  outtextxy(xmax - 200, 13 * width + 12, text);

}

//......................................................................

void map()

{

  int xmax = getmaxx();
  int ymax = getmaxy();

  //draw diagonal line

  setfillstyle(1, BLACK);
  setcolor(BLACK);

  delay(5);
  bar(0, 0, xmax, 13 * width);

  setfillstyle(9, WHITE); // E - SPAWN / BASE   [9/10]

  bar(xmax, 13 * width, xmax - 2 * width + 15, 11 * width + 15);
  bar(0, 0, 2 * width - 15, 2 * width - 10);

  message();

  setfillstyle(1, WHITE);
  bar(0, 0, 2, ymax);
  bar(xmax, 0, xmax - 2, ymax);
  bar(0, 0, xmax, 2);

  int i = 0;
  setcolor(WHITE);


  int j;


  setfillstyle(11, LIGHTRED);

  i = 0;
  while (i < 40) //BRICK

  {

    bar(xw[i] * width, yw[i] * width, (xw[i] + 1) * width, (yw[i] + 1) * width);
    i++;
    bar(xw[i] * width, yw[i] * width, (xw[i] + 1) * width, (yw[i] + 1) * width);
    i++;

  }

  setfillstyle(11, CYAN);
  i = 0;
  while (i < 10) //WATER

  {

    bar(xr[i] * width, yr[i] * width, (xr[i] + 1) * width, (yr[i] + 1) * width);
    i++;
    bar(xr[i] * width, yr[i] * width, (xr[i] + 1) * width, (yr[i] + 1) * width);
    i++;

  }

  //................

  tank();
  enemy();
  bullet();
  setfillstyle(9, GREEN);
  i = 0;
  while (i < 50) //GRASS

  {

    bar(xg[i] * width, yg[i] * width, (xg[i] + 1) * width, (yg[i] + 1) * width);
    i++;
    bar(xg[i] * width, yg[i] * width, (xg[i] + 1) * width, (yg[i] + 1) * width);
    i++;

  }

  setcolor(CYAN);
  settextstyle(4, HORIZ_DIR, 3);
  char far * score;
  char sc[25];
  itoa(killscore, sc, 10);
  score = sc;

  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  outtextxy(160, 13 * width + 17, score);
  outtextxy(95, 13 * width + 30, "TIMER: ");
  outtextxy(160, 13 * width + 30, ttime);
  //outtextxy(500,500,"TEXT");

  if (shotscount < 2)

  {
    setcolor(RED + BLINK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(getmaxx() - 400, 13 * width + 13, "RELOAD");

  }

}

/****************************************************/

void tank()

{

  midx = (xx + xx + width) / 2;
  midy = (yy + yy + width) / 2;
  setfillstyle(9, col);

  if (dir == 's' || dir == 'w')

  {

    bar(xx, yy + 2, xx + width, yy + width - 2); //body

  } else

  {

    bar(xx + 2, yy, xx + width - 2, yy + width);

  }

  if (dir == 's' || dir == 'w')

  {

    setfillstyle(9, col2);
    bar(xx, yy, xx + 3, yy + width); //LEFT TREAD
    bar(xx + width, yy, xx + width - 3, yy + width); //RIGHT TREAD

  } else

  {

    setfillstyle(9, col2);
    bar(xx, yy, xx + width, yy + 3); //LEFT TREAD
    bar(xx, yy + width, xx + width, yy + width - 3); //RIGHT TREAD

  }

  setfillstyle(9, CYAN);

  if (dir == 's')

  {

    bar(midx - 2, midy, midx + 2, midy + 28); //TURRET

  } else if (dir == 'w')

  {

    bar(midx - 2, midy - 28, midx + 2, midy);

  } else if (dir == 'd')

  {

    bar(midx, midy - 2, midx + 28, midy + 2);

  } else if (dir == 'a')

  {

    bar(midx - 28, midy - 2, midx, midy + 2);

  }

  setfillstyle(9, LIGHTRED);

  setcolor(YELLOW);
  fillellipse(midx, midy, 9, 9);

}

/*******************************************************/
int pcheck(char d)

{

  int mov = 5;
  int xmax = getmaxx();
  int ymax = getmaxy();
  int x, y;
  x = midx;
  y = midy;

  // if(dir ==
  if (d == 's')

  {

    y = midy + mov + 16;

  } else if (d == 'w')

  {

    y = midy - mov - 16;

  } else if (d == 'd')

  {

    x = midx + mov + 16;

  } else if (d == 'a')

  {

    x = midx - mov - 16;

  }

  int m = (x / width);
  int n = (y / width);
  //gotoxy(0,0);
  //cout <<m<<" "<<n;
  //getch();

  if ((x > xmax) || (y > ymax - (2 * width)) || x < 0 || y < 0)

  {
    return 0;
  }

  for (int i = 50; i < mcount; i++)

  {

    if (xm[i] == m && ym[i] == n)

    {
      return 0;
    }

  }

  return 1;

}

/*************************************************************************/

void bullet()

{

  int dist = 15;
  int xmax = getmaxx();
  int ymax = getmaxy();

  for (int i = 0; i < bcount; i++)

  {

    if (xb[i] > 0 && yb[i] > 0 && xb[i] < xmax && yb[i] < ymax && statb[i] != 1)

    {

      if (ch[i] == 'w')

      {

        yb[i] -= dist;

      }

      if (ch[i] == 's')

      {

        yb[i] += dist;

      }

      if (ch[i] == 'a')

      {

        xb[i] -= dist;

      }

      if (ch[i] == 'd')

      {

        xb[i] += dist;

      }

      int m = xb[i] / width;
      int n = yb[i] / width;
      for (int j = 0; j < 40; j++)

      {

        if (xw[j] == m && yw[j] == n)

        {

          xw[j] = -10;
          yw[j] = -10;
          statb[i] = 1;
          xm[50 + j] = -10;
          ym[50 + j] = -10;
          xb[i] = -10;
          yb[i] = -10;

        }

      }

      //kill bots
      for (int q = 0; q < nbots; q++)

      {

        if ((statb[i] == 2) && (estat[q] != 1) && (xb[i] > (emidx[q] - 10) && (xb[i] < emidx[q] + 10)) && (yb[i] > emidy[q] - 10) && (yb[i] < emidy[q] + 10))

        {

          estat[q] = 1;
          xb[i] = -10;
          yb[i] = -10;
          destroy(q);
          msgc = random(9);

        }

      }

    }

    if ((xb[i] > (midx - 10) && (xb[i] < midx + 10)) && (yb[i] > midy - 10) && (yb[i] < midy + 10))

    {

      xb[i] = -10;
      yb[i] = -10;
      msgc = random(10);
      life -= 25;

    }

    setfillstyle(8, YELLOW);
    setcolor(RED);
    fillellipse(xb[i], yb[i], 3, 3);

  }

}

//********************************************************
void destroy(int f)

{

  setcolor(RED);
  if (shots > 20) shots = 21;
  killscore = killscore + (100 * (21 - shots) / 20);;
  shots = 0;
  for (int i = 0; i < 30; i++)

  {

    circle(emidx[f], emidy[f], i);
    delay(3);

  }

}

//[][][][]][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]

void save()

{

  cleardevice();
  char uname[50];
  gotoxy(35, 10);

  ifstream fin;
  fin.open("score.txt", ios::out);

  int flag = 0;

  fin.seekg(0, ios::end);
  int size = fin.tellg();
  int scount = size / sizeof(score);
  char rname[50][50];
  int rkills[50], rtime[50];

  fin.seekg(0, ios::beg);
  score ob;
  int temp;

  for (int i = 0; i < scount; i++)

  {

    fin.read((char * ) & ob, sizeof(score));
    rkills[i] = ob.kills;
    if (killscore < rkills[i]) flag++;

  }

  fin.close();

  if (flag <= 10)

  {

    cout << "HIGH SCORE";
    gotoxy(10, 12);
    cout << "------------------------------------------------------------";
    gotoxy(25, 14);
    cout << "Enter NAME: ";
    gets(uname);
    obj.input(uname, killscore, sctime);
    ofstream fout;
    fout.open("score.txt", ios::app);
    fout.write((char * ) & obj, sizeof(score));
    fout.close();

  }

  cleardevice();
  gotoxy(35, 10);
  cout << "HIGH SCORE";
  gotoxy(10, 12);
  cout << "------------------------------------------------------------";
  gotoxy(12, 14);
  cout << "NAME\t\t     SCORE\t\t\tTIME";

  fin;
  fin.open("score.txt", ios::out);
  int c = 16;

  fin.seekg(0, ios::end);
  size = fin.tellg();
  scount = size / sizeof(score);

  fin.seekg(0, ios::beg);

  for (i = 0; i < scount; i++)

  {

    fin.read((char * ) & ob, sizeof(score));
    strcpy(rname[i], ob.name);
    rkills[i] = ob.kills;
    rtime[i] = ob.time;

  }

  fin.close();

  for (i = 0; i < scount - 1; i++)

  {

    for (int k = i; k < scount; k++)

    {

      if (rkills[i] < rkills[k])

      {

        temp = rkills[k];
        rkills[k] = rkills[i];
        rkills[i] = temp;

        temp = rtime[k];
        rtime[k] = rtime[i];
        rtime[i] = temp;
        char str[50];

        strcpy(str, rname[i]);
        strcpy(rname[i], rname[k]);
        strcpy(rname[k], str);

      }

    }

  }

  int cc;
  if (scount > 10) cc = 10;
  else cc = scount;

  for (int o = 0; o < cc; o++)

  {

    gotoxy(12, c);
    cout << rname[o];
    gotoxy(36, c);
    cout << rkills[o];
    gotoxy(63, c);
    cout << rtime[o];

    c++;

  }

  getch();

}

//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void main(void)

{

  //cout<<"Enter username: ";
  //gets(uname);

  time_t initial, final;
  flushall();
  int gdriver = DETECT, gmode, errorcode;
  int xmax, ymax;

  initgraph( & gdriver, & gmode, "C:\\TC\\BGI");

  errorcode = graphresult();

  if (errorcode != grOk)

  {

    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);

  }

  //cout <<"  "<<xmax<<" "<<ymax;     //640 & 480

  start();

  estat[0] = 0;
  nbots++;
  ex[0] = 10;
  ey[0] = 10;
  initpos[0] = 1;
  nbots++;
  ex[1] = 18 * width + 20;
  ey[1] = 11 * width + 25;
  initpos[1] = 1;

  init();
  map();
  tank();

  dir = 's';
  int mov = 5;
  int now = 9;
  int key;
  getch();

  initial = time(NULL);

  while (1)

  {

    INPUT:

      while (bioskey(1) == 0);
    key = bioskey(0);

    switch (key)

    {

    case 20480:
      if (pcheck('s') == 1)

      {

        yy = yy + mov;
        dir = 's';

      }

      break;

    case 18432:
      if (pcheck('w') == 1)

      {

        yy = yy - mov;
        dir = 'w';

      }

      break;

    case 19712:
      if (pcheck('d') == 1)

      {

        xx = xx + mov;
        dir = 'd';

      }

      break;

    case 19200:
      if (pcheck('a') == 1)

      {

        xx = xx - mov;
        dir = 'a';

      }

      break;

    case 4978:
      if (shotscount < 5) shotscount++;
      break;

    case 14624:

      if (shotscount == 1) break;

      if (dir == 's')

      {

        xb[bcount] = midx;
        yb[bcount] = midy + 28;
        ch[bcount] = dir;

      } else if (dir == 'w')

      {

        xb[bcount] = midx;
        yb[bcount] = midy - 28;
        ch[bcount] = dir;

      } else if (dir == 'd')

      {

        xb[bcount] = midx + 28;
        yb[bcount] = midy;
        ch[bcount] = dir;

      } else if (dir == 'a')

      {

        ch[bcount] = dir;
        xb[bcount] = midx - 28;
        yb[bcount] = midy;

      }

      statb[bcount] = 2;
      bcount++;
      shots++;
      shotscount--;
      break;

    case 283:
      exit(0);

    }

    while (!kbhit())

    {

      map();
      emove();
      final = time(NULL);

      char chtime[100];
      ltoa((final - initial), chtime, 10);
      sctime = atol(chtime);
      ttime = chtime;
      if ((final - initial) == now)

      {

        now = now + 9;

        nbots++;
        ex[nbots] = 10;
        ey[nbots] = 10;
        nbots++;
        ex[nbots] = 18 * width + 20;
        ey[nbots] = 11 * width + 25;
        initpos[nbots] = 1;

      }

      if (life < 0)

      {

        setcolor(RED);
        for (int i = 0; i < 500; i++)

        {

          circle(xx, yy, i);
          delay(5);

        }

        for (i = 0; i < 25; i++)

        {

          setfillstyle(1, WHITE);
          bar(0, 0, getmaxx(), getmaxy());
          delay(50);
          setfillstyle(1, BLACK);
          bar(0, 0, getmaxx(), getmaxy());

        }

        save();
        exit(0);

      }

      delay(10);

    }

    goto INPUT;

  }

}
