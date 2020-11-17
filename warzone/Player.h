#pragma once

using namespace std;
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

class Map;
class Territory;
class Order;
class OrdersList;
class Deck;
class Hand;

class Player {
public:

	Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Deck* deckToTakeFrom);  //constructor
	~Player();   //destructor

	Player* operator= (const Player& one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player& player); //stream overloading

	const vector<Territory*>* toDefend(); //Returns territories to defend. To keep in Player
	const vector<Territory*>* toAttack(); //Returns territories to attack
	void issueOrder(Order* newOrder);  //Issue order method

	//Getters
	vector<Territory*>* getTerritories(); //Get territories
	Hand* getHand(); //Get hand
	OrdersList* getOrdersList(); //Get order list
	int getReinforcements();

	//Setters
	void setOrdersList(OrdersList* ordersList); //Set territories
	void setTerritories(vector<Territory*>* territoriesToAdd); //Set Orders List
	void addTerritory(Territory* territoryToAdd);  // Add one territory to player's list of territories.
	void setHand(Hand* handToAdd); //Set hand 
	void addReinforcements(int addedReinforcements);

private:
	Hand* playerHand; //returns player's hand
	OrdersList* playerOrdersList; //returns player's order list
	vector<Territory*>* playerTerritories; //returns player's territories
	int reinforcementPool;
};