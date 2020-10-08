#pragma once

using namespace std;
#include "Map.h"
#include "Hand.h"
#include "Orders.h"
#include<vector>
#include<iostream>


class Player {
public:
	Player(); //constructor 
	Player(vector<Territory*>* territoriesToAdd, vector<Orders*>* ordersToAdd, Hand* handToAdd);  //constructor
	~Player();   //destructor
	Player& operator= (const Player* one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player &player); //stream overloading
	friend istream& operator>> (istream& input, Player &player);   //stream overloading

	vector<Territory*> toDefend(); //Returns territories to defend
	vector<Territory*> toAttack(); //Returns territories to attack
	//void issueOrder();

	vector<Territory*>* getTerritories(); //get territories
	vector<Orders*>* getOrders(); //get orders
	Hand* getHand(); //get hand

	void setTerritories(vector<Territory*>* territoriesToAdd);  //set territories 
	void setOrders(vector<Orders*>* ordersToAdd); //set orders
	void setHand(Hand* handToAdd);  //set hand
	
private:
	vector<Territory*>* playerTerritory; //returns player's territories
	vector<Orders*>* playerOrders; //returns player's orders
	Hand* playerHand; //returns player's hand
};
