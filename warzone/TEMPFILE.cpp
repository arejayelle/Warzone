#include "PlayerStrategies.h";

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
	int index;
	while (!(std::cin >> index) || index < 0 || index >= max) {
		cout << "Error: enter a valid index";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
	return index;
}

char HumanPlayerStrategy::inputYNLoop() {
	char result;
	while (!(std::cin >> result) || result != 'y' || result != 'n') {
		cout << "Error: enter a valid value";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
	return result;
}

bool HumanPlayerStrategy::issueOrder(Player* player)
{
	int reinforcementPool = player->getReinforcements();

	if (reinforcementPool > 0) {
		return issueDeployOrders(player);
	}

	// play cards from hand
	char playCards;
	cout << "Would you like to play a card? (y/n)";
	playCards = inputYNLoop();

	if (playCards == 'y') {
		if (player->getHand()->getNumberOfCardsInHand()>0)
		{
			return issueCardOrders(player);
		}
		else {
			cout << "No more cards in hand" << endl;
		}
	}
		
	char advanceArmies;
	cout << "Would you like to advance your armies? (y/n)";
	advanceArmies = inputYNLoop();
	if (advanceArmies == 'y') return issueAdvanceOrders(player);

	cout << "No longer issuing orders";
	return false;
}

bool HumanPlayerStrategy::issueDeployOrders(Player* player) {

	player->getTerritoriesWithAdvanceOrder()->clear();
	int reinforcementPool = player->getReinforcements();
	// Select deploy target
	auto defendableTerritories = toDefend(player);
	int index = 0;
	cout << "printing territories" << endl;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to add armies to? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendableTerritories->size());

	Territory* deployTarget = (*defendableTerritories)[territoryIndex];
	int numArmies = inputIndexLoop(reinforcementPool);

	player->getOrdersList()->add(new DeployOrder(player, numArmies, deployTarget));
	deployTarget->setIncomingArmies(deployTarget->getIncomingArmies() + numArmies);

	return true;
}

bool HumanPlayerStrategy::issueCardOrders(Player* player) {
	auto hand = player->getHand();
	int size = hand->getNumberOfCardsInHand();
	if (size > 0) {
		cout << hand << endl;
		cout << "Enter the index of the card you want to play";
		int cardIndex = inputIndexLoop(hand->getNumberOfCardsInHand());
		
		hand->play(cardIndex);
		return true;
	}
}

bool HumanPlayerStrategy::issueAdvanceOrders(Player* player)
{
	auto defendableTerritories = toDefend(player);
	int index = 0;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to move armies from? (0 -" << (index - 1) << ")";

	int fromIndex = inputIndexLoop(defendableTerritories->size());

	Territory* source = (*defendableTerritories)[fromIndex];
	int totalArmies = source->getArmies() + source->getIncomingArmies();
	cout << "How many armies? " << source->getName() << " has " << totalArmies << " armies" << endl;

	int numArmies = inputIndexLoop(totalArmies);

	cout << "Adjacent Territories to " << source->getName();

	auto borders = source->getBorders();
	for (auto it = borders->begin(); it != borders->end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to move armies to? (0 -" << (borders->size() - 1) << ")";

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
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to target? (0 -" << (index - 1) << ")";
	int territoryIndex = inputIndexLoop(enemies.size());

	return new BombOrder(player, enemies[territoryIndex]);
}

NegotiateOrder* HumanPlayerStrategy::useDiplomacy(Player* player)
{
	auto enemies = toAttack(player);
	int index = 0;
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to negotiate with? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(enemies.size());
	return new NegotiateOrder(player, enemies[territoryIndex]->getOwner());
}

AirliftOrder* HumanPlayerStrategy::useAirlift(Player* player)
{
	auto defendableTerritories = toDefend(player);
	int index = 0;
	for (auto it = defendableTerritories->begin(); it != defendableTerritories->end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to move armies from? (0 -" << (index - 1) << ")";

	int fromIndex = inputIndexLoop(defendableTerritories->size());

	Territory* source = (*defendableTerritories)[fromIndex];
	int numArmies = inputIndexLoop(source->getArmies());

	cout << "Which territory would you like to move armies to? (0 -" << (index - 1) << ")";

	int toIndex = inputIndexLoop(defendableTerritories->size());
	Territory* target = (*defendableTerritories)[toIndex];

	return new AirliftOrder(player, numArmies, source, target);
}

BlockadeOrder* HumanPlayerStrategy::useBlockade(Player* player)
{
	auto defendable = *toDefend(player);
	int index = 0;
	for (auto it = defendable.begin(); it != defendable.end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to blockade? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendable.size());
	return new BlockadeOrder(player, defendable[territoryIndex]);
}

DeployOrder* HumanPlayerStrategy::useReinforcement(Player* player)
{
	auto defendable = *toDefend(player);
	int index = 0;
	for (auto it = defendable.begin(); it != defendable.end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}

	cout << "Which territory would you like to deploy to? (0 -" << (index - 1) << ")";

	int territoryIndex = inputIndexLoop(defendable.size());

	cout << "Which territory would you like to deploy to? (0-10)";
	int numArmies = inputIndexLoop(11);

	return new DeployOrder(player, numArmies, defendable[territoryIndex]);
}
