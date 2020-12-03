#include "StrategyDriver.h"

int StrategyDriver::main()
{

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
    Player* player1 = new Player("Human Player (You!)", player1Territories, new OrdersList(), deck);

    vector<Territory*>* player2Territories = new vector<Territory*>();
    player2Territories->push_back(map->getTerritory(3));
    player2Territories->push_back(map->getTerritory(4));
    Player* player2 = new Player("Benevolent Player", player2Territories, new OrdersList(), deck);

    vector<Territory*>* player3Territories = new vector<Territory*>();
    player3Territories->push_back(map->getTerritory(5));
    player3Territories->push_back(map->getTerritory(6));
    Player* player3 = new Player("Agressive Player", player3Territories, new OrdersList(), deck);

    cout << "giving player 1 one of each card" << endl;
    player1->getHand()->addCard(new AirliftCard());
    player1->getHand()->addCard(new BombCard());
    player1->getHand()->addCard(new BlockadeCard());
    player1->getHand()->addCard(new ReinforcementCard());
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

    cout << "Player 1 will use human player strategy" << endl;
    player1->setStrategy(new HumanPlayerStrategy());
    
    cout << "Player 2 will use benevolent strategy" << endl;
    player2->setStrategy(new BenevolentComputerStrategy());

    cout << "Player 3 will use aggressive strategy" << endl;
    player3->setStrategy(new AggressiveComputerStrategy());

    cout << "Do one game loop with observers on" << endl;

    GameEngine gameEngine(map, *players);
	
    gameEngine.attachObservers();
    gameEngine.reinforcementPhase();
    gameEngine.issueOrdersPhase();
    gameEngine.executeOrdersPhase();
	
    cout << "Changing human player startegy to neutral player strategy and continue the game" << endl;
    player1->setStrategy(new NeutralPlayerStrategy());

    gameEngine.mainGameLoop();
    return 0;
}