#include "GameEngine.h"

GameEngine::GameEngine()
{
	cout <<"What file would you like?"; 



	bool playerInputValid = false;   //Validating user input 
	while (playerInputValid == false) {
		cout << "How many players do you want?" << endl;
		cin >> numberOfPlayers;
		if (numberOfPlayers < 2 || numberOfPlayers>6)
			playerInputValid = false;
		else
			playerInputValid = true;
	}
	string playerAnswer;		// Asking player for observers
	cout << "Would you like to turn observers on or off? y/n" << endl;
	cin >> playerAnswer;
	if (playerAnswer.compare("y") == 0 || playerAnswer.compare("Y") == 0)
		observersOn == true;
	else
		observersOn == false;
}

GameEngine::~GameEngine()
{
}

void GameEngine::startupPhase()
{
}
