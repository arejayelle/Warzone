#include "Player.h"


Player::Player(vector<Territory*>* territoriesToAdd, OrdersList* playerList, Deck* deckToTakeFrom) { //Constructor with all parameters
	this->territories = territoriesToAdd;
	this->ordersList = playerList;
	this->hand = new Hand(deckToTakeFrom, this);
	this->reinforcementPool = 0;
	this->inNegotiatonWith = vector<Player*>();
}

Player::~Player() {  //destructor 
	delete territories;
	delete hand;
	delete ordersList;
}


Player* Player::operator=(const Player & one)  //assignment operator
{
	return new Player(one);
}

Player::Player(const Player& player)  //copy constructor
{
	for (Territory* t : *player.territories)
	{
		Territory* temp = new Territory(t);
		this->territories->push_back(temp);    //copies each territory in the incoming player's territories 
	}
	this->ordersList = new OrdersList(*player.ordersList);
	this->hand = new Hand(*player.hand);
	this->reinforcementPool = player.reinforcementPool;
	
	// Copy each player in the new player's inNegotiationWith vector.
	for (Player* p : player.inNegotiatonWith) {
		Player* newPlayer = new Player(*p);
		this->inNegotiatonWith.push_back(newPlayer);
	}
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

// Add a player to the vector inNegotiationWith.
void Player::addPlayerInNegotiationWith(Player* player)
{
	this->inNegotiatonWith.push_back(player);
}

// Return true if the player is found in the vector and false if not found.
bool Player::isInNegotiationWithPlayer(Player* player)
{
	return(std::find(this->inNegotiatonWith.begin(), this->inNegotiatonWith.end(), player) != this->inNegotiatonWith.end());
}

// Removes everything from the vector inNegotiationWith. Should be called at the end of a turn.
void Player::clearInNegotiationWith()
{
	this->inNegotiatonWith.erase(this->inNegotiatonWith.begin(), this->inNegotiatonWith.end());
}

// Remove a territory from the player's list of territories in the case where they lose it.
void Player::removeTerritory(Territory* territoryToRemove) 
{
	vector<Territory*>::iterator index = std::find(this->getTerritories()->begin(), this->getTerritories()->end(), territoryToRemove);
	if (index != this->getTerritories()->end()) {
		this->getTerritories()->erase(index);
	}
}

 vector<Territory*>* Player::getTerritories()  //returns all the player's territories 
{
	return territories;
}


OrdersList* Player::getOrdersList()   //returns the player's order list
{
	return ordersList;
}

Hand* Player::getHand()  //returns the cards in the player's hand
{
	return hand;
}

void Player::setTerritories(vector<Territory*>* territoriesToAdd) //sets all the player's territories 
{
	this->territories = territoriesToAdd;
}

// Used to add a single territory to the list of territories.
void Player::addTerritory(Territory* territoryToAdd)
{
	this->territories->push_back(territoryToAdd);
}

void Player::setOrdersList(OrdersList* ordersList) //sets the player's order list
{
	this->ordersList = ordersList;
}

void Player::setHand(Hand* handToAdd)  //sets the cards in the player's hand
{
	this->hand = handToAdd;
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
	output << "Hand: " << *player.hand << endl;
	output << "Territories: " << player.territories<< endl;
	output << "Orders list: " << *player.ordersList<< endl;
	return output;
}
