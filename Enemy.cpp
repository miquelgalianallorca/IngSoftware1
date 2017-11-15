#include "stdafx.h"
#include "Utils.h"
#include "Enemy.h"

Enemy::Enemy() {
	pos     = -1;
	dir     = Direction::Left;
	graphic = "@";
}

void Enemy::Init(const unsigned int _lineSize) {
	if (rand() % 2 == 0) {
		dir = Direction::Left;
		pos = 0;
	}
	else {
		dir = Direction::Right;
		pos = _lineSize - 1;
	}
}

void Enemy::Update() {
	// Move enemy
	if      (dir == Direction::Left)  pos++;
	else if (dir == Direction::Right) pos--;
}

int Enemy::GetPos() const {
	return pos;
}

char * Enemy::GetGraphic() const {
	return graphic;
}