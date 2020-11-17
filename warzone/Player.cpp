#include "Player.h"


Player::Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Deck* deckToTakeFrom) { //Constructor with all parameters
	this->playerTerritories = territoriesToAdd;
	this->playerOrdersList = playerList;
	this->playerHand = new Hand(deckToTakeFrom, this);
	this->reinforcementPool = 0;
}

Player::~Player() {  //destructor 
	delete playerTerritories;
	delete playerHand;
	delete playerOrdersList;
}


Player* Player::operator=(const Player & one)  //assignment operator
{
	return new Player(one);
}

Player::Player(const Player& player)  //copy constructor
{
	for (Territory* t : *player.playerTerritories)
	{
		Territory* temp = new Territory(t);
		this->playerTerritories->push_back(temp);    //copies each territory in the incoming player's territories 
	}
	this->playerOrdersList = new OrdersList(*player.playerOrdersList);
	this->playerHand = new Hand(*player.playerHand);
	this->reinforcementPool = player.reinforcementPool;
}

const vector<Territory*>* Player::toDefend()   //returns territories the player can defend
{
	vector<Territory*>* toDefend = new vector<Territory*>(); //TODO- Add actual territories to defend later
	return toDefend;
}

const vector<Territory*>* Player::toAttack()   //returns territories the player can attack
{
	vector<Territory*>* toAttack = new vector<Territory*>(); //TODO - Add actual territories to attack later
	return toAttack;
}

void Player::issueOrder(Order* newOrder)  //allows player to issue an order
{
	// TODO
	// Order* playerOrder = new Order(*newOrder);
	// playerOrdersList->add(playerOrder);
}

 vector<Territory*>* Player::getTerritories()  //returns all the player's territories 
{
	return playerTerritories;
}


OrdersList* Player::getOrdersList()   //returns the player's order list
{
	return playerOrdersList;
}

Hand* Player::getHand()  //returns the cards in the player's hand
{
	return playerHand;
}

void Player::setTerritories(vector<Territory*>* territoriesToAdd) //sets all the player's territories 
{
	this->playerTerritories = territoriesToAdd;
}

// Used to add a single territory to the list of territories.
void Player::addTerritory(Territory* territoryToAdd)
{
	// TODO Do I need to dereference this?
	this->playerTerritories->push_back(territoryToAdd);
}

void Player::setOrdersList(OrdersList* ordersList) //sets the player's order list
{
	this->playerOrdersList = ordersList;
}

void Player::setHand(Hand* handToAdd)  //sets the cards in the player's hand
{
	this->playerHand = handToAdd;
}

void Player::addReinforcements(int addedReinforcements)
{
	this->reinforcementPool += addedReinforcements;
}

int Player::getReinforcements()
{
	return this->reinforcementPool;
}

ostream& operator<<(ostream& output, const Player &player)  //output stream
{
	output << "Player Information:" << endl;
	output << "Hand: " << *player.playerHand << endl;
	output << "Territories: " << player.playerTerritories<< endl;
	output << "Orders list: " << *player.playerOrdersList<< endl;
	return output;
}
