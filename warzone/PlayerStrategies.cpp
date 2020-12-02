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
	player->pass();
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
	player->pass();
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

HumanPlayerStrategy::HumanPlayerStrategy()
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& other)
{
}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& other)
{
	return *this;
}

ostream& operator<<(ostream& output, const HumanPlayerStrategy& other)
{
	return output << "Human Player \"Strategy\"";
}

const vector<Territory*>* HumanPlayerStrategy::toDefend(Player* player)
{
	return player->getTerritories();
}

const vector<Territory*> HumanPlayerStrategy::toAttack(Player* player)
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

int HumanPlayerStrategy::inputIndexLoop(int max) {
	bool isValid = false;
	int index;
	while (!isValid) {
		std::cin >> index;
		if (index < 0 || index >= max) {
			std::cout << "Error: enter a valid value"<<endl;
		}
		else {

		isValid = true;
		}
	}

	return index;
}

char HumanPlayerStrategy::inputYNLoop() {
	bool isValid = false;
	char result;
	while (!isValid) {
		std::cin >> result;
		if (result == 'y' || result == 'n') {
			return result;
		}
		else {
			std::cout << "Error: enter a valid value";
		}
	}
	
}

bool HumanPlayerStrategy::issueOrder(Player* player)
{
	
	if (player->getReinforcements() > 0) {
		return issueDeployOrders(player);
	}

	// play cards from hand
	std::cout << "Would you like to play a card? (y/n)";
	char playCards = inputYNLoop();

	if (playCards == 'y') {
		if (player->getHand()->getNumberOfCardsInHand() > 0)
		{
			return issueCardOrders(player);
		}
		else {
			std::cout << "No more cards in hand" << endl;
		}
	}


	std::cout << "Would you like to advance your armies? (y/n)";
	char advanceArmies = inputYNLoop();
	if (advanceArmies == 'y') return issueAdvanceOrders(player);

	std::cout << "No longer issuing orders"<<endl;
	player->pass();
	return false;
}

bool HumanPlayerStrategy::issueDeployOrders(Player* player) {

	player->getTerritoriesWithAdvanceOrder()->clear();

	// Select deploy target
	auto defendableTerritories = toDefend(player);
	int index = 0;
	std::cout << "printing territories" << endl;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to add armies to? (0 - " << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendableTerritories->size());

	Territory* deployTarget = (*defendableTerritories)[territoryIndex];
	std::cout << "How many armies? (0 - " << player->getReinforcements() << ")";
	int numArmies = inputIndexLoop(player->getReinforcements()+1);
	player->removeReinforcements(numArmies);
	player->getOrdersList()->add(new DeployOrder(player, numArmies, deployTarget));
	deployTarget->setIncomingArmies(deployTarget->getIncomingArmies() + numArmies);

	return true;
}

bool HumanPlayerStrategy::issueCardOrders(Player* player) {
	auto hand = player->getHand();
	int size = hand->getNumberOfCardsInHand();
	if (size > 0) {
		std::cout << *hand << endl;
		std::cout << "Enter the index of the card you want to play";
		int cardIndex = inputIndexLoop(hand->getNumberOfCardsInHand());

		hand->play(cardIndex);
	}
	else {
		std::cout << "No cards in hand";
	}
	return true;
}

bool HumanPlayerStrategy::issueAdvanceOrders(Player* player)
{
	auto defendableTerritories = toDefend(player);
	int index = 0;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to move armies from? (0 -" << (index - 1) << ")";

	int fromIndex = inputIndexLoop(defendableTerritories->size());

	Territory* source = (*defendableTerritories)[fromIndex];
	int totalArmies = source->getArmies() + source->getIncomingArmies();
	std::cout << "How many armies? (0-" << totalArmies << " armies)" << endl;

	int numArmies = inputIndexLoop(totalArmies+1);

	std::cout << "Adjacent Territories to " << source->getName();
	index = 0;
	auto borders = source->getBorders();
	for (auto it = borders->begin(); it != borders->end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to move armies to? (0 -" << (borders->size() - 1) << ")";

	int toIndex = inputIndexLoop(borders->size());

	Territory* target = (*borders)[toIndex];
	player->getOrdersList()->add(new AdvanceOrder(player, numArmies, source, target));


	return true;
}

BombOrder* HumanPlayerStrategy::useBomb(Player* player)
{
	auto enemies = toAttack(player);
	int index = 0;
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to target? (0 -" << (index - 1) << ")";
	int territoryIndex = inputIndexLoop(enemies.size());

	return new BombOrder(player, enemies[territoryIndex]);
}

NegotiateOrder* HumanPlayerStrategy::useDiplomacy(Player* player)
{
	auto enemies = toAttack(player);
	int index = 0;
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to negotiate with? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(enemies.size());
	return new NegotiateOrder(player, enemies[territoryIndex]->getOwner());
}

AirliftOrder* HumanPlayerStrategy::useAirlift(Player* player)
{
	auto defendableTerritories = toDefend(player);
	int index = 0;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to move armies from? (0 -" << (index - 1) << ")";

	int fromIndex = inputIndexLoop(defendableTerritories->size());
	Territory* source = (*defendableTerritories)[fromIndex];
	std::cout << "How many armies? (0 -" << source->getArmies() << ")";
	int numArmies = inputIndexLoop(source->getArmies());

	std::cout << "Which territory would you like to move armies to? (0 -" << (index - 1) << ")";

	int toIndex = inputIndexLoop(defendableTerritories->size());
	Territory* target = (*defendableTerritories)[toIndex];

	return new AirliftOrder(player, numArmies, source, target);
}

BlockadeOrder* HumanPlayerStrategy::useBlockade(Player* player)
{
	auto defendable = *toDefend(player);
	int index = 0;
	for (auto it = defendable.begin(); it != defendable.end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}
	std::cout << "Which territory would you like to blockade? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendable.size());
	return new BlockadeOrder(player, defendable[territoryIndex]);
}

DeployOrder* HumanPlayerStrategy::useReinforcement(Player* player)
{
	auto defendable = *toDefend(player);
	int index = 0;
	for (auto it = defendable.begin(); it != defendable.end(); it++) {
		std::cout << index++ << "\t" << *(*it) << endl;
	}

	std::cout << "Which territory would you like to deploy to? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendable.size());

	return new DeployOrder(player, 7, defendable[territoryIndex]);
}
