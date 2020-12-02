#pragma once

using namespace std;
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "PlayerStrategies.h"
#include <algorithm>
#include <cstdlib>

class Map;
class Territory;
class Order;
class BombOrder;
class NegotiateOrder;
class AirliftOrder;
class BlockadeOrder;
class DeployOrder;
class OrdersList;
class Deck;
class Hand;
class PlayerStrategy;

class Player {
public:

	Player(std::string name, vector<Territory*>* territoriesToAdd, OrdersList* playerList, Deck* deckToTakeFrom);  //constructor
	~Player();   //destructor

	Player* operator= (const Player& one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player& player); //stream overloading

	const vector<Territory*>* toDefend(); //Returns territories to defend. To keep in Player
	const vector<Territory*> toAttack(); //Returns territories to attack

	// Contains the decision-making for a player to issue an order.
	// The order should be issued to the player's ordersList
	// Return true if an order was issued, false if no order was issued
	bool issueOrder();  //Issue order method

	void addPlayerInNegotiationWith(Player* player);
	bool isInNegotiationWithPlayer(Player* player);
	void clearInNegotiationWith();

	void removeTerritory(Territory* territoryToRemove);

	// Play Cards
	BombOrder* useBomb();
	NegotiateOrder* useDiplomacy();
	AirliftOrder* useAirlift();
	BlockadeOrder* useBlockade();
	DeployOrder* useReinforcement();

	//Getters
	vector<Territory*>* getTerritories(); //Get territories
	Hand* getHand(); //Get hand
	OrdersList* getOrdersList(); //Get order list
	int getReinforcements(); // Get reinforcements
	string getName();
	bool getConqueredTerritoryThisTurn();


	//Setters
	void setOrdersList(OrdersList* ordersList); //Set Orders List 
	void setTerritories(vector<Territory*>* territoriesToAdd); //Set territories
	void addTerritory(Territory* territoryToAdd);  // Add one territory to player's list of territories.
	void setHand(Hand* handToAdd); //Set hand 
	void addReinforcements(int addedReinforcements);
	void removeReinforcements(int removedReinforcements);
	void grantTerritory(Territory* territory);
	void setConqueredTerritoryThisTurn(bool value);
	vector<Territory*>* getTerritoriesWithAdvanceOrder();
	void setStrategy(PlayerStrategy* strategy);

private:
	Hand* hand; //returns player's hand
	OrdersList* ordersList; //returns player's order list
	vector<Territory*>* territories; //returns player's territories
	int reinforcementPool;
	vector<Player*> inNegotiationWith;
	vector<Territory*>* territoriesWithAdvanceOrder;
	string name;
	bool conqueredTerritoryThisTurn;
	PlayerStrategy* playerStrategy;
};