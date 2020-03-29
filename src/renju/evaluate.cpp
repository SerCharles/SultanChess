#include "define.h"
#include "evaluate.h"

std::vector<ScoreShape> ScoreList;

/*
�����������ܵ÷�
�����������Ƶ�������ɫ
���أ��÷�
*/
int Evaluate(int Evaluated)
{
	int PlayerScore = 0;
	int ComputerScore = 0;
	ScoreList.clear();
	for (int i = 0; i < PlayerList.size(); i++)
	{
		PlayerScore += EvaluateOnePoint(PlayerList[i].x, PlayerList[i].y, Player);
	}
	/*PrintScoreList();
	cout << "��ǰ����ܹ�ֵ��" << PlayerScore << endl;
	cout << "--------------------------------------------" << endl;*/

	ScoreList.clear();
	for (int i = 0; i < ComputerList.size(); i++)
	{
		ComputerScore += EvaluateOnePoint(ComputerList[i].x, ComputerList[i].y, Computer);
	}
	/*PrintScoreList();
	cout << "��ǰ�����ܹ�ֵ��" << ComputerScore << endl;*/
	int TotalScore = -1;
	if (Evaluated == Player)
	{
		TotalScore = PlayerScore - 0.1 * ComputerScore;
	}
	else
	{
		TotalScore = ComputerScore - 0.1 * PlayerScore;
	}
	/*cout << "��ǰ�ܹ�ֵ��" << TotalScore << endl;
	cout << "--------------------------------------------" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "--------------------------------------------" << endl;*/
	return TotalScore;
}

/*
����������ĳһ��ĵ÷�
��������ǰ��x,y�������Ƶ�������ɫ
���أ��÷�
*/
int EvaluateOnePoint(int x, int y, int Evaluated)
{
	int TotalScore = 0;
	//����
	for (int Direction = 0; Direction < 4; Direction++)
	{
		//����˷����ϣ��õ��Ѿ��е÷���״�����ظ�����
		if (JudgeRepeat(x, y, DirectionX[Direction], DirectionY[Direction]))
		{
			continue;
		}
		int MaxScore = 0;
		ScoreShape CurrentMax;
		//offsetƫ��
		//��ǰ�������ֵ
		for (int offset = -5; offset <= 0; offset++)
		{
			ChessShape Shape5;
			ChessShape Shape6;
			ScoreShape Score5;
			ScoreShape Score6;
			Score5.DX = DirectionX[Direction];
			Score5.DY = DirectionY[Direction];
			Score6.DX = DirectionX[Direction];
			Score6.DY = DirectionY[Direction];
			Shape5.TotalNum = 5;
			Shape6.TotalNum = 6;
			Score5.TotalNum = 5;
			Score6.TotalNum = 6;

			//biasλ��
			//��ȡ��ǰ����
			for (int bias = 0; bias < 6; bias++)
			{
				int NewX = x + (bias + offset) * DirectionX[Direction];
				int NewY = y + (bias + offset) * DirectionY[Direction];
				Shape5.List[bias] = GetPlace(NewX, NewY);
				Shape6.List[bias] = GetPlace(NewX, NewY);
				Score5.List[bias] = GetPlace(NewX, NewY);
				Score6.List[bias] = GetPlace(NewX, NewY);
				Point TempPoint(NewX, NewY);
				Score5.Place[bias] = TempPoint;
				Score6.Place[bias] = TempPoint;
			}
			//�������ͷ���
			int score5 = EvaluateOneShape(Evaluated, Shape5);
			Score5.Score = score5;
			int score6 = EvaluateOneShape(Evaluated, Shape6);
			Score6.Score = score6;
			if (score5 > MaxScore)
			{
				MaxScore = score5;
				CurrentMax = Score5;
			}
			if (score6 > MaxScore)
			{
				MaxScore = score6;
				CurrentMax = Score6;
			}
		}
		if (MaxScore > 0)
		{
			//����������״�ཻ�� ������3�� �ཻ�� �÷����� һ���ӵĳ���
			int AddScore = CalculateAddScore(x, y, CurrentMax.DX, CurrentMax.DY, MaxScore);

			ScoreList.push_back(CurrentMax);
			TotalScore += MaxScore;
			TotalScore += AddScore;
		}
	}
	return TotalScore;
}

/*
�������жϵ�ǰ���Ƿ��ظ�����
��������ǰ��x,y������dx��dy
���أ��Ƿ�
*/
bool JudgeRepeat(int x, int y, int dx, int dy)
{
	for (int i = 0; i < ScoreList.size(); i++)
	{
		ScoreShape TheOne = ScoreList[i];
		if (TheOne.DX == dx && TheOne.DY == dy)
		{
			int Length = TheOne.TotalNum;
			for (int j = 0; j < Length; j++)
			{
				if (TheOne.Place[j].x == x && TheOne.Place[j].y == y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

/*
�������жϵ�ǰ���Ƿ������������е÷֣��еĻ��������ӷ�
��������ǰ��x,y������dx��dy����ǰ�÷�
���أ�����ӷ�
*/
int CalculateAddScore(int x, int y, int dx, int dy, int score)
{
	int AddScore = 0;
	for (int i = 0; i < ScoreList.size(); i++)
	{
		ScoreShape TheOne = ScoreList[i];
		if (TheOne.DX == dx && TheOne.DY == dy)
		{
			int Length = TheOne.TotalNum;
			for (int j = 0; j < Length; j++)
			{
				if (TheOne.Place[j].x == x && TheOne.Place[j].y == y && TheOne.Score > 0)
				{
					AddScore += score;
					AddScore += TheOne.Score;
					break;
				}
			}
		}
	}
	return AddScore;
}

/*
��������ӡ�÷��б�
��������ǰ��x,y������dx��dy����ǰ�÷���
���أ���
*/
void PrintScoreList()
{
	for (int i = 0; i < ScoreList.size(); i++)
	{
		cout << "��" << i << "���÷�����" << endl;
		cout << "�ܹ��÷֣�" << ScoreList[i].Score << endl;
		cout << "��ǰ����" << "(" << ScoreList[i].DX << "," << ScoreList[i].DY << ")" << endl;
		if (ScoreList[i].TotalNum == 5)
		{
			cout << "�÷ֵ㣺" <<
				"(" << ScoreList[i].Place[0].x << "," << ScoreList[i].Place[0].y << ")" << "," <<
				"(" << ScoreList[i].Place[1].x << "," << ScoreList[i].Place[1].y << ")" << "," <<
				"(" << ScoreList[i].Place[2].x << "," << ScoreList[i].Place[2].y << ")" << "," <<
				"(" << ScoreList[i].Place[3].x << "," << ScoreList[i].Place[3].y << ")" << "," <<
				"(" << ScoreList[i].Place[4].x << "," << ScoreList[i].Place[4].y << ")" << endl;
			cout << "���ͣ�"
				<< ScoreList[i].List[0]
				<< ScoreList[i].List[1]
				<< ScoreList[i].List[2]
				<< ScoreList[i].List[3]
				<< ScoreList[i].List[4] << endl;
		}
		else
		{
			cout << "�÷ֵ㣺" <<
				"(" << ScoreList[i].Place[0].x << "," << ScoreList[i].Place[0].y << ")" << "," <<
				"(" << ScoreList[i].Place[1].x << "," << ScoreList[i].Place[1].y << ")" << "," <<
				"(" << ScoreList[i].Place[2].x << "," << ScoreList[i].Place[2].y << ")" << "," <<
				"(" << ScoreList[i].Place[3].x << "," << ScoreList[i].Place[3].y << ")" << "," <<
				"(" << ScoreList[i].Place[4].x << "," << ScoreList[i].Place[4].y << ")" << "," <<
				"(" << ScoreList[i].Place[5].x << "," << ScoreList[i].Place[5].y << ")" << endl;
			cout << "���ͣ�"
				<< ScoreList[i].List[0]
				<< ScoreList[i].List[1]
				<< ScoreList[i].List[2]
				<< ScoreList[i].List[3]
				<< ScoreList[i].List[4]
				<< ScoreList[i].List[5] << endl;
		}
		cout << "--------------------------------------------------------------------------------------------" << endl;
	}
}

/*
�������жϵ�ǰλ�����͵÷�
���������жϵ�������, ����
���أ��÷�
*/
int EvaluateOneShape(int Evaluated, ChessShape TheShape)
{
	if (TheShape.TotalNum == 5)
	{
		//01100 50
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == blank
			&& TheShape.List[4] == blank)
		{
			return 50;
		}
		//00110 50
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == blank
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == blank)
		{
			return 50;
		}
		//11010 200
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == blank
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == blank)
		{
			return 200;
		}
		//11100 500
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == blank
			&& TheShape.List[4] == blank)
		{
			return 500;
		}
		//00111 500
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == blank
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated)
		{
			return 500;
		}
		//01110 5000
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == blank)
		{
			return 5000;
		}
		//11101 5000
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == blank
			&& TheShape.List[4] == Evaluated)
		{
			return 5000;
		}
		//11011 5000
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == blank
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated)
		{
			return 5000;
		}
		//10111 5000
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == blank
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated)
		{
			return 5000;
		}
		//11110 5000
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == blank)
		{
			return 5000;
		}
		//01111 5000
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated)
		{
			return 5000;
		}
		//11111 10000000
		if (TheShape.List[0] == Evaluated
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated)
		{
			return 10000000;
		}
	}
	if (TheShape.TotalNum == 6)
	{
		//010110 5000
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == blank
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated
			&& TheShape.List[5] == blank)
		{
			return 5000;
		}
		//011010 5000
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == blank
			&& TheShape.List[4] == Evaluated
			&& TheShape.List[5] == blank)
		{
			return 5000;
		}
		//011110 50000
		if (TheShape.List[0] == blank
			&& TheShape.List[1] == Evaluated
			&& TheShape.List[2] == Evaluated
			&& TheShape.List[3] == Evaluated
			&& TheShape.List[4] == Evaluated
			&& TheShape.List[5] == blank)
		{
			return 50000;
		}
	}
	return 0;
}

