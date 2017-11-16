#pragma once

class MeteoManager {
public:
	MeteoManager();
	~MeteoManager();
	void Init(const unsigned int _dropSpawnTime);

	void Update();

	char GetGraphicAt(const unsigned int _pos) const;

private:
	enum class DropState { Fall, Splash, End, Nothing };
	
	class RainDrop {
	public:
		RainDrop(unsigned int _posX, unsigned int _posY);

	private:
		DropState    state;
		unsigned int posX;
		unsigned int posY;
	};
	
	// Raindrop graphics
	char   graphicFall;
	char   graphicSplash;
	char   graphicEnd;
	char   graphicGround;
	// Basic line
	/*char * groundLine;
	char * upperLine;*/
	
	std::vector<RainDrop> rainDrops;

	unsigned int dropSpawnTime;
	unsigned int dropTimer;
};