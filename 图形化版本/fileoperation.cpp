#include "head.h"
#include <stdio.h>
#include <stdlib.h>

#include <graphics.h>
#include <conio.h>


#define EASY 1
#define MEDIUM 2
#define HARD 3
#define CUSTOMIZE 4

int fileoperation(int type, int inputminute, int inputsecond, int inputgamemode)
{
	FILE * fPtr;

	if (type == READ)
	{
		if (fopen_s(&fPtr, "C:\\Users\\Public\\Documents\\game.ini", "r") == 0)
		{
			cleardevice();

			int y = 80;
			const int x = 150;
			int minutes, seconds, gamemode;

			settextcolor(BLACK);
			settextstyle(30, 0, L"微软雅黑");
			int returnvalue = 0;

			outtextxy(x, y, L"最近的游戏记录：");
			y += 60;

			bool notreadanynum = true;

			while ((!feof(fPtr)) && y <= HEIGHT - 150 && returnvalue != EOF)
			{
				returnvalue = fscanf_s(fPtr, "%d%d%d", &minutes, &seconds, &gamemode);

				if (returnvalue != EOF)
				{
					notreadanynum = false;

					printnum(x, y, minutes);
					if (minutes < 10)
					{
						outtextxy(x + 25, y, L":");
						printnum(x + 50, y, seconds);
					}
					else if (minutes < 100)
					{
						outtextxy(x + 40, y, L":");
						printnum(x + 60, y, seconds);
					}
					else
					{
						outtextxy(x + 55, y, L":");
						printnum(x + 70, y, seconds);
					}

					if (gamemode == EASY)
						outtextxy(x + 200, y, L"简单模式");
					else if (gamemode == MEDIUM)
						outtextxy(x + 200, y, L"普通模式");
					else if (gamemode == HARD)
						outtextxy(x + 200, y, L"困难模式");
					else if (gamemode == CUSTOMIZE)
						outtextxy(x + 200, y, L"自定义模式");

					y += 50;
				}
				else
				{
					if (notreadanynum)
						outtextxy(x, y, L"未读取到记录。左键单击以返回");
					printf("EOF\n");
					break;
				}
			}
			if (!notreadanynum)
				outtextxy(x, y + 10, L"左键单击以返回");

			fclose(fPtr);

			ExMessage mouseclick;
			while (true)
			{
				mouseclick = getmessage(EX_MOUSE | EX_KEY);
				if (mouseclick.message == WM_LBUTTONDOWN)
				{
					break;
				}
			}
			return 0;
		}
		else
		{
			cleardevice();
			settextcolor(BLACK);
			settextstyle(30, 0, L"微软雅黑");

			outtextxy(150, 80, L"未读取到文件。左键单击以返回");
			outtextxy(150, 150, L"请创建文件“C:\\Users\\Public\\Documents\\game.ini”以继续");

			ExMessage mouseclick;
			while (true)
			{
				mouseclick = getmessage(EX_MOUSE | EX_KEY);
				if (mouseclick.message == WM_LBUTTONDOWN)
				{
					break;
				}
			}
			return 0;
		}
	}
	else if (type == WRITE)
	{
		if (fopen_s(&fPtr, "C:\\Users\\Public\\Documents\\game.ini", "r") == 0)
		{
			FILE* cachefileptr;
			if (fopen_s(&cachefileptr, "C:\\Users\\Public\\Documents\\cache.ini", "w") == 0)
			{
				fseek(cachefileptr, 0, SEEK_END);

				fprintf(cachefileptr, "%d %d %d\n", inputminute, inputsecond, inputgamemode);

				fseek(fPtr, 0, SEEK_SET);
				while (!feof(fPtr))
				{
					int returnvalue = fscanf_s(fPtr, "%d%d%d", &inputminute, &inputsecond, &inputgamemode);
					if (feof(fPtr)||returnvalue==EOF)
						break;
					fprintf(cachefileptr, "%d %d %d\n", inputminute, inputsecond, inputgamemode);
				}

				fclose(fPtr);
				fclose(cachefileptr);

				remove("C:\\Users\\Public\\Documents\\game.ini");
				if (rename("C:\\Users\\Public\\Documents\\cache.ini", "C:\\Users\\Public\\Documents\\game.ini") == 0)
				{
					printf("rename successfully done");
				}
				return -1;
			}
		}
		else
			return 1;
	}
}
