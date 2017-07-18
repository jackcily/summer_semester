#include"stack.h"
#include"game.h"
int color;
int NumOfStar;
int SetColor(POINT firstcurp)
{
	color = StarMap[firstcurp.x][firstcurp.y];
	return 0;
}
int Pass(POINT p)
{
	if (StarMap[p.x][p.y] == color)
	{
	  NumOfStar++;//���ǵ���Ŀ����++
      return 1;
	}
	   return 0;
}
//����һ��ջ��������ɹ��򷵻�1������ͷ���0
int Initstack(Mystack * s)
{
	s->base = (SElement*)malloc(STACK_INIT_SIZE * sizeof(SElement));//Ϊջ�����ʼ�ռ�
	if (!s->base)
		return 0;
	s->top = s->base;//�趨Ϊ��ջ
	s->stacksize = STACK_INIT_SIZE;
	return 1;
}
//����Ԫ��Ϊe��Ԫ�أ��ɹ�����1 ʧ�ܷ���0
int Push(Mystack* s, SElement e)
{
	if (s->top - s->base >= STACK_INIT_SIZE)//���ջ���ˣ�����������
	{
		s->base = (SElement*)realloc(s->base, (s->stacksize + STACKINCREMENT) * sizeof(SElement));
		if (NULL != s->base)
		{
			return 0;
		}
		s->top = s->base + s->stacksize;
		s->stacksize += STACKINCREMENT;
	}
	*(s->top) = e;
	s->top++;
	return 1;
}
//��˳ʱ�뷽��Ӷ���ʼѰ�Ҿ�����ĳһ��λ�õ��ٽ�λ��
POINT Nextposition(POINT now, int direction)
{
	POINT next;
	int x = now.x;
	int y = now.y;
	switch (direction)
	{
	case 1:
		//��
	{
		next.x = x;
		next.y = y + 1;
		break;
	}
	//��
	case 2: {
		next.x = x + 1;
		next.y = y;
		break;
	}
			//��
	case 3: {
		next.x = x;
		next.y = y - 1;
		break;
	}
			//��
	case 4:
	{
		next.x = x - 1;
		next.y = y;
		break;
	}
	default:break;
	}
	return next;
}
int  GetRightDirection(POINT a, int *di)
{//ͨ����ǰ�Ĳ��Ӻͷ�������ж��Ƿ�Ҫ���и��ķ���
	if ((*di) == 1)
	{
		if (a.y == 9)
		{
			if (a.x == 9)
				(*di) += 2;
			else
				(*di) += 1;
		}
	}
	else if ((*di) == 2)
	{
		if (a.x == 9)
		{
			if (a.y== 0)
				(*di) += 2;
			else
				(*di)++;
		}
	}
	else if ((*di) == 3)
	{
		if (a.y == 0)
		{
			if (a.x == 0)
				(*di) += 2;
			else
				(*di)++;
		}
	}

	else if ((*di) == 4)
	{
		if (a.x== 0)
		{
			(*di)++;
		}
	}
	return 0;
}
//�ж�ջ�Ƿ�Ϊ�գ�����ǿյľͷ���0������ͷ���1
int isStackempty(Mystack *s)
{
	//�ж�ջ�Ƿ�Ϊ�գ�����ǿյľͷ���0������ͷ���1
	if (s->top == s->base)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//����ջ��Ԫ�ظ�ֵ��e�����ɹ�����1������ʧ�ܷ���0
int Pop(Mystack* s, SElement* e)
{
	if (isStackempty(s))
	{
		*e = *(s->top - 1);
		s->top--;
		return 1;
	}
	else
	{
		return 0;
	}
}
//·����ջ�Ļ�������-1�ı��
void Markprint(POINT p)
{
	StarMap[p.x][p.y] = -1;
}
void clear(Mystack *pS)
{
	if (NULL == pS) //���
	{
		return;
	}
	free(pS->base);
}
//�����㼣
int  Footprint(POINT p)
{//�����㼣
   StarMap[p.x][p.y] = -1;
   return 0;
}