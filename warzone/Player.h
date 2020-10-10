#pragma once

using namespace std;
#include "Map.h"
#include "Hand.h"
#include "Orders.h"

//#include<vector>
//#include<iostream>


class Player {
public:
	Player(); //constructor 
	Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Hand* handToAdd);  //constructor
	~Player();   //destructor
	Player& operator= (const Player& one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player &player); //stream overloading
	//friend istream& operator>> (istream& input, Player &player);   //stream overloading

	const vector<Territory*>* toDefend(); //Returns territories to defend. To keep in Player
	const vector<Territory*>* toAttack(); //Returns territories to attack
	void issueOrder(Order* newOrder);

	const vector<Territory*>* getTerritories(); //get territories
	const Hand* getHand(); //get hand
	const OrdersList* getOrdersList(); //get order list

	void setTerritories(vector<Territory*>* territoriesToAdd);  //set territories 
	void setOrdersList(OrdersList* ordersList); // set orders list
	void setHand(Hand* handToAdd);  //set hand
	
private:
	vector<Territory*>* playerTerritory; //returns player's territories
	OrdersList* playerOrdersList; //returns player's order list
	Hand* playerHand; //returns player's hand
};
