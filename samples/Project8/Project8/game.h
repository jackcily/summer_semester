//ʵ��������Ϸ��Ҫ����
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BITMAP_FILE_BK		"dee111.bmp"
#define BITMAP_FILE_BK2	"face3.bmp"
#define BITMAP_FILE_BK3	"help.bmp"
#define BITMAP_FILE_BK4   "tongguan.bmp"
#define BITMAP_FILE_BK5    "fail1.bmp"
#define BITMAP_FILE_BK6    "fail.bmp"
#define REMOVE -1//������Ϊ  -1
#define BLANK 5  //�ո�Ϊ5
#define INIT_SCORE 1000//��ʼͨ�ط���

#define SCORE_TWO_TO_FOUR  10//2-4  ÿ��ש��ķ�ֵ
#define  SCORE_FIVE_TO_EIGHT  15//5-8  ÿ��ש��ķ�ֵ  15
#define  SCORE_NINE_  16   //9��������    ÿ��ש��ķ�ֵ  16
#define CELL_PIXEL			20// ��ͼʱʹ�õı�ʾֱ�����ص������
#define COLOR_BOUNDARY		RGB(139, 134, 130)//��ͼʱ�߿���ɫ
#define COLOR_TEXT			RGB(173,216,230)//��ͼʱ�ı���ɫ
#define MAX_X		20// ��Ϸ�����С
#define MAX_Y		20// ��Ϸ�����С

extern POINT boundary;
extern int StarMap[10][10];//��¼���ǵ�״̬�Ķ�ά����
extern int level;//�������Ϸ�ĵȼ�
extern int score;//��ҵķ���
 extern  INT menu;//menu������״̬ 0 �ǽ���˵�״̬  1 �ǿ�ʼ��Ϸ״̬  2����Ϸ����״̬  3���м�״̬

int  GetColorNum();//�������ǵ���ɫ��Ŀ
int InitStarmap(int size);//��ʼ����ά����
int InitGame();//��ʼ����Ϸ��������
int  AddScore(int num);//ÿһ�����������ӷ���
int isDead();//�ж��Ƿ�������� ����Ϸ�Ƿ����
int ChangeSit();//��������������Ϊ-1 ���������Ǳ���Ϊ -1��  ���н�������  Ȼ�����ÿ���ǲ����б�������  ������Ӧ����λ����
int RemoveStar(POINT pt);
double  GetRate();//���ݵȼ�����Ҫ ������Ҫ�ĳ�ʼ����������
double GetGainScoreRate() ;//���ݵȼ����ؼƷ�ʱ��Ҫ���ӵķ�������
int  GetLevelScore();//���ݲ�ͬ�ĵȼ����ظõȼ���Ҫ�ﵽ�ķ���
int isWin();//�ж��Ƿ������һ��
int  GetSeat(POINT *p);//���ݷ��ص����ص�õ��ڶ�ά�����ϵĶ�Ӧ�ĺ�������
int CloseStar();//�ж��Ƿ���Ҫ�������������ϵ��ػ�
int AddLevel();//���Ӯ�˾��еȼ��ļӼ�
int InitLevel();//��ʼ���ȼ�
int  Judge(POINT pt);//�������	1 ��ִ�п�ʼ��Ϸ �������2 ��ִ����Ϸ����  ����������ͽ�����Ϸ
int JudgeChange(POINT *pt);//�жϽ���menu������״̬
int JudgeSeat(POINT pt);//�жϽ��������������Ƿ�Ϸ�
int  InitMenu();//��ʼ���˵�״̬
int  JudgeForHelp(POINT pt);//�ж��Ƿ�Ӱ���ҳ���л���ȥ
JudgeForSwitch(POINT pt);//�л�ʱ�ж���һ���Ĳ���


