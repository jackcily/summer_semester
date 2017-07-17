#include <windows.h>
#include "mmsystem.h"
#include "game.h"
#include "stack.h"

#pragma comment(lib, "winmm.lib")
#define CELL_PIXEL			20// ��ͼʱʹ�õ�ֱ�����ص������
#define COLOR_BOUNDARY		RGB(139, 134, 130)// ������ͼ����ɫ
#define MAX_X		20// ��Ϸ�����С//���õ���Ϸ����Ĵ�С
#define MAX_Y		20// ��Ϸ�����С

HINSTANCE hinst; /// HINSTANCE��������ʾ��������ʵ���ľ����ĳЩAPI������ʹ�õ����������
RECT rectBoundary;
HBITMAP hbmpBackground1;//���ڻ��Ʊ���
HBITMAP hbmpBackground2;//���ڻ��Ʊ���
HBITMAP hbmpBackground3;//���ڻ��Ʊ���
HBITMAP hbmpBackground4;//���ڻ��Ʊ���
HBITMAP hbmpBackground5;//���ڻ��Ʊ���
HBITMAP hbmpBackground6;//���ڻ��Ʊ���
HBITMAP hbmpFighter0;//���ڻ��Ʒɻ�
HBITMAP hbmpFighter1;//���ڻ��Ʒɻ�
HBITMAP hbmpFighter2;//���ڻ��Ʒɻ�
HBITMAP hbmpFighter3;//���ڻ��Ʒɻ�
HBITMAP hbmpFighter4;//���ڻ��Ʒɻ�
HBITMAP hbmpFighter5;//���ڻ��Ʒɻ�
INT flag = 0;
INT menu;//�����жϳ����Ƿ��ڲ˵���״̬
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,  int nCmdShow) 
{
	WNDCLASS wc;
	HWND hwnd;// ���ھ����hwnd�����������ڵľ�������������ֻ�õ���һ�����ڡ�
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
		MessageBox(NULL, "��������classʧ��", "����", MB_ICONERROR | MB_OK);
		return -1;
	}
	//��������ʱ�ᴥ���¼�   �ڻ��ƴ���֮ǰ���Ȼ����   �Ǹ��¼�   ȥ������ƴ���֮ǰ���¼�
	hwnd = CreateWindow("MainWClass",				"Pop Star!!",	
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME,//�̶����ڴ�С
		CW_USEDEFAULT,			// ����ˮƽλ��default horizontal POINT 
		CW_USEDEFAULT,			// ���ڴ�ֱλ��default vertical POINT 
		CW_USEDEFAULT,			// ���ڿ�� default width 
		CW_USEDEFAULT,			// ���ڸ߶� default height 
		(HWND)NULL,				// �����ھ�� no owner window 
		(HMENU)NULL,			// ���ڲ˵��ľ�� use class menu 
		hinstance,				// Ӧ�ó���ʵ����� handle to application instance 
		(LPVOID)NULL);			// ָ�򸽼����ݵ�ָ�� no window-creation data 
	if (!hwnd)
	{
		MessageBox(NULL, "��������ʧ��", "����", MB_ICONERROR | MB_OK);
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
//������ʾ����ͼƬ
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
	FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));//������
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
	//������Դ   �ͷ�ռ�õ�DC����Դ
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
	hbmpBackground1 = LoadImage(NULL, BITMAP_FILE_BK, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//����� 1 �����л��ؿ���ͼƬ
	hbmpBackground2 = LoadImage(NULL, BITMAP_FILE_BK2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����2 ���ǿ�ʼ�Ĺؿ�
	hbmpBackground3 = LoadImage(NULL, BITMAP_FILE_BK3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����3 ���ǲ˵��Ĺؿ�
	hbmpBackground4= LoadImage(NULL, BITMAP_FILE_BK4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����3 ���ǲ˵��Ĺؿ�
	hbmpBackground5 = LoadImage(NULL, BITMAP_FILE_BK5, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����3 ���ǲ˵��Ĺؿ�
	hbmpBackground6 = LoadImage(NULL, BITMAP_FILE_BK6, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//�����3 ���ǲ˵��Ĺؿ�
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
	hdcmem = CreateCompatibleDC(hdc);//һ���Ǵ���dc
	hbmMem = CreateCompatibleBitmap(hdc,//һ���Ǵ���λͼ
	rect.right - rect.left, rect.bottom - rect.top);
	SelectObject(hdcmem, hbmMem);//ѡ��ʧ��
	hpen = CreatePen(PS_NULL, 0, RGB(90, 90, 90));  // PEN�� PS_NULL��ʾ���ɼ�
	hPenBoundary = CreatePen(0, 3, COLOR_BOUNDARY);
	 (HPEN)SelectObject(hdcmem, hpen);
	 hdcBitmapSrc = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmapSrc, hbmpFighter0);
	 GetObject(hbmpFighter0, sizeof(BITMAP), &bmp);
	 FillRect(hdcmem, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH)); // ������
	for (j= 0; j < 10; j++)//������  �������е�����  ����ֻҪ�ٸı��ˢ������
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
	SelectObject(hdcmem, hPenBoundary);//	 ��PEN�ƶ�����Ҫ���Ƶķ�������Ͻ�
	MoveToEx(hdcmem, rectBoundary.left, rectBoundary.top, NULL);//	 ����һ��������ʾLineTo����
	LineTo(hdcmem, rectBoundary.left, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.bottom);
	LineTo(hdcmem, rectBoundary.right, rectBoundary.top);
	LineTo(hdcmem, rectBoundary.left, rectBoundary.top);
	//	 ������һ���������
	hFont = CreateFont(25, 0, 0, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Consolas"));
	if (hOldFont = (HFONT)SelectObject(hdcmem, hFont))	// �����FONT�������DC��
	{
		CHAR szSourceInfo[1024];
		wsprintf(szSourceInfo, "Goal %d Score %d Level %d", GetLevelScore(),score,level);
		SetTextColor(hdcmem, COLOR_TEXT);	//	 ���������ɫ
		TextOut(hdcmem, rectBoundary.left + 3, rectBoundary.bottom + 3,	szSourceInfo, lstrlen(szSourceInfo));	//	 ����ַ�����
		SelectObject(hdcmem, hOldFont);//	 �����ɣ���ԭ�����������Ż�DC��
	}
	BitBlt(hdc,rect.left, rect.top,	rect.right - rect.left, rect.bottom - rect.top,	hdcmem,	0, 0,	SRCCOPY);
	DeleteObject(hbmMem);  //   ������Դ
	DeleteObject(hdcmem);
	DeleteObject(hpen);
	DeleteObject(hPenBoundary);
	DeleteObject(hFont);
	DeleteObject(hdcBitmapSrc);
	ReleaseDC(hwnd, hdc);	//�ͷ�ռ�õ�DC����Դ
}
 ///������Ϸ���������ϵ��С������Ϸ���ڴ�С    
void ReSizeGameWnd(HWND hwnd)
{
	POINT ptLeftTop;		// ���Ͻ�
	POINT ptRightBottom;	// ���½�
	RECT rectWindow;
	POINT* pCoordBoundary = GetBoundary();
	rectBoundary.left = 10;// ������Ϸ�߽�
	rectBoundary.top = 10;
	rectBoundary.right = 10 + CELL_PIXEL*(pCoordBoundary->x );
	rectBoundary.bottom = 10 + CELL_PIXEL*(pCoordBoundary->y );
	ptLeftTop.x = rectBoundary.left;// �����������ҽǵ�λ��
	ptLeftTop.y = rectBoundary.top;
	ptRightBottom.x = rectBoundary.right;
	ptRightBottom.y = rectBoundary.bottom;
	ClientToScreen(hwnd, &ptLeftTop);//ȡ�����������Ļ������
	ClientToScreen(hwnd, &ptRightBottom);
	GetWindowRect(hwnd, &rectWindow);
	// ������ˣ����ô��ڴ�С��
	MoveWindow(hwnd,  	rectWindow.left,rectWindow.top,
		ptLeftTop.x - rectWindow.left + ptRightBottom.x - rectWindow.left,//ͬʱ������һ���Ŀռ�   ͬʱ��ȥһ��ֵ
	  rectBoundary.bottom+120, //��������Ϣ������ʾ�ռ䡣   //û�иı䴰�ڵĴ�Сֻ�Ǹı��˴��ڵ����λ��
		TRUE);
}
LONG CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch (msg)
	{
	// �����ڱ�����ʱ���յ��ĵ�һ����Ϣ����WM_CREATE��һ���յ������Ϣ��������У�������������һЩ��ʼ���Ĺ���
	case WM_CREATE:
		SetBoundary();
		InitGame();
		InitLevel();
		InitMenu();//�Ѳ˵���Ϊ��ʼֵ
		InitStarmap(GetColorNum());//��ʼ���Թ�
		ReSizeGameWnd(hwnd);
		hbmpFighterInit();//��ʼ����ͼ����
		break;
	case WM_PAINT:
		if (menu == 0)
		{//���ڲ˵���״̬
			GamePaint2(hwnd,2);
		}
		else if (menu == 1)
		{
             GamePaint(hwnd);	
		 }
		else if (menu == 2)
		{//������
			GamePaint2(hwnd,3);
		}
	      break;
	case WM_LBUTTONDOWN:	//�����������д���  �������¼�
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (menu==1)	
		{//��ʼ��Ϸ
				if (JudgeSeat(pt))
				{
	            GetSeat(&pt);//�������ж������Ƿ���Ч
				if (RemoveStar(pt))   //�������������ж�
				{
					  PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\touch.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				AddScore(NumOfStar);//�����������ǽ��мӷ�	
				if (ChangeSit())  Sleep(50000);
				GamePaint(hwnd);//�ػ�
				if (CloseStar())	 Sleep(30000);
				GamePaint(hwnd);//�ػ�
				if (isWin())//�ж��Ƿ��Ѿ�Ӯ��
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
						InitStarmap(GetColorNum());//��ʼ���Թ�
						menu = 3;
					}
				}
				if (isDead() == 0 && isWin() == 0)
				{//���ûӮ�Ļ����ж���Ϸ�Ƿ��Ѿ�����
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
	else  if(menu==0)//���˵���
		{
			if (Judge(pt) == 1)
			{//��ʼִ����Ϸ	
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				GamePaint(hwnd);
				menu = 1;
			}
			else if (Judge(pt) == 2)
			{//������Ϸ����
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				menu = 2;
				GamePaint2(hwnd,3);//��Ϸ��������
			}
			else if(Judge(pt)==3)//�˳���Ϸ
				ExitProcess(0);
		}
		else if (menu == 2)//�����˵�
		{
			if (JudgeForHelp(pt) == 1)
			{
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				menu = 0;
				GamePaint2(hwnd, 2);
			}
		}
		else if (menu == 3)
		{//�����ؿ�   ������Ӧ�Ĵ���  
			if (JudgeForSwitch(pt) == 1)//������һ��
			{
				PlaySound("d:\\Documents\\Visual Studio 2017\\Projects\\Project8\\Project8\\ui.wav", NULL, SND_FILENAME | SND_ASYNC);
				GamePaint(hwnd);
				menu = 1;
			}
			else if (JudgeForSwitch(pt) == 2)//�˳��ؿ�
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
