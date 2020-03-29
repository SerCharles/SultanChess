#include "define.h"

//����Ϸ�йص�ȫ�ֱ���
int chessBoard[GRID_NUM][GRID_NUM];//��������
int Player = -1; //���
int Computer = -1; //AI
int CurrentSide = -1;//��ǰ
int NewComputerX = -1; //AI��ǰ��������X
int NewComputerY = -1; //AI��ǰ��������Y
int NewPlayerX = -1; //��ҵ�ǰ����λ��X
int NewPlayerY = -1; //��ҵ�ǰ����λ��Y
int GameResult = -1; //��һ����Ϸ���
//����������
std::vector<Point> PlayerList;
//�����������
std::vector<Point> ComputerList;


//���õĵײ㺯����װ

//�Է�����
int Opposite(int a)
{
	return black + white - a;
}

//������ǰ����
extern void SwitchSide()
{
	CurrentSide = black + white - CurrentSide;
}

//x��4������
int DirectionX[4] = { 0, 1, 1, -1 };

//y��4������
int DirectionY[4] = { 1, 0, 1, 1 };

//��ȡ����ĳλ��ֵ��1��2��0��-1Խ��
int GetPlace(int x, int y)
{
	if (x <= 0 || y <= 0 || x >= GRID_NUM || y >= GRID_NUM)
	{
		return outbound;
	}
	return chessBoard[x][y];
}

//�ж�����ĳλ���Ƿ����ھ�
extern bool JudgeNeighbor(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int newx = x + DirectionX[i];
		int newy = y + DirectionY[i];
		if (GetPlace(newx, newy) == black || GetPlace(newx, newy) == white)
		{
			return true;
		}
		newx = x - DirectionX[i];
		newy = y - DirectionY[i];
		if (GetPlace(newx, newy) == black || GetPlace(newx, newy) == white)
		{
			return true;
		}
	}
	return false;
}



//ʵ���ø���ȫ�ֱ���
//��һ����Ϸ�ܹ��������弸��
int TotalSearchMove = 0;
//��������
int SearchNum = 0;
//��֦����
int CutNum = 0;
//��һ����Ϸ�ܹ���������
int TotalSearchNum = 0;
//��һ����Ϸ�ܹ���֦����
int TotalCutNum = 0;
//��һ����Ϸ�ܹ�����ʱ��
int TotalCostTime = 0;