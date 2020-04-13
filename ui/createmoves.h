#ifndef _CREATEMOVES_
#define _CREATEMOVES_

//��ȡ���ߵĲ������ϣ����ҽ��������֦

/*
��������ȡ���ƶ���λ�ü��ϣ�û�������������ų���̫����λ�õĹ���
��������
���أ�Ԫ�ؼ���
*/
vector<Point> CreateMovesNaive();

/*
��������ȡ���ƶ���λ�ü��ϣ�û�����������������ų���̫����λ��
��������
���أ�Ԫ�ؼ���
*/
vector<Point> CreateMovesWithNeighbor();

/*
�������жϵ�ǰλ���Ƿ������ȼ�������������
������x,y�����ȼ���
���أ��Ƿ�
*/
extern bool JudgeInPriorityList(int x, int y, std::vector<Point> PriorityList);

/*
��������ȡ���ƶ���λ�ü��ϣ����������ϴ�������Χ��λ�ã��ų���Χû���κ����ӵ�λ��
��������
���أ�Ԫ�ؼ���
*/
extern vector<Point> CreateMoves();
#endif

