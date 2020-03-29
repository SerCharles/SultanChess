#include "define.h"
#include "evaluate.h"
#include "gameover.h"

/*
�������жϵ�ǰλ�������Ƿ�ʤ��
���������жϵ�������, ����
���أ��Ƿ�
*/
bool JudgeOneShapeSuccess(int Evaluated, ChessShape TheShape)
{
	//11111 10000000
	if (TheShape.TotalNum == 5
		&& TheShape.List[0] == Evaluated
		&& TheShape.List[1] == Evaluated
		&& TheShape.List[2] == Evaluated
		&& TheShape.List[3] == Evaluated
		&& TheShape.List[4] == Evaluated)
	{
		return true;
	}
	return false;
}

/*
�������ж���Ϸ����
��������
���أ�0��ûӮ -1������ 1����ʤ�� 2����ʤ��
*/
int JudgeWin()
{
	for (int i = 0; i < PlayerList.size(); i++)
	{
		int x = PlayerList[i].x;
		int y = PlayerList[i].y;
		for (int Direction = 0; Direction < 4; Direction++)
		{
			ChessShape Shape;
			Shape.TotalNum = 5;

			//biasλ��
			//��ȡ��ǰ����
			for (int bias = 0; bias < 5; bias++)
			{
				int NewX = x + bias * DirectionX[Direction];
				int NewY = y + bias * DirectionY[Direction];
				Shape.List[bias] = GetPlace(NewX, NewY);
			}
			if (JudgeOneShapeSuccess(Player, Shape))
			{
				return Player;
			}
		}
	}

	for (int i = 0; i < ComputerList.size(); i++)
	{
		int x = ComputerList[i].x;
		int y = ComputerList[i].y;
		for (int Direction = 0; Direction < 4; Direction++)
		{
			ChessShape Shape;
			Shape.TotalNum = 5;

			//biasλ��
			//��ȡ��ǰ����
			for (int bias = 0; bias < 5; bias++)
			{
				int NewX = x + bias * DirectionX[Direction];
				int NewY = y + bias * DirectionY[Direction];
				Shape.List[bias] = GetPlace(NewX, NewY);
			}
			if (JudgeOneShapeSuccess(Computer, Shape))
			{
				return Computer;
			}
		}
	}
	if (ComputerList.size() + PlayerList.size() >= TOTAL_PLACE)
	{
		return -1;
	}
	return 0;
}
