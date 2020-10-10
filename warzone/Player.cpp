#include "Player.h"
#include <iostream>

Player::Player() {
	this->playerTerritory = new vector<Territory*>();
	//this->playerOrders = new Orders();
	this->playerHand = new Hand();
	//this->playerOrdersList = new OrdersList();
}

//Player::Player(vector<Territory*>* territoriesToAdd, Orders* ordersToAdd, Hand* handToAdd) { //add OrdersList in parameters
//	this->playerTerritory = territoriesToAdd;
//	this->playerOrders = ordersToAdd;
//	this->playerHand = handToAdd;
//}

Player::Player(vector<Territory*>* territoriesToAdd, Hand* handToAdd) { //add OrdersList in parameters
	this->playerTerritory = territoriesToAdd;
	this->playerHand = handToAdd;
}

Player::~Player() {
	for (Territory* t : *playerTerritory) {
		delete t;
		t = nullptr;
	}
	delete playerTerritory;
	playerTerritory = nullptr;
	//delete playerOrders;
	//playerOrders = nullptr;
	delete playerHand;
	playerHand = nullptr;
	//delete playerOrdersList;
	//playerOrdersList = nullptr;
}

Player& Player::operator=(const Player& one)  //assignment operator
{
	this->playerHand = one.playerHand;
	//this->playerOrders = one.playerOrders;
	this->playerTerritory = one.playerTerritory;
	//this->playerOrdersList=one.playerOrdersList;
}

Player::Player(const Player& player)  //copy constructor
{

}

vector<Territory*> Player::toDefend()
{

}

vector<Territory*> Player::toAttack()
{
}

void Player::issueOrder(Orders* newOrder)
{

}

vector<Territory*>* Player::getTerritories()
{
	return nullptr;
}

//Orders* Player::getOrders()
//{
//	return nullptr;
//}

Hand* Player::getHand()
{
	return nullptr;
}

void Player::setTerritories(vector<Territory*>* territoriesToAdd)
{
	this->playerTerritory = territoriesToAdd;
}

//void Player::setOrders(Orders* ordersToAdd)
//{
//	this->playerOrders = ordersToAdd;
//}

//void Player::setOrdersList(OrdersList* ordersList)
//{
//	this->playerOrdersList= ordersList
//}

void Player::setHand(Hand* handToAdd)
{
	this->playerHand = handToAdd;
}

ostream& operator<<(ostream& output, const Player& player)
{
	output << "Player Information:"<<endl;
	output << "Hand: "<< player.playerHand<<endl;
	//output << player.playerOrders<<endl;
	output << "Territories: "<< player.playerTerritory<<endl;
	//	output << "Orders list: " <<player.OrdersList<<endl;
	return output;
}

