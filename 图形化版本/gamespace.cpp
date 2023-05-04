#include<stdio.h>
#include<string.h>
#include<time.h>
#include"head.h"

#include <graphics.h>
#include <conio.h>


int gamespacex, gamespacey;//长、宽的游戏区域
int minenum;//游戏地雷的数目
char space[24 + 1][30 + 1] = { '\0' }; //记录原始雷区数据
char numspace[24 + 1][30 + 1] = { '\0' }; //直接记录个位置雷与数字
char outputspace[24 + 1][30 + 1] = { '\0' };//记录输出的游戏数据

int main()
{
	initgraph(WIDTH, HEIGHT);
	setbkcolor(0xE7EFDE);
	setbkmode(TRANSPARENT);
	cleardevice();

	gamespacex = 10;
	gamespacey = 12;
	minenum = 20;
	gamedraw();//绘制游戏区域。开始点击操作游戏的进程

	closegraph();
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

	rectangle(left + i1 * each + 50, top, left + i1 * each + square * 2 + 50, top + square);
	TCHAR exit[] = _T("退出游戏");
	settextstyle(square / 2, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	outtextxy(left + i1 * each + 50 + square / 4, top + square / 4, exit);

	remainmine(minenum);

	ExMessage mouseclick;

	bool isthefirstclick = true;
	int operation_return;

	while (true)
	{
		mouseclick = getmessage(EX_MOUSE | EX_KEY);
		int k1, k2;

		if (mouseclick.x >= left && mouseclick.x <= right && mouseclick.y >= top && mouseclick.y <= bottom - interval)
		{
			if (mouseclick.message == WM_LBUTTONDOWN)
			{
				int time = clock();
				while (true)
				{
					mouseclick = getmessage(EX_MOUSE | EX_KEY);
					int nowtime = clock();
					if (mouseclick.message == WM_LBUTTONUP)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;
						if (isthefirstclick)
						{
							creatspace(k1, k2);
							isthefirstclick = false;
						}

						operation_return = operation(LEFTCLICK, k1 + 1, k2 + 1);
						if (operation_return >= -1)
							minenum -= operation_return;
						else if (operation_return == -2)
							;
						remainmine(minenum);
						break;
					}
					else if (mouseclick.message == WM_RBUTTONDOWN)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;
						operation(BOTHCLICK, k1 + 1, k2 + 1);
						break;
					}
					if (nowtime - time > 500)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;
						if (isthefirstclick)
						{
							creatspace(k1, k2);
							isthefirstclick = false;
						}
						
						operation_return = operation(LEFTCLICK, k1 + 1, k2 + 1);
						if (operation_return >= -1)
							minenum -= operation_return;
						else if (operation_return == -2)
							;
						remainmine(minenum);
						break;
					}
				}
			}
			else if (mouseclick.message == WM_RBUTTONDOWN)
			{
				int time = clock();
				while (true)
				{
					mouseclick = getmessage(EX_MOUSE | EX_KEY);
					int nowtime = clock();
					if (mouseclick.message == WM_RBUTTONUP)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;

						operation_return = operation(RIGHTCLICK, k1 + 1, k2 + 1);
						if (operation_return >= -1)
							minenum -= operation_return;
						else if (operation_return == -2)
							;
						remainmine(minenum);
						break;
					}
					else if (mouseclick.message == WM_LBUTTONDOWN)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;
						operation(BOTHCLICK, k1 + 1, k2 + 1);
						break;
					}
					if (nowtime - time > 500)
					{
						k1 = (mouseclick.x - left) / each;
						k2 = (mouseclick.y - top) / each;

						operation_return = operation(RIGHTCLICK, k1 + 1, k2 + 1);
						if (operation_return >= -1)
							minenum -= operation_return;
						else if (operation_return == -2)
							;
						remainmine(minenum);
						break;
					}
				}
			}
		}

		else if (((mouseclick.x >= left + i1 * each + 50 && mouseclick.x <= left + i1 * each + square * 2 + 50) && (mouseclick.y >= top && mouseclick.y <= top + square)) && mouseclick.lbutton == 1)
			break;
	}
	return;
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
	if (numspace[k1 + 1][k2 + 1] != '0' && numspace[k1 + 1][k2 + 1] != '*')
		printnum(left + k1 * each + square / 4, top + k2 * each, numspace[k1 + 1][k2 + 1] - '0');
	else if (numspace[k1 + 1][k2 + 1] == '*')
	{
		TCHAR mine[] = _T("💣");
		settextcolor(RED);
		outtextxy(left + k1 * each, top + k2 * each, mine);
	}

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

void unopenspace(int k1, int k2)
{
	float top = 50, bottom = HEIGHT - top;
	float each = (bottom - top) / gamespacey;
	float square = each * 5 / 6;
	float interval = each - square;
	float left, right;
	left = WIDTH / 2 - (gamespacex / 2) * 6 * interval;
	right = left + (gamespacex - 1) * each + square;

	setfillcolor(0xE7EFDE);
	fillrectangle(left + k1 * each, top + k2 * each, left + k1 * each + square, top + k2 * each + square);
	return;
}

void remainmine(int remain)
{
	TCHAR remainmine[] = _T("剩余的地雷数目：");
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(0x332300);
	outtextxy(30, 30, remainmine);

	clearrectangle(20, 80, 60, 120);
	printnum(30, 90, remain);
	return;
}

void printnum(int x, int y, int printnum)//在x,y位置输出数字'printnum'
{
	TCHAR s[8];
	_stprintf_s(s, _T("%d"), printnum);
	outtextxy(x, y, s);

	return;
}

void creatspace(int k1, int k2)
{
	TCHAR waiting[] = _T("雷区生成，请稍后");
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	outtextxy(550, 10, waiting);

	int i1, i2;
	for (i1 = 1; i1 <= gamespacex; i1++)
	{
		for (i2 = 1; i2 <= gamespacey; i2++)
			space[i1][i2] = '.';
	}//确定的游戏区域使用'.'标记

	//随机生成开始
	int a, b;//在(a,b)上放雷
	int minenow = 0;
	srand(time(NULL));
	while (minenow < minenum)
	{
		a = rand() % gamespacex + 1;
		b = rand() % gamespacey + 1;
		if (a != k1 + 1 || b != k2 + 1)
		{
			if (space[a][b] == '.')
			{
				space[a][b] = '*';
				minenow += 1;
			}
		}
	}
	clearrectangle(500, 5, 800, 40);
	TCHAR start[] = _T("请开始游戏");
	settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(BLACK);
	outtextxy(580, 10, start);


	//对雷区数据的预处理
	int p1, p2;
	int aroundmine;
	for (i1 = 1; i1 <= gamespacex; i1++)
	{
		for (i2 = 1; i2 <= gamespacey; i2++)
		{
			if (space[i1][i2] == '*')
			{
				outputspace[i1][i2] = '.';
				numspace[i1][i2] = '*';
			}
			else if (space[i1][i2] == '.')
			{
				aroundmine = 0;
				for (p1 = -1; p1 <= 1; p1++)
				{
					for (p2 = -1; p2 <= 1; p2++)
					{
						if ((p1 != 0 || p2 != 0) && space[i1 + p1][i2 + p2] == '*')
							aroundmine += 1;
					}
				}
				numspace[i1][i2] = aroundmine + '0';
				outputspace[i1][i2] = '.';
			}
		}
	}
	return;
}

int operation(int operatype, int xspace, int yspace)
{
	if (operatype == 1)//左键点击
	{
		if (outputspace[xspace][yspace] != '.')
			return 0;
		if (numspace[xspace][yspace] == '0')
		{
			outputspace[xspace][yspace] = '0';
			openspace(xspace - 1, yspace - 1);

			int k1, k2;
			for (k1 = -1; k1 <= 1; k1++)
			{
				for (k2 = -1; k2 <= 1; k2++)
				{
					if (k1 != 0 || k2 != 0)
						operation(1, xspace + k1, yspace + k2);
				}
			}
			return 0;
		}
		else if (numspace[xspace][yspace] == '*')
		{
			//所有地雷所在位置输出"*"
			int k1, k2;
			for (k1 = 1; k1 <= gamespacex; k1++)
			{
				for (k2 = 1; k2 <= gamespacey; k2++)
				{
					if (space[k1][k2] == '*' && outputspace[k1][k2] == '.')
					{
						outputspace[k1][k2] = '*';
						openspace(k1 - 1, k2 - 1);
					}
				}
			}
			return -2;
		}
		else
		{
			outputspace[xspace][yspace] = numspace[xspace][yspace];
			openspace(xspace - 1, yspace - 1);
			return 0;
		}
	}
	else if (operatype == 2)//右键点击
	{
		if (outputspace[xspace][yspace] == '.')
		{
			outputspace[xspace][yspace] = '!';
			markmine(xspace - 1, yspace - 1);
			return 1;
		}
		else if (outputspace[xspace][yspace] == '!')
		{
			outputspace[xspace][yspace] = '?';
			markquestion(xspace - 1, yspace - 1);
			return -1;
		}
		else if (outputspace[xspace][yspace] == '?')
		{
			outputspace[xspace][yspace] = '.';
			unopenspace(xspace - 1, yspace - 1);
			return 0;
		}
	}
	else if (operatype == 3)//左右键（双击）
	{
		int minenow = 0;
		int k1, k2;
		if (outputspace[xspace][yspace] != '!' && outputspace[xspace][yspace] != '?')
		{
			for (k1 = -1; k1 <= 1; k1++)
			{
				for (k2 = -1; k2 <= 1; k2++)
					if (outputspace[xspace + k1][yspace + k2] == '!')
						minenow += 1;
			}
		}//统计周围标记雷的数量

		if (minenow + '0' == numspace[xspace][yspace])
		{
			for (k1 = -1; k1 <= 1; k1++)
			{
				for (k2 = -1; k2 <= 1; k2++)
				{
					if (outputspace[xspace + k1][yspace + k2] == '.' && space[xspace + k1][yspace + k2] == '*')
						return -2;
				}
			}
			for (k1 = -1; k1 <= 1; k1++)
			{
				for (k2 = -1; k2 <= 1; k2++)
				{
					if (outputspace[xspace + k1][yspace + k2] == '.')
						operation(LEFTCLICK, xspace + k1, yspace + k2);
				}
			}
			return 0;
		}
		else if (minenow + '0' != numspace[xspace][yspace])
			return 0;
	}
}
