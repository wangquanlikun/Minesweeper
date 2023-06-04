#include <graphics.h>
#include <conio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string>
#include"head.h"
#include <iostream>



void Creat(int x1, int y1, int x2, int y2, wchar_t* text)
{
	setlinecolor(LIGHTGRAY);		// 设置画线颜色
	setbkcolor(WHITE);			// 设置背景颜色
	setfillcolor(WHITE);			// 设置填充颜色
	fillrectangle(x1, y1, x2, y2);
	if (*text == NULL)
	{
	}
	else
	{
		outtextxy(x1 + 10, y1 + 5, text);
	}

}

wchar_t* onMessage(int x1, int y1, int x2, int y2, wchar_t* text)
{

	setlinecolor(BLACK);			// 设置画线颜色
	setbkcolor(WHITE);				// 设置背景颜色
	setfillcolor(WHITE);			// 设置填充颜色
	fillrectangle(x1, y1, x2, y2);
	outtextxy(x1 + 10, y1 + 5, text);

	int width = 0;
	width = textwidth(text);	// 字符串总宽度
	int counter = 0;				// 光标闪烁计数器
	bool binput = true;				// 是否输入中

	ExMessage msg;
	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))	// 获取消息，但不从消息队列拿出
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				// 如果鼠标点击文本框外面，结束文本输入
				if (msg.x < x1 || msg.x > x2 || msg.y < y1 || msg.y > y2)
				{
					binput = false;
					break;
				}
			}
			else if (msg.message == WM_CHAR)
			{
				size_t len = wcslen(text);
				if (msg.ch == '\b')
				{
					if (len > 0)
					{
						*(text + len - 1) = 0;
						width = textwidth(text);
						counter = 0;
						clearrectangle(x1 + 10 + width, y1 + 1, x2 - 1, y2 - 1);
					}
				}
				else if (msg.ch == '\r')
				{
					binput = false;
					break;
				}
				else
					if (len < 10)
					{
						text[len++] = msg.ch;
						text[len] = 0;

						clearrectangle(x1 + 10 + width + 1, y1 + 3, x2 - 2, y2 - 3);	// 清除画的光标
						width = textwidth(text);
						counter = 0;
						outtextxy(x1 + 10, y1 + 5, text);
					}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR);
		}

		counter = (counter + 1) % 32;
		if (counter < 16)
		{
			line(x1 + 10 + width + 1, y1 + 3, x1 + 10 + width + 1, y2 - 3);
		}
		else
		{
			clearrectangle(x1 + 10 + width + 1, y1 + 3, x2 - 1, y2 - 3);
		}

		Sleep(20);
	}
	clearrectangle(x1, y1, x2, y2);
	Creat(x1, y1, x2, y2, text);
	return text;
}

JUDGE Textbox()
{
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 1);
	JUDGE a;
	JUDGE b;
	int i;
	for (i = 0; i < 10; i++)
	{
		a.line[i] = { '\0' };
		a.row[i] = { '\0' };
		a.minetext[i] = { '\0' };
	}
	wchar_t* line = a.line;
	wchar_t* row = a.row;
	wchar_t* minetext = a.minetext;

	wchar_t* start = b.line;
	settextstyle(45, 0, L"微软雅黑");
	cleardevice();
	setbkcolor(0xE7EFDE);
	settextcolor(BLACK);
	outtextxy(265, 145, L"行数:");
	Creat(350, 140, 900, 200, line);
	outtextxy(265, 285, L"列数:");
	Creat(350, 280, 900, 340, row);
	outtextxy(265, 425, L"雷数:");
	Creat(350, 420, 900, 480, minetext);

	Creat(545, 555, 690, 610, start);
	outtextxy(550, 560, L"开始游戏");


	ExMessage msg;
	while (true)
	{
		msg = getmessage(EX_MOUSE | EX_CHAR);
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 350 && msg.x <= 900 && msg.y >= 140 && msg.y <= 200)
			{
				onMessage(350, 140, 900, 200, line);
			}
			if (msg.x >= 350 && msg.x <= 900 && msg.y >= 280 && msg.y <= 340)
			{
				onMessage(350, 280, 900, 340, row);
			}
			if (msg.x >= 350 && msg.x <= 900 && msg.y >= 420 && msg.y <= 480)
			{
				onMessage(350, 420, 900, 480, minetext);
			}
			if (msg.x >= 545 && msg.x <= 690 && msg.y >= 555 && msg.y <= 610)
			{
				a.mine = 0;
				a.spacex = 0;
				a.spacey = 0;
				a.spacex = transport(a.line);
				a.spacey = transport(a.row);
				a.mine = transport(a.minetext);
				if (a.spacex > 24)
				{
					HWND hWnd = GetForegroundWindow();
					MessageBox(hWnd, L"行数超限", L"参数错误", MB_OK | MB_ICONERROR);
				}
				else if (a.spacey > 30)
				{
					HWND hWnd = GetForegroundWindow();
					MessageBox(hWnd, L"列数超限", L"参数错误", MB_OK | MB_ICONERROR);
				}
				else if (a.mine > a.spacex * a.spacey * 75 / 100)
				{
					HWND hWnd = GetForegroundWindow();
					MessageBox(hWnd, L"雷数超限", L"参数错误", MB_OK | MB_ICONERROR);
				}
				else if (a.mine == 0 || a.spacex == 0 || a.spacey == 0)
				{
					HWND hWnd = GetForegroundWindow();
					MessageBox(hWnd, L"输入不能为零", L"参数错误", MB_OK | MB_ICONERROR);
				}
				else
				{
					cleardevice();
					return a;
				}

			}
		}
	}
}

int transport(wchar_t* ch)
{
	char ch1[10];
	ch1[0] = ch[0];
	ch1[1] = ch[1];
	ch1[2] = ch[2];
	ch1[3] = ch[3];
	int n = 0;
	n = atoi(ch1);
	return n;
}
