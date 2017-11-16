#include "stdafx.h"
#include "Utils.h"
#include "MeteoManager.h"

MeteoManager::MeteoManager() {
	graphicGround = '_';
	graphicFall   = '|';
	graphicSplash = 'v';
	graphicEnd    = '.';
	dropSpawnTime = 0;
	dropTimer     = 0;
}

MeteoManager::~MeteoManager() {
	/*delete[] groundLine;
	delete[] upperLine;*/
}

void MeteoManager::Init(const unsigned int _dropSpawnTime) {
	dropSpawnTime = _dropSpawnTime;
	// Initialize lines
	/*groundLine = new char[lineSize];
	upperLine  = new char[lineSize];
	for (unsigned int i = 0; i < lineSize; i++) {
		groundLine[i] = graphicGround;
		upperLine[i]  = ' ';
	}*/
}

void MeteoManager::Update() {
	// Spawn raindrops
	if (dropTimer > dropSpawnTime) {
		dropTimer = 0;
		RainDrop rd(rand() % lineSize, 1);
		rainDrops.push_back(rd);
	}
	else dropTimer++;

	// Change drop graphics on ground
	for (auto it = rainDrops.begin(); it != rainDrops.end();) {
		bool deleteDrop = false;
		
		if()

		if (deleteDrop) rainDrops.erase(it);
		else it++;
	}
	/*switch (state) {
		case DropState::Nothing: 
			if (dropTimer > dropSpawnTime) state = DropState::Fall;
			else dropTimer++;
			break;
		case DropState::Fall:   state = DropState::Splash;  break;
		case DropState::Splash: state = DropState::End;     break;
		case DropState::End:     
			state = DropState::Nothing; 
			dropTimer = 0;
			InvertRain();
			break;
	}*/
}

char MeteoManager::GetGraphicAt(const unsigned int _pos) const {
	// Error check
	if (_pos < 0 || _pos >= lineSize) return 'E';
	// Return
	//switch (state) {
	//	case DropState::Nothing: return groundLine[_pos];
	//	/*case DropState::Fall:    return fallLine[_pos];
	//	case DropState::Splash:  return splashLine[_pos];
	//	case DropState::End:     return endLine[_pos];*/
	//	default:                 return 'E';
	//}
	return ' ';
}

MeteoManager::RainDrop::RainDrop(unsigned int _posX, unsigned int _posY) {
	posX = _posX;
	posY = _posY;
}