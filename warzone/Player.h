#pragma once

using namespace std;

#include<vector>
#include<iostream>


class Player {
public:
	Player(); //constructor 
	Player(Territory* initialTerritories);  //constructor
	~Player();   //destructor
	Player& operator= (const Player* one);  //assignment operator
	Player(const Player& player);  //copy constructor 

	friend ostream& operator<< (ostream& output, const Player &player); //stream overloading
	friend istream& operator>> (istream& input, Player &player);   //stream overloading

	vector<Territory*> toDefend(); //Returns territories to defend
	vector<Territory*> toAttack(); //Returns territories to attack
	//void issueOrder();
	
private:
	vector<Territory*>* playerTerritory; //returns player's territories
//	vector<Order*>* playerOrders; //returns player's orders
//	Hand* playerHand; //returns player's hand
};