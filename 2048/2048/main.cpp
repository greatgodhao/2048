#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <easyx.h>
#include <time.h>
#define MAX_GRID 4 //每行格子数
#define GRID_WIDTH 100 //格子宽度
#define INTERVAL 15 //间隔

enum Color //枚举格子颜色
{
	zero = RGB(205, 193, 180),
	twoTo1 = RGB(238, 228, 218),
	twoTo2 = RGB(237, 224, 200),
	twoTo3 = RGB(242, 177, 121),
	twoTo4 = RGB(245, 149, 99),
	twoTo5 = RGB(246, 124, 95),
	twoTo6 = RGB(246, 94, 59),
	twoTo7 = RGB(242, 177, 121),
	twoTo8 = RGB(237, 204, 97),
	twoTo9 = RGB(255, 0, 128),
	twoTo10 = RGB(145, 0, 72),
	twoTo11 = RGB(242, 17, 158),
	back = RGB(187, 173, 160),
};
Color arr[13] = { zero, twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6, twoTo7, twoTo8, twoTo9, twoTo10, twoTo11, back };
int num[12] = { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int map[MAX_GRID][MAX_GRID];
POINT pos[MAX_GRID][MAX_GRID];
bool flag = false;

int towOrFour()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}

void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0)
		{
			map[x][y] = towOrFour();
			break;
		}
	}
}

void GameInit()
{
	//设置随机数种子
	srand(time(NULL));
	//计算格子坐标
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			printf("%d %d\n", i, k);
			pos[i][k].x = k * GRID_WIDTH + (k + 1) * INTERVAL;
			pos[i][k].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
		}
	}
	//随机生成两个数
	CreateNumber();
	CreateNumber();
}

void GameDraw()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			for (int q = 0; q < 12; q++)
			{
				if (map[i][k] == num[q])
				{
					//判断map值是多少
					setfillcolor(arr[q]);
					solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_WIDTH);
					if (map[i][k] != 0)
					{
						char number[5] = " ";
						settextcolor(RGB(119, 110, 101));
						settextstyle(50, 0, "楷体");
						setbkmode(TRANSPARENT);
						sprintf(number, "%d", map[i][k]);
						
						int tempx = GRID_WIDTH / 2 - textwidth(number) / 2;
						int tempy = GRID_WIDTH / 2 - textheight(number) / 2;
						outtextxy(pos[i][k].x + tempx, pos[i][k].y + tempy, number);
					}
				}
			}
			
		}
	}
}

void moveup()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int j = 1; j < MAX_GRID; j++)
		{
			if (map[j][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[j][i];
					map[j][i] = 0;
				}
				else if (map[temp][i] == map[j][i])
				{
					map[temp][i] += map[j][i];
					map[j][i] = 0;
				}
				else
				{
					map[temp + 1][i] = map[j][i];
					if (temp + 1 != j)
					{
						map[j][i] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("up\n");
}
//下移
void movedown()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID - 1;
		for (int j = MAX_GRID - 2; j >= 0; j--)
		{
			if (map[j][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[j][i];
					map[j][i] = 0;
				}
				else if (map[temp][i] == map[j][i])
				{
					map[temp][i] += map[j][i];
					map[j][i] = 0;
				}
				else
				{
					map[temp - 1][i] = map[j][i];
					if (temp - 1 != j)
					{
						map[j][i] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("down\n");
}
//左移
void moveleft()
{
	for (int j = 0; j < MAX_GRID; j++)
	{
		int temp = 0;
		for (int i = 1; i < MAX_GRID; i++)
		{
			if (map[j][i] != 0)
			{
				if (map[j][temp] == 0)
				{
					map[j][temp] = map[j][i];
					map[j][i] = 0;
				}
				else if (map[j][temp] == map[j][i])
				{
					map[j][temp] += map[j][i];
					map[j][i] = 0;
				}
				else
				{
					map[j][temp + 1] = map[j][i];
					if (temp + 1 != i)
					{
						map[j][i] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("left\n");
}
//右移
void moveright()
{
	for (int j = 0; j < MAX_GRID; j++)
	{
		int temp = MAX_GRID - 1;
		for (int i = MAX_GRID - 2; i >= 0; i--)
		{
			if (map[j][i] != 0)
			{
				if (map[j][temp] == 0)
				{
					map[j][temp] = map[j][i];
					map[j][i] = 0;
				}
				else if (map[j][temp] == map[j][i])
				{
					map[j][temp] += map[j][i];
					map[j][i] = 0;
				}
				else
				{
					map[j][temp - 1] = map[j][i];
					if (temp - 1 != i)
					{
						map[j][i] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("right\n");
}

void GameJude()
{
	if (flag)
	{
		CreateNumber();
		flag = false;
	}
}

//键盘控制数字移动
void GameContorl()
{
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		moveup();
		
		break;
	case 's':
	case 'S':
	case 80:
		movedown();
		break;
	case 'a':
	case 'A':
	case 75:
		moveleft();
		break;
	case 'd':
	case 'D':
	case 77:
		moveright();
		break;
	}
}

int main()
{
	initgraph(MAX_GRID * GRID_WIDTH + 5 * INTERVAL, MAX_GRID * GRID_WIDTH + 5 * INTERVAL);
	setbkcolor(back);
	cleardevice();
	GameInit();
	while(1)
	{
		GameDraw();
		GameContorl();
		GameJude();
	}
	
	return 0;
}