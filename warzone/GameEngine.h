#pragma once

#include <vector>
#include <iostream>

#include "Map.h"
#include "Player.h"

class GameEngine
{
public:
	GameEngine();
	GameEngine(Map* map, std::vector<Player*> Players);
	~GameEngine();

	int mainGameLoop();
	void reinforcementPhase();
	int issueOrdersPhase();
	int executeOrdersPhase();

	const std::vector<Player*>* getPlayers();

private:
	Map* map;
	std::vector<Player*> players;

};

