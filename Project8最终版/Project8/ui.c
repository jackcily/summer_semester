#include <windows.h>
#include "mmsystem.h"
#include "game.h"
#include "stack.h"

#pragma comment(lib, "winmm.lib")
#define CELL_PIXEL			20// 画图时使用的直径像素点个数。
#define COLOR_BOUNDARY		RGB(139, 134, 130)// 用来绘图的颜色
#define MAX_X		20// 游戏界面大小//设置的游戏界面的大小
#define MAX_Y		20// 游戏界面大小

HINSTANCE hinst; /// HINSTANCE是用来表示程序运行实例的句柄，某些API函数会使用到这个变量。
RECT rectBoundary;
HBITMAP hbmpBackground1;//用于绘制背景
HBITMAP hbmpBackground2;//用于绘制背景
HBITMAP hbmpBackground3;//用于绘制背景
HBITMAP hbmpBackground4;//用于绘制背景
HBITMAP hbmpBackground5;//用于绘制背景
HBITMAP hbmpBackground6;//用于绘制背景
HBITMAP hbmpFighter0;//用于绘制飞机
HBITMAP hbmpFighter1;//用于绘制飞机
HBITMAP hbmpFighter2;//用于绘制飞机
HBITMAP hbmpFighter3;//用于绘制飞机
HBITMAP hbmpFighter4;//用于绘制飞机
HBITMAP hbmpFighter5;//用于绘制飞机
INT flag = 0;
INT menu;//用于判断程序是否处于菜单栏状态
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,  int nCmdShow) 
{
	WNDCLASS wc;
	HWND hwnd;// 窗口句柄，hwnd变量是主窗口的句柄，这个程序中只用到了一个窗口。
	MSG msg;
	int fGotMessage;
	hinst = hinstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,	IDC_CROSS);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = "MainMenu";
	wc.lpszClassName = "MainWClass";
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "创建窗口class失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	//创建窗口时会触发事件   在绘制窗口之前首先会进入   那个事件   去处理绘制窗口之前的事件
	hwnd = CreateWindow("MainWClass",				"Pop Star!!",	
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,//固定窗口大小
		CW_USEDEFAULT,			// 窗口水平位置default horizontal POINT 
		CW_USEDEFAULT,			// 窗口垂直位置default vertical POINT 
		CW_USEDEFAULT,			// 窗口宽度 default width 
		CW_USEDEFAULT,			// 窗口高度 default height 
		(HWND)NULL,				// 父窗口句柄 no owner window 
		(HMENU)NULL,			// 窗口菜单的句柄 use class menu 
		hinstance,				// 应用程序实例句柄 handle to application instance 
		(LPVOID)NULL);			// 指向附加数据的指针 no window-creation data 
	if (!hwnd)
	{
		MessageBox(NULL, "创建窗口失败", "错误！", MB_ICONERROR | MB_OK);
		return -1;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	mciSendString("close back.mp3", 0, 0, 0);
	mciSendString("play back.mp3", NULL, NULL, NULL);
	mciSendString(L"play back repeat", NULL, 0, NULL);
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0	&& fGotMessage != -1)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//用于显示各种图片
void GamePaint2(HWND hwnd,int x)
{
	HDC hdc, hdcmem;
	HBITMAP hbmMem;
    BITMAP bmp;
    RECT rect;
	GetClientRect(hwnd, &rect);
	hdc = GetDC(hwnd);
	hdcmem = CreateCompatibleDC(hdc);
	hbmMem = CreateCompatibleBitmap(hdc,rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));//画背景
	  if (x == 1)
	  {
		  SelectObject(hdcmem, hbmpBackground1);
		  GetObject(hbmpBackground1, sizeof(BITMAP), &bmp);
	  }
	  else if (x == 2)
	  {
		  SelectObject(hdcmem, hbmpBackground2);
		  GetObject(hbmpBackground2, sizeof(BITMAP), &bmp);
	  }
	  else if (x == 3)
	  {
		  SelectObject(hdcmem, hbmpBackground3);
		  GetObject(hbmpBackground3, sizeof(BITMAP), &bmp);
	  }
	  else if (x == 4)
	  {
		  SelectObject(hdcmem, hbmpBackground4);
		  GetObject(hbmpBackground3, sizeof(BITMAP), &bmp);
	  }
	  else if (x == 5)
	  {
		  SelectObject(hdcmem, hbmpBackground5);
		  GetObject(hbmpBackground5, sizeof(BITMAP), &bmp);
	  }
	  else if (x == 6)
	  {
		  SelectObject(hdcmem, hbmpBackground6);
		  GetObject(hbmpBackground6, sizeof(BITMAP), &bmp);
	  }
	BitBlt(hdc, 10, 10, rect.right - rect.left, rect.bottom - rect.top, hdcmem, 0, 0, SRCCOPY);
	//回收资源   释放占用的DC等资源
	DeleteObject(hbmMem);
	DeleteObject(hdcmem);
	ReleaseDC(hwnd, hdc);
}
int hbmpFighterInit()
{
	hbmpFighter0 = LoadImage(NULL, "red.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpFighter1 = LoadImage(NULL, "blue.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpFighter2 = LoadImage(NULL, "green.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpFighter3 = LoadImage(NULL, "yellow.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpFighter4 = LoadImage(NULL, "purple.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpFighter5 = LoadImage(NULL, "b4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmpBackground1 = LoadImage(NULL, BITMAP_FILE_BK, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是 1 就是切换关卡的图片
	hbmpBackground2 = LoadImage(NULL, BITMAP_FILE_BK2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是2 就是开始的关卡
	hbmpBackground3 = LoadImage(NULL, BITMAP_FILE_BK3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是3 就是菜单的关卡
	hbmpBackground4= LoadImage(NULL, BITMAP_FILE_BK4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是3 就是菜单的关卡
	hbmpBackground5 = LoadImage(NULL, BITMAP_FILE_BK5, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是3 就是菜单的关卡
	hbmpBackground6 = LoadImage(NULL, BITMAP_FILE_BK6, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//如果是3 就是菜单的关卡
	return 1;
}
void GamePaint(HWND hwnd)
{
	HPEN hpen;
	HDC hdc, hdcmem, hdcBitmapSrc;
	HBITMAP hbmMem;	
	BITMAP bmp;
	HPEN hPenBoundary;
	HFONT hFont, hOldFont;
	RECT rect;
	int i, j;

	GetClientRect(hwnd, &rect);
     hdc = GetDC(hwnd); 
	hdcmem = CreateCompatibleDC(hdc);//一个是创建dc
	hbmMem = CreateCompatibleBitmap(hdc,//一个是创建位图
	rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);//选入失败
	hpen = CreatePen(PS_NULL, 0, RGB(90, 90, 90));  // PEN， PS_NULL表示不可见
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	 (HPEN)SelectObject(hdcmem, hpen);
	 hdcBitmapSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmapSrc, hbmpFighter0);
	 GetObject(hbmpFighter0, sizeof(BITMAP), &bmp);
	 FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH)); // 画背景
	for (j= 0; j < 10; j++)//画方格  画出所有的星星  后期只要再改变笔刷就行了
	{
    for (i= 0; i < 10; i++)
	{
		if (StarMap[i][j] == 0)		SelectObject(hdcBitmapSrc, hbmpFighter0);
		else if (StarMap[i][j] == 1)		SelectObject(hdcBitmapSrc, hbmpFighter1);
		else if (StarMap[i][j] == 2)   SelectObject(hdcBitmapSrc, hbmpFighter2);
		else if (StarMap[i][j] == 3)	SelectObject(hdcBitmapSrc, hbmpFighter3);
		else if (StarMap[i][j] == 4)	SelectObject(hdcBitmapSrc, hbmpFighter4);
		else if (StarMap[i][j] == 5)    SelectObject(hdcBitmapSrc, hbmpFighter5);
	StretchBlt(hdcmem,rectBoundary.left + j*CELL_PIXEL * 2, rectBoundary.top + i*CELL_PIXEL * 2, 40, 40,	hdcBitmapSrc,0, 0, bmp.bmWidth, bmp.bmHeight,SRCCOPY);
	}
}
	SelectObject(hdcmem, hPenBoundary);//	 将PEN移动到需要绘制的方框的左上角
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);//	 画了一个方框。演示LineTo函数
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);
	//	 创建了一个字体对象
	hFont = CreateFont(25, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))	// 将这个FONT对象放入DC中
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "Goal %d Score %d Level %d", GetLevelScore(),score,level);
		SetTextColor(hdcmem, COLOR_TEXT);	//	 设置输出颜色
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,	szSourceInfo, lstrlen(szSourceInfo));	//	 输出字符串。
		SelectObject(hdcmem, hOldFont);//	 输出完成，将原来的字体对象放回DC中
	}
	BitBlt(hdc,rect.left, rect.top,	rect.right - rect.left, rect.bottom - rect.top,	hdcmem,	0, 0,	SRCCOPY);
	DeleteObject(hbmMem);  //   回收资源
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hdcBitmapSrc);
	ReleaseDC(hwnd, hdc);	//释放占用的DC等资源
}
 ///根据游戏界面的坐标系大小设置游戏窗口大小    
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// 左上角
	POINT ptRightBottom;	// 右下角
	RECT rectWindow;
	POINT* pCoordBoundary = GetBoundary();
	rectBoundary.left = 10;// 设置游戏边界
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x );
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y );
	ptLeftTop.x = rectBoundary.left;// 计算上下左右角的位置
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);//取得相对整个屏幕的坐标
	ClientToScreen(hwnd, &ptRightBottom);
	GetWindowRect(hwnd, &rectWindow);
	// 计算好了，设置窗口大小。
	MoveWindow(hwnd,  	rectWindow.left,rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left,//同时向左移一定的空间   同时减去一个值
	  rectBoundary.bottom+120, //给积分信息留出显示空间。   //没有改变窗口的大小只是改变了窗口的相对位置
		TRUE);
}
LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch (msg)
	{
	// 当窗口被创建时，收到的第一个消息就是WM_CREATE，一般收到这个消息处理过程中，可以用来进行一些初始化的工作
	case WM_CREATE:
		SetBoundary();
		InitGame();
		InitLevel();
		InitMenu();//把菜单设为初始值
		InitStarmap(GetColorNum());//初始化迷宫
		ReSizeGameWnd(hwnd);
		hbmpFighterInit();//初始化画图操作
		break;
	case WM_PAINT:
		if (menu == 0)
		{//处于菜单栏状态
			GamePaint2(hwnd,2);
		}
		else if (menu == 1)
		{
             GamePaint(hwnd);	
		 }
		else if (menu == 2)
		{//帮助栏
			GamePaint2(hwnd,3);
		}
	      break;
	case WM_LBUTTONDOWN:	//当鼠标左键击中窗口  触发该事件
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (menu==1)	
		{//开始游戏
				if (JudgeSeat(pt))
				{
	            GetSeat(&pt);//首先先判断坐标是否有效
				if (RemoveStar(pt))   //进行星星消除判断
				{
					  PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\touch.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				AddScore(NumOfStar);//对消除的星星进行加分	
				if (ChangeSit())  Sleep(50000);
				GamePaint(hwnd);//重绘
				if (CloseStar())	 Sleep(30000);
				GamePaint(hwnd);//重绘
				if (isWin())//判断是否已经赢了
				{
					AddLevel();
					if (level > 6)
					{
						GamePaint2(hwnd, 4);
						Sleep(800);
						ExitProcess(0);
					}
					else
					{
						GamePaint2(hwnd, 1);
						InitGame();
						InitStarmap(GetColorNum());//初始化迷宫
						menu = 3;
					}
				}
				if (isDead() == 0 && isWin() == 0)
				{//如果没赢的话就判断游戏是否已经结束
					if (level == 1)
					{
						GamePaint2(hwnd, 5);
					}
					else GamePaint2(hwnd, 6);
					Sleep(800);
					ExitProcess(0);
				}
			}
		}		
	else  if(menu==0)//主菜单栏
		{
			if (Judge(pt) == 1)
			{//开始执行游戏	
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				GamePaint(hwnd);
				menu = 1;
			}
			else if (Judge(pt) == 2)
			{//进入游戏帮助
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				menu = 2;
				GamePaint2(hwnd,3);//游戏帮助界面
			}
			else if(Judge(pt)==3)//退出游戏
				ExitProcess(0);
		}
		else if (menu == 2)//帮助菜单
		{
			if (JudgeForHelp(pt) == 1)
			{
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				menu = 0;
				GamePaint2(hwnd, 2);
			}
		}
		else if (menu == 3)
		{//画出关卡   进行相应的处理  
			if (JudgeForSwitch(pt) == 1)//进入下一关
			{
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				GamePaint(hwnd);
				menu = 1;
			}
			else if (JudgeForSwitch(pt) == 2)//退出关卡
			{
				ExitProcess(0);
			}
		}
       break;
	case WM_DESTROY:
	   ExitProcess(0);
		break;
	default:
		break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
