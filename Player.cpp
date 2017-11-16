#include "stdafx.h"
#include "Utils.h"
#include "Player.h"

Player::Player() {
	pos     = lineSize / 2;
	graphic = 'X';
	points  = 0;
	lives   = startingLives;
}

void Player::Move(Direction _dir) {
	if (_dir == Direction::Left) {
		if (pos > 0)            pos--;
	}
	else {
		if (pos < lineSize - 1) pos++;
	}
}

void Player::AddPoints(const unsigned int _points) {
	points += _points;
}

void Player::Damage() {
	if (lives > 0) lives--;
	else {
		// Game over
		lives  = startingLives;
		points = 0;
		pos    = lineSize / 2;
		//TO DO...
	}
}

unsigned int  Player::GetPos()     const { return pos;     }

         char Player::GetGraphic() const { return graphic; }

unsigned int  Player::GetLives()   const { return lives;   }

unsigned int  Player::GetPoints()  const { return points;  }
