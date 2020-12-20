#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"
#include <string>

using namespace std;

bool gameover; // �������� �� ��������

const int width = 30; // ������� �����
const int height = 20;

int snakeX, snakeY; //���������� ������ ����
int fruitX, fruitY, score;//���������� ������ � ���� ����
int tailX[100], tailY[100], Ntail; //����� ����, Ntail - ������ ������

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };// ���� ��������
eDirection dir;

void setup() { // ��������� ��������� ��� ������� ����
	gameover = false;
	SetConsoleTitle(L"Snake");
	dir = STOP;
	snakeX = height / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
// ���� ������� 2-��� �����������, ����� ���������� �� ������
void draw() { // ��������� �������������� ��������
	system("cls");//�������� ���������� ����, ������ �������� ����� ����
	Sleep(100); // �������� � 1/10 �������
	for (int i = 0; i < width; ++i)
		cout << "Z";
	cout << endl;

	for (int i = 0; i < height; ++i) { // ���������� �����
		for (int j = 0; j < width - 1; ++j) {//������� ����
			if (j == 0 || j == width - 2)// ������ � ����� ����
				cout << "H";
			if (i == snakeY && j == snakeX)// ������ ����
				cout << "0";
			else if (i == fruitY && j == fruitX)// ������
				cout << "$";
			else {
				bool drawTail = false;// �������� �� �����
				for (int k = 0; k < Ntail; ++k) {
					if (tailX[k] == j && tailY[k] == i) {
					drawTail = true;
					cout << "%";
				}
				}
				if (!drawTail) cout << " ";// ������ ����� �����, ���� ����� �� ��������
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; ++i)// ������ ���� �����
		cout << "Z";
	cout << endl;
	cout << "Score: " << score; // ����������� �����
	Sleep(100);
}

void input() { // ��������� ������ ����������
	if (_kbhit()) {
		switch (_getch()) {
			case 'a': dir = LEFT; break;
			case 'w': dir = UP; break;
			case 's': dir = DOWN; break;
			case 'd': dir = RIGHT; break;
			case 'x': gameover = true; break;
		}
	}
}

void logic() { // ������ ����, �������� ������ ����
	// ������� �����

	switch (dir) { // �������� ��� ������� �������
		case LEFT: 
			snakeX--;
			break;
		case RIGHT: 
			++snakeX;
			break;
		case DOWN: // ������-�� ���������� �������� �������� ����� � ����
			++snakeY;
			break;
		case UP: 
			snakeY--;
			break;
	}
	
	// ������������ �� ��������������� ����
		
	
	for (int i = 0; i < Ntail; ++i) { // �������� �� ������� ������
		if (tailX[i] == snakeX && tailY[i] == snakeY)
			gameover = true; // ���� ���� ����� ��������
	}

	if (snakeX == fruitX && snakeY == fruitY) {// �������� �� �������� ������
		score += 10;
		fruitX = rand() % (width - 1);// ��������� ������ ������
		fruitY = rand() % (height - 1);
		++Ntail; // ����� �������� ������ ����� �������������
	}
}

int main() {
	setup();
	while (!gameover) { // ���� �� �������� �������� � ���������
		draw();
		input();
		logic();
	}

	return 0;
}

# snake
