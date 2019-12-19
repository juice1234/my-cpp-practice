#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include "common.h"
using namespace std;

#define	GAME_TIME	5	// seconds

static void CountDown( int seconds )
{
	for( int i = seconds; i >= 1; i-- )
	{
		cout << i << "!            \r";
		Sleep(1000); // �ȴ�1��
	}
	return;
}
void GameInput()
{
	cout << "You have only "<< GAME_TIME << " seconds to input!" << endl;
	cout << "Are you ready? ";
	system("pause"); // ��ͣ
	system("cls"); // ����
	system("color 0c"); // ��ɫǰ��ɫ
	CountDown(3); // ����ʱ3��
	// ��ʼ��Ϸ
	cout << "Go!" << endl;
	system("color 0a"); // ��ɫǰ��ɫ

	int start_tm = clock(), pass_tm = 0, n = 0;
	while( pass_tm < GAME_TIME*100 )
	{
		cout << setw(5) << GAME_TIME*100 - pass_tm << ' '; // ��ʾʣ��ʱ��
		if( kbhit()) // �ж��Ƿ��а�������
		{
			int key = getch(); // ��ȡ������ֵ������
			if( key > 0x80 ) // ���ư���
			{
				int key2 = getch(); // ��ȡ���ư����ĵڶ���ֵ
				switch( key2 )
				{
					case KEY_UP:	cout << "��" << ' '; break;
					case KEY_DOWN:	cout << "��" << ' '; break;
					case KEY_LEFT:	cout << "��" << ' '; break;
					case KEY_RIGHT:	cout << "��" << ' '; break;
					default:		cout << (char)key2 << ' ';
				}
				cout << setw(3) << key << ' ' << key2;
			}
			else
				cout << (char)key << ' ' << setw(3) << key << "    ";
			n++;
		}
		cout << '\r';
		Sleep(10);
		pass_tm = (clock() - start_tm)/10; // �����Ѿ�����ʱ��
	}
	// ��Ϸ����
	system("color 0f"); // �ָ�ǰ��ɫ
	cout << setw(5) << 0 << ' ' << endl;
	cout << "You hit " << n << " keys!" << endl;
	WaitExit();
	return;
}