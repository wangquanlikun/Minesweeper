#ifndef GUI_HEAD
#define GUI_HEAD

#define WIDTH 1280
#define HEIGHT 720

//#define _CRT_SECURE_NO_WARNINGS

#define BACKGROUNDCOLOR 0xE7EFDE
#define OPENCOLOE WHITE
#define UNOPENCOLOR 0xFFDB9D
#define MARKMINECOLOR 0xFFFBE8
#define MARKQUESTIONCOLOR 0xE3FEFF
#define MINEBOOMCOLOR 0x5848FF

#include<Windows.h>

struct judge
{
	int spacex;
	int spacey;
	int mine;
	int gamemode;
};
typedef struct judge JUDGE;

int opening();
JUDGE setting(int flag);

int inputnum();

void creatspace(int k1,int k2);//k1,k2是第一次点击的位置。不能有雷
void gamedraw();

void remainmine(int remain);

void gamestatusprint(int status);
#define GAMEINPROGRESS 1
#define HITMINE 2
#define GAMEWIN 3

void printusetime();

int operation(int operatype, int xspace, int yspace);
#define LEFTCLICK 1
#define RIGHTCLICK 2
#define BOTHCLICK 3

bool adjustwin();
void gameover(int status);

void openspace(int k1, int k2);
void markmine(int k1, int k2);
void markquestion(int k1, int k2);
void unopenspace(int k1, int k2);

void printnum(int x, int y, int printnum);

int fileoperation(int type, int inputminute, int inputsecond, int inputgamemode);//对文件的操作
#define READ 1
#define WRITE 2

#endif
