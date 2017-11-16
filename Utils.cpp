#include "stdafx.h"
#include "Utils.h"

unsigned int Distance(int posA, int posB) {
	return abs(posA - posB);
}

bool OutOfBounds(int pos) {
	if (pos < 0 || pos >= lineSize) return true;
	else return false;
}
