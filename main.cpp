// Ing1D - Main
// Miquel Galiana Llorca
// Ingenieria del Software

#include "stdafx.h"

using std::vector;

struct Key {
	// ASCII
	enum { Esc = 27, Z = 122, C = 99, H = 104, J = 106 };
};

// Movement direction (for bullet type and enemy type)
enum class Direction { Left, Right };

struct Bullet {
	Direction bulletType   = Direction::Left;
	int       bulletPos    = -1;
};

struct Enemy {
	int       enemyPos = -1;
	Direction enemyType = Direction::Left;
};

struct Mushroom {
	int  mushPos = -1;
};

// Points
const int startingLives = 3;
const int pointsEnemyKill = 5;
const int pointsMushroom = 10;

// Remove _ blinking in console
void ShowConsoleCursor(bool showFlag);



int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	ShowConsoleCursor(false);
	printf("\n\n\n\n");

	//Game vars
	bool seguir = true;
	unsigned int  gPoints = 0;
	unsigned int  gLives = startingLives;

	//Char vars
	unsigned int charPos = 20;
	const unsigned int lineSize = 41;

	//Entities
	vector<Bullet>   bullets;
	vector<Enemy>    enemies;
	vector<Mushroom> mushrooms;

	const unsigned int enemySpawnTime    = 10;
	const unsigned int mushroomSpawnTime = 20;
	unsigned int enemyTimer    = 0;
	unsigned int mushroomTimer = 0;

	while (seguir) {
		//======================================== UPDATEs		
		//Input
		if (_kbhit()) {
			Bullet b;
			char input = _getch();
			switch (input) {
			case Key::Esc:
				seguir = false;
				break;
			case Key::Z:
				if (charPos > 0) charPos--;
				break;
			case Key::C:
				if (charPos < lineSize - 1) charPos++;
				break;
			case Key::H:
				b.bulletType = Direction::Left;
				b.bulletPos  = charPos - 1;
				bullets.push_back(b);
				break;
			case Key::J:
				b.bulletType = Direction::Right;
				b.bulletPos  = charPos + 1;
				bullets.push_back(b);
				break;
			///default: printf("%i\n", input);
			}
		}

		//Bullet logic
		for (auto it = bullets.begin(); it != bullets.end(); it++) {
			if      (it->bulletType == Direction::Left)  it->bulletPos--;
			else if (it->bulletType == Direction::Right) it->bulletPos++;
		}
		//if (bulletActive) {
		//	if      (bulletType == Direction::Left)  bulletPos--;
		//	else if (bulletType == Direction::Right) bulletPos++;
		//	//Bullet collision with enemy
		//	if (enemyActive && enemyPos == bulletPos) {
		//		enemyActive  = false;
		//		bulletActive = false;
		//		gPoints     += pointsEnemyKill;
		//	}
		//	//Bullet collision with mushroom
		//	if (mushActive && mushPos == bulletPos) {
		//		mushActive   = false;
		//		bulletActive = false;
		//	}
		//}
		//if (bulletPos < 0 || bulletPos >= lineSize) bulletActive = false;

		//Enemy logic
		if (enemyTimer > enemySpawnTime) {
			//Spawn enemy
			//TO DO
			enemyTimer = 0;
		}
		else enemyTimer++;
		for (auto it = enemies.begin(); it != enemies.end(); it++){
			//Move enemy
			if      (it->enemyType == Direction::Left)  it->enemyPos++;
			else if (it->enemyType == Direction::Right) it->enemyPos--;

			//Destroy enemy out of bounds
			if (it->enemyPos < 0 || it->enemyPos >= lineSize)
				enemies.erase(it);
		}
		//if (enemyActive) {
		//	deadTime = 0;
		//	if      (enemyType == Direction::Left)  enemyPos++;
		//	else if (enemyType == Direction::Right) enemyPos--;
		//	//Enemy collision with bullet
		//	if (bulletActive && enemyPos == bulletPos) {
		//		//Kill enemy
		//		enemyActive  = false;
		//		bulletActive = false;
		//		gPoints     += pointsEnemyKill;
		//	}
		//	//Enemy collision with player
		//	if (enemyPos == charPos) {
		//		//If dead reset game
		//		if (gLives == 0) {
		//			gLives  = startingLives;
		//			gPoints = 0;
		//		}
		//		else gLives--;
		//	}
		//}
		////Enemy not active
		//else {
		//	deadTime++;
		//	if (deadTime > spawnTime) {
		//		//Spawn enemy
		//		enemyActive = true;
		//		if (rand() % 2 == 0) {
		//			enemyType = Direction::Left;
		//			enemyPos  = 0;
		//		}
		//		else {
		//			enemyType = Direction::Right;
		//			enemyPos  = lineSize - 1;
		//		} 
		//		spawnTime = rand() % 4 + 1;
		//	}
		//}

		//Mushroom logic
		/*for (auto it = mushrooms.begin(); it != mushrooms.end(); it++) {

		}*/
		//if (mushActive) {
		//	mushDeadTime = 0;
		//	//Character collision with mushroom
		//	if (mushPos == charPos) {
		//		mushActive = false;
		//		gPoints   += pointsMushroom;
		//	}
		//}
		//else {
		//	mushDeadTime++;
		//	if (mushDeadTime > mushSpawnTime) {
		//		//Spawn mushroom
		//		mushPos    = rand() % lineSize;
		//		mushActive = true;
		//		mushSpawnTime = rand() % 12 + 1;
		//	}
		//}

		////======================================== DRAW
		printf("\r"); //Rewrite line
		for (int i = 0; i < lineSize; i++) {
			char *draw = "_";
			
			//Draw character
			if (i == charPos) draw = "X";
			
			//Draw bullets
			for (auto it = bullets.begin(); it != bullets.end(); it++) {
				if (it->bulletPos == i) {
					if      (it->bulletType == Direction::Left)  draw = "<";
					else if (it->bulletType == Direction::Right) draw = ">";
				}
			}
			
			//Draw enemies
			for (auto it = enemies.begin(); it != enemies.end(); i++) {
				if (it->enemyPos == i) draw = "@";
			}
			
			//Draw mushrooms
			for (auto it = mushrooms.begin(); it != mushrooms.end(); i++) {
				if (it->mushPos == i) draw = "o";
			}
			
			printf(draw);
		}
		//printf(" deadTime: %i, spawnTime: %i", deadTime, spawnTime);
		printf(" LIVES: %i    POINTS: %03i", gLives, gPoints);

		Sleep(50);
	}

    return 0;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
