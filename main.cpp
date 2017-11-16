// Ing1D - Main
// Miquel Galiana Llorca
// Ingenieria del Software

#include "stdafx.h"
#include "Utils.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "MeteoManager.h"
#include "World.h"

using std::vector;

// Tools
void ShowConsoleCursor(bool showFlag);
void MoveConsoleCursor(int x, int y);

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	ShowConsoleCursor(false);

	printf("\n\n");
	printf("                       1D SHOOTER - THE GAME\n");
	printf("                              Z/C - Move    \n");
	printf("                              H/J - Shoot   \n");
	printf("                              Esc - Exit    \n");
	printf("\n\n\n\n");
		
	// Entities
	World world;
	world.Init();

	bool seguir = true;
	while (seguir) {
		// Input
		if (_kbhit()) {
			char input = _getch();
			switch (input) {
				case Key::Esc: seguir = false; break;
				case Key::Z:   world.MovePlayer(Direction::Left);  break;
				case Key::C:   world.MovePlayer(Direction::Right); break;
				case Key::H:   world.AddBullet(Direction::Left);   break;
				case Key::J:   world.AddBullet(Direction::Right);  break;
				///default: printf("%i\n", input);
			}
		}

		world.Update();
		world.Draw();

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

void MoveConsoleCursor(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}