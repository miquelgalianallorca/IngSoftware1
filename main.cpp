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

int main() {
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
				case Key::Esc: seguir = false;                     break;
				case Key::Z:   world.MovePlayer(Direction::Left);  break;
				case Key::C:   world.MovePlayer(Direction::Right); break;
				case Key::H:   world.AddBullet(Direction::Left);   break;
				case Key::J:   world.AddBullet(Direction::Right);  break;
			}
		}
		world.Update();
		world.Draw();
		Sleep(60);
	}

    return 0;
}
