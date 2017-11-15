#include "stdafx.h"
#include "Utils.h"
#include "Bullet.h"

Bullet::Bullet() {
	pos     = -1;
	dir     = Direction::Left;
	graphic = " ";
}

void Bullet::SetLeftBullet(const unsigned int _pos) {
	pos     = _pos;
	dir     = Direction::Left;
	graphic = "<";
}

void Bullet::SetRightBullet(const unsigned int _pos) {
	pos     = _pos;
	dir     = Direction::Right;
	graphic = ">";
}

void Bullet::Update() {
	// Bullet movement
	if      (dir == Direction::Left)  pos--;
	else if (dir == Direction::Right) pos++;
}

int Bullet::GetPos() const {
	return pos;
}

char * Bullet::GetGraphic() const {
	return graphic;
}