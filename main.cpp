// Ing1D - Main
// Miquel Galiana Llorca
// Ingenieria del Software

#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include <time.h>

// Key value declarations (ASCII)
//enum Key{ Esc = 27, Z = 122, C = 99, H = 104, J = 106}; 
//Asi es peligroso pq los valores son accesibles desde fuera
//enum class es mejor pero ya no lo podemos usar como ints
struct Key {
	enum { Esc = 27, Z = 122, C = 99, H = 104, J = 106 };
};

// Movement direction (for bullet type and enemy type)
enum class Direction{ Left, Right };

//Points
const int startingLives   = 3;
const int pointsEnemyKill = 5;
const int pointsMushroom  = 10;


// Remove _ blinking in console
void ShowConsoleCursor(bool showFlag);

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	ShowConsoleCursor(false);

	//Game vars
	         bool seguir  = true;
	         char input   = 0;
	unsigned int  gPoints = 0;
	unsigned int  gLives  = startingLives;

	//Char vars
	      unsigned int charPos  = 20;
	const unsigned int lineSize = 41;
	
	//Bullet vars
	bool      bulletActive = false;
	Direction bulletType   = Direction::Left;
	int       bulletPos    = -1;
	
	//Enemy vars
	bool      enemyActive = false;
	int       enemyPos    = -1;
	int       spawnTime   = rand() % 4 + 1;
	int       deadTime    = 0;
	Direction enemyType   = Direction::Left;

	//Mushroom vars
	bool      mushActive    = false;
	int       mushPos       = -1;
	int       mushSpawnTime = rand() % 12 + 1;
	int       mushDeadTime  = 0;


	while (seguir) {
		//======================================== UPDATEs		
		//Input
		if (_kbhit()) {
			input = _getch();
			switch (input) {
			case Key::Esc:
				seguir = false; 
				break;
			case Key::Z:
				if(charPos > 0) charPos--; 
				break;
			case Key::C:
				if(charPos < lineSize - 1) charPos++; 
				break; 
			case Key::H:
				if (!bulletActive) {
					bulletType = Direction::Left;
					bulletPos = charPos - 1;
					bulletActive = true;
				}
				break;
			case Key::J:
				if (!bulletActive) {
					bulletType = Direction::Right;
					bulletPos = charPos + 1;
					bulletActive = true;
				}
				break;
			//default: printf("%i\n", input);
			}
		}
		
		//Auto. bullet movement
		if (bulletActive) {
			if      (bulletType == Direction::Left)  bulletPos--;
			else if (bulletType == Direction::Right) bulletPos++;
			//Bullet collision with enemy
			if (enemyActive && enemyPos == bulletPos) {
				enemyActive  = false;
				bulletActive = false;
				gPoints     += pointsEnemyKill;
			}
			//Bullet collision with mushroom
			if (mushActive && mushPos == bulletPos) {
				mushActive   = false;
				bulletActive = false;
			}
		}
		if (bulletPos < 0 || bulletPos >= lineSize) bulletActive = false;

		//Enemy logic
		if (enemyActive) {
			deadTime = 0;
			if      (enemyType == Direction::Left)  enemyPos++;
			else if (enemyType == Direction::Right) enemyPos--;
			//Enemy collision with bullet
			if (bulletActive && enemyPos == bulletPos) {
				//Kill enemy
				enemyActive  = false;
				bulletActive = false;
				gPoints     += pointsEnemyKill;
			}
			//Enemy collision with player
			if (enemyPos == charPos) {
				//If dead reset game
				if (gLives == 0) {
					gLives  = startingLives;
					gPoints = 0;
				}
				else gLives--;
			}
		}
		//Enemy not active
		else {
			deadTime++;
			if (deadTime > spawnTime) {
				//Spawn enemy
				enemyActive = true;
				if (rand() % 2 == 0) {
					enemyType = Direction::Left;
					enemyPos  = 0;
				}
				else {
					enemyType = Direction::Right;
					enemyPos  = lineSize - 1;
				} 
				spawnTime = rand() % 4 + 1;
			}
		}
		//Disable enemy if out of line
		if (enemyPos < 0 || enemyPos >= lineSize) {
			enemyActive = false;
		}

		//Mushroom logic
		if (mushActive) {
			mushDeadTime = 0;
			//Character collision with mushroom
			if (mushPos == charPos) {
				mushActive = false;
				gPoints   += pointsMushroom;
			}
		}
		else {
			mushDeadTime++;
			if (mushDeadTime > mushSpawnTime) {
				//Spawn mushroom
				mushPos    = rand() % lineSize;
				mushActive = true;
				mushSpawnTime = rand() % 12 + 1;
			}
		}

		////======================================== DRAW
		printf("\r"); //Rewrite line
		for (int i = 0; i < lineSize; i++) {
			//Draw character
			if (i == charPos) printf("X");
			//Draw bullet
			else if (bulletActive && bulletPos == i) {
				if      (bulletType == Direction::Left)  printf("<");
				else if (bulletType == Direction::Right) printf(">");
			}
			//Draw enemy
			else if (enemyActive && enemyPos == i) printf("@");
			//Draw mushroom
			else if (mushActive && mushPos == i)   printf("o");
			//Draw empty line
			else printf("_"); //Line
		}
		//printf(" deadTime: %i, spawnTime: %i", deadTime, spawnTime);
		printf(" LIVES: %i    POINTS: %03i", gLives, gPoints);

		Sleep(100); //0.1s delay
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
