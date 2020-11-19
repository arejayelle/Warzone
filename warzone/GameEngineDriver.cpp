#include "GameEngineDriver.h"

int GameEngineDriver::main()
{
	GameEngine* Game = new GameEngine();
	Game->startUpPhase();
	cout << "Printing Game Deck"<<endl;
	cout << "---------------------------------------------" << endl;
	Deck* deck = Game->getDeck();
	cout << *deck << endl;

	for (int i = 0; i < Game->getPlayers()->size(); i++) {
		Player* playerToPrint = Game->getPlayers()->at(i);
		cout << "Here is the player's information. Player Name: ";
		cout << playerToPrint->getName() << endl;
		cout << "Here are the amount of reinforcements a player has:";
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
