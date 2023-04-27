#include<stdio.h>
#include<string.h>
#include"head.h"

#include <graphics.h>
#include <conio.h>


int gamespacex, gamespacey;//长、宽的游戏区域

int main()
{
	initgraph(WIDTH, HEIGHT);
	setbkcolor(0xE7EFDE);
	setbkmode(TRANSPARENT);
	cleardevice();

	gamespacex = 16;
	gamespacey = 12;
	gamedraw();//绘制游戏区域。开始点击操作游戏的进程

	return 0;
}

void gamedraw()
{
	setlinecolor(0x332300);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 2);
	cleardevice();

	float top = 50, bottom = HEIGHT - top;
	float each = (bottom - top) / gamespacey;
	float square = each * 5 / 6;
	float interval = each - square;
	float left, right;
	left = WIDTH / 2 - (gamespacex / 2) * 6 * interval;
	right = left + (gamespacex - 1) * each + square;

	int i1, i2;
	for (i1 = 0; i1 < gamespacex; i1++)
	{
		for (i2 = 0; i2 < gamespacey; i2++)
			rectangle(left + i1 * each, top + i2 * each, left + i1 * each + square, top + i2 * each + square);
	}

	remainmine();

	ExMessage mouseclick;
	while (true)
	{
		mouseclick = getmessage(EX_MOUSE | EX_KEY);
		int k1, k2;
		if (mouseclick.lbutton == 1 && (mouseclick.x >= left && mouseclick.x <= right && mouseclick.y >= top && mouseclick.y <= bottom))
		{
			remainmine();

			k1 = (mouseclick.x - left) / each;
			k2 = (mouseclick.y - top) / each;

			openspace(k1, k2);
		}
		else if (mouseclick.rbutton == 1 && (mouseclick.x >= left && mouseclick.x <= right && mouseclick.y >= top && mouseclick.y <= bottom))
		{
			remainmine();

			k1 = (mouseclick.x - left) / each;
			k2 = (mouseclick.y - top) / each;

			markmine(k1, k2);
		}
	}
}

void openspace(int k1, int k2)
{
	float top = 50, bottom = HEIGHT - top;
	float each = (bottom - top) / gamespacey;
	float square = each * 5 / 6;
	float interval = each - square;
	float left, right;
	left = WIDTH / 2 - (gamespacex / 2) * 6 * interval;
	right = left + (gamespacex - 1) * each + square;

	setfillcolor(WHITE);
	fillrectangle(left + k1 * each, top + k2 * each, left + k1 * each + square, top + k2 * each + square);
	settextstyle(square, 0, _T("Consolas"));
	settextcolor(BLACK);
	printnum(left + k1 * each + square / 4, top + k2 * each, 3);

	return;
}

void markmine(int k1, int k2)
{
	TCHAR minemark[] = _T("🚩");

	float top = 50, bottom = HEIGHT - top;
	float each = (bottom - top) / gamespacey;
	float square = each * 5 / 6;
	float interval = each - square;
	float left, right;
	left = WIDTH / 2 - (gamespacex / 2) * 6 * interval;
	right = left + (gamespacex - 1) * each + square;

	setfillcolor(0xFFFBE8);
	fillrectangle(left + k1 * each, top + k2 * each, left + k1 * each + square, top + k2 * each + square);
	settextstyle(square, 0, _T("Consolas"));
	settextcolor(RED);
	outtextxy(left + k1 * each, top + k2 * each, minemark);

	return;
}

void markquestion(int k1, int k2)
{
	TCHAR questionmark[] = _T("?");

	float top = 50, bottom = HEIGHT - top;
	float each = (bottom - top) / gamespacey;
	float square = each * 5 / 6;
	float interval = each - square;
	float left, right;
	left = WIDTH / 2 - (gamespacex / 2) * 6 * interval;
	right = left + (gamespacex - 1) * each + square;

	setfillcolor(0xE3FEFF);
	fillrectangle(left + k1 * each, top + k2 * each, left + k1 * each + square, top + k2 * each + square);
	settextstyle(square, 0, _T("Consolas"));
	settextcolor(BLUE);
	outtextxy(left + k1 * each + square / 4, top + k2 * each, questionmark);

	return;
}

void remainmine()
{
	TCHAR remainmine[] = _T("剩余的地雷数目：");
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(0x332300);
	outtextxy(30, 30, remainmine);
}

void printnum(int x, int y, int printnum)//在x,y位置输出数字'printnum'
{
	TCHAR s[8];
	_stprintf_s(s, _T("%d"), printnum);
	outtextxy(x, y, s);

	return;
}