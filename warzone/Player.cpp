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

bool compareTerritories(Territory* i, Territory* j) {
	return i->getName().compare(j->getName()) < 0;
}

const vector<Territory*>* Player::toDefend()   //returns territories the player can defend
{
	std::sort(this->territories->begin(), this->territories->end(), compareTerritories);
	return this->territories;
}

const vector<Territory*> Player::toAttack()   //returns territories the player can attack
{
	// TODO make sure this gets destructed at some point... or return by value
	vector<Territory*> toAttack = vector<Territory*>();

	for (std::vector<Territory*>::iterator it = this->territories->begin(); it != this->territories->end(); it++) {
		Territory* territory = *it;

		for (std::vector<Territory*>::const_iterator it2 = territory->getBorders()->begin(); it2 != territory->getBorders()->end(); it2++) {
			Territory* neighbor = *it2;

			if (std::find(toAttack.begin(), toAttack.end(), neighbor) == toAttack.end()) {
				toAttack.push_back(neighbor);
			}
		}
	}

	std::sort(toAttack.begin(), toAttack.end(), compareTerritories);

	return toAttack;
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
	// Execute on the adjacent enemy territory with the most troops
	auto enemies = toAttack();
	int maxTroops = enemies.at(0)->getArmies();
	Territory* territoryWithMaxTroops = enemies.at(0);
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		if ((*it)->getArmies() > maxTroops) {
			maxTroops = (*it)->getArmies();
			territoryWithMaxTroops = (*it);
		}
	}

	return new BombOrder(this, territoryWithMaxTroops);
}

NegotiateOrder* Player::useDiplomacy() {
	// Use on a player adjacent to us
	return new NegotiateOrder(this, toAttack().at(0)->getOwner());
}

AirliftOrder* Player::useAirlift() {
	// Randomly move some troops around
	auto defend = toDefend();

	int index1 = rand() % defend->size();
	int index2 = rand() % defend->size();
	return new AirliftOrder(this, 3, defend->at(index1), defend->at(index2));
}

BlockadeOrder* Player::useBlockade() {
	// Blockade a random territory
	auto defend = toDefend();
	int index = rand() % defend->size();
	return new BlockadeOrder(this, defend->at(index));
}

DeployOrder* Player::useReinforcement() {
	// Reinforce our territory with least reinforcements
	auto defendedTerritories = toDefend();

	int min = defendedTerritories->at(0)->getArmies() + defendedTerritories->at(0)->getIncomingArmies();
	Territory* territoryWithLeast = defendedTerritories->at(0);

	for (std::vector<Territory*>::const_iterator it = defendedTerritories->begin(); it != defendedTerritories->end(); it++) {
		if ((*it)->getArmies() + (*it)->getIncomingArmies() < min) {
			territoryWithLeast = (*it);
		}
	}

	return new DeployOrder(this, 7, territoryWithLeast);
}

bool Player::issueOrder() {
	const std::vector<Territory*>* defendedTerritories = this->toDefend();
	int defendedTerritoryCount = defendedTerritories->size();

	// Deploy order
	if (this->reinforcementPool > 0) {
		this->territoriesWithAdvanceOrder->clear();

		// Reinforce the highest priority territory with the least armies
		int min = defendedTerritories->at(0)->getArmies() + defendedTerritories->at(0)->getIncomingArmies();
		Territory* territoryWithLeast = defendedTerritories->at(0);
		for (std::vector<Territory*>::const_iterator it = defendedTerritories->begin(); it != defendedTerritories->end(); it++) {
			if ((*it)->getArmies() + (*it)->getIncomingArmies() < min) {
				territoryWithLeast = (*it);
			}
		}

		this->reinforcementPool -= 1;
		this->ordersList->add(new DeployOrder(this, 1, territoryWithLeast));
		territoryWithLeast->setIncomingArmies(territoryWithLeast->getIncomingArmies() + 1);
		return true;
	}

	// Play cards from hand
	const std::vector<Card*>* cards = this->hand->getCurrentHand();
	if (cards->size() > 0) {
		// Because Jun is smart, this will issue the order and add it to the orderList for us.
		this->hand->play(0);
		return true;
	}

	// Advance orders
	// Advance order has 
	// int - number of armies
	// territory source and territory target
	// owner

	// Issue one advance order per territory
	// Move all but 2-3 troops (move all troops?) to an adjacent enemy territory
	// If there are no adjacent enemy territories move all troops to a random adjacent friendly territory
	
	for (auto it = defendedTerritories->begin(); it != defendedTerritories->end(); it++) {
		if (std::find(this->territoriesWithAdvanceOrder->begin(), this->territoriesWithAdvanceOrder->end(), *it) == this->territoriesWithAdvanceOrder->end()) {
			
			Territory* territory = *it;
			// Don't issue an advance order if there are no armies
			if (territory->getArmies() + territory->getIncomingArmies() == 0) {
				territoriesWithAdvanceOrder->push_back(territory);
				continue;
			}

			const std::vector<Territory*>* adjacentTerritories = (*it)->getBorders();
			
			// Look for adjacent territory that belongs to an enemy
			for (auto it2 = adjacentTerritories->begin(); it2 != adjacentTerritories->end(); it2++) {
				if ((*it2)->getOwner() != this) {
					//It is an enemy territory; attack!
					int numberOfArmies = territory->getArmies() + territory->getIncomingArmies();
					Territory* source = territory;
					Territory* target = (*it2);
					Player* owner = this;
					this->ordersList->add(new AdvanceOrder(this, numberOfArmies, source, target));
					this->territoriesWithAdvanceOrder->push_back(territory);
					return true;
				}
			}

			// No adjacent territory that belongs to an enemy
			// Let's send all our troops to a neighbor then
			int index = rand() % (adjacentTerritories->size());

			int numberOfArmies = territory->getArmies() + territory->getIncomingArmies();
			Territory* source = territory;
			Territory* target = adjacentTerritories->at(index);
			this->ordersList->add(new AdvanceOrder(this, numberOfArmies, source, target));
			this->territoriesWithAdvanceOrder->push_back(territory);
			return true;
		}
	}

	// Done issuing orders
	return false;
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
void Player::grantTerritory(Territory* territory)
{
	territory->setOwner(this);
	this->territories->push_back(territory);

}
ostream& operator<<(ostream& output, const Player &player)  //output stream
{
	output << "Player Information:" << endl;
	output << "Hand: " << *player.hand << endl;
	output << "Territories: " << player.territories<< endl;
	output << "Orders list: " << *player.ordersList<< endl;
	return output;
}
