#include "Player.h"
#include "MapDriver.h"
#include <iostream>

Player::Player() {
	this->playerTerritory = new vector<Territory*>();
	this->playerHand = new Hand();
	//this->playerOrdersList = new OrdersList();
}

Player::Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Hand* handToAdd) { //add OrdersList in parameters
	this->playerTerritory = territoriesToAdd;
	this->playerHand = handToAdd;
	this->playerOrdersList = playerList;
}

Player::~Player() {
	for (Territory* t : *playerTerritory) {
		delete t;
	}
	delete playerTerritory;
	delete playerHand;
	delete playerOrdersList;
}

Player& Player::operator=(const Player& one)  //assignment operator
{	
	delete playerHand;
	this->playerHand = one.playerHand;
	delete playerTerritory;
	this->playerTerritory = one.playerTerritory;
	delete playerOrdersList;
	this->playerOrdersList=one.playerOrdersList;
}

Player::Player(const Player& player)  //copy constructor
{
	for (Territory* t : *player.playerTerritory)
	{
		Territory temp = new Territory(t);
		this->playerTerritory->push_back(t);
	}
	this->playerOrdersList = new OrdersList(*player.playerOrdersList);
	this->playerHand = new Hand(*player.playerHand);
}

const vector<Territory*>* Player::toDefend()
{
	Map* map= MapDriver::getValidMap();
	map->getTerritories();
	return map->getTerritories();
}

const vector<Territory*>* Player::toAttack()
{
	Map* map = MapDriver::getValidMap();
	map->getTerritories();
	return map->getTerritories();
}

void Player::issueOrder(Order* newOrder)
{
	Order* playerOrder = new Order(*newOrder);

}

const vector<Territory*>* Player::getTerritories() 
{
	return playerTerritory;
}

const OrdersList* Player::getOrdersList()
{
	return playerOrdersList;
}

const Hand* Player::getHand()
{
	return playerHand;
}

void Player::setTerritories(vector<Territory*>* territoriesToAdd)
{
	this->playerTerritory = territoriesToAdd;
}

void Player::setOrdersList(OrdersList* ordersList)
{
	this->playerOrdersList= ordersList
}

void Player::setHand(Hand* handToAdd)
{
	this->playerHand = handToAdd;
}

ostream& operator<<(ostream& output, const Player& player)
{
	output << "Player Information:"<<endl;
	output << "Hand: "<< player.playerHand<<endl;
	output << "Territories: "<< player.playerTerritory<<endl;
	output << "Orders list: " <<player.playerOrdersList<<endl;
	return output;
}

