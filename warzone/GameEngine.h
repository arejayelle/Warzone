#pragma once
#include <string>
#include <iostream>
#include "Player.h" 
#include "Map.h"
#include "MapLoader.h"



using namespace std;

class GameEngine
{
private:
	Map* map;
	std::vector<Player*> playerArray;
	MapLoader* loader;
public:
	GameEngine();
	~GameEngine();
	void setUpPhase();
	void startUpPhase();
};

