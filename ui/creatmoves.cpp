#include "define.h"
#include "createmoves.h"

/*
�������жϵ�ǰλ���Ƿ������ȼ�������������
������x,y�����ȼ���
���أ��Ƿ�
*/
bool JudgeInPriorityList(int x, int y, std::vector<Point> PriorityList)
{
	for (int i = 0; i < PriorityList.size(); i++)
	{
		if (x == PriorityList[i].x && y == PriorityList[i].y)
		{
			return true;
		}
	}
	return false;
}

/*
��������ȡ���ƶ���λ�ü��ϣ�û�������������ų���̫����λ�õĹ���
��������
���أ�Ԫ�ؼ���
*/
vector<Point> CreateMovesNaive()
{
	vector<Point> MoveList;
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			if (chessBoard[i][j] == blank)
			{
				Point NewPoint(i, j);
				MoveList.push_back(NewPoint);
			}
		}
	}
	return MoveList;
}

/*
��������ȡ���ƶ���λ�ü��ϣ�û�����������������ų���̫����λ��
��������
���أ�Ԫ�ؼ���
*/
vector<Point> CreateMovesWithNeighbor()
{
	vector<Point> MoveList;
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			if (chessBoard[i][j] == blank && JudgeNeighbor(i, j))
			{
				Point NewPoint(i, j);
				MoveList.push_back(NewPoint);
			}
		}
	}
	return MoveList;
}

/*
��������ȡ���ƶ���λ�ü��ϣ����������ϴ�������Χ��λ�ã��ų���Χû���κ����ӵ�λ��
��������
���أ�Ԫ�ؼ���
*/
vector<Point> CreateMoves()
{
	//�Ȳ������һ���Լ�/�Է�����֮���λ�ã�����
	vector<Point> PriorityList;
	if (ComputerList.size() > 0)
	{
		int x = ComputerList[ComputerList.size() - 1].x;
		int y = ComputerList[ComputerList.size() - 1].y;
		for (int Direction = 0; Direction < 4; Direction++)
		{
			int Newx = x + DirectionX[Direction];
			int Newy = y + DirectionY[Direction];
			if (GetPlace(Newx, Newy) == blank)
			{
				Point NewPoint(Newx, Newy);
				PriorityList.push_back(NewPoint);
			}
			Newx = x - DirectionX[Direction];
			Newy = y - DirectionY[Direction];
			if (GetPlace(Newx, Newy) == blank)
			{
				Point NewPoint(Newx, Newy);
				PriorityList.push_back(NewPoint);
			}
		}
	}
	if (PlayerList.size() > 0)
	{
		int x = PlayerList[PlayerList.size() - 1].x;
		int y = PlayerList[PlayerList.size() - 1].y;

		for (int Direction = 0; Direction < 4; Direction++)
		{
			int Newx = x + DirectionX[Direction];
			int Newy = y + DirectionY[Direction];
			if (GetPlace(Newx, Newy) == blank)
			{
				Point NewPoint(Newx, Newy);
				PriorityList.push_back(NewPoint);
			}
			Newx = x - DirectionX[Direction];
			Newy = y - DirectionY[Direction];
			if (GetPlace(Newx, Newy) == blank)
			{
				Point NewPoint(Newx, Newy);
				PriorityList.push_back(NewPoint);
			}
		}
	}

	//�ټ�������λ��,�ų�֮ǰ�������ĺ���Χû���������ӵ�
	vector<Point> OtherList;
	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			if (chessBoard[i][j] == blank && JudgeNeighbor(i, j)
				&& JudgeInPriorityList(i, j, PriorityList) == false
				)
			{
				Point NewPoint(i, j);
				OtherList.push_back(NewPoint);
			}
		}
	}

	//�ϲ�
	vector<Point> MoveList;
	for (int i = 1; i < PriorityList.size(); i++)
	{
		MoveList.push_back(PriorityList[i]);
	}
	for (int i = 1; i < OtherList.size(); i++)
	{
		MoveList.push_back(OtherList[i]);
	}
	return MoveList;
}