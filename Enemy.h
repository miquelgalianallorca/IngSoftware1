#pragma once

class Enemy {
public:
	Enemy();
	void Init(const unsigned int _lineSize);

	void Update();

	int  GetPos()     const;
	char GetGraphic() const;

private:
	int       pos;
	Direction dir;
	char      graphic;
};