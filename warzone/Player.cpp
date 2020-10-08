#include "Player.h"

Player::Player() {
	this->playerTerritory = new vector<Territory*>();
	this->playerOrders = new vector<Orders*>();
	this->playerHand = 0;
}

Player::Player(vector<Territory*>* territoriesToAdd, vector<Orders*>* ordersToAdd, Hand* handToAdd) {
	this->playerTerritory = territoriesToAdd;
	this->playerOrders = ordersToAdd;
	this->playerHand = handToAdd;
}

Player::~Player() {
	delete playerTerritory;
	delete playerOrders;
	delete playerHand;
}

Player& Player::operator=(const Player* one)
{
	
}

Player::Player(const Player& player)
{
}

vector<Territory*> Player::toDefend()
{
	return vector<Territory*>();
}

vector<Territory*> Player::toAttack()
{
	
}

vector<Territory*>* Player::getTerritories()
{
	return nullptr;
}

vector<Orders*>* Player::getOrders()
{
	return nullptr;
}

Hand* Player::getHand()
{
	return nullptr;
}

void Player::setTerritories(vector<Territory*>* territoriesToAdd)
{
}

void Player::setOrders(vector<Orders*>* ordersToAdd)
{
}

void Player::setHand(Hand* handToAdd)
{
}

ostream& operator<<(ostream& output, const Player& player)
{

}

istream& operator>>(istream& input, Player& player)
{

}
