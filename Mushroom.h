#pragma once

class Mushroom {
public:
	Mushroom();
	void Init(const unsigned int _lineSize);

	int    GetPos()     const;
	char * GetGraphic() const;

private:
	int    pos;
	char * graphic;
};