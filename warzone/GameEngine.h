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
	GameEngine();  //Constructor
	~GameEngine(); //Destructor
	GameEngine* operator= (const GameEngine& engine);  //assignment operator
	GameEngine(const GameEngine& Engine);  //copy constructor 

	friend ostream& operator<< (ostream& output, const GameEngine& engine); //stream overloading
	void startUpPhase();
};

