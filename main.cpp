#include<iostream>
#include<conio.h>
#include<windows.h>
#include <cstdlib>
using namespace std;

void gameOverScreen();

bool gameOver;
enum eDirection{STOP = 0, LEFT,RIGHT,UP,DOWN}dir;
const int width = 20;
int score;
int Gspeed = 200;
int height = 20;
int x, y, fruitX, fruitY, ObstacleX, ObstacleY, Obstacle2X, Obstacle2Y;
int tailX[100], tailY[100];
int nTail;

void initialize() {
	score = 0;
	dir = STOP;
	gameOver = false;
	x = width / 2;
	y = height / 2;
	Gspeed = 200;
	int height = 20;
	nTail = 0;
	ObstacleX = rand() % width;
	ObstacleY = rand() % height;
	Obstacle2X = rand() % width;
	Obstacle2Y = rand() % height;
	fruitX = rand() % width;
	fruitY = rand() % height;
	
	return;
}

void setup() {
	 gameOver = false;
	 dir = STOP;
	 x = width / 2;
	 y = height / 2;
	 fruitX = rand() % width;
	 fruitY = rand() % height;
	 ObstacleX = rand() % width;
	 ObstacleY = rand() % height;
	 Obstacle2X = rand() % width;
	 Obstacle2Y = rand() % height;
	 score = 0;

	 return;
}

void draw() {
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "@";
			else if (fruitY > height) 
				fruitY = rand() % height;		
			else if (i == ObstacleY && j == ObstacleX)
				cout << "X";
			else if (i == Obstacle2Y && j == Obstacle2X)
				cout << "X";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}	
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Move with WASD... Press x to quite" << endl;

	return;
}

void input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
	return;
}

void instructionScreen() {
	cout << "In this game you are a snake the 'o' and you must eat the food '@' to grow your score will grow along with you." << endl;
	cout << "You must also avoid the obstacle 'X' on screen as running into those will reduce your score and not only your size\nbut the size of the board." << endl;
	cout << "The game gets faster as time goes on. you lose if the screen gets too small or you run into yourself.\n Are you up for the challenge? <Y>es or <N>o" << endl;

	_getch();
	switch (_getch()) {
	case 'y':
		system("cls");
		return;
		break;
	case 'Y':
		system("cls");
		return;
		break;
	case 'n':
		exit(0);
		break;
	case 'N':
		system("exit");
	}
		return;
}

void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width) x = 0; 
	else if (x < 0) x = width - 1;
	if (y >= height) y = 0; 
	else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		if (Gspeed > 20)
			Gspeed = Gspeed - 20;
		else if (Gspeed <= 20 && Gspeed > 1)
			Gspeed = Gspeed - 1;

		if (Gspeed <= 100) {
			ObstacleX = rand() % width;
			ObstacleY = rand() % height;
		}
		
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
	if (x == ObstacleX && y == ObstacleY)
	{
		if (Gspeed > 20)
			Gspeed = Gspeed - 20;
		else if (Gspeed <= 20 && Gspeed > 1)
			Gspeed = Gspeed - 1;

		score -= 5;
		height--; 
		ObstacleX = rand() % width;
		ObstacleY = rand() % height;
		if(nTail > 0)
			nTail--;
	}
	if (x == Obstacle2X && y == Obstacle2Y)
	{
		if (Gspeed > 20)
			Gspeed = Gspeed - 20;
		else if (Gspeed <= 20 && Gspeed > 1)
			Gspeed = Gspeed - 1;

		score -= 5;
		height--;
		Obstacle2X = rand() % width;
		Obstacle2Y = rand() % height;
		if (nTail > 0)
			nTail--;
	}
	if (height < 5)
		gameOver = true;

	if (Gspeed <= 1) {
		Gspeed = 100;
	}

	return;
}

int main(void) {
	setup();
	instructionScreen();
	 while(gameOver != true) {
		draw();
		input();
		logic();
		Sleep(Gspeed);
	}

	gameOverScreen();
	 
	return 0;
}

void gameOverScreen() {
	system("cls");
	cout << "YOU LOST WITH A SCORE: " << score;
	cout << endl;
	initialize();
	cout << "WOULD YOU LIKE TO PLAY AGAIN? <Y>es or <N>o" << endl;

	_getch();
		switch (_getch()) {
		case 'y':
			system("cls");
			main();
			break;
		case 'Y':
			system("cls");
			main();
			break;
		case 'n':
			exit(0);
			break;
		case 'N':
			system("exit");
		
	}
		return;
}
