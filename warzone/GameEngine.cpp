#include "GameEngine.h"

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
    return 0;
}

int GameEngine::executeOrdersPhase()
{
    return 0;
}
