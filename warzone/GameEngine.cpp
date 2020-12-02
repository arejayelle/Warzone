#include "GameEngine.h"
#include "Orders.h"
   
GameEngine::GameEngine() {
	map = nullptr;
	playerArray = std::vector<Player*>();
	gameDeck = new Deck();
	this->phaseObservable = new PhaseObservable();
	this->statsObservable = new StatsObservable();
}

GameEngine::~GameEngine() {    
	delete map;
	for (Player* player : playerArray)
		delete player;
	delete gameDeck;
	delete phaseObservable;
	delete statsObservable;
}
GameEngine::GameEngine(Map* map, std::vector<Player*> players)
{
	this->map = map;
	this->playerArray = players;
	this->phaseObservable = new PhaseObservable();
    this->statsObservable = new StatsObservable();
}
GameEngine* GameEngine::operator=(const GameEngine& engine) //assignment operator
{
	return new GameEngine(engine);
}

GameEngine::GameEngine(const GameEngine& Engine) //Copy constructor
{
	this->map = Engine.map;
	this->gameDeck = Engine.gameDeck;
	for (Player* p : Engine.playerArray)
	{
		Player* player = new Player(*p);
		this->playerArray.push_back(player); 
	}
}

ostream& operator<<(ostream& output, const GameEngine& engine)  //stream overloading
{
	output << "Game Engine Information:" << endl;
	output << "Deck: " << *engine.gameDeck << endl;
	output << "Territories: " << engine.map->getTerritories() << endl;
	for (int i = 0; i < engine.playerArray.size(); i++) {
		output << "Player: " << engine.playerArray.at(i)->getTerritories();
		output << "Player: " << engine.playerArray.at(i)->getHand();
		output << "Player: " << engine.playerArray.at(i)->getOrdersList();
}
	return output;

}

void GameEngine::startUpPhase() {

	// Local Methods for Loop
	bool playerInputValid = false;  //Validating user input 
	string playerAnswer;		   // Asking player for observers
	int numberOfPlayers;
	bool fileInvalid = true;
	string mapFileName;

	MapLoader* loader = nullptr;
	ConquestFileReader* conqLoader = nullptr;
	ConquestFileReaderAdapter* adapter = nullptr;

	//Map Loading 
	while (fileInvalid == true) {
		cout << "What map file would you like?";
		cin >> mapFileName;
		loader = new MapLoader(mapFileName);
		conqLoader = new ConquestFileReader(mapFileName);
		adapter = new ConquestFileReaderAdapter(conqLoader);

		if (loader->validateMapFormatML()) {
			fileInvalid = false;
			map = loader->convertFileToMap();

			delete loader;
			delete conqLoader;
			delete adapter;
		}
		else if(adapter->validateMapFormatML()) {
			fileInvalid = false;
			map = adapter->convertFileToMap();

			delete loader;
			delete conqLoader;
			delete adapter;
		}
		else {
			cout << "\n File could not be converted as Domination or Conquest, please try another file." << endl;
			fileInvalid = true;

			delete loader;
			delete conqLoader;
			delete adapter;
		}
	}

	//Setting up Observers
	cout << "Would you like to turn observers on? y/n" << endl;
	cin >> playerAnswer;
	if (playerAnswer.compare("y") == 0 || playerAnswer.compare("Y") == 0 || playerAnswer.compare("yes") ==0 ||playerAnswer.compare("Yes")==0) 
		attachObservers();


	//PlayerNumberSetup
	while (playerInputValid == false) { //Getting number of players
		cout << "How many players do you want? Please choose a number between 2 - 5 inclusive" << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers>6)
		{
			playerInputValid = false;
			cout << "Input invalid. Please choose a number between 2 - 5 inclusive";

		}
		else
			playerInputValid = true;
	}

	//Populate Deck 
	for (int i = 0; i < 4; i++)
	{
		ReinforcementCard* reinforce = new ReinforcementCard();
		gameDeck->add(reinforce);
		AirliftCard* airlift = new AirliftCard();
		gameDeck->add(airlift);
		BlockadeCard* blockade = new BlockadeCard();
		gameDeck->add(blockade);
		BombCard* bomb = new BombCard();
		gameDeck->add(bomb);
	}
	gameDeck->add(new DiplomacyCard());

	//Create players with reinforcements
	for (int i = 0; i < numberOfPlayers; i++)
	{
		vector<Territory*>* territories = new vector<Territory*>(); 
		OrdersList* orders = new OrdersList();
		ostringstream name;
		name << "Player" << i;
		Player* player = new Player(name.str(), territories, orders, gameDeck);
		if (numberOfPlayers == 2)
			player->addReinforcements(40);
		else if (numberOfPlayers == 3)
			player->addReinforcements(35);
		else if (numberOfPlayers == 4)
			player->addReinforcements(30);
		else if (numberOfPlayers == 5)
			player->addReinforcements(25);
		playerArray.push_back(player);
	}

	//Shuffle Player Array and Territories
	random_shuffle(playerArray.begin(), playerArray.end());

	std::vector<int>territoryIndexes;
	for (int i = 0; i < map->getTerritories()->size(); i++)
		territoryIndexes.push_back(i);
	random_shuffle(territoryIndexes.begin(), territoryIndexes.end());

	//Assign Players Their Territories 
	int territoryIterator = 0;
	while (territoryIterator != map->getTerritories()->size()) {
		playerArray[territoryIterator % playerArray.size()]->grantTerritory(map->getTerritories()->at(territoryIndexes.at(territoryIterator)));
		territoryIterator++;
	}

}

int GameEngine::mainGameLoop()
{
	while (playerArray.size() > 1) {
		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();
	}

	phaseObservable->notify("\n\n\n\n\n " + playerArray.at(0)->getName() + std::string(" is the WINNER!!!!!!\n"));

	return 0;
}
/**
 * Add armies to Player's reinforcement Pool dependant of the number of territories they own
 * and the continent bonus for continents they own.
 * if less than 3, gives 3
 */
void GameEngine::reinforcementPhase()
{
    
	phaseObservable->notify("\n\n\n\n\n\n\n\n\n==================== Reinforcement Phase ====================\n\n");
    
    for (Player* player : playerArray)
    {
        int reinforcements = player->getTerritories()->size() / 3;
        if (reinforcements < 3) {
            reinforcements = 3;
        }
        player->addReinforcements(reinforcements);
		player->setConqueredTerritoryThisTurn(false);
    }

    for (std::vector<Continent*>::const_iterator it = map->getContinents()->begin(); it != map->getContinents()->end(); it++) {
        Player* owner = (**it).getContinentOwner();
        if (owner != nullptr) {
            owner->addReinforcements((**it).getValue());
        }
    }

    for (Player* player : playerArray){
        phaseObservable->notify("----------" + player->getName() + std::string(": Reinforcement phase----------\n"));
        phaseObservable->notify(player->getName() + " has " + std::to_string(player->getReinforcements()) + std::string(" reinforcements\n\n"));
    }
	
	for (auto territory : (*map->getTerritories())) {
		territory->setIncomingArmies(0);
	}
}

int GameEngine::issueOrdersPhase()
{
	phaseObservable->notify("\n\n\n\n\n\n\n\n\n==================== Issue Orders Phase ====================\n\n");
    bool allPlayersPassed;
    do {
        allPlayersPassed = true;
        for (Player* player : playerArray) {
            bool issuedOrder = player->issueOrder();
            if (issuedOrder) {
                allPlayersPassed = false;
            }
        }
    } while (!allPlayersPassed);

    for (Player* player : playerArray) {
        phaseObservable->notify("----------" + player->getName()  + std::string(": Issue Order phase----------\n"));
		phaseObservable->notify(player->getOrdersList()->print());
    }

    return 0;
}

int GameEngine::executeOrdersPhase()
{
	// Get the highest priority order from each player in round-robin fashion
	int currentPriority = 3;
	phaseObservable->notify("\n\n\n\n\n\n\n\n\n==================== Execute Orders Phase ====================\n\n");

	while (currentPriority >= 0) {
		bool currentPriorityOrdersRemain = false;
		int counter = 1;
		for (auto it = playerArray.begin(); it != playerArray.end(); it++) {
			Player* player = *it;
			if (player->getOrdersList()->size() == 0) {
				continue;
			}
			Order* top = player->getOrdersList()->peek();

			if (top->getPriority() == currentPriority) {
				Order* popped = player->getOrdersList()->pop();
				_ASSERT(popped != nullptr);
				top->execute();
				currentPriorityOrdersRemain = true;
				phaseObservable->notify(player->getName() + std::string(" has Issued ") + popped->toString() + "\n");
			}
			counter++;
		}

		if (!currentPriorityOrdersRemain) {
			currentPriority -= 1;
		}
	}

	std::vector<Player*> removeList;
	for (auto it = playerArray.begin(); it != playerArray.end(); it++)
	{
		(*it)->clearInNegotiationWith();
		if ((*it)->getTerritories()->size() == 0) {
			removeList.push_back((*it));
			statsObservable->notify((*it)->getName() + std::string(": has been eliminated.\n"));
		}
		else {
			float percentageOwned = ((*it)->getTerritories()->size() * 100.0f) / (map->getTerritories()->size() );
			statsObservable->notify((*it)->getName() + std::string(": has ") + std::to_string(percentageOwned) + "% of all territories\n");
		}
	}

	for (auto it = removeList.begin(); it != removeList.end(); it++)
	{
		auto removed = std::find(playerArray.begin(), playerArray.end(), (*it));
		if (removed != playerArray.end()) {
			playerArray.erase(removed);
		}
	}


	return 0;
}

void GameEngine::attachObservers()
{
	PhaseObserver* phaseObserver = new PhaseObserver();
	StatsObserver* gameStatisticsObserver = new StatsObserver();
	phaseObservable->attach(phaseObserver);
	statsObservable->attach(gameStatisticsObserver);
	AdvanceOrder::statsObservable->attach(gameStatisticsObserver);
}

const std::vector<Player*>* GameEngine::getPlayers()
{
    return &playerArray;
}

Deck* GameEngine::getDeck()
{
	return gameDeck;
}


Map* GameEngine::getMap()
{
    return map;
}
