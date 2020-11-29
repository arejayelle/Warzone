#include "Player.h"


Player::Player(string name, vector<Territory*>* territoriesToAdd, OrdersList* playerList, Deck* deckToTakeFrom) { //Constructor with all parameters
	for (std::vector<Territory*>::iterator it = territoriesToAdd->begin(); it != territoriesToAdd->end(); it++) {
		(*it)->setOwner(this);
	}
	this->name = name;
	this->territories = territoriesToAdd;
	this->ordersList = playerList;
	this->hand = new Hand(deckToTakeFrom, this);
	this->reinforcementPool = 0;
	this->inNegotiationWith = vector<Player*>();
	this->territoriesWithAdvanceOrder = new std::vector<Territory*>();
}

Player::~Player() {  //destructor 
	delete territories;
	delete hand;
	delete ordersList;
	delete playerStrategy;
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
	for (Player* p : player.inNegotiationWith) {
		Player* newPlayer = new Player(*p);
		this->inNegotiationWith.push_back(newPlayer);
	}
	this->territoriesWithAdvanceOrder = player.territoriesWithAdvanceOrder;
}

const vector<Territory*>* Player::toDefend()   //returns territories the player can defend
{
	return playerStrategy->toDefend(this);
}

const vector<Territory*> Player::toAttack()   //returns territories the player can attack
{
	return playerStrategy->toAttack(this);
}

// Add a player to the vector inNegotiationWith.
void Player::addPlayerInNegotiationWith(Player* player)
{
	this->inNegotiationWith.push_back(player);
}

// Return true if the player is found in the vector and false if not found.
bool Player::isInNegotiationWithPlayer(Player* player)
{
	return(std::find(this->inNegotiationWith.begin(), this->inNegotiationWith.end(), player) != this->inNegotiationWith.end());
}

// Removes everything from the vector inNegotiationWith. Should be called at the end of a turn.
void Player::clearInNegotiationWith()
{
	this->inNegotiationWith.erase(this->inNegotiationWith.begin(), this->inNegotiationWith.end());
}

// Remove a territory from the player's list of territories in the case where they lose it.
void Player::removeTerritory(Territory* territoryToRemove)
{
	vector<Territory*>:: iterator index = std::find(this->getTerritories()->begin(), this->getTerritories()->end(), territoryToRemove);
	if (index != this->getTerritories()->end()) {
		this->getTerritories()->erase(index);
	}
}

BombOrder* Player::useBomb() {
	return playerStrategy->useBomb(this);
}

NegotiateOrder* Player::useDiplomacy() {
	return playerStrategy->useDiplomacy(this);
}

AirliftOrder* Player::useAirlift() {
	return playerStrategy->useAirlift(this);
}

BlockadeOrder* Player::useBlockade() {
	return playerStrategy->useBlockade(this);
}

DeployOrder* Player::useReinforcement() {
	return playerStrategy->useReinforcement(this);
}

bool Player::issueOrder() {
	return playerStrategy->issueOrder(this);
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
int Player::getReinforcements()
{
	return reinforcementPool;
}
string Player::getName()
{
	return this->name;
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

bool Player::getConqueredTerritoryThisTurn() {
	return conqueredTerritoryThisTurn;
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

void Player::removeReinforcements(int removedReinforcements)
{
	this->reinforcementPool -= removedReinforcements;
}

void Player::grantTerritory(Territory* territory)
{
	territory->setOwner(this);
	this->territories->push_back(territory);

}

void Player::setConqueredTerritoryThisTurn(bool value) {
	conqueredTerritoryThisTurn = value;
}

vector<Territory*>* Player::getTerritoriesWithAdvanceOrder() {
	return territoriesWithAdvanceOrder;
}

void Player::setStrategy(PlayerStrategy* playerStrategy) {
	this->playerStrategy = playerStrategy;
}

ostream& operator<<(ostream& output, const Player &player)  //output stream
{
	output << "Player Information:" << endl;
	output << "Hand: " << *player.hand << endl;
	output << "Territories: " << player.territories<< endl;
	output << "Orders list: " << *player.ordersList<< endl;
	return output;
}
