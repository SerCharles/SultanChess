#ifndef _GAMEOVER_
#define _GAMEOVER_
#include "evaluate.h"

/*
�������жϵ�ǰλ�������Ƿ�ʤ��
���������жϵ�������, ����
���أ��Ƿ�
*/
extern bool JudgeOneShapeSuccess(int Evaluated, ChessShape TheShape);

/*
�������ж���Ϸ����
��������
���أ�0��ûӮ -1������ 1����ʤ�� 2����ʤ��
*/
extern int JudgeWin();

#endif