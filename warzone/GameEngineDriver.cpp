#include "GameEngineDriver.h"

int GameEngineDriver::main()
{
	GameEngine* Game = new GameEngine();
	Game->startUpPhase();
	cout << "Printing Game Deck"<<endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < Game->getDeck()->size();i++) {
		Card* cardToPrint=Game->getDeck()->at(i);
		cout << *cardToPrint<<endl;
	
	}
	for (int i = 0; i < Game->getPlayers()->size(); i++) {
		Player* playerToPrint = Game->getPlayers()->at(i);
		cout << *playerToPrint << endl;
		cout << playerToPrint->getReinforcements() << endl;
		for (int i = 0; i < playerToPrint->getTerritories()->size(); i++)
		{
			Territory* territoryToPrint=playerToPrint->getTerritories()->at(i);
			cout << territoryToPrint->getName()<<endl;
		}			
		cout << "Done with this player." << endl;
		cout << "--------------------------------------------------------------------------------"<<endl;
	}
	Game->~GameEngine();
	return 0;

}
