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
    Player* player1 = new Player("Cleopatra", player1Territories, new OrdersList(), deck);

    vector<Territory*>* player2Territories = new vector<Territory*>();
    player2Territories->push_back(map->getTerritory(3));
    player2Territories->push_back(map->getTerritory(4));
    player2Territories->push_back(map->getTerritory(6));
    Player* player2 = new Player("Rameses II", player2Territories, new OrdersList(), deck);

    vector<Territory*>* player3Territories = new vector<Territory*>();
    player3Territories->push_back(map->getTerritory(5));
    Player* player3 = new Player("Casimir", player3Territories, new OrdersList(), deck);

    cout << "giving player 1 a BombCard and a DiplomacyCard" << endl;
    player1->getHand()->addCard(new BombCard());
    player1->getHand()->addCard(new DiplomacyCard());
    
    cout << "giving player 2 a BlockadeCard and a AirliftCard" << endl;
    player2->getHand()->addCard(new BlockadeCard());
    player2->getHand()->addCard(new AirliftCard());
    
    cout << "giving player 3 a ReinforcementCard and a BombCard" << endl;
    player3->getHand()->addCard(new ReinforcementCard());
    player3->getHand()->addCard(new BombCard());

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
    cout << "Creating a player with 17 territories" << endl;

    // Create a map with a lot of territories and assign them to one player
    Map* map = new Map();
    Continent* continent = new Continent("BigContinent", "Blue", 5);
    vector<Territory*>* playerTerritories = new vector<Territory*>();

    for (int i = 0; i < 17; i++) {
        Territory* territory = new Territory("" + i, continent, 0, 0);
        map->addTerritory(territory);
        playerTerritories->push_back(territory);
    }
    Deck* deck = new Deck();
    Player* onlyPlayer = new Player("TheOnlyPlayer", playerTerritories, new OrdersList(), deck);

    // Create a gameengine and run the reinforcement phase
    GameEngine engine(map, { onlyPlayer });
    engine.reinforcementPhase();

    cout << "Player with 17 territories should get 5 reinforcements, has: " << onlyPlayer->getReinforcements() << endl;
}

void GameLoopDriver::issueOrdersPhase(GameEngine* gameEngine)
{
    cout << "=== GameLoopDriver Issue Orders Phase ===" << endl;
    gameEngine->issueOrdersPhase();

    cout << "Player 1 Orders List: " << endl;
    cout << gameEngine->getPlayers()->at(0)->getOrdersList()->print() << endl;
    
    cout << "Player 2 Orders List: " << endl;
    cout << gameEngine->getPlayers()->at(1)->getOrdersList()->print() << endl;

    cout << "Player 3 Orders List: " << endl;
    cout << gameEngine->getPlayers()->at(2)->getOrdersList()->print() << endl;

    // This should show that
    // - Player can only issue DeployOrders if they still have armies in their reinforcement pool
    // - Can issue AdvanceOrders, will have to demonstrate with better printing that they can both defend and attack, but both are being generated here
    // - That the player can issue orders with cards
    
}

void GameLoopDriver::executeOrdersPhase(GameEngine* gameEngine)
{
    cout << "=== GameLoopDriver Execute Orders Phase ===" << endl;
    gameEngine->attachObservers();
    gameEngine->executeOrdersPhase();

    cout << "Order priority is Deploy > Airlift > Blockade > Others " << endl;
    // The output should show the orders executed in order of priority
    // Let's finish off by printing the map
    cout << *gameEngine->getMap() << endl;

    cout << "=== GameLoopDriver Show that players are eliminated and a winner will appear" << endl;
    cout << "We will create a game with 2 territories and 2 players, and give a ton of extra units to player 1 to end the game quickly" << endl;

    Map* map = new Map();
    Deck* deck = new Deck();
    deck->add(new BombCard());
    Continent* continent = new Continent("Test continent", "blue", 10);
    map->addContinent(continent);
    Territory* territory1 = new Territory("territory1", continent, 0, 0);
    Territory* territory2 = new Territory("territory2", continent, 0, 0);
    vector<Territory*> territory1Borders = { territory2 };
    vector<Territory*> territory2Borders = { territory1 };
    territory1->addBorders(&territory1Borders);
    territory2->addBorders(&territory2Borders);
    map->addTerritory(territory1);
    map->addTerritory(territory2);
    vector<Territory*>* player1Territories = new vector<Territory*>();
    vector<Territory*>* player2Territories = new vector<Territory*>();
    player1Territories->push_back(territory1);
    player2Territories->push_back(territory2);

    Player* player1 = new Player("DuelPlayer1", player1Territories, new OrdersList(), deck);
    Player* player2 = new Player("DuelPlayer2", player2Territories, new OrdersList(), deck);

    GameEngine* almostDoneGameEngine = new GameEngine(map, { player1, player2 });

    cout << "Executing game loops until the game is over" << endl;
    almostDoneGameEngine->mainGameLoop();
    cout << "Game has ended" << endl;
    cout << "Number of players remaining: " << almostDoneGameEngine->getPlayers()->size();
}

