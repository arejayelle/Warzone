#include "GameEngine.h"


GameEngine::GameEngine() {
	map = nullptr;
	playerArray = std::vector<Player*>();
	gameDeck = new Deck();
}

GameEngine::~GameEngine() {    
	delete map;
	for (auto i : playerArray)
		delete i;
	delete gameDeck;
}

void GameEngine::startUpPhase() {

	// Local Methods for Loop
	bool playerInputValid = false;  //Validating user input 
	string playerAnswer;		   // Asking player for observers
	int numberOfPlayers;
	bool fileInvalid = true;
	string mapFileName;
	bool observersOn= true;

	MapLoader* loader = nullptr;
	//Map Loading 
	while (fileInvalid == true) {
		cout << "What map file would you like?";
		cin >> mapFileName;
		loader = new MapLoader(mapFileName);
		if (loader->validateMapFormat() == true)
			fileInvalid = false;
		else {
			fileInvalid = true;
			delete loader;
		}
	}
	map = loader->convertFileToMap();
	delete loader;

	//Setting up Observers
	cout << "Would you like to turn observers on or off? y/n" << endl;
	cin >> playerAnswer;
	if (playerAnswer.compare("y") == 0 || playerAnswer.compare("Y") == 0)
		observersOn = true;
	else
		observersOn = false;

	//PlayerNumberSetup
	while (playerInputValid == false) { //Getting number of players
		cout << "How many players do you want?" << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers>6)
			playerInputValid = false;
		else
			playerInputValid = true;
	}

	//Populate Deck 
	for (int i = 0; i < 4; i++)
	{
		SpyCard* spy = new SpyCard();
		gameDeck->add(spy);
		ReinforcementCard* reinforce = new ReinforcementCard();
		gameDeck->add(reinforce);
		AirliftCard* airlift = new AirliftCard();
		gameDeck->add(airlift);
		BlockadeCard* blockade = new BlockadeCard();
		gameDeck->add(blockade);
		BombCard* bomb = new BombCard();
		gameDeck->add(bomb);
	}

	//Create players with reinforcements
	for (int i = 0; i <= numberOfPlayers; i++)
	{
		vector<Territory*>* territories = new vector<Territory*>(); 
		OrdersList* orders = new OrdersList();
		Player* player = new Player(territories, orders, gameDeck);
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
	//Shuffle Player Array 
	random_shuffle(playerArray.begin(), playerArray.end());

	//Assign Players Their Territories 
	int territoryIterator = 0;
	while (territoryIterator != map->getTerritories()->size()) {
		playerArray[territoryIterator % playerArray.size()]->grantTerritory(map->getTerritories()->at(territoryIterator));
		territoryIterator++;
	}

}

