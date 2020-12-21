#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "windows.h"
#include <string>

using namespace std;

bool gameover; // проверка на проигрыш

const int width = 30; // размеры карты
const int height = 20;

int snakeX, snakeY; //координаты головы змеи
int fruitX, fruitY, score;//координаты фрукта и счет игры
int tailX[100], tailY[100], Ntail; //хвост змеи, Ntail - размер хвоста

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };// виды движения
eDirection dir;

void setup() { // начальные параметры при запуске игры
	gameover = false;
	SetConsoleTitle(L"Snake");
	dir = STOP;
	snakeX = height / 2;
	snakeY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
// надо сделать 2-ную буферизацию, чтобы избавиться от бликов
void draw() { // процедура прорисовывания картинки
	system("cls");//очистить консольное окно, начать рисовать новый кадр
	Sleep(100); // задержка в 1/10 секунды
	for (int i = 0; i < width; ++i)
		cout << "Z";
	cout << endl;

	for (int i = 0; i < height; ++i) { // прорисовка карты
		for (int j = 0; j < width - 1; ++j) {//верхний край
			if (j == 0 || j == width - 2)// правый и левый края
				cout << "H";
			if (i == snakeY && j == snakeX)// головы змеи
				cout << "0";
			else if (i == fruitY && j == fruitX)// фрукта
				cout << "$";
			else {
				bool drawTail = false;// рисовать ли хвост
				for (int k = 0; k < Ntail; ++k) {
					if (tailX[k] == j && tailY[k] == i) {
					drawTail = true;
					cout << "%";
				}
				}
				if (!drawTail) cout << " ";// пустое место карты, если хвост не рисовать
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; ++i)// нижний края карты
		cout << "Z";
	cout << endl;
	cout << "Score: " << score; // отображения счета
	Sleep(100);
}

void input() { // настройки клавиш клавиатуры
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

void logic() { // логика игры, проверка правил игры
	int prevX = tailX[0], prevY = tailY[0]; // рисовка хвоста
	int prev2X, prev2Y;
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < Ntail; ++i) { 
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) { // движение при нажатии клавиши
		case LEFT: 
			snakeX--;
			break;
		case RIGHT: 
			++snakeX;
			break;
		case DOWN: // почему-то получилась инверсия движений вверх и вниз
			++snakeY;
			break;
		case UP: 
			snakeY--;
			break;
	}
	
	if (snakeX >= width - 2) // телепортация на противоположный край
		snakeX = 0;			// при достижении края
	else if (snakeX < 0)
		snakeX = width - 3;

	if (snakeY >= height)
		snakeY = 0;
	else if (snakeY < 0)
		snakeY = height - 1;
		
	
	for (int i = 0; i < Ntail; ++i) { // проверка на косания хвоста
		if (tailX[i] == snakeX && tailY[i] == snakeY)
			gameover = true; // если съел хвост проиграл
	}

	if (snakeX == fruitX && snakeY == fruitY) {// проверка на съедение фрукта
		score += 10;
		fruitX = rand() % (width - 1);// генерация нового фрукта
		fruitY = rand() % (height - 1);
		++Ntail; // после поедания фрукта хвост увеличивается
	}
}

int main() {
	setup();
	while (!gameover) { // пока не проиграл рисовать и проверять
		draw();
		input();
		logic();
	}

	return 0;
}

# snake
