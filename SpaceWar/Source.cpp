#include <iostream>
#include "Header.h"


int main() {

	system("title Космическая война");

	int score = 0;
	bool gameOver = false;
	const int width = 60, widthSpaceShip = 10;
	const int height = 30, heightSpaceShip = 3, heigthAsteroid = 3;
	int numberShot = -1;
	string healPoints = "$ $ $";

	string spaceShip[heightSpaceShip] = { "   _/\\_   ",
										  "/__    __\\",
										  "   \\/\\/   " };

	Direction dir;

	const int qShot = 30;
	coordinates accomSpaceShip[heightSpaceShip], accomAsteroid[heigthAsteroid], accomShot[qShot];

	setup(dir, accomSpaceShip, accomAsteroid, width, widthSpaceShip, height, heightSpaceShip);

	while (!gameOver) {

		draw(spaceShip, accomSpaceShip, accomAsteroid, accomShot, score, numberShot, width, widthSpaceShip, height, heightSpaceShip, healPoints);
		input(dir, accomSpaceShip, accomShot, gameOver, numberShot, widthSpaceShip);
		move(dir, accomSpaceShip, accomAsteroid, accomShot, numberShot, width, widthSpaceShip, height);
		hittingAnAsteroid(accomShot, accomAsteroid, accomSpaceShip, width, widthSpaceShip, numberShot, score);
		breakTheShip(accomSpaceShip, accomAsteroid, widthSpaceShip, gameOver, spaceShip, healPoints);
		speedUp(score);
	}

	endGame(score);



	system("pause");
	return 0;

}