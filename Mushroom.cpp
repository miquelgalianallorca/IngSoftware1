#include "stdafx.h"
#include "Utils.h"
#include "Mushroom.h"

Mushroom::Mushroom() {
	pos     = -1;
	graphic = "o";
}

void Mushroom::Init(const unsigned int _lineSize) {
	pos = rand() % _lineSize;
}

int Mushroom::GetPos() const {
	return pos;
}

char * Mushroom::GetGraphic() const {
	return graphic;
}
