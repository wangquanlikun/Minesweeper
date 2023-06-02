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
	wchar_t line[10] = { 0 };
	wchar_t row[10] = { 0 };
	wchar_t minetext[10] = { 0 };
};
typedef struct judge JUDGE;

int opening();
JUDGE setting(int flag);
JUDGE Textbox();//自定义文本框函数

void Creat(int x1, int y1, int x2, int y2, wchar_t* text);//创建自定义窗口
int transport(wchar_t* ch);//将字符串转换成数字
wchar_t* onMessage(int x1, int y1, int x2, int y2, wchar_t* text);//文本框的输入和删除


int inputnum();

void creatspace(int k1, int k2);//k1,k2是第一次点击的位置。不能有雷
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
void reset();
int fileoperation(int type, int inputminute, int inputsecond, int inputgamemode);//对文件的操作
#define READ 1
#define WRITE 2

#endif
