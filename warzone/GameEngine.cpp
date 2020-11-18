#include "GameEngine.h"


GameEngine::GameEngine() { //FINISH THIS PART
	map = nullptr;
	playerArray = std::vector<Player*>();
	loader = nullptr;
}

GameEngine::~GameEngine() {    //FINISH THIS PART
	delete map;
	delete loader;
}

void GameEngine::startUpPhase() {

	// Local Methods for Loop
	bool playerInputValid = false;  //Validating user input 
	string playerAnswer;		   // Asking player for observers
	int numberOfPlayers;
	bool fileInvalid = true;
	string mapFileName;
	bool observersOn= true;

	//Map Loading 
	while (fileInvalid == true) {
		cout << "What map file would you like?";
		cin >> mapFileName;
		*loader = MapLoader(mapFileName);
		if (loader->validateMapFormat() == true)
			fileInvalid = false;
		else
			fileInvalid - true;
	}
	*map = loader->convertFileToMap();

	//Setting up Observers
	cout << "Would you like to turn observers on or off? y/n" << endl;
	cin >> playerAnswer;
	if (playerAnswer.compare("y") == 0 || playerAnswer.compare("Y") == 0)
		observersOn == true;
	else
		observersOn == false;

	//PlayerNumberSetup
	while (playerInputValid == false) { //Getting number of players
		cout << "How many players do you want?" << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers>6)
			playerInputValid = false;
		else
			playerInputValid = true;
	}
	for (int i = 0; i <= numberOfPlayers; i++)
	{
		vector<Territory*>* territories = nullptr;
		OrdersList* orders = nullptr;
		Deck* gameDeck = nullptr;
		Player* player = new Player(territories, orders, gameDeck);
		playerArray.push_back(player);
	}



}

