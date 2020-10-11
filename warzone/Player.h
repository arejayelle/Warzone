#pragma once
using namespace std;
#include "Cards.h"
#include "Orders.h"
#include "Map.h"

class Map;
class Territory;
class Order;

class Player {
public:
	Player();
	Player(vector<Territory*>* territoriesToAdd,  OrdersList* playerList, Cards::Deck* deckToTakeFrom);  //constructor
	~Player();   //destructor
	Player* operator= (const Player& one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player& player); //stream overloading

	const vector<Territory*>* toDefend(); //Returns territories to defend. To keep in Player
	const vector<Territory*>* toAttack(); //Returns territories to attack
	void issueOrder(Order* newOrder);  //Issue order method

	//Getters
	vector<Territory*>* getTerritories(); //Get territories
	Cards::Hand* getHand(); //Get hand
	OrdersList* getOrdersList(); //Get order list

	//Setters
	void setOrdersList(OrdersList* ordersList); //Set territories
	void setTerritories(vector<Territory*>* territoriesToAdd); //Set Orders List
	void setHand(Cards::Hand* handToAdd); //Set hand 

private:
	Cards::Hand* playerHand; //returns player's hand
	OrdersList* playerOrdersList; //returns player's order list
	vector<Territory*>* playerTerritories; //returns player's territories
	Map* playerMap; 
};
