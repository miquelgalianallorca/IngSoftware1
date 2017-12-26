#include "stdafx.h"
#include "Utils.h"
#include "MeteoManager.h"

MeteoManager::MeteoManager() {
	graphicGround = '_';
	graphicFall   = '|';
	graphicSplash = 'v';
	graphicEnd    = '.';
	graphicSky    = ' ';
	dropSpawnTime = 0;
	dropTimer     = 0;
}

MeteoManager::~MeteoManager() {
	delete[] printLine;
	delete[] skyLine;
}

void MeteoManager::Init(const unsigned int _dropSpawnTime) {
	dropSpawnTime = _dropSpawnTime;
	printLine     = new char[lineSize];
	skyLine       = new char[lineSize];
	for (int i = 0; i < lineSize; i++) {
		printLine[i] = graphicGround;
		skyLine[i]   = graphicSky;
	}
}

void MeteoManager::Update() {
	// Change drop graphics
	std::vector<RainDrop> addQueue;
	for (auto it = rainDrops.begin(); it != rainDrops.end();) {
		bool deleteDrop = false;
		// Ground drops
		if (it->GetPosY() == 0) {
			switch (it->GetState()) {
				case DropState::SkySpawned: 
					it->SetState(DropState::Fall); 
					break;
				case DropState::Fall:   
					it->SetState(DropState::Splash);
					break;
				case DropState::Splash: 
					it->SetState(DropState::End);
					break;
				case DropState::End:   
					printLine[it->GetPosX()] = graphicGround; 
					deleteDrop               = true;              
					break;
			}
		}
		// Air drops
		else if (it->GetPosY() == 1) {
			if (it->GetState() == DropState::SkySpawned) {
				it->SetState(DropState::Fall);
			}
			else {
				// Get space under high raindrop
				// move from up to down
				unsigned int x = it->GetPosX();
				RainDrop *rd = GetRainDropAt(x, 0);
				if (rd) {
					// If there was another drop under this one
					// then reset under and delete this one
					rd->SetState(DropState::Fall);
				}
				else {
					// If there wasn't
					// then add new RainDrop down
					RainDrop newDrop(x, 0);
					addQueue.push_back(newDrop);
				}
				// Remove air drop
				deleteDrop = true;
			}
		}
		if (deleteDrop) it = rainDrops.erase(it);
		else            it++;
	}
	// Add new drops to vector
	for (auto it = addQueue.begin(); it != addQueue.end(); it++) {
		rainDrops.push_back(*it);
	}

	// Update graphics in line
	UpdateRainLine();
	UpdateSkyLine();

	// Spawn raindrops
	if (dropTimer > dropSpawnTime) {
		dropTimer = 0;
		RainDrop rd(rand() % lineSize, 1);
		rainDrops.push_back(rd);
	}
	else dropTimer++;
}

char MeteoManager::GetGraphicAt(const unsigned int _posX, const unsigned int _posY) const {
	// Error check
	if (_posX < 0 || _posX >= lineSize)
		return 'E';
	// Return
	if (_posY == 1) return skyLine[_posX];
	else            return printLine[_posX];
}

void MeteoManager::UpdateRainLine() {
	for (auto it = rainDrops.begin(); it != rainDrops.end(); it++) {
		char graphic = graphicGround;
		if (it->GetPosY() == 0) {
			switch (it->GetState()) {
				case DropState::SkySpawned: graphic = graphicFall;   break;
				case DropState::Fall:   graphic = graphicFall;   break;
				case DropState::Splash: graphic = graphicSplash; break;
				case DropState::End:    graphic = graphicEnd;    break;
				default:                graphic = 'E';
			}
		}
		printLine[it->GetPosX()] = graphic;
	}
}

void MeteoManager::UpdateSkyLine() {
	for (auto it = rainDrops.begin(); it != rainDrops.end(); it++) {
		char graphic = graphicSky;
		if (it->GetPosY() == 1) {
			graphic = graphicFall;
		}
		skyLine[it->GetPosX()] = graphic;
	}
}

MeteoManager::RainDrop::RainDrop(unsigned int _posX, unsigned int _posY) {
	posX  = _posX;
	posY  = _posY;
	state = DropState::SkySpawned;
}

unsigned int MeteoManager::RainDrop::GetPosX() const { return posX; }

unsigned int MeteoManager::RainDrop::GetPosY() const { return posY; }

MeteoManager::DropState MeteoManager::RainDrop::GetState() const { 
	return state; 
}

void MeteoManager::RainDrop::SetState(DropState _state) {
	state = _state;
}

MeteoManager::RainDrop * MeteoManager::GetRainDropAt(unsigned int _posX, unsigned int _posY) {
	for (auto it = rainDrops.begin(); it != rainDrops.end(); it++) {
		if (it->GetPosX() == _posX && it->GetPosY() == _posY)
			return &(*it);
	}
	return nullptr;
}