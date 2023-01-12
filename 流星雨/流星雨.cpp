

#include<stdio.h>
#include<graphics.h>		//easyX 库头文件：安装
#include<conio.h>			//_getch()
#include<math.h>
#include<Windows.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define PI 3.1415926535897932384624
#define MAXSTAR 1024	
#define MAXMETEOR 300

//定义图片变量
IMAGE img1, img2, img3;
//星星
struct Star
{
	int x, y;
	int speed;
	int color;
}star[MAXSTAR];
//流星
struct Meteor
{
	int x, y;
	int speed;
	int style;
}meteor[MAXMETEOR];
//初始化星星
void initStar(int i)
{
	star[i].x = rand() % 1500;
	star[i].y = rand() % 1000;
	star[i].speed = rand() % 8;
	star[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
}

//画星星并且移动星星
void drawAndMoveStar(int i)
{
	//画像素点
	putpixel(star[i].x, star[i].y, star[i].color);
	//移动
	star[i].x += star[i].speed;
	//移动到窗口外面
	if (star[i].x > 1500)
	{
		initStar(i);
		//画像素点
		putpixel(star[i].x, star[i].y, star[i].color);
	}
}

//初始化流星
void initMeteor(int i)
{
	meteor[i].x = rand() % 2200 - 1500;		//[0,2199]--->[-1500,1199]
	meteor[i].y = -400;
	meteor[i].speed = rand() % 40;
	meteor[i].style = rand() % 2;			//[0,1]
}

//画流星：显示图片过程
void drawMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		if (meteor[i].style == 0)
		{
			putimage(meteor[i].x, meteor[i].y, &img1, SRCPAINT);	//背景图
		}
		if (meteor[i].style == 1)
		{
			putimage(meteor[i].x, meteor[i].y, &img2, SRCPAINT);	//背景图
		}
	}
}

//移动流星
void moveMeteor(int i)
{
	for (i = 0; i < MAXMETEOR; i++)
	{
		meteor[i].x += meteor[i].speed;
		meteor[i].y += meteor[i].speed;
		//流星移到窗口外面
		if (meteor[i].x > 1500 || meteor[i].y > 1000)
		{
			initMeteor(i);
		}
	}
}

//文字输出
void textPrint()
{
	for (int i = 0; i < 60; i++)
	{
		cleardevice();
		settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		//圆心的位置：600，300   半径150   
		int x = 600 + int(150 * sin(PI * 2 * i / 60));
		int y = 300 + int(150 * cos(PI * 2 * i / 60));
		outtextxy(x - 50, y - 100, "两情若是久长时");
		settextstyle(i, 0, "华文新魏");
		outtextxy(x, y, "又岂在朝朝暮暮");
		Sleep(50);
	}
	Sleep(1000);
	cleardevice();
	settextcolor(YELLOW); 
	outtextxy(250, 100, "择一城终老  遇一人白首"); Sleep(2000);
	outtextxy(250, 200, "挽一帘幽梦  许一世倾城"); Sleep(2000);
	outtextxy(250, 300, "写一字决别  言一梦长眠"); Sleep(2000);
	outtextxy(250, 400, "我倾尽一生  囚你无期");   Sleep(2000);
	outtextxy(500, 500, "----------爱你的小孙同学");
	Sleep(4000);
	cleardevice();
}

int main()
{
	//加载图片
	loadimage(&img1, "1.jpg", 50, 50);
	loadimage(&img2, "2.jpg", 50, 50);
	srand((unsigned int)time(NULL));
	//创建一个图形窗口
	HWND hwnd;
	hwnd = initgraph(1500, 1000);
	ShowWindow(hwnd, 3);

	//播放音乐
	mciSendString("open 小幸运.mp3 alias MM", 0, 0, 0);
	mciSendString("play MM repeat", 0, 0, 0);

	//设置背景模式
	setbkmode(0);
	textPrint();
	int i;
	for (i = 0; i < MAXSTAR; i++)
	{
		initStar(i);
	}
	for (i = 0; i < MAXMETEOR; i++)
	{
		initMeteor(i);
	}
	while (1)
	{
		BeginBatchDraw();
		cleardevice();
		for (i = 0; i < MAXSTAR; i++)
		{
			drawAndMoveStar(i);
		}

		drawMeteor(i);
		moveMeteor(i);

		Sleep(100);
		EndBatchDraw();
	}
	_getch();		//为了防止闪屏
	//关闭图形环境
	closegraph();
	return 0;
}

