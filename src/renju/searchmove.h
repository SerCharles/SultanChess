#ifndef _SEARCHMOVE_
#define _SEARCHMOVE_
//��������

/*
����������AI����λ��
��������
���أ���
*/
extern void SearchMove();

/*
������minimax��������������ֵȡ��ֵ��ʱ����max����ֵ��ʱ����min
��������ǰside����ȣ�alpha��betaֵ
*/
extern int MiniMax(int Side, int Depth, int alpha, int beta);

/*
��������ӡ����һ�ֵ�ʵ����
��������
���أ���
*/
extern void PrintLog();



#endif
