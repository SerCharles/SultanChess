#ifndef _EVALUATE_
#define _EVALUATE_
//��ֵ������

//������
struct ChessShape
{
	//��������,1����,2����,0�հ�,-1Խ��
	int List[6];
	//������Чλ�ó���
	int TotalNum;
};

//�÷���״��
struct ScoreShape
{
	//��������,1����,2����,0�հ�,-1Խ��
	int List[6];
	//������Чλ�ó���
	int TotalNum;
	//��������
	Point Place[6];
	//�÷�
	int Score;
	//x����
	int DX;
	//y����
	int DY;
};
extern std::vector<ScoreShape> ScoreList;

/*
�������жϵ�ǰλ�����͵÷�
���������жϵ�������, ����
���أ��÷�
*/
extern int EvaluateOneShape(int Evaluated, ChessShape TheShape);

/*
����������ĳһ��ĵ÷�
��������ǰ��x,y�������Ƶ�������ɫ
���أ��÷�
*/
extern int EvaluateOnePoint(int x, int y, int Evaluated);

/*
�����������ܵ÷�
�����������Ƶ�������ɫ
���أ��÷�
*/
extern int Evaluate(int Evaluated);

/*
�������жϵ�ǰ���Ƿ��ظ�����
��������ǰ��x,y������dx��dy
���أ��Ƿ�
*/
extern bool JudgeRepeat(int x, int y, int dx, int dy);
/*
�������жϵ�ǰ���Ƿ������������е÷֣��еĻ��������ӷ�
��������ǰ��x,y������dx��dy����ǰ�÷�
���أ�����ӷ�
*/
extern int CalculateAddScore(int x, int y, int dx, int dy, int score);
/*
��������ӡ�÷��б�
��������ǰ��x,y������dx��dy����ǰ�÷���
���أ���
*/
extern void PrintScoreList();

#endif
