//实现所有需要进行的操作
//#include"stack.h"
//#include"game.h"
//#include<stdio.h>
//#include<Windows.h>
//int main()
//{
//	InitStarmap(GetLevelScore());//初始化迷宫
//	InitGame();//每次进行的时候都要重新进行初始化
//
//
//	
//	我写的只是一次消除
//	如果进行多次消除的话 需要把它封装成一个函数
//	POINT  a;
//	do
//	{
//	int i, j;
//	printf("\n\n\n*********************************\n");
//	for (i = 0; i < 10; i++)
//	{
//		for (j = 0; j < 10; j++)
//		{
//			printf("%d  ", StarMap[i][j]);
//		}
//		printf("\n");
//	}
//    printf("请输入要消除的坐标值\n");
//	scanf("%d   %d", &a.x, &a.y);//输入的是行和列
//	RemoveStar(a);
//	printf("\n消除了  %d  个\n",NumOfStar);
//
//	printf("\n分数为%d\n", score);
//	
//
//	
//	ChangeSit();//进行消除判断
//	AddScore(NumOfStar);
//	
//	
//	isWin();
//	if (level > 6)
//	{
//		printf("满级!!!!\n");
//		
//		return 0;
//	}
//
//	} while (isDead() != 0);
//	if (isDead() == 0)
//	{
//		printf("死亡!!!!\n");
//		return 0;
//	}
//
//
//system("pause");
//
//	return 0;
//}
