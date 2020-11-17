#include "GameEngine.h"

GameEngine::GameEngine()
{
    this->map = nullptr;
    this->players = std::vector<Player*>();
}

GameEngine::GameEngine(Map* map, std::vector<Player*> players)
{
    this->map = map;
    this->players = players;
}

GameEngine::~GameEngine() {
    delete map;
    for (Player* player : players) {
        delete player;
    }
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
}

int GameEngine::issueOrdersPhase()
{
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

    return 0;
}

int GameEngine::executeOrdersPhase()
{
    // Get the highest priority order from each player in round-robin fashion

    // Deploy -> Airlift -> Blockage -> All the others
    return 0;
}

const std::vector<Player*>* GameEngine::getPlayers()
{
    return &players;
}
