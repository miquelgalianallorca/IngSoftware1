#include "stdafx.h"
#include "Utils.h"

unsigned int Distance(int posA, int posB) {
	return abs(posA - posB);
}

bool OutOfBounds(int pos) {
	if (pos < 0 || pos >= lineSize) return true;
	else return false;
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
	COORD pos = { (short)x, (short)y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}