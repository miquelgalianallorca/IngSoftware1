#pragma once

class Player {
public:
	Player();

	void Move(Direction _dir);
	void AddPoints(const unsigned int _points);
	void Damage();

	unsigned int  GetPos()     const;
	         char GetGraphic() const;
	unsigned int  GetLives()   const;
	unsigned int  GetPoints()  const;

private:
	unsigned int  pos;
	         char graphic;
	unsigned int  points;
	unsigned int  lives;
};