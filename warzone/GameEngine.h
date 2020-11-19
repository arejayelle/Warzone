#pragma once
#include <algorithm>
#include <random>
#include <string>
#include <iostream>
#include "Player.h" 
#include "Map.h"
#include "Player.h"
#include "GameObservers.h"
#include "MapLoader.h"
#include <sstream>

using namespace std;

class GameEngine
{
public:
	GameEngine();
	GameEngine(Map* map, std::vector<Player*> Players);
	~GameEngine();
	GameEngine* operator= (const GameEngine& engine);  //assignment operator
	GameEngine(const GameEngine& Engine);  //copy constructor 

	friend ostream& operator<< (ostream& output, const GameEngine& engine); //stream overloading
	void startUpPhase();
	int mainGameLoop();
	void reinforcementPhase();
	int issueOrdersPhase();
	int executeOrdersPhase();
	void attachObservers();

	const std::vector<Player*>* getPlayers();
	Deck* getDeck();
	Map* getMap();

private:
	Map* map;
	PhaseObservable* phaseObservable;
	StatsObservable* statsObservable;
	std::vector<Player*> playerArray;
	Deck* gameDeck;

};

