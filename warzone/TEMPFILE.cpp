#include "Strategies.h";

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
	// TODO: insert return statement here
}

const vector<Territory*>* HumanPlayerStrategy::toDefend(Player* player)
{
	return player->getTerritories();
}

const vector<Territory*> HumanPlayerStrategy::toAttack(Player* player)
{
	return *player->getTerritories();
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
	while (!(std::cin >> playCards) || playCards != 'y' || playCards != 'n') {
		cout << "Error: enter a valid value";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

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
	while (!(std::cin >> advanceArmies) || advanceArmies != 'y' || advanceArmies != 'n') {
		cout << "Error: enter a valid value";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
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

	int territoryIndex;
	while (!(std::cin >> territoryIndex) || territoryIndex < 0 || territoryIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	Territory* deployTarget = (*defendableTerritories)[territoryIndex];
	int numArmies;
	while (!(std::cin >> numArmies) || numArmies < 0 || numArmies >= reinforcementPool) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
	player->getOrdersList()->add(new DeployOrder(player, numArmies, deployTarget));
	deployTarget->setIncomingArmies(deployTarget->getIncomingArmies() + numArmies);

	return true;
}

bool HumanPlayerStrategy::issueCardOrders(Player* player) {
	auto hand = player->getHand();
	int size = hand->getNumberOfCardsInHand();
	if (size > 0) {
		cout << hand << endl;
		int cardIndex;
		cout << "Enter the index of the card you want to play";
		while (!(std::cin >> cardIndex) || cardIndex < 0 || cardIndex >= size) {
			cout << "Error: enter a valid number";
			std::cin.clear();
			std::cin.ignore(123, '\n');
		}
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

	int fromIndex;
	while (!(std::cin >> fromIndex) || fromIndex < 0 || fromIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	Territory* source = (*defendableTerritories)[fromIndex];
	int totalArmies = source->getArmies() + source->getIncomingArmies();
	int numArmies;
	cout << "How many armies? " << source->getName() << " has " << totalArmies << " armies" << endl;
	while (!(std::cin >> numArmies) || numArmies < 0 || numArmies >= totalArmies) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	cout << "Adjacent Territories to " << source->getName();

	auto borders = source->getBorders();
	for (auto it = borders->begin(); it != borders->end(); it++) {
		cout << index++ << "\t" << (*it) << endl;
	}
	cout << "Which territory would you like to move armies to? (0 -" << (borders->size() - 1) << ")";

	int toIndex;
	while (!(std::cin >> toIndex) || toIndex < 0 || toIndex >= borders->size()) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

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
	int territoryIndex;
	while (!(std::cin >> territoryIndex) || territoryIndex < 0 || territoryIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
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

	int territoryIndex;
	while (!(std::cin >> territoryIndex) || territoryIndex < 0 || territoryIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
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

	int fromIndex;
	while (!(std::cin >> fromIndex) || fromIndex < 0 || fromIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	Territory* source = (*defendableTerritories)[fromIndex];
	int numArmies;

	while (!(std::cin >> numArmies) || numArmies < 0 || numArmies >= source->getArmies()) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	cout << "Which territory would you like to move armies to? (0 -" << (index - 1) << ")";

	int toIndex;
	while (!(std::cin >> toIndex) || toIndex < 0 || toIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
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

	int territoryIndex;
	while (!(std::cin >> territoryIndex) || territoryIndex < 0 || territoryIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}
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

	int territoryIndex;
	while (!(std::cin >> territoryIndex) || territoryIndex < 0 || territoryIndex >= index) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	int numArmies;
	cout << "Which territory would you like to deploy to? (0-10)";

	while (!(std::cin >> numArmies) || numArmies < 0 || numArmies > 11) {
		cout << "Error: enter a valid number";
		std::cin.clear();
		std::cin.ignore(123, '\n');
	}

	return new DeployOrder(player, numArmies, defendable[territoryIndex]);
}
