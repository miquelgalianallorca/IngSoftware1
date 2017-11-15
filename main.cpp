// Ing1D - Main
// Miquel Galiana Llorca
// Ingenieria del Software

#include "stdafx.h"

using std::vector;

// ASCII Input
struct Key {
	enum { Esc = 27, Z = 122, C = 99, H = 104, J = 106 };
};

// Movement direction (for bullet type and enemy type)
enum class Direction { Left, Right };

// Entities
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

// Game globals
const unsigned int startingLives   = 3;
const unsigned int pointsEnemyKill = 5;
const unsigned int pointsMushroom  = 10;
const unsigned int lineSize        = 41;

// Utils
         void ShowConsoleCursor(bool showFlag);
unsigned int  Distance(int posA, int posB);
         bool OutOfBounds(int pos);

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	ShowConsoleCursor(false);
	printf("\n\n\n\n");

	// Game vars
	bool seguir = true;
	unsigned int gamePoints = 0;
	unsigned int gameLives  = startingLives;

	// Char vars
	unsigned int charPos = 20;

	// Entities
	vector<Bullet>   bullets;
	vector<Enemy>    enemies;
	vector<Mushroom> mushrooms;

	const unsigned int enemySpawnTime    = 10;
	const unsigned int mushroomSpawnTime = 20;
	      unsigned int enemyTimer        = 0;
	      unsigned int mushroomTimer     = 0;
	
	while (seguir) {
		//======================================== UPDATEs		
		// Input
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

		// Bullet logic
		for (auto itB = bullets.begin(); itB != bullets.end();) {
			
			bool eraseBullet = false;

			// Bullet movement
			if      (itB->bulletType == Direction::Left)  itB->bulletPos--;
			else if (itB->bulletType == Direction::Right) itB->bulletPos++;
			
			// Destroy bullet out of bounds
			if (OutOfBounds(itB->bulletPos)) eraseBullet = true;
			else {
				// Collision bullet/enemy
				for (auto itE = enemies.begin(); itE != enemies.end();) {
					bool eraseEnemy = false;
					if (Distance(itB->bulletPos, itE->enemyPos) <= 1) {
						eraseEnemy  = true;
						eraseBullet = true;
						gamePoints += pointsEnemyKill;
					}
					if (eraseEnemy) itE = enemies.erase(itE);
					else            itE++;
				}
				// Collision bullet/mushroom
				for (auto itM = mushrooms.begin(); itM != mushrooms.end();) {
					bool eraseMushroom = false;
					if (Distance(itB->bulletPos, itM->mushPos) < 1) {
						eraseBullet   = true;
						eraseMushroom = true;
					}
					if (eraseMushroom) itM = mushrooms.erase(itM);
					else               itM++;
				}
			}
			
			if (eraseBullet) itB = bullets.erase(itB);
			else             itB++;
		}

		// Enemy logic
		if (enemyTimer > enemySpawnTime) {
			//Spawn enemy
			Enemy e;
			if (rand() % 2 == 0) {
				e.enemyType = Direction::Left;
				e.enemyPos  = 0;
			}
			else {
				e.enemyType = Direction::Right;
				e.enemyPos  = lineSize - 1;
			}
			enemies.push_back(e);
			enemyTimer = 0;
		}
		else enemyTimer++;

		for (auto it = enemies.begin(); it != enemies.end();){
			bool remove = false;
			//Move enemy
			if      (it->enemyType == Direction::Left)  it->enemyPos++;
			else if (it->enemyType == Direction::Right) it->enemyPos--;
			//Destroy enemy out of bounds
			if (OutOfBounds(it->enemyPos)) remove = true;
			else {
				//Collision enemy/player
				if (Distance(charPos, it->enemyPos) <= 1) {
					remove = true;
					if (gameLives > 0) gameLives--;
					else {
						gameLives  = startingLives;
						gamePoints = 0;
					}
				}
			}
			if (remove) it = enemies.erase(it);
			else        it++;
		}

		// Mushroom logic
		if (mushroomTimer > mushroomSpawnTime) {
			//Spawn mushroom
			Mushroom m;
			m.mushPos = rand() % lineSize;
			mushrooms.push_back(m);
			mushroomTimer = 0;
		}
		else mushroomTimer++;
		for (auto itM = mushrooms.begin(); itM != mushrooms.end();) {
			bool eraseMushroom = false;
			//Collision mushroom/player
			if (Distance(charPos, itM->mushPos) < 1) {
				eraseMushroom = true;
				gamePoints += pointsMushroom;
			}
			if (eraseMushroom) itM = mushrooms.erase(itM);
			else               itM++;
		}
		

		////======================================== DRAW
		printf("\r");
		for (int i = 0; i < lineSize; i++) {
			char *draw = "_";
			
			// Draw character
			if (i == charPos) draw = "X";
			// Draw bullets
			for (auto it = bullets.begin(); it != bullets.end(); it++) {
				if (it->bulletPos == i) {
					if      (it->bulletType == Direction::Left)  draw = "<";
					else if (it->bulletType == Direction::Right) draw = ">";
				}
			}
			// Draw enemies
			for (auto it = enemies.begin(); it != enemies.end(); it++) {
				if (it->enemyPos == i) draw = "@";
			}
			// Draw mushrooms
			for (auto it = mushrooms.begin(); it != mushrooms.end(); it++) {
				if (it->mushPos == i) draw = "o";
			}
			
			printf(draw);
		}
		///printf(" deadTime: %i, spawnTime: %i", deadTime, spawnTime);
		printf(" LIVES: %i    POINTS: %03i", gameLives, gamePoints);

		Sleep(60);
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

unsigned int Distance(int posA, int posB) {
	return abs(posA - posB);
}

bool OutOfBounds(int pos) {
	if (pos < 0 || pos >= lineSize) return true;
	else return false;
}