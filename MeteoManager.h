#pragma once

class MeteoManager {
public:
	MeteoManager();
	~MeteoManager();
	void Init(const unsigned int _dropSpawnTime);
	void Update();
	char GetGraphicAt(const unsigned int _posX, const unsigned int _posY) const;

private:
	enum class DropState { Fall, Splash, End, SkySpawned };
	class RainDrop {
	public:
		RainDrop(unsigned int _posX, unsigned int _posY);
		unsigned int GetPosX()  const;
		unsigned int GetPosY()  const;
		DropState    GetState() const;
		void         SetState(DropState _state);
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
	char   graphicSky;
	// Lines for drawing
	char * printLine;
	char * skyLine;
	
	std::vector<RainDrop> rainDrops;
	RainDrop * GetRainDropAt(unsigned int _posX, unsigned int _posY);
	void       UpdateRainLine();
	void       UpdateSkyLine();
	
	unsigned int dropSpawnTime;
	unsigned int dropTimer;
};