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
	  NumOfStar++;//星星的数目进行++
      return 1;
	}
	   return 0;
}
//创建一个栈如果创建成功则返回1，否则就返回0
int Initstack(Mystack * s)
{
	s->base = (SElement*)malloc(STACK_INIT_SIZE * sizeof(SElement));//为栈分配初始空间
	if (!s->base)
		return 0;
	s->top = s->base;//设定为空栈
	s->stacksize = STACK_INIT_SIZE;
	return 1;
}
//插入元素为e的元素，成功返回1 失败返回0
int Push(Mystack* s, SElement e)
{
	if (s->top - s->base >= STACK_INIT_SIZE)//如果栈满了，进行再扩大
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
//按顺时针方向从东开始寻找矩阵当中某一个位置的临近位置
POINT Nextposition(POINT now, int direction)
{
	POINT next;
	int x = now.x;
	int y = now.y;
	switch (direction)
	{
	case 1:
		//东
	{
		next.x = x;
		next.y = y + 1;
		break;
	}
	//南
	case 2: {
		next.x = x + 1;
		next.y = y;
		break;
	}
			//西
	case 3: {
		next.x = x;
		next.y = y - 1;
		break;
	}
			//北
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
{//通过当前的步子和方向进行判断是否要进行更改方向
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
//判断栈是否为空，如果是空的就返回0，否则就返回1
int isStackempty(Mystack *s)
{
	//判断栈是否为空，如果是空的就返回0，否则就返回1
	if (s->top == s->base)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//弹出栈顶元素赋值给e弹出成功返回1，弹出失败返回0
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
//路径入栈的话就留下-1的标记
void Markprint(POINT p)
{
	StarMap[p.x][p.y] = -1;
}
void clear(Mystack *pS)
{
	if (NULL == pS) //如果
	{
		return;
	}
	free(pS->base);
}
//留下足迹
int  Footprint(POINT p)
{//留下足迹
   StarMap[p.x][p.y] = -1;
   return 0;
}