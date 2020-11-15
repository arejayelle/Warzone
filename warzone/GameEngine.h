#pragma once
#include <string>
#include <iostream>
#include <filesystem>
#include "Player.h" 
#include "Map.h"
#include "MapLoader.h"

using namespace std;

class GameEngine
{
private:
	int numberOfPlayers =5;
	string mapName;
	bool observersOn;
	string* fileNamesArray;
	Player* playerArray;
public:
	GameEngine();
	~GameEngine();
	void startupPhase();
};

