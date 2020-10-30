#pragma once

#include <vector>
#include <iostream>

#include "Map.h"
#include "Player.h"

class GameEngine
{
public:
	GameEngine();
	GameEngine(Map map, std::vector<Player*> Players);

	int mainGameLoop();
	int reinforcementPhase();
	int issueOrdersPhase();
	int executeOrdersPhase();

private:
	Map* map;
	std::vector<Player*> players;

};

