#pragma once

class MeteoManager {
public:
	enum class DropState{ Fall, Splash, End, Nothing };
	MeteoManager();
	~MeteoManager();
	void Init(const unsigned int _lineSize, const unsigned int _dropSpawnTime);

	void Update();
	char GetGraphicAt(const unsigned int _pos) const;

private:
	unsigned int lineSize;
	// Raindrop graphics
	char graphicFall;
	char graphicSplash;
	char graphicEnd;
	char graphicGround;
	// Basic line
	char * groundLine;
	// Rain lines
	char * fallLine;
	char * splashLine;
	char * endLine;
	// State
	DropState state;
	unsigned int dropSpawnTime;
	unsigned int dropTimer;

	void InvertRain();
};