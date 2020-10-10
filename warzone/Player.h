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
	//Player(vector<Territory*>* territoriesToAdd, Orders* ordersToAdd, Hand* handToAdd);  //constructor
	Player(vector<Territory*>* territoriesToAdd, Hand* handToAdd);  //constructor
	~Player();   //destructor
	Player& operator= (const Player& one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player &player); //stream overloading
	//friend istream& operator>> (istream& input, Player &player);   //stream overloading

	vector<Territory*> toDefend(); //Returns territories to defend
	vector<Territory*> toAttack(); //Returns territories to attack
	void issueOrder(Orders* newOrder);

	vector<Territory*>* getTerritories(); //get territories
	//Orders* getOrders(); //get orders
	Hand* getHand(); //get hand
	//OrdersList* getOrdersList(); //get order list

	void setTerritories(vector<Territory*>* territoriesToAdd);  //set territories 
	//void setOrders(Orders* ordersToAdd); //set orders
	//void setOrdersList(OrdersList* ordersList); // set orders list
	void setHand(Hand* handToAdd);  //set hand
	
private:
	vector<Territory*>* playerTerritory; //returns player's territories
	//Orders* playerOrders; //returns player's orders
	//OrdersList* playerOrdersList; //returns player's order list
	Hand* playerHand; //returns player's hand
};
