#include<Windows.h>
extern int color;//每次进栈前存储颜色的数目
extern int NumOfStar;//存储每次要消去的星星

#define STACK_INIT_SIZE 15
#define STACKINCREMENT 10

typedef struct SElement
{
	int  ord;//通道在路径块上的序号
	POINT  seat;//通道块在路径上的坐标
	int di;//从此通道块走向下一块的“方向“
}SElement;
typedef struct Mystack
{
	SElement *base;
	SElement *top;
	int stacksize;
}Mystack;

int Pass(position);//判断能否入栈
int SetColor(POINT firstcurp);//设置判断颜色
int Initstack(Mystack * s);
int Push(Mystack* s, SElement e);
int  GetRightDirection(POINT a, int *di);
int isStackempty(Mystack *s);
int Pop(Mystack* s, SElement* e);
void Markprint(POINT p);
void clear(Mystack *pS);
POINT Nextposition(POINT now, int direction);//按顺时针方向从东开始寻找矩阵当中某一个位置的临近位置