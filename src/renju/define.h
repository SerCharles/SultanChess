
#ifndef _DEFINE_
#define _DEFINE_
//ȫ�ֱ�������

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

struct Point
{
	int x;
	int y;
	Point() {}
	Point(int a, int b)
	{
		x = a;
		y = b;
	}
};

//ȫ�ֳ���
#define blank 0		//�հ׵�
#define black 1		//�ڷ�
#define white 2		//�׷�
#define outbound -1 //Խ��
#define inf 100000000		
#define GRID_NUM 16	//���̹�ģ	
#define TOTAL_PLACE (GRID_NUM - 1) * (GRID_NUM - 1)
#define MAX_DEPTH 3 //�������



//����Ϸ�йص�ȫ�ֱ���
extern int chessBoard[GRID_NUM][GRID_NUM]; //����
extern int Player; //���
extern int Computer; //AI
extern int CurrentSide;//��ǰ
extern int NewComputerX; //AI��ǰ��������X
extern int NewComputerY; //AI��ǰ��������Y
extern int NewPlayerX; //��ҵ�ǰ����λ��X
extern int NewPlayerY; //��ҵ�ǰ����λ��Y
extern int GameResult; //��һ����Ϸ���
//����������
extern std::vector<Point> PlayerList;
//�����������
extern std::vector<Point> ComputerList;

//���õĵײ㺯����װ
//�Է�����
extern int Opposite(int a); 
//������ǰ����
extern void SwitchSide();
//x��4������
extern int DirectionX[4];
//y��4������
extern int DirectionY[4];
//��ȡ����ĳλ��ֵ��1��2��0��-1Խ��
extern int GetPlace(int x, int y);
//�ж�����ĳλ���Ƿ����ھ�
extern bool JudgeNeighbor(int x, int y);

//ʵ���ø���ȫ�ֱ���
//��һ����Ϸ�ܹ��������弸��
extern int TotalSearchMove;
//��������
extern int SearchNum;
//��֦����
extern int CutNum;
//��һ����Ϸ�ܹ���������
extern int TotalSearchNum;
//��һ����Ϸ�ܹ���֦����
extern int TotalCutNum;
//��һ����Ϸ�ܹ�����ʱ��
extern int TotalCostTime;
#endif
