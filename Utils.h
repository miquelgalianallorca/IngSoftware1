#pragma once

// Game globals
const unsigned int startingLives = 3;
const unsigned int lineSize      = 41;

// Movement direction (for bullet type and enemy type)
enum class Direction { Left, Right };

// ASCII Input
struct Key {
	enum { Esc = 27, Z = 122, C = 99, H = 104, J = 106 };
};

unsigned int  Distance(int posA, int posB);
         bool OutOfBounds(int pos);

// Windows console
void ShowConsoleCursor(bool showFlag);
void MoveConsoleCursor(int x, int y);