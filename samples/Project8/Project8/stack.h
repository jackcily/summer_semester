#include<Windows.h>
extern int color;//ÿ�ν�ջǰ�洢��ɫ����Ŀ
extern int NumOfStar;//�洢ÿ��Ҫ��ȥ������

#define STACK_INIT_SIZE 15
#define STACKINCREMENT 10

typedef struct SElement
{
	int  ord;//ͨ����·�����ϵ����
	POINT  seat;//ͨ������·���ϵ�����
	int di;//�Ӵ�ͨ����������һ��ġ�����
}SElement;
typedef struct Mystack
{
	SElement *base;
	SElement *top;
	int stacksize;
}Mystack;

int Pass(position);//�ж��ܷ���ջ
int SetColor(POINT firstcurp);//�����ж���ɫ
int Initstack(Mystack * s);
int Push(Mystack* s, SElement e);
int  GetRightDirection(POINT a, int *di);
int isStackempty(Mystack *s);
int Pop(Mystack* s, SElement* e);
void Markprint(POINT p);
void clear(Mystack *pS);
POINT Nextposition(POINT now, int direction);//��˳ʱ�뷽��Ӷ���ʼѰ�Ҿ�����ĳһ��λ�õ��ٽ�λ��