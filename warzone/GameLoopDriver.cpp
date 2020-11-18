#include "GameLoopDriver.h"

int GameLoopDriver::main()
{
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
    Player* player1 = new Player(player1Territories, new OrdersList(), deck);

    vector<Territory*>* player2Territories = new vector<Territory*>();
    player2Territories->push_back(map->getTerritory(3));
    player2Territories->push_back(map->getTerritory(4));
    player2Territories->push_back(map->getTerritory(6));
    Player* player2 = new Player(player2Territories, new OrdersList(), deck);

    vector<Territory*>* player3Territories = new vector<Territory*>();
    player3Territories->push_back(map->getTerritory(5));
    Player* player3 = new Player(player3Territories, new OrdersList(), deck);

    vector<Player*>* players = new vector<Player*>();
    players->push_back(player1);
    players->push_back(player2);
    players->push_back(player3);


    GameEngine* gameEngine = new GameEngine(map, *players);

    GameLoopDriver::reinforcements(gameEngine);
    GameLoopDriver::issueOrdersPhase(gameEngine);
    GameLoopDriver::executeOrdersPhase(gameEngine);
    return 0;
}

void GameLoopDriver::reinforcements(GameEngine* gameEngine)
{
    cout << "=== GameLoopDriver Reinforcement Phase ===" << endl;

    gameEngine->reinforcementPhase();
    
    // minimum 3 reinforcements
    cout << "Player 3 owns one country and part of a continent, should have 3 reinforcements; has " << gameEngine->getPlayers()->at(2)->getReinforcements() << endl;

    // continent owned by a player
    cout << "Player 1 owns a continent worth 5 troops, should have 8 troops total; has " << gameEngine->getPlayers()->at(0)->getReinforcements() << endl;

    // continent partially owned by 2 players (no bonus)
    cout << "Player 2 owns a continent worth 6 troops and owns only part of a continent, should have 9 troops total; has " << gameEngine->getPlayers()->at(1)->getReinforcements() << endl;

    // check rounding is done properly (owned territories / 3 rounded down)
    cout << "TODO validate rounding is done properly by giving a player 12 or more territories" << endl;

}

void GameLoopDriver::issueOrdersPhase(GameEngine* gameEngine)
{
    cout << "=== GameLoopDriver Issue Orders Phase ===" << endl;
    gameEngine->issueOrdersPhase();

    cout << "Player 1 Orders List: " << endl;
    gameEngine->getPlayers()->at(0)->getOrdersList()->print();
    
    cout << "Player 2 Orders List: " << endl;
    gameEngine->getPlayers()->at(1)->getOrdersList()->print();

    cout << "Player 3 Orders List: " << endl;
    gameEngine->getPlayers()->at(2)->getOrdersList()->print();

    // This should show that
    // - Player can only issue DeployOrders if they still have armies in their reinforcement pool
    // - Can issue AdvanceOrders, will have to demonstrate with better printing that they can both defend and attack, but both are being generated here
    
    // Does not demonstrate
    // That the player can issue orders with cards
    
}

void GameLoopDriver::executeOrdersPhase(GameEngine* gameEngine)
{
    cout << "=== GameLoopDriver Execute Orders Phase ===" << endl;
    gameEngine->executeOrdersPhase();

    // The output should show the orders executed in order of priority
    // Let's finish off by printing the map
    cout << *gameEngine->getMap() << endl;
}

