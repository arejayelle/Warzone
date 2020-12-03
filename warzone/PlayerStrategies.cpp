#include "PlayerStrategies.h";

/// <summary>
/// Default constructor for PlayerStrategy
/// </summary>
PlayerStrategy::PlayerStrategy()
{

}

/// <summary>
/// Copy constructor that does nothing since PlayerStrategy has no member variables.
/// </summary>
PlayerStrategy::PlayerStrategy(const PlayerStrategy& other)
{

}

/// <summary>
/// Assignment operator that does nothing since PlayerStrategy has no member variables.
/// </summary>
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& other)
{
	return *this;
}

/// <summary>
/// Outputs "PlayerStrategy" to the console.
/// </summary>
ostream& operator<<(ostream& output, const PlayerStrategy& player)
{
	return output << "PlayerStrategy";
}

/// <summary>
/// Default constructor for DefaultStrategy
/// </summary>
DefaultStrategy::DefaultStrategy()
{

}

/// <summary>
/// Copy constructor that does nothing since DefaultStrategy has no member variables.
/// </summary>
DefaultStrategy::DefaultStrategy(const DefaultStrategy& other)
{
	
}

/// <summary>
/// Assignment operator that does nothing since DefaultStrategy has no member variables.
/// </summary>
DefaultStrategy& DefaultStrategy::operator=(const DefaultStrategy& other)
{
	return *this;
}

/// <summary>
/// Prints "DefaultStrategy" to the console
/// </summary>
ostream& operator<<(ostream& output, const DefaultStrategy& other)
{
	return output << "DefaultStrategy";
}

/// <summary>
/// Compares two territories, i and j, based on lexicographical/alphabetical order.
/// Returns True if the first territory is smaller than the second.
/// </summary>
bool compareTerritoriesAlphabetically(Territory* i, Territory* j) {
	return i->getName().compare(j->getName()) < 0;
}

/// <summary>
/// Returns the list of territories to defend. This implementation returns the player's
/// territories sorted by lexicographical order.
/// </summary>
const vector<Territory*>* DefaultStrategy::toDefend(Player* player)
{
	std::sort(player->getTerritories()->begin(), player->getTerritories()->end(), compareTerritoriesAlphabetically);
	return player->getTerritories();
}

/// <summary>
/// Returns the list of territories to attack. This implementation returns all territories
/// adjacent to owned territories that belong to other players, sorted alphabetically.
/// </summary>
const vector<Territory*> DefaultStrategy::toAttack(Player* player)
{
	// TODO make sure this gets destructed at some point... or return by value
	vector<Territory*> toAttack = vector<Territory*>();

	for (std::vector<Territory*>::iterator it = player->getTerritories()->begin(); it != player->getTerritories()->end(); it++) {
		Territory* territory = *it;

		for (std::vector<Territory*>::const_iterator it2 = territory->getBorders()->begin(); it2 != territory->getBorders()->end(); it2++) {
			Territory* neighbor = *it2;

			if (std::find(toAttack.begin(), toAttack.end(), neighbor) == toAttack.end()) {
				toAttack.push_back(neighbor);
			}
		}
	}

	std::sort(toAttack.begin(), toAttack.end(), compareTerritoriesAlphabetically);

	return toAttack;
}

/// <summary>
/// Issues an order to the player's OrderList. Returns true if an order was issued, returns false if
/// the player decides to not issue an order this time. The order is added directly to the OrdersList.
/// This strategy spreads its reinforcements evenly across all its territories, plays cards as soon
/// as it can, and issues one advance order per territory. It advances all but 2-3 units in a territory
/// to an adjacent enemy territory, and if there are no adjacent territories it moves all units to a
/// random adjacent friendly territory.
/// </summary>
bool DefaultStrategy::issueOrder(Player* player)
{
	const std::vector<Territory*>* defendedTerritories = player->toDefend();
	int defendedTerritoryCount = defendedTerritories->size();

	// Deploy order
	if (player->getReinforcements() > 0) {
		player->getTerritoriesWithAdvanceOrder()->clear();

		// Reinforce the highest priority territory with the least armies
		int min = defendedTerritories->at(0)->getArmies() + defendedTerritories->at(0)->getIncomingArmies();
		Territory* territoryWithLeast = defendedTerritories->at(0);
		for (std::vector<Territory*>::const_iterator it = defendedTerritories->begin(); it != defendedTerritories->end(); it++) {
			if ((*it)->getArmies() + (*it)->getIncomingArmies() < min) {
				territoryWithLeast = (*it);
			}
		}

		player->removeReinforcements(1);
		player->getOrdersList()->add(new DeployOrder(player, 1, territoryWithLeast));
		territoryWithLeast->setIncomingArmies(territoryWithLeast->getIncomingArmies() + 1);
		return true;
	}

	// Play cards from hand
	const std::vector<Card*>* cards = player->getHand()->getCurrentHand();
	if (cards->size() > 0) {
		// Because Jun is smart, this will issue the order and add it to the orderList for us.
		player->getHand()->play(0);
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
		auto territoriesWithAdvanceOrder = player->getTerritoriesWithAdvanceOrder();
		if (std::find(territoriesWithAdvanceOrder->begin(), territoriesWithAdvanceOrder->end(), *it) == territoriesWithAdvanceOrder->end()) {

			Territory* territory = *it;
			// Don't issue an advance order if there are no armies
			if (territory->getArmies() + territory->getIncomingArmies() == 0) {
				territoriesWithAdvanceOrder->push_back(territory);
				continue;
			}

			const std::vector<Territory*>* adjacentTerritories = (*it)->getBorders();

			// Look for adjacent territory that belongs to an enemy
			for (auto it2 = adjacentTerritories->begin(); it2 != adjacentTerritories->end(); it2++) {
				if ((*it2)->getOwner() != player) {
					//It is an enemy territory; attack!
					int numberOfArmies = territory->getArmies() + territory->getIncomingArmies();
					Territory* source = territory;
					Territory* target = (*it2);
					Player* owner = player;
					player->getOrdersList()->add(new AdvanceOrder(player, numberOfArmies, source, target));
					territoriesWithAdvanceOrder->push_back(territory);
					return true;
				}
			}

			// No adjacent territory that belongs to an enemy
			// Let's send all our troops to a neighbor then
			int index = rand() % (adjacentTerritories->size());

			int numberOfArmies = territory->getArmies() + territory->getIncomingArmies();
			Territory* source = territory;
			Territory* target = adjacentTerritories->at(index);
			player->getOrdersList()->add(new AdvanceOrder(player, numberOfArmies, source, target));
			territoriesWithAdvanceOrder->push_back(territory);
			return true;
		}
	}

	// Done issuing orders
	return false;
}

/// <summary>
/// Create and return a BombOrder. This implementation issues a bomb order to the territory in
/// toAttack that has the most units in it.
/// </summary>
BombOrder* DefaultStrategy::useBomb(Player* player)
{
	// Execute on the adjacent enemy territory with the most troops
	auto enemies = toAttack(player);
	int maxTroops = enemies.at(0)->getArmies();
	Territory* territoryWithMaxTroops = enemies.at(0);
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		if ((*it)->getArmies() > maxTroops) {
			maxTroops = (*it)->getArmies();
			territoryWithMaxTroops = (*it);
		}
	}

	return new BombOrder(player, territoryWithMaxTroops);
}

/// <summary>
/// Creates and returns a NegotiateOrder. This implementation targets the player
/// that owns the first territory in toAttack.
/// </summary>
NegotiateOrder* DefaultStrategy::useDiplomacy(Player* player)
{
	// Use on a player adjacent to us
	return new NegotiateOrder(player, player->toAttack().at(0)->getOwner());
}

/// <summary>
/// Creates and returns an AirliftOrder. This implementation picks two random
/// friendly territories and moves 3 units from the first to the second.
/// </summary>
AirliftOrder* DefaultStrategy::useAirlift(Player* player)
{
	// Randomly move some troops around
	auto defend = player->toDefend();
	int index1 = rand() % defend->size();
	int index2 = rand() % defend->size();
	return new AirliftOrder(player, 3, defend->at(index1), defend->at(index2));
}

/// <summary>
/// Creates and returns a BlockadeOrder. This implementation blockades a
/// random friendly territory in toDefend.
/// </summary>
BlockadeOrder* DefaultStrategy::useBlockade(Player* player)
{
	// Blockade a random territory
	auto defend = player->toDefend();
	int index = rand() % defend->size();
	return new BlockadeOrder(player, defend->at(index));
}

/// <summary>
/// Creates and returns a DeployOrder matching the specs of a Reinforcement Card.
/// This implementation adds 7 units to the territory in toDefend with the fewest
/// units in it.
/// </summary>
DeployOrder* DefaultStrategy::useReinforcement(Player* player)
{
	// Reinforce our territory with least reinforcements
	auto defendedTerritories = player->toDefend();

	int min = defendedTerritories->at(0)->getArmies() + defendedTerritories->at(0)->getIncomingArmies();
	Territory* territoryWithLeast = defendedTerritories->at(0);

	for (std::vector<Territory*>::const_iterator it = defendedTerritories->begin(); it != defendedTerritories->end(); it++) {
		if ((*it)->getArmies() + (*it)->getIncomingArmies() < min) {
			territoryWithLeast = (*it);
		}
	}

	return new DeployOrder(player, 7, territoryWithLeast);
}



//AggressiveComputerStrategy 


AggressiveComputerStrategy::AggressiveComputerStrategy()
{

}

AggressiveComputerStrategy::AggressiveComputerStrategy(const AggressiveComputerStrategy& other)
{
}

AggressiveComputerStrategy& AggressiveComputerStrategy::operator=(const AggressiveComputerStrategy& other)
{
	return *this;
}
ostream& operator<<(ostream& output, const AggressiveComputerStrategy& other)
{
	return output << "AggressiveStrategy";
}

//Issue Order Phase of Aggressive Computer Strategy.
bool AggressiveComputerStrategy::issueOrder(Player* player)
{
	//Reinforcement phase
	Territory* territoryWithMost = player->toDefend()->at(0);
	//Find territory with most armies
	if (player->getReinforcements() > 0) {
		//Assign the player's reinforcement pool to territory
		player->getOrdersList()->add(new DeployOrder(player, player->getReinforcements(), territoryWithMost));
		player->removeReinforcements(player->getReinforcements());
		territoryWithMost->setIncomingArmies(territoryWithMost->getIncomingArmies() + player->getReinforcements());
		return true;
	}
	// Play cards from hand
	const std::vector<Card*>* cards = player->getHand()->getCurrentHand();
	if (cards->size() > 0) {
		player->getHand()->play(0);
	}

	//Create enemy and neighboring territories
	const std::vector<Territory*>* adjacentTerritories = territoryWithMost->getBorders();
	std::vector<Territory*> enemyTerritories;
	std::vector<Territory*> friendlyTerritories;

	for (int i= 0; i < adjacentTerritories->size(); i++) {
		if (adjacentTerritories->at(i)->getOwner() != player) {
			enemyTerritories.push_back(adjacentTerritories->at(i));
		}
		else {
			friendlyTerritories.push_back(adjacentTerritories->at(i));
		}
	}

	if (territoriesAttacked.size() < enemyTerritories.size()) {
		for (int i = territoriesAttacked.size(); i < enemyTerritories.size(); i++)
		{
			player->getOrdersList()->add(new AdvanceOrder(player, territoryWithMost->getArmies(), territoryWithMost, enemyTerritories.at(i)));
			territoriesAttacked.push_back(enemyTerritories.at(i));
			return true;
		}
	}

	//Fortify strongest territory with neighbors armies if they have armies to give

	if (territoriesDrained.size() < friendlyTerritories.size()) {
		for (int i = territoriesDrained.size(); i < friendlyTerritories.size(); i++)
		{
			player->getOrdersList()->add(new AdvanceOrder(player, territoryWithMost->getArmies(), territoryWithMost, friendlyTerritories.at(i)));
			territoriesDrained.push_back(friendlyTerritories.at(i));
			return true;
		}
	}
	return false;
}

bool compareTerritoriesArmiesAscendingOrder(Territory* i, Territory* j)
{
	return i->getArmies() > j->getArmies();
}

const vector<Territory*>* AggressiveComputerStrategy::toDefend(Player* player)
{
	std::sort(player->getTerritories()->begin(), player->getTerritories()->end(), compareTerritoriesArmiesAscendingOrder);
	return player->getTerritories();

}
const vector<Territory*> AggressiveComputerStrategy::toAttack(Player* player)
{
	vector<Territory*> toAttack = vector<Territory*>();

	for (std::vector<Territory*>::iterator it = player->getTerritories()->begin(); it != player->getTerritories()->end(); it++) {
		Territory* territory = *it;

		for (std::vector<Territory*>::const_iterator it2 = territory->getBorders()->begin(); it2 != territory->getBorders()->end(); it2++) {
			Territory* neighbor = *it2;

			if (std::find(toAttack.begin(), toAttack.end(), neighbor) == toAttack.end()) {
				toAttack.push_back(neighbor);
			}
		}
	}
	return toAttack;

}

BombOrder* AggressiveComputerStrategy::useBomb(Player* player)
{
	// Execute on an enemy territory with the most troops
	auto enemies = toAttack(player);
	int maxTroops = enemies.at(0)->getArmies();
	Territory* territoryWithMaxTroops = enemies.at(0);
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		if ((*it)->getArmies() > maxTroops) {
			maxTroops = (*it)->getArmies();
			territoryWithMaxTroops = (*it);
		}
	}
	return new BombOrder(player, territoryWithMaxTroops);
}

NegotiateOrder* AggressiveComputerStrategy::useDiplomacy(Player* player)
{
	return nullptr;
}

AirliftOrder* AggressiveComputerStrategy::useAirlift(Player* player)
{
	return nullptr;
}


BlockadeOrder* AggressiveComputerStrategy::useBlockade(Player* player)
{
	return nullptr;
}

DeployOrder* AggressiveComputerStrategy::useReinforcement(Player* player)
{
	const std::vector<Territory*>* playerTerritories = player->getTerritories();
	int playerSize = player->getTerritories()->size();
	int maximum = playerTerritories->at(0)->getArmies() + playerTerritories->at(0)->getIncomingArmies();
	Territory* territoryWithMost = playerTerritories->at(0);
	for (int i = 0; i < playerSize; i++) {
		if (playerTerritories->at(i)->getArmies() + playerTerritories->at(i)->getIncomingArmies() > maximum)
			territoryWithMost = playerTerritories->at(i);
	}
	return new DeployOrder(player, 7, territoryWithMost);
}




// NEUTRAL PLAYER
NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other) : PlayerStrategy(other)
{
}
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& other)
{
	return *this;
}
const vector<Territory*>* NeutralPlayerStrategy::toDefend(Player* player)
{
	return player->getTerritories();
}
const vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player)
{
	return *player->getTerritories();
}
bool NeutralPlayerStrategy::issueOrder(Player* player)
{
	return false;
}
BombOrder* NeutralPlayerStrategy::useBomb(Player* player)
{
	return nullptr;
}
NegotiateOrder* NeutralPlayerStrategy::useDiplomacy(Player* player)
{
	return nullptr;
}
AirliftOrder* NeutralPlayerStrategy::useAirlift(Player* player)
{
	return nullptr;
}
BlockadeOrder* NeutralPlayerStrategy::useBlockade(Player* player)
{
	return nullptr;
}
DeployOrder* NeutralPlayerStrategy::useReinforcement(Player* player)
{
	return nullptr;
}
ostream& operator<<(ostream& output, const NeutralPlayerStrategy& other)
{
	return output << "Neutral Strategy";
}
