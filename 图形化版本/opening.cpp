#include <stdio.h>
#include <string.h>
#include <time.h>
#include "head.h"

#include <graphics.h>
#include <conio.h>

#include <iostream>
#include <thread>//多线程
#include <chrono>//计时器

int opening()
{
	setlinecolor(BLACK);
	settextcolor(BLACK);
	settextstyle(60, 0, L"微软雅黑");
	//开始游戏
	//设置参数
	//查看记录
	//	退出
	for (int i = 1; i <= 3; i++)
	{
		rectangle(510, 100 * i, 770, 100 * i + 80);
	}
	outtextxy(550, 110, L"开始游戏");
	outtextxy(550, 210, L"查看记录");
	outtextxy(572, 310, L"  退出  ");
	ExMessage msg;
	while (1)
	{
		msg = getmessage();
		if (msg.message == WM_LBUTTONDOWN)
		{
			int x = msg.x;
			int y = msg.y;
			if (x >= 510 && x <= 770)
			{
				if (y > 100 && y < 180)	//开始游戏
				{
					return 1;
				}
				else if (y > 200 && y < 280)	//查看记录
				{
					return 2;
				}
				else if (y > 300 && y < 380)	//退出游戏
				{					
					return 3;
				}
			}
		}
	}
}

JUDGE setting(int flag)
{
	JUDGE game;

	cleardevice();
	if (flag == 1)
	{
		setlinecolor(BLACK);
		settextcolor(BLACK);
		settextstyle(60, 0, L"微软雅黑");
		//初级
		//中级
		//高级
		//自定义
		for (int i = 1; i <= 4; i++)
		{
			rectangle(510, 100 * i, 770, 100 * i + 80);
		}
		outtextxy(600, 110, L"初级");
		outtextxy(600, 210, L"中级");
		outtextxy(600, 310, L"高级");
		outtextxy(572, 410, L"自定义");
		ExMessage msg;
		while (1)
		{
			msg = getmessage();
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x >= 510 && x <= 770)
				{
					if (y > 100 && y < 180)	//初级
					{
						game.spacex = 9;
						game.spacey = 9;
						game.mine = 10;
						game.gamemode = 1;
						return game;
					}
					else if (y > 200 && y < 280)	//中级
					{
						game.spacex = 16;
						game.spacey = 16;
						game.mine = 40;
						game.gamemode = 2;
						return game;
					}
					else if (y > 300 && y < 380)	//高级
					{
						game.spacex = 30;
						game.spacey = 24;
						game.mine = 99;
						game.gamemode = 3;
						return game;
					}
					else if (y > 400 && y < 480)	//自定义
					{
						game = Textbox();
						game.gamemode = 4;
						return game;
					}
				}
			}
		}
	}
}
