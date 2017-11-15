#pragma once

class Bullet {
public:
	Bullet();

	void SetLeftBullet (const unsigned int _pos);
	void SetRightBullet(const unsigned int _pos);
	void Update();

	int    GetPos()     const;
	char * GetGraphic() const;

private:
	Direction dir;
	int       pos;
	char *    graphic;
};