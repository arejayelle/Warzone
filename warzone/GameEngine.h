#pragma once
#include <algorithm>
#include <random>
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
	Deck* gameDeck;
public:
	GameEngine();
	~GameEngine();
	void startUpPhase();
};

