#include "stdafx.h"
#include "Utils.h"
#include "MeteoManager.h"

MeteoManager::MeteoManager() {
	graphicGround = '_';
	graphicFall   = '|';
	graphicSplash = 'v';
	graphicEnd    = '.';
	state         = DropState::Nothing;
	dropSpawnTime = 0;
	dropTimer     = 0;
}

MeteoManager::~MeteoManager() {
	delete[] groundLine;
	delete[] fallLine;
	delete[] splashLine;
	delete[] endLine;
}

void MeteoManager::Init(const unsigned int _lineSize, const unsigned int _dropSpawnTime) {
	lineSize = _lineSize;
	dropSpawnTime = _dropSpawnTime;
	// Initialize lines
	groundLine = new char[lineSize];
	fallLine   = new char[lineSize];
	splashLine = new char[lineSize];
	endLine    = new char[lineSize];
	for (int i = 0; i < lineSize; i++) {
		groundLine[i] = graphicGround;
		if (i % 2 == 0) {
			fallLine[i]   = graphicFall;
			splashLine[i] = graphicSplash;
			endLine[i]    = graphicEnd;
		}
		else {
			fallLine[i]   = graphicGround;
			splashLine[i] = graphicGround;
			endLine[i]    = graphicGround;
		}
	}
}

void MeteoManager::Update() {
	// Iterate through states
	switch (state) {
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
	}
}

char MeteoManager::GetGraphicAt(const unsigned int _pos) const {
	// Error check
	if (_pos < 0 || _pos >= lineSize) return 'E';
	// Return
	switch (state) {
		case DropState::Nothing: return groundLine[_pos];
		case DropState::Fall:    return fallLine[_pos];
		case DropState::Splash:  return splashLine[_pos];
		case DropState::End:     return endLine[_pos];
	}
}

void MeteoManager::InvertRain() {
	for (int i = 0; i < lineSize; i++) {
		if (fallLine[i] == graphicFall) 
			 fallLine[i] = graphicGround;
		else fallLine[i] = graphicFall;
		if (splashLine[i] == graphicSplash)
			 splashLine[i] = graphicGround;
		else splashLine[i] = graphicSplash;
		if (endLine[i] == graphicEnd) 
			 endLine[i] = graphicGround;
		else endLine[i] = graphicEnd;
	}
}