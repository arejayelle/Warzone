#include "GameObserversDriver.h"
#include "GameObservers.h"
#include "GameEngine.h"
#include "MapDriver.h"
#include <vector>


int GameObserversDriver::main() {
    cout << "Creating sample map with 7 countries, 3 players" << endl;

    Map* map = MapDriver::getValidMap();

    Deck* deck = new Deck();
    for (int i = 0; i < 4; i++) {
        deck->add(new ReinforcementCard());
        deck->add(new BlockadeCard());
        deck->add(new DiplomacyCard());
        deck->add(new BombCard());
        deck->add(new AirliftCard());
    }

    vector<Territory*>* player1Territories = new vector<Territory*>();
    player1Territories->push_back(map->getTerritory(0));
    player1Territories->push_back(map->getTerritory(1));
    player1Territories->push_back(map->getTerritory(2));
    player1Territories->push_back(map->getTerritory(3));
    player1Territories->push_back(map->getTerritory(4));
    player1Territories->push_back(map->getTerritory(6));
    Player* player1 = new Player("Obama", player1Territories, new OrdersList(), deck);
    player1->getHand()->addCard(new BombCard());

    vector<Territory*>* player3Territories = new vector<Territory*>();
    player3Territories->push_back(map->getTerritory(5));
    Player* player3 = new Player("Poutine", player3Territories, new OrdersList(), deck);

    vector<Player*>* players = new vector<Player*>();
    players->push_back(player1);
    players->push_back(player3);


	GameEngine* Game = new GameEngine(map, *players);
	Game->attachObservers();
    Game->mainGameLoop();

	return 0;
}

