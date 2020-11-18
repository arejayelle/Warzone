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
	//Shuffle Player Array and Territories

	random_shuffle(playerArray.begin(), playerArray.end());
	random_shuffle(map->getTerritories()->begin(), map->getTerritories()->end());

	//Assign Players Their Territories 
	int territoryIterator = 0;
	while (territoryIterator != map->getTerritories()->size()) {
		playerArray[territoryIterator % playerArray.size()]->grantTerritory(map->getTerritories()->at(territoryIterator));
		territoryIterator++;
	}

}

