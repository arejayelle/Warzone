#include "GameEngine.h"

GameEngine::GameEngine()
{
    this->map = nullptr;
    this->players = std::vector<Player*>();
    this->phaseObservable = new PhaseObservable();
    this->statsObservable = new StatsObservable();
}

GameEngine::GameEngine(Map* map, std::vector<Player*> players)
{
    this->map = map;
    this->players = players;
    this->phaseObservable = new PhaseObservable();
    this->statsObservable = new StatsObservable();
}

GameEngine::~GameEngine() {
    delete map;
    for (Player* player : players) {
        delete player;
    }
    delete phaseObservable;
    delete statsObservable;
}

int GameEngine::mainGameLoop()
{
   
    reinforcementPhase();
    return 0;
}
/**
 * Add armies to Player's reinforcement Pool dependant of the number of territories they own
 * and the continent bonus for continents they own.
 * if less than 3, gives 3
 */
void GameEngine::reinforcementPhase()
{
    PhaseObserver* phaseObserver = new PhaseObserver();
    StatsObserver* gameStatisticsObserver = new StatsObserver();
    phaseObservable->attach(phaseObserver);
    statsObservable->attach(gameStatisticsObserver);
    phaseObservable->notify("\n\n\n\n\n\n\n\n\n");
    
    for (Player* player : players)
    {
        int reinforcements = player->getTerritories()->size() / 3;
        if (reinforcements < 3) {
            reinforcements = 3;
        }
        player->addReinforcements(reinforcements);
      
        
    }

    for (std::vector<Continent*>::const_iterator it = map->getContinents()->begin(); it != map->getContinents()->end(); it++) {
        Player* owner = (**it).getContinentOwner();
        if (owner != nullptr) {
            owner->addReinforcements((**it).getValue());
        }
    }

    int counter = 1;
    for (Player* player : players){
        phaseObservable->notify("----------Player " + std::to_string(counter) + std::string(": Reinforcement phase----------\n"));
        phaseObservable->notify("Player " + std::to_string(counter) + " has " + std::to_string(player->getReinforcements()) + std::string(" reinforcements\n\n"));
        counter++;
    }
}

int GameEngine::issueOrdersPhase()
{
    phaseObservable->notify("\n\n\n\n\n\n\n\n\n");
    bool allPlayersPassed;
    do {
        allPlayersPassed = true;
        for (Player* player : players) {
            bool issuedOrder = player->issueOrder();
            if (issuedOrder) {
                allPlayersPassed = false;
            }
        }
    } while (!allPlayersPassed);

    int counter = 1;
    for (Player* player : players) {
        phaseObservable->notify("----------Player " + std::to_string(counter) + std::string(": Issue Order phase----------\n"));
        player->getOrdersList()->print();

        counter++;
    }

    return 0;
}

int GameEngine::executeOrdersPhase()
{
    phaseObservable->notify("\n\n\n\n\n\n\n\n\n=== Execute Orders Phase ===");
   
    // Get the highest priority order from each player in round-robin fashion
    int currentPriority = 3;

    while (currentPriority >= 0) {
        bool currentPriorityOrdersRemain = false;
        int counter = 1;
        for (auto it = players.begin(); it != players.end(); it++) {
            Player* player = *it;
            if (player->getOrdersList()->size() == 0) {
                continue;
            }
            Order* top = player->getOrdersList()->peek();
            
            if (top->getPriority() == currentPriority) {
                Order* popped = player->getOrdersList()->pop();
                _ASSERT(popped != nullptr);
                top->execute();
                currentPriorityOrdersRemain = true;
                phaseObservable->notify("----------Player " + std::to_string(counter) + std::string(": has Issued") + popped->toString());
            }
            counter++;
        }

        if (!currentPriorityOrdersRemain) {
            currentPriority -= 1;
        }
    }

    return 0;
}

const std::vector<Player*>* GameEngine::getPlayers()
{
    return &players;
}
