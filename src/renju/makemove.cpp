#include "define.h"
#include "evaluate.h"
#include "gameover.h"
#include "printchessboard.h"

/*
��������ʼ����Ϸ
��������
���أ���
*/
void InitializeGame()
{
	while (1)
	{
		std::cout << "����Ϸ" << endl;
		std::cout << "���� newblack ѡ���������" << endl;
		std::cout << "���� newwhite ѡ����Ӻ���" << endl;

		std::string TheString;
		std::cin >> TheString;
		if (TheString == "newblack")
		{
			Player = black;
			Computer = white;
			break;
		}
		else if (TheString == "newwhite")
		{
			Player = white;
			Computer = black;
			break;
		}
		cout << "�Ƿ�������������룡" << endl;
	}
	//��������
	CurrentSide = black;

	//���AI���֣���ʼ������������
	if (Player == white)
	{
		int newx = GRID_NUM / 2;
		int newy = GRID_NUM / 2;
		Point newpoint(newx, newy);
		ComputerList.push_back(newpoint);
		chessBoard[newx][newy] = Computer;
		SwitchSide();
	}
}


/*
�����������������
��������
���أ��������巵��1�����Ҹ�������λ�ã����������巵��2���쳣����0��ֱ���˳�-1
*/
int PlayerMove()
{
	std::cout << "���� move x y ������(x,y)" << endl;
	std::cout << "���� unmove ����" << endl;
	std::cout << "���� quit �˳���Ϸ" << endl;


	std::string TheString;
	int x = -1;
	int y = -1;
	std::cin >> TheString;

	if (TheString == "move")
	{
		std::cin >> x >> y;
		if (x <= 0 || x >= GRID_NUM || y <= 0 || y >= GRID_NUM)
		{
			cout << "�Ƿ�λ�ã�Խ�磡" << endl;
			return 0;
		}
		if (chessBoard[x][y] != blank)
		{
			cout << "�Ƿ�λ�ã��˴��ǿգ�" << endl;
			return 0;
		}
		NewPlayerX = x;
		NewPlayerY = y;
		return 1;
	}
	else if (TheString == "unmove")
	{
		return 2;
	}
	else if (TheString == "quit")
	{
		return -1;
	}
	else
	{
		cout << "Invalid order!" << endl;
		return 0;
	}
}

/*
������ִ���������--�������̺�����ջ
��������
���أ���
*/
void makeMove()
{
	if (CurrentSide == Player)
	{
		chessBoard[NewPlayerX][NewPlayerY] = CurrentSide;
		Point NewMove(NewPlayerX, NewPlayerY);
		PlayerList.push_back(NewMove);
	}
	else if (CurrentSide == Computer)
	{
		chessBoard[NewComputerX][NewComputerY] = CurrentSide;
		Point NewMove(NewComputerX, NewComputerY);
		ComputerList.push_back(NewMove);
	}
}


/*
������ִ�л������--�������̺�����ջ
��������
���أ��������巵��true�����򷵻�false
*/
bool unMakeMove()
{
	int size1 = PlayerList.size();
	int size2 = ComputerList.size();
	if (size1 == 0)
	{
		cout << "�޷��ٻ��壡" << endl;
		return false;
	}
	Point PreviousMove1 = PlayerList[size1 - 1];
	chessBoard[PreviousMove1.x][PreviousMove1.y] = blank;
	PlayerList.pop_back();
	if (size2 > 0)
	{
		Point PreviousMove2 = ComputerList[size2 - 1];
		chessBoard[PreviousMove2.x][PreviousMove2.y] = blank;
		ComputerList.pop_back();
	}
	return true;
}

/*
�������ж���Ϸ�Ƿ�����������������Ӧ��Ϣ���������
��������
���أ���������true�����򷵻�false
*/
bool GameOver()
{
	int result = JudgeWin();
	if (result == Player)
	{
		cout << "���ʤ����" << endl;
		GameResult = Player;
	}
	else if (result == Computer)
	{
		cout << "����ʤ����" << endl;
		GameResult = Computer;
	}
	else if (result == -1)
	{
		cout << "���壡" << endl;
		GameResult = blank;
	}
	else
	{
		return false;
	}
	return true;
}

/*
����������
��������
���أ���
*/
void Replay()
{
	while (1)
	{
		std::cout << "�Ƿ�Ҫ���̣�(yes/no)" << endl;
		std::string TheString;
		int x = -1;
		int y = -1;
		std::cin >> TheString;

		if (TheString == "yes")
		{
			break;
		}
		else if (TheString == "no")
		{
			return;
		}
		else
		{
			std::cout << "�Ƿ����룬�����ԣ�" << endl;
		}
	}

	for (int i = 1; i < GRID_NUM; i++)
	{
		for (int j = 1; j < GRID_NUM; j++)
		{
			chessBoard[i][j] = blank;
		}
	}
	print();

	int PlayerFlag = 0;
	int ComputerFlag = 0;
	int CurrentPrint = black;
	for (int i = 0; i < PlayerList.size() + ComputerList.size(); i++)
	{
		if (CurrentPrint == Player)
		{
			int x = PlayerList[PlayerFlag].x;
			int y = PlayerList[PlayerFlag].y;
			chessBoard[x][y] = Player;
			print();
			cout << "�� " << i + 1 << "�������������(" << x << "," << y << ")λ��" << endl;
			PlayerFlag++;
			CurrentPrint = Opposite(CurrentPrint);
		}
		else if (CurrentPrint == Computer)
		{
			int x = ComputerList[ComputerFlag].x;
			int y = ComputerList[ComputerFlag].y;
			chessBoard[x][y] = Computer;
			print();
			cout << "�� " << i + 1 << "��������������(" << x << "," << y << ")λ��" << endl;
			ComputerFlag++;			
			CurrentPrint = Opposite(CurrentPrint);
		}
	}
	if (GameResult == Player)
	{
		cout << "������һ�ʤ" << endl;
	}
	else if (GameResult == Computer)
	{
		cout << "���յ��Ի�ʤ" << endl;
	}
	else if (GameResult == blank)
	{
		cout << "���պ���" << endl;
	}
}