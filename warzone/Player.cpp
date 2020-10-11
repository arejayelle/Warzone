#include "Player.h"

Player::Player()
{
	this->playerOrdersList = new OrdersList();
}

OrdersList* Player::getOrdersList()
{
	return this->playerOrdersList;
}
