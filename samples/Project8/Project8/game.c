#include "game.h"
#include "stack.h"
 int StarMap[10][10];//��¼���ǵ�״̬�Ķ�ά����
 int level;//�������Ϸ�ĵȼ�
 int score;//��ҵķ���
 POINT boundary;
 int  InitMenu()
 {
	 menu = 0;
	 return 0;
 }
int InitStarmap(int size)//��ʼ����ά����
{
	srand(time(NULL));
	int i;
	int j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			StarMap[i][j] = rand() % size;
		}
	}
	return 0;
}
// ���ñ߽�����
int  SetBoundary()
 {
	 boundary.x = MAX_X;
	 boundary.y =  MAX_Y;
	 return 0;
 }
// ��ñ߽�����
POINT*  GetBoundary()
 {
	 return &boundary;
 }
//�������ǵ���ɫ��Ŀ
int  GetColorNum()
{
	if (level <= 3)return 4;
	return 5;
}
int InitLevel()
{
	level = 1;
	return 0;
}
int AddLevel()
{
	level++;
	return 0;
}
//��ʼ����Ϸ��������
int InitGame()
{
	score = 0;
	return 0;
}
//����֮��Ĺ滮��������  ���ܻ���ַ�����ʧ������  scoreӦ����С������ 
//������С����ʧС������   �����̶ֹ� ����һ���ı������
int  AddScore(int num)
{
	if(num<5)
	score += GetGainScoreRate()*SCORE_TWO_TO_FOUR *num;
	else if(num<9)
		score += GetGainScoreRate()*SCORE_FIVE_TO_EIGHT*num;
	else 
		score += GetGainScoreRate()*SCORE_NINE_*num;
	return 0;
}
//�ж��Ƿ��������(û�п��Խ���������Ԫ����) ����Ϸ�Ƿ����
int isDead()
{
	int i;
	int j;
	for (i = 0; i <10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (StarMap[i][j] != 5)//������ǿո�
			{
				//���ֻ�������ڽӿ�
				if (i == 9 && j == 9)
				{
					if (StarMap[9][9] == StarMap[9][8] || StarMap[9][9] == StarMap[8][9])   return 1;
				}
				else if (i == 0 && j == 0)
				{
					if (StarMap[0][0] == StarMap[0][1] || StarMap[0][0] == StarMap[1][0])   return 1;
				}
				else if (i == 0 && j == 9)
				{
                          if(StarMap[0][9] == StarMap[0][8] || StarMap[0][9] == StarMap[1][9])  return 1;
				}
				else if (i == 9 && j == 0)
				{
					if (StarMap[9][0] == StarMap[9][1] || StarMap[9][0] == StarMap[8][0])    return 1;
				}
		      //���ֻ�������ڽӿ�
				else if (i == 0)
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1])  return 1;
				}
				else if (i == 9)
				{
					if ( StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1] || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else if (j == 0)
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1]  || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else if (j == 9)
				{
					if (StarMap[i][j] == StarMap[i + 1][j]|| StarMap[i][j] == StarMap[i][j - 1] || StarMap[i][j] == StarMap[i - 1][j])  return 1;

				}
				else
				{
					if (StarMap[i][j] == StarMap[i + 1][j] || StarMap[i][j] == StarMap[i][j + 1] || StarMap[i][j] == StarMap[i][j - 1]||StarMap[i][j]==StarMap[i-1][j])  return 1;
				}
			}	
		 }
	}
	return 0;//����
}
//��������������Ϊ-1 ���������Ǳ���Ϊ -1��  ���н�������  Ȼ�����ÿ���ǲ����б�������  ������Ӧ����λ����
int ChangeSit()
{
	int i;
	int j;
	int flag = 0;
	int flag2 = 0;
	int leftnum=9;
	for (j = 0; j < 10; j++)
	{
		flag = 0;
		leftnum = 9;
		int n[10];
		for (i = 9; i >= 0; i--)
		{  //��һ��ɸѡ����ȥ
			if (flag == 1) flag = 2;
			if (StarMap[i][j] != -1)
			{
				n[leftnum--] = StarMap[i][j];
			}
			else if (flag == 0) flag = 1;
		}
		while (leftnum >= 0)
		{
			n[leftnum--] = 5;//��ʣ��ĵط���Ϊ�ո�
		}
		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = n[i];//�ٸ��ƻ�ȥ
		}
		if (flag == 2)
		{
			flag2 = 1;
		}
	}
	if (flag == 1)return 1;
	return 0;
}
int RemoveStar(POINT pt)//����ֵ�������������Ǹ��� ���ݴ��������Ͷ�ά�����ж������������Ǹ���
{
	Mystack path;//��¼·����ջ
	Initstack(&path);//��ʼ��·�� ����ʼ��ջ��?
	int  flag;
	POINT curp;//�����ߵ������
	curp.x = pt.x;//��ʼ�����
	curp.y = pt.y;
	int curstep = 1;//̽���Ĳ���
	NumOfStar = 0;
	int  InitColor = StarMap[pt.x][pt.y];
	if (InitColor == 5)  return 0;//�����ʼ��ɫ��Ϊ�ո񣬾�ֱ�ӷ���
	SetColor(pt);
	//��¼�������ɫ������ֻ��һ�����ǿ�Ļ�  �����˻�ȥ
	do
	{
		if (Pass(curp))//��ǰλ�ÿ���ͨ��
		{//����ǰλ�ô���ջ
			Footprint(curp);
			SElement e;
			e.di = 1;//�趨̽������
			e.ord = curstep;
			e.seat.x = curp.x;
			e.seat.y = curp.y;
			Push(&path, e);
			//printf("����%d %d)��ջ\n\n", curp.x, curp.y);
			GetRightDirection(curp, &e.di);//��֤�������ֵ��  ��ȷ�ķ���  
			curp = Nextposition(curp, e.di);//�ҵ�ǰһ�����Կ鶫���·������Ϊ���Կ飬��������ߵĿ�
			curstep++;//̽��������
		}
		else
		{
			if (isStackempty(&path))//���ջ����
			{
				SElement e;
				Pop(&path, &e);//�˻���һ��
				curstep--;
				//�����������������ǵ�ǰ�ı�������
				//�ѵ���ʱ��
				e.di++;
				GetRightDirection(e.seat, &e.di);//��֤�������ֵ��  ��ȷ�ķ���  
				e.di--;						 //��������Χ�����Թ���·��ջ�����
				while (e.di >=4 && isStackempty(&path))
				{
					Pop(&path, &e);
					e.di++;
					GetRightDirection(e.seat, &e.di);//��֤�������ֵ��  ��ȷ�ķ���  
					e.di--;						 //��������Χ�����Թ���·��ջ�����
				}
				//�����ǰջ������û�б����Ե�·���ͽ��в���
				if (e.di < 4)
				{
					curp = Nextposition(e.seat, e.di+1);
					e.di++;
					curstep++;
					Push(&path, e);
				}
			}
		}
	} while (isStackempty(&path));
	if (NumOfStar == 1)
	{
       StarMap[pt.x][pt.y]=InitColor ;
	   NumOfStar--;
	    //���ֻ��һ������Ҫ�����Ļ� �Ͳ�������
	   flag = 0;
	}	
	else flag = 1;
	//������һ����������Ҫ������д�����
	clear(&path);
	return  flag;
}
//���ݵȼ�����Ҫ ������Ҫ�ĳ�ʼ����������
double GetRate()
{
	return 1 + level*0.15;
}
//���ݵȼ����ؼƷ�ʱ��Ҫ���ӵķ�������
double   GetGainScoreRate()
{
	return 1 + level*0.2;
}
//���ݲ�ͬ�ĵȼ����ظõȼ���Ҫ�ﵽ�ķ���
int  GetLevelScore()
{
	return  GetRate()*INIT_SCORE;
}
//�ж��Ƿ������һ��
int isWin()
{//ֻ������һ��
	if (GetLevelScore() <= score)
	{
	 return 1;
	}
	return 0;
}
int  GetSeat(POINT* p)
{
	int k;
	p->x = (p->x - 10) / 40;
	p->y = (p->y - 10) / 40;
	k = p->x;
	p->x = p->y;
	p->y = k;
	if(p->x<0||p->x>10||p->y<0||p->y>10)
	return 0;
	return 1;
}
//�Ͱ������������� ����д ���е���Ҫ����������
int CloseStar()
{//д����  ������
	int  num=0;
	int n[10];
	int i, j;
	int k = 0;
	int flag = 0;
	//�Ƚ����ǿ��е�Ԫ�ش������
	for (j = 0; j < 10; j++)
	{
		for (i = 0; i < 10; i++)
		{
			if (StarMap[i][j] != 5)
			{
				if (flag==1)flag == 2;
				n[num++] = j;
				break;
			}
			else  if(flag==0)
			{
				flag = 1;
			}
		}
	}
	//�������θ�ֵ
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = StarMap[i][n[k]];
		}
		k++;
   }
	//�հ״�����ո�
	while (j < 10)
	{
		for (i = 0; i < 10; i++)
		{
			StarMap[i][j] = 5;
		}
		j++;
	}
	if (flag == 2)  return 1;
	return 0;
}
//�������	1 ��ִ�п�ʼ��Ϸ �������2 ��ִ����Ϸ����  ����������ͽ�����Ϸ
int  JudgeChange(POINT *pt)
{
	
	pt->x = pt->x-10;
	pt->y = pt->y-10;
	return 0;
}
int  Judge(POINT pt)
{
	if (pt.x < 200 && pt.x>70)
	{
		if (pt.y < 240 && pt.y>200) return 1;
		else if (pt.y < 290 && pt.y>250)  return 2;
		else if (pt.y < 340 && pt.y>300)   return 3;
		else return 0;
	}
	else  return 0;
}
 //����һ��ֵ  ���Ƿ�ص����˵�(����1)
int  JudgeForHelp(POINT pt)  
{
	if (pt.x < 200 && pt.x>20 && pt.y < 400 && pt.y>350)
		return 1;
		return 0;
}
//���������Ч�Ļ��ͷ���1  ���򷵻�0
int JudgeSeat(POINT pt)
{
	if (pt.x < 410 && pt.x>10 && pt.y < 410 && pt.y>10)
		return 1;
    	return 0; 
}
//����1 ����һ��   ����2���˳���Ϸ   ����0��������
JudgeForSwitch(POINT pt)
{
	if (pt.x < 320 && pt.x>125 && pt.y < 170 && pt.y>107)
		return 1;
	else if (pt.x < 375 && pt.x>260 && pt.y < 460 && pt.y>430)
		return 2;
	else
		return 0;
}

