#include "define.h"
#include "makemove.h"
#include "gameover.h"
#include "createmoves.h"
#include "searchmove.h"
//#include "printchessboard.h"

/*
��������ӡ����һ�ֵ�ʵ����
��������
���أ���
*/
void PrintLog()
{
	cout << "�ܹ�����������" << TotalSearchNum << endl;
	cout << "�ܹ���֦������" << TotalCutNum << endl;
	cout << "�ܹ������ķ�ʱ�䣺" << TotalCostTime << "ms" << endl;

	int AverageSearchNum = TotalSearchNum / TotalSearchMove;
	int AverageCutNum = TotalCutNum / TotalSearchMove;
	int AverageCostTime = TotalCostTime / TotalSearchMove;

	cout << "ƽ������������" << AverageSearchNum << endl;
	cout << "ƽ����֦������" << AverageCutNum << endl;
	cout << "ƽ�������ķ�ʱ�䣺" << AverageCostTime << "ms" << endl;
}


/*
����������AI����λ��
��������
���أ���
*/
void SearchMove()
{
	CutNum = 0;
	SearchNum = 0;
	int StartTime = clock();
	MiniMax(Computer, MAX_DEPTH, -inf, inf);
	int StopTime = clock();
	int CostTime = (StopTime - StartTime) * 1000 / CLOCKS_PER_SEC;
	cout << "���ι�����������" << SearchNum << endl;
	cout << "���ι���֦������" << CutNum << endl;
	cout << "���������ķ�" << CostTime << "ms" << endl;
	TotalSearchMove++;
	TotalCostTime += CostTime;
	TotalSearchNum += SearchNum;
	TotalCutNum += CutNum;
}

/*
������minimax��������������ֵȡ��ֵ��ʱ����max����ֵ��ʱ����min
��������ǰside����ȣ�alpha��betaֵ
*/
int MiniMax(int Side, int Depth, int alpha, int beta)
{
	if (Depth <= 0 || JudgeWin() != 0)
	{
		return Evaluate(Side);
	}

	//��ȡ���п��е�����λ��
	//todo:�滻��������λ�ú��������в���
	vector<Point> MoveList = CreateMoves();


	for (int i = 0; i < MoveList.size(); i++)
	{
		//makemove�׶�
		int x = MoveList[i].x;
		int y = MoveList[i].y;
		SearchNum++;
		chessBoard[x][y] = Side;
		//TODO:�ڸ���chessboard֮����ɢ���ж��Ƿ�������������棬�ǵĻ���ֱ�Ӽ�֦
		Point NewMove(x, y);
		if (Side == Player)
		{
			PlayerList.push_back(NewMove);
		}
		else
		{
			ComputerList.push_back(NewMove);
		}

		//�ݹ�
		int value = -MiniMax(Opposite(Side), Depth - 1, -beta, -alpha);

		//unmakemove�׶�
		chessBoard[x][y] = blank;
		if (Side == Player)
		{
			PlayerList.pop_back();
		}
		else
		{
			ComputerList.pop_back();
		}

		if (value > alpha)
		{
			//����
			if (Depth == MAX_DEPTH)
			{
				NewComputerX = x;
				NewComputerY = y;
			}

			//��֦
			if (value >= beta)
			{
				CutNum++;
				return beta;
			}
			alpha = value;
		}
	}
	return alpha;
}


