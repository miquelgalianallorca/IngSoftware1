#pragma once

class MeteoManager {
public:
	enum class RainState{ Fall, Splash, End, Nothing };
	MeteoManager();
	void Init();

	void Update();

private:
	char * graphicFall;
	char * graphicSplash;
	char * graphicEnd;
	std::vector<RainState> line1;
	std::vector<RainState> line2;
	std::vector<RainState> line3;
};