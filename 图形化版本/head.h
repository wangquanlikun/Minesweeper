#ifndef GUI_HEAD
#define GUI_HEAD

#define WIDTH 1280
#define HEIGHT 720

#define BACKGROUNDCOLOR 0xE7EFDE

#include<Windows.h>

void opening();

void creatspace(int k1,int k2);//k1,k2是第一次点击的位置。不能有雷
void gamedraw();
void remainmine(int remain);

int operation(int operatype, int xspace, int yspace);
#define LEFTCLICK 1
#define RIGHTCLICK 2
#define BOTHCLICK 3

void openspace(int k1, int k2);
void markmine(int k1, int k2);
void markquestion(int k1, int k2);
void unopenspace(int k1, int k2);

void printnum(int x, int y, int printnum);

#endif
