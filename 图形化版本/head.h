#ifndef GUI_HEAD
#define GUI_HEAD

#define WIDTH 1280
#define HEIGHT 720

#define BACKGROUNDCOLOR 0xE7EFDE

#include<Windows.h>

void opening();
void gamedraw();
void remainmine(int remain);

void operation(int operatype, int k1, int k2);

void openspace(int k1, int k2);
void markmine(int k1, int k2);
void markquestion(int k1, int k2);
void unopenspace(int k1, int k2);

void printnum(int x, int y, int printnum);

#endif
