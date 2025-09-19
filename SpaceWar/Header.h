#pragma once

#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

enum Direction {
	STOP = 0,
	LEFT,
	RIGHT
};

struct coordinates {

	int X;
	int Y;

};

void setup(Direction& dir, coordinates accomSpaceShip[], coordinates accomAsteroid[], const int width, const int widthSpaceShip, const int height, const int heightSpaceShip) {

	srand(time(NULL));

	const int heigthAsteroid = 3, widthAsteroid = 4;

	dir = STOP;
	accomSpaceShip[0].X = width / 2 - widthSpaceShip;
	accomSpaceShip[0].Y = height - heightSpaceShip - 1;

	accomAsteroid[0].X = rand() % width - widthAsteroid - 1;
	accomAsteroid[0].Y = 0;

}

void draw(string spaceShip[], coordinates accomSpaceShip[], coordinates accomAsteroid[], coordinates accomShot[], int score, int numberShot, const int width, const int widthSpaceShip, const int height, const int heightSpaceShip, string healPoints) {

	const int heigthAsteroid = 3, widthAsteroid = 4;
	string asteroid[heigthAsteroid] = { " ** ",
										"****",
										" ** " };


	system("cls");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);

	//int color = rand() % 14 + 1;
	for (int i = 1; i < heightSpaceShip; i++) {
		accomSpaceShip[i].X = accomSpaceShip[0].X;        //инициализация координат строк рисунков
		accomSpaceShip[i].Y = accomSpaceShip[0].Y + i;
	}
	for (int i = 1; i < heigthAsteroid; i++) {
		accomAsteroid[i].X = accomAsteroid[0].X;
		accomAsteroid[i].Y = accomAsteroid[0].Y + i;
	}

	//SetConsoleTextAttribute(h, 8);
	for (int i = 0; i < width + 1; i++) {        //рисуем верхнюю границу поля

		cout << "#";
	}
	cout << endl;

	//SetConsoleTextAttribute(h, 8);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {

				cout << "#";
			}

			//SetConsoleTextAttribute(h, 15);
			for (int k = 0; k < heightSpaceShip; k++) {
				if (i == accomSpaceShip[k].Y && j == accomSpaceShip[k].X) {
					cout << spaceShip[k];
					j += widthSpaceShip;
				}
			}

			//SetConsoleTextAttribute(h, color);

			for (int k = 0; k < heigthAsteroid; k++) {
				if (i == accomAsteroid[k].Y && j == accomAsteroid[k].X) {
					cout << asteroid[k];
					j += widthAsteroid;
				}
			}


		//	SetConsoleTextAttribute(h, 15);
			for (int k = 0; k < numberShot; k++) {
				if (i == accomShot[k].Y && j == accomShot[k].X) {
					cout << "^";
					j++;
				}
			}
			cout << " ";
			//SetConsoleTextAttribute(h, 8);
		}
		cout << endl;
	}

//	SetConsoleTextAttribute(h, 8);
	for (int i = 0; i < width + 1; i++) {     //рисуем нижнюю границу поля
		cout << "#";
	}
	cout << endl;

	//SetConsoleTextAttribute(h, 15);
	cout << "Score: " << score;
	cout << setw(50) << healPoints << endl;
}



void input(Direction& dir, coordinates accomSpaceShip[], coordinates accomShot[], bool& gameOver, int& numberShot, const int widthSpaceShip) {

	if (_kbhit()) {

		switch (_getch()) {
		case 'a': dir = LEFT; break;
		case 'd': dir = RIGHT; break;
		case 'o': gameOver = true; break;
		case ' ': {
			numberShot++;
			accomShot[numberShot].X = accomSpaceShip[0].X + widthSpaceShip / 2;  //задаем начальные координаты очередному выстрелу
			accomShot[numberShot].Y = accomSpaceShip[0].Y;
			if (numberShot == 29) {
				numberShot = 0;
			}
		}
				break;
		}
	}

}

void move(Direction& dir, coordinates accomSpaceShip[], coordinates accomAsteroid[], coordinates accomShot[], int numberShot, const int width, const int widthSpaceShip, const int height) {


	//движение космолёта
	switch (dir) {

	case LEFT: {

		accomSpaceShip[0].X--; //перемещение влевo

		if (accomSpaceShip[0].X < 1) {
			dir = STOP;
		}
	}
			 break;

	case RIGHT: {

		accomSpaceShip[0].X++;   //перемещение вправо

		if (accomSpaceShip[0].X > width - widthSpaceShip - 3) {
			dir = STOP;
		}
	}
			  break;
	}


	//движение астероида 
	const int widthAsteroid = 4, heigthAsteroid = 3;

	for (int k = 0; k < heigthAsteroid; k++) {
		accomAsteroid[k].Y++;

		if (accomAsteroid[heigthAsteroid - 1].Y == height) {
			accomAsteroid[0].X = rand() % width - widthAsteroid - 1;
			accomAsteroid[0].Y = 0;
		}
	}

	//движение выстрела 

	for (int k = 0; k < numberShot; k++) {
		accomShot[k].Y--;

	}
}


void hittingAnAsteroid(coordinates accomShot[], coordinates accomAsteroid[], coordinates accomSpaceShip[], const int width, const int widthSpaceShip, int numberShot, int& score) {
	const int widthAsteroid = 4, heigthAsteroid = 3;

	for (int k = 0; k < numberShot; k++) {
		if ((accomAsteroid[heigthAsteroid - 1].X <= accomShot[k].X && accomShot[k].X <= accomAsteroid[heigthAsteroid - 1].X + widthAsteroid) && accomAsteroid[heigthAsteroid - 1].Y == accomShot[k].Y) {
				score += 10;
				accomAsteroid[0].X = rand() % width - widthAsteroid - 1;          //задаём начальные координаты новому астероиду
				accomAsteroid[0].Y = 0;
				accomShot[k].X = accomSpaceShip[0].X + widthSpaceShip / 2;    //задаем начальные координаты очередному выстрелу
				accomShot[k].Y = accomSpaceShip[0].Y;
				

		}
	}
}

void breakTheShip(coordinates accomSpaceShip[], coordinates accomAsteroid[],   const int widthSpaceShip,  bool& gameOver, string spaceShip[], string& healPoints) {

	const int heightSpaceShip = 3, widthAsteroid = 4, heigthAsteroid = 3;

	string leftBrokenSpaceShip[heightSpaceShip] = { "   _/\\_   ",
													"  _    __\\",
													"   \\/\\/   " };

	string rightBrokenSpaceShip[heightSpaceShip] = { "   _/\\_   ",
													 "/__    _  ",
													 "   \\/\\/   " };

	string fullBrokenSpaceShip[heightSpaceShip] = {  "   _/\\_   ",
													 "  _    _  ",
													 "   \\/\\/   " };

	bool comparison1 = false, comparison2 = false, comparison3 = false;

	for (int i = 0; i < heightSpaceShip; i++) {
		if (spaceShip[i] == leftBrokenSpaceShip[i]) {
			comparison1 = true;
		}
		else {
			comparison1 = false;
			break;
		}
	}

	for (int i = 0; i < heightSpaceShip; i++) {
		if (spaceShip[i] == rightBrokenSpaceShip[i]) {
			comparison2 = true;
		}
		else {
			comparison2 = false;
			break;
		}
	}

	for (int i = 0; i < heightSpaceShip; i++) {
		if (spaceShip[i] == fullBrokenSpaceShip[i]) {
			comparison3 = true;
		}
		else {
			comparison3 = false;
			break;
		}
	}

	if (comparison1) {
		healPoints = "$ $";
		if (accomSpaceShip[0].Y == accomAsteroid[heigthAsteroid - 1].Y && (accomAsteroid[heigthAsteroid - 1].X <= accomSpaceShip[0].X + widthSpaceShip && accomAsteroid[heigthAsteroid - 1].X > accomSpaceShip[0].X + widthSpaceShip / 2)) {
			for (int i = 0; i < heightSpaceShip; i++) {
				spaceShip[i] = fullBrokenSpaceShip[i];
			};
		}
	} 
	else if (comparison2) {
		healPoints = "$ $";
		if (accomSpaceShip[0].Y == accomAsteroid[heigthAsteroid - 1].Y && (accomAsteroid[heigthAsteroid - 1].X >= accomSpaceShip[0].X - 3 && accomAsteroid[heigthAsteroid - 1].X <= accomSpaceShip[0].X + widthSpaceShip / 2)) {
			for (int i = 0; i < heightSpaceShip; i++) {
				spaceShip[i] = fullBrokenSpaceShip[i];
			};
		}
	}
	else if (comparison3) {
		healPoints = "$";
		if (accomSpaceShip[0].Y == accomAsteroid[heigthAsteroid - 1].Y && (accomAsteroid[heigthAsteroid - 1].X >= accomSpaceShip[0].X - 3 && accomAsteroid[heigthAsteroid - 1].X <= accomSpaceShip[0].X + widthSpaceShip / 2 )) {
			gameOver = true;
		}
	}
	else if (accomSpaceShip[0].Y == accomAsteroid[heigthAsteroid - 1].Y && (accomAsteroid[heigthAsteroid - 1].X >= accomSpaceShip[0].X - 3 && accomAsteroid[heigthAsteroid - 1].X < accomSpaceShip[0].X + widthSpaceShip / 2-2)) {
		
	
			for (int i = 0; i < heightSpaceShip; i++) {
				spaceShip[i] = leftBrokenSpaceShip[i];
			}

	}
	else if (accomSpaceShip[0].Y == accomAsteroid[heigthAsteroid - 1].Y && (accomAsteroid[heigthAsteroid - 1].X <= accomSpaceShip[0].X + widthSpaceShip && accomAsteroid[heigthAsteroid - 1].X > accomSpaceShip[0].X + widthSpaceShip / 2-2)) {

		for (int i = 0; i < heightSpaceShip; i++) {
			spaceShip[i] = rightBrokenSpaceShip[i];
		}

	}
	
}

void speedUp(int score) {

	int  timeForSleep = 60;
	Sleep(timeForSleep);

	if (score == 100) {
		timeForSleep = 30;
	}

	if (score == 200) {
		timeForSleep = 15;
	}

	if (score == 300) {
		timeForSleep = 0;
	}

}

void endGame(int score) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
	SetConsoleTextAttribute(h, 4);

	system("cls");

	string GameOver[12] = { "****   *   *   * ***",
						   "*     * *  ** ** *  ",
						   "* ** *   * * * * ***",
						   "*  * ***** *   * *  ",
						   "**** *   * *   * ***",
						   "                    ",
						   "                    ",
						   "**** *   * **** ****",
						   "*  * *   * *    *  *",
						   "*  * *   * **** ****",
						   "*  *  * *  *    * * ",
						   "****   *   **** *  *" };

	for (int i = 0; i < 12; i++) {
		cout << setw(50) << GameOver[i] << endl;
	}
	cout << endl;

	cout << "SCORE: " << score << endl;
	cout << endl;
}